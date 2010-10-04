CSci4041 F2010 Assignment 2
section: 3
login: norma272
date: 10/4/10
name: Brian E Norman
id: 4332223


    Compiling

To compile the .java files into .class files, navigate to the directory that
contains the .java files and Makefile and simply type make into the command
prompt.
Example
    $ make


    Syntax

To run the program, you will need to decide which sorting function you want to
use. Once that has been decided you will then need to decide how you want to
test that sorting function. There are a several ways to run each function. The
following is some sample calls:
    1.) java [sorting function] [file that contains list] [size of file list]
    [increasing or decreasing (0,1)]
    2.) java [sorting function] [file that contains list] [size of file list]
    3.) java [sorting function] [size of list you want to create]
    [increasing or decreasing (0,1)]
    4.) java [sorting function] [size of list you want to create]
Examples
If you want to sort 1 Magabyte size list that's stored in a file in decreasing
order:
    java hsort 1M.txt 1048576 1
If you want to test sorting 1000 random numbers in increasing order:
    java qsortrandom1 1000

If you are getting Java heap size errors, try adding the following options to
the java command:
    $ java -Xmx1024m -Xms512m [everything else]
These options will set the maximum heap size to 1024MB and the minimum heap
size to 512MB. Increase the heap size until you are no longer receiving this
error.


    Description

Each sorting program does essentially the same thing. They each take input,
sort that input, and then if requested write that sorted input to an output
file. How each program sorts their input is different, but that is the only
thing that varies between the 8 programs.