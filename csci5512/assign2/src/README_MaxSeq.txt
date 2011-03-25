/**
 * CSci5512 Spring '11 Homework 2
 * login: norma272
 * date: 3/23/2011
 * name: Brian Norman
 * id: 4332223
 * algorithm: MaxSeq
 */

Compiling:

To compile, navigate to the folder that contains the file MaxSeq.java. Run
the command:
   javac MaxSeq.java
This will compile the program MaxSeq.

Running:

To run the program MaxSeq, navigate to the folder that contains the file
MaxSeq.class. Run the command:
   java MaxSeq 10 0 1 0 1 0 1 0 1 0 1
This will run the program MaxSeq with the evidence F, T, F, T, F, T, F, T, F,
T. The usage of this program is:
   java GibbsRain <numEvidance> <sequence of evidence>
Another example:
   java GibbsRain 10 0 0 0 1 1 1 1 0 0 0

Information:

This program returns the most likely sequence of events given the input
evidence. 