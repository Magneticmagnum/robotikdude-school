#include "wrapper.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

extern int errno;
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
    // Append code for error handling
    printf("ERROR! please enter a tab index that exists.");
  }

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
  // Append your code here
  new_req.type = CREATE_TAB;
  new_req.req.new_tab_req.tab_index = tab_index;
  write(channel.child_to_parent_fd[1], &new_req, sizeof(child_req_to_parent));
}

int main() {
  // Append your code here
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
          printf("router got a message!\n");
          // CREATE TAB *******************************************************
          if (new_req.type == CREATE_TAB) {
            printf("router creating tab...\n");
            pipe(channel[tab_index].parent_to_child_fd);
            pipe(channel[tab_index].child_to_parent_fd);

            int tab_pid = fork();
            if (tab_pid == 0) {
              // **************************************************************
              // TAB PROCESS
              // **************************************************************
              printf("tab created.\n");
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
                } else {
                  // printf("tab %i got a message!\n", tab_index);
                  // NEW URI PASSED TO TAB ************************************
                  if (new_req_tab.type == NEW_URI_ENTERED) {
                    printf("new uri requested.\n");
                    render_web_page_in_tab(new_req_tab.req.uri_req.uri, tab);
                  }
                  // TAB ASKED TO TERMINATE ***********************************
                  else if (new_req_tab.type == TAB_KILLED) {
                    printf("closing tab...\n");
                    process_all_gtk_events();
                    // close(channel[new_req.req.killed_req.tab_index].parent_to_child_fd[0]);
                    // close(channel[new_req.req.killed_req.tab_index].child_to_parent_fd[1]);
                    kill_tab = 1;
                  } else if (new_req_tab.type == CREATE_TAB) {
                    // error? ignore
                  } else {
                    // error? no type specified
                  }
                }
                process_single_gtk_event();
              }

              printf("tab %i closed.\n", tab_index);
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
            printf("passing uri message to child...\n");
            write(channel[new_req.req.uri_req.render_in_tab].parent_to_child_fd[1], &new_req,
                sizeof(child_req_to_parent));
          }
          // TAB KILLED *******************************************************
          else if (new_req.type == TAB_KILLED) {
            printf("router closing tab %i...\n", new_req.req.killed_req.tab_index);
            printf("tabs left: %i.\n", open_tabs - 1);
            write(channel[new_req.req.killed_req.tab_index].parent_to_child_fd[1], &new_req,
                sizeof(child_req_to_parent));

            close(channel[new_req.req.killed_req.tab_index].parent_to_child_fd[1]);
            close(channel[new_req.req.killed_req.tab_index].child_to_parent_fd[0]);
            open_tabs--;
          } else {
            // error? no type specified
          }
        } else {
          // else [if (nread == -1 && errno == EAGAIN)] [if (nread > 0)]
          // error? fd is closed
        }
      } // for (i = 0; i < tab_index; i++)
    } // end while (open_tabs > 0)
  } // end else [if (pid == 0)]

  return 0;
  // ************************************************************************
  // ROUTER PROCESS
  // ************************************************************************
}

