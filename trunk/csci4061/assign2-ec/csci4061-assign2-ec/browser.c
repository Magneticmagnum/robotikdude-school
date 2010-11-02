#include "wrapper.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/ipc.h>

extern int errno;
// This is used to hold the ID of the shared segment created by the ROUTER process
extern int shared_bookmarks;
comm_channel channel[UNRECLAIMED_TAB_COUNTER];

/*
 * Name:		uri_entered_cb
 * Input arguments:'entry'-address bar where the url was entered
 *			 'data'-auxiliary data sent along with the event
 * Output arguments:void
 * Function:	When the user hits the enter after entering the url
 *			in the address bar, 'activate' event is generated
 *			for the Widget Entry, for which 'uri_entered_cb'
 *			callback is called. Controller-tab captures this event
 *			and sends the browsing request to the router(/parent)
 *			process.
 */
void uri_entered_cb(GtkWidget* entry, gpointer data) {
  if (!data)
    return;
  browser_window* b_window = (browser_window*) data;
  comm_channel channel = b_window->channel;
  // Get the tab index where the URL is to be rendered
  int tab_index = query_tab_id_for_request(entry, data);
  if (tab_index <= 0) {
    //Append code for error handling
    printf("ERROR! please enter a tab index that exists.");
  } else {
    // Get the URL.
    char* uri = get_entered_uri(entry);

    // Prepare 'request' packet to send to router (/parent) process.
    // Append your code here
    child_req_to_parent new_req;
    new_req.type = NEW_URI_ENTERED;
    new_req.req.uri_req.render_in_tab = tab_index;
    strcpy(new_req.req.uri_req.uri, uri);
    write(channel.child_to_parent_fd[1], &new_req, sizeof(child_req_to_parent));
  }
}

/*
 * Name:		new_tab_created_cb
 * Input arguments:	'button' - whose click generated this callback
 *			'data' - auxillary data passed along for handling
 *			this event.
 * Output arguments:    void
 * Function:		This is the callback function for the 'create_new_tab'
 *			event which is generated when the user clicks the '+'
 *			button in the controller-tab. The controller-tab
 *			redirects the request to the parent (/router) process
 *			which then creates a new child process for creating
 *			and managing this new tab.
 */
void new_tab_created_cb(GtkButton *button, gpointer data)

{
  if (!data)
    return;
  int tab_index = ((browser_window*) data)->tab_index;
  comm_channel channel = ((browser_window*) data)->channel;

  // Create a new request of type CREATE_TAB

  child_req_to_parent new_req;
  //Append your code here
  new_req.type = CREATE_TAB;
  new_req.req.new_tab_req.tab_index = tab_index;
  write(channel.child_to_parent_fd[1], &new_req, sizeof(child_req_to_parent));
}

/*
 * Name:                bookmark_curr_page_cb
 * Input Arguments:     data - pointer to 'browser_window' data
 *                      which got initialized after call to 'create_window'
 * Output arguments:    void
 * Function:            The callback is called when the user-clicks the
 *                      bookmark menu in the URL-RENDERING window. The function
 *                      extracts the list of bookmarked web-pages from the
 *                      shared memory and appends the current webpage
 *                      into the list.
 */

void bookmark_curr_page_cb(void *data) {
  browser_window* b_window = (browser_window*) data;

  //get the current web-page to bookmark
  const char* curr_webpage = get_current_uri(b_window);

  //Append your code here
  // The following code is used to populate a new 'bookmarks' data structrue and
  // store it into the shared membery.  The count of bookmarked webpages is also incremented 
  bookmarks* bms = (bookmarks*) shmat(shared_bookmarks, NULL, 0);
  if (bms == (void*) -1) {
    printf("ERROR: Unable to attach to shared memory. ERRNO CODE: %i\n", errno);
  } else {
    if (bms[0].bookmarks_count < MAX_BOOKMARKS) {
      strcpy(bms[bms[0].bookmarks_count].uri, curr_webpage);
      bms[0].bookmarks_count++;
    }
    shmdt(bms);
  }
}

int main() {
  // Append your code here
  // **************************************************************************
  // BOOKMARK CODE
  // **************************************************************************
  int BOOKMARK_KEY = 100;
  // the shared-member segment is created for storing bookmarks
  shared_bookmarks = shmget(BOOKMARK_KEY, MAX_BOOKMARKS * sizeof(bookmarks), 0777 | IPC_CREAT);
  if (shared_bookmarks == -1) {
    perror("Unable to create shared memory. ERRNO CODE: %i\n", errno);
    exit(1);
  }
  bookmarks* bms = (bookmarks*) shmat(shared_bookmarks, NULL, 0);
  if (bms == (void*) -1) {
    perror("Unable to attach to shared memory. ERRNO CODE: %i\n", errno);
    exit(1);
  }
  bms[0].bookmarks_count = 0;
  shmdt(bms);
  // **************************************************************************
  // END BOOKMARK CODE
  // **************************************************************************

  pipe(channel[0].child_to_parent_fd);
  pipe(channel[0].parent_to_child_fd);
  int tab_index = 0;
  int open_tabs = 0;

  int pid = fork();
  if (pid == 0) {
    // ************************************************************************
    // CONTROLLER PROCESS
    // ************************************************************************
    close(channel[0].child_to_parent_fd[0]);
    close(channel[0].parent_to_child_fd[1]);

    browser_window* controller = NULL;
    create_browser(CONTROLLER_TAB, 0, (void(*)(void)) &new_tab_created_cb, (void(*)(void)) &uri_entered_cb,
        &controller, channel[0]);
    show_browser();
    exit(0);
    // ************************************************************************
    // END CONTROLLER PROCESS
    // ************************************************************************
  } else {
    // ************************************************************************
    // ROUTER PROCESS
    // ************************************************************************
    tab_index++;
    open_tabs++;
    close(channel[0].parent_to_child_fd[0]);
    close(channel[0].child_to_parent_fd[1]);

    int flags = fcntl(channel[0].child_to_parent_fd[0], F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(channel[0].child_to_parent_fd[0], F_SETFL, flags);

    while (open_tabs > 0) {
      int i;
      for (i = 0; i < tab_index; i++) {
        child_req_to_parent new_req;
        int nread = read(channel[i].child_to_parent_fd[0], &new_req, sizeof(child_req_to_parent));
        if (nread == -1 && errno == EAGAIN) {
          // printf("router got no messages...\n");
          usleep(10);
        } else if (nread > 0) {
          // printf("INFO: router got a message!\n");
          // CREATE TAB *******************************************************
          if (new_req.type == CREATE_TAB) {
            // printf("INFO: router creating tab...\n");
            pipe(channel[tab_index].parent_to_child_fd);
            pipe(channel[tab_index].child_to_parent_fd);

            int tab_pid = fork();
            if (tab_pid == 0) {
              // **************************************************************
              // TAB PROCESS
              // **************************************************************
              // printf("INFO: tab created.\n");
              comm_channel tab_comm = channel[tab_index];
              close(tab_comm.parent_to_child_fd[1]);
              close(tab_comm.child_to_parent_fd[0]);

              browser_window* tab = NULL;
              create_browser(URL_RENDERING_TAB, tab_index, (void(*)(void)) &new_tab_created_cb,
                  (void(*)(void)) &uri_entered_cb, &tab, tab_comm);

              int flags = fcntl(tab_comm.parent_to_child_fd[0], F_GETFL);
              flags |= O_NONBLOCK;
              fcntl(tab_comm.parent_to_child_fd[0], F_SETFL, flags);

              int kill_tab = 0;
              while (kill_tab == 0) {
                child_req_to_parent new_req_tab;
                int nread_tab = read(tab_comm.parent_to_child_fd[0], &new_req_tab, sizeof(child_req_to_parent));
                if (nread_tab == -1 && errno == EAGAIN) {
                  usleep(10);
                  // printf("tab %i got no messages...\n", tab_index);
                } else if (nread_tab > 0) {
                  // printf("tab %i got a message!\n", tab_index);
                  // NEW URI PASSED TO TAB ************************************
                  if (new_req_tab.type == NEW_URI_ENTERED) {
                    // printf("INFO: new uri requested.\n");
                    render_web_page_in_tab(new_req_tab.req.uri_req.uri, tab);
                  }
                  // TAB ASKED TO TERMINATE ***********************************
                  else if (new_req_tab.type == TAB_KILLED) {
                    // printf("INFO: closing tab...\n");
                    process_all_gtk_events();
                    close(channel[tab_index].parent_to_child_fd[0]);
                    close(channel[tab_index].child_to_parent_fd[1]);
                    kill_tab = 1;
                  } else if (new_req_tab.type == CREATE_TAB) {
                    // ignore
                  } else {
                    // error? no type specified
                    perror("No type is specified or not correctly specified, closing tab");
                    close(channel[tab_index].parent_to_child_fd[0]);
                    close(channel[tab_index].child_to_parent_fd[1]);
                    kill_tab = 1;
                  }
                } else {
                  // read didn't get any data.
                  perror("No data is read in");
                }
                process_single_gtk_event();
              }

              // printf("INFO: tab %i closed.\n", tab_index);
              exit(0);
              // **************************************************************
              // END TAB PROCESS
              // **************************************************************
            } else {
              close(channel[tab_index].parent_to_child_fd[0]);
              close(channel[tab_index].child_to_parent_fd[1]);

              int flags = fcntl(channel[tab_index].child_to_parent_fd[0], F_GETFL);
              flags |= O_NONBLOCK;
              fcntl(channel[tab_index].child_to_parent_fd[0], F_SETFL, flags);

              tab_index++;
              open_tabs++;
            }
          }
          // NEW URI ENTERED **************************************************
          else if (new_req.type == NEW_URI_ENTERED) {
            // printf("INFO: passing uri message to child...\n");
            write(channel[new_req.req.uri_req.render_in_tab].parent_to_child_fd[1], &new_req,
                sizeof(child_req_to_parent));
          }
          // TAB KILLED *******************************************************
          else if (new_req.type == TAB_KILLED) {
            // printf("INFO: router closing tab %i...\n", new_req.req.killed_req.tab_index);
            write(channel[new_req.req.killed_req.tab_index].parent_to_child_fd[1], &new_req,
                sizeof(child_req_to_parent));

            close(channel[new_req.req.killed_req.tab_index].parent_to_child_fd[1]);
            close(channel[new_req.req.killed_req.tab_index].child_to_parent_fd[0]);
            open_tabs--;
            // printf("INFO: tabs left: %i.\n", open_tabs);

            if (new_req.req.killed_req.tab_index == 0 && open_tabs > 0) {
              // close other browsers...?
              // printf("INFO: closing other tabs...\n");
              int i;
              for (i = 1; i < UNRECLAIMED_TAB_COUNTER; i++) {
                // printf("INFO: closing tab %i\n", i);
                child_req_to_parent new_req;
                new_req.type = TAB_KILLED;
                new_req.req.killed_req.tab_index = i;
                write(channel[i].parent_to_child_fd[1], &new_req, sizeof(child_req_to_parent));

                close(channel[i].parent_to_child_fd[1]);
                close(channel[i].child_to_parent_fd[0]);
              }
              open_tabs = 0;
            }
          } else {
            // error? no type specified
            perror("Type not specified or not specified correctly");
          }
        } else {
          // error? fd is closed
          // perror("File descriptor is closed");
          // not an error, if tab one is closed, it's file descriptors will still try and
          // be read as part of the loop.
        } // end else [if (nread == -1 && errno == EAGAIN)] [if (nread > 0)]

      } // for (i = 0; i < tab_index; i++)

    } // end while (open_tabs > 0)

  } // end else [if (pid == 0)]

  return 0;
  // ************************************************************************
  // ROUTER PROCESS
  // ************************************************************************
}

