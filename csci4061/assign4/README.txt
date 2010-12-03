/* csci4061 F2010 Assignment 4
 * section: one_digit_number
 * login: norma272
 * date: 11/26/10
 * names: Brian Norman, Chaichana Noree, Joshua Houltou
 * ID:    4332223     , 4295362        , 3688485
 */

About
==================
The purpose of this assignment is to construct a multithreaded web server using
POSIX threads (pthreads) in C to learn abuot thread programming and 
synchronization methods.  The web server handles any tope of files such as 
HTML, GIF, JPEG, TXT, etc.  It will also handle a limited portion of the
HTTP web protocol.  The server will be composed of three different types of 
threads; dispatcher, worker, and prefetcher.  The dispatcher thread repeadly
accepts an incoming connection, read in the request, and place the request
in queue for the worker thread.  The worker thread monitors the request queue, 
picks up requests form it and serves it to the client.  Worker threads puts 
these requests back to another prefetching queue which is read by the
prefetcher thread.  Prefetcher threads check if they can guess what the next
request is going to be and bring the guessed page from the disk to the cache.

 How to compile
 ====================
 
 Extract all the files to a separate folder and navigate to the folder.
 From there you may build and run the following makefile commands:
 
 make all - Builds everything (recommended)
 
 make web_server_http -
 
 make server.o -
