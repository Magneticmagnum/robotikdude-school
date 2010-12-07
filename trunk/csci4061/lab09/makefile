all:alarm shm_server shm_client message_send message_recv
	
shm_server: shm_server.c
	gcc -o shm_server shm_server.c
shm_client: shm_client.c
	gcc -o shm_client shm_client.c
message_send: message_send.c
	gcc -o message_send message_send.c
message_recv: message_recv.c
	gcc -o message_recv message_recv.c
alarm:alarm.c
	gcc -o alarm alarm.c
clean:
	rm -f alarm shm_server shm_client message_send message_recv
