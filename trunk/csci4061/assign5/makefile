CC = gcc
CFLAGS = -D_REENTRANT
LDFLAGS = -lpthread -lnsl

all: web_server_http

web_server_http: server.o http-util.o
	${CC} ${CFLAGS} ${LDFLAGS} -o web_server_http server.o http-util.o

server.o: server.c
http-util.o: http-util.c
clean:
	rm server.o web_server_http http-util.o
