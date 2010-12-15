CC = gcc
CFLAGS = -D_REENTRANT
LDFLAGS = -lpthread -lnsl

all: web_server_http

web_server_http: http-util.o
	${CC} ${CFLAGS} ${LDFLAGS} -o web_server_http server.c http-util.o

http-util.o: http-util.c
	${CC} ${CFLAGS} -c http-util.c

clean:
	rm -f http-util.o web_server_http