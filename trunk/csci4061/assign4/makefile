CC = gcc
CFLAGS = -D_REENTRANT
LDFLAGS = -lpthread -lnsl

all: web_server_http

web_server_http: server.c util-http.o
	${CC} ${CFLAGS} ${LDFLAGS} -o web_server_http server.c util-http.o

server.o: server.c
	${CC} ${CFLAGS} -c server.c

clean:
	rm -f server.o web_server_http
