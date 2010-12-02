CC = gcc
CFLAGS = -D_REENTRANT
LDFLAGS = -lpthread

all: web_server_http

web_server_http: server.c util-http.o
	${CC} ${CFLAGS} ${LDFLAGS} -o web_server_http server.c util-http.o

server.o: server.c

clean:
	rm server.o web_server_http
