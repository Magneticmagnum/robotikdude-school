#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

int main(int argc, char** argv)
{
  int socket_fd;
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htons(INADDR_ANY);
  server.sin_port = htons((short) 5500);

  bind(socket_fd, (struct sockaddr*) &server, sizeof(server));

  listen(socket_fd, 100);

  struct sockaddr_in client_addr;
  int size = sizeof(struct sockaddr);

  int new_socket = accept(socket_fd, (struct sockaddr*) &client_addr, &size);

  write(new_socket, "Hello Client", 13);
  close(new_socket);
}
