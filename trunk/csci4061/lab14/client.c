#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>

int main(int argc, char** argv)
{
  char buffer[1024];
  int n;

  //create socket
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  struct hostent* host;
  host = gethostbyname("cs1260-06.cselabs.umn.edu");

  //set up server address
  struct sockaddr_in server;
  bzero((char*) &server, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons((short) 5500);
  bcopy((char*) host->h_addr, (char*) &server.sin_addr.s_addr, host->h_length);

  //create connection and communicate
  connect(sock, (struct sockaddr*) &server, sizeof(server));
  write(sock, "Hello Server", 13);
  close(sock);
}
