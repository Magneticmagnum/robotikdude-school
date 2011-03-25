/**
 * CSci5512 Spring '11 Homework 2
 * login: norma272
 * date: 3/23/2011
 * name: Brian Norman
 * id: 4332223
 * algorithm: SmoothHMM
 */

Compiling:

To compile, navigate to the folder that contains the file SmoothHMM.java. Run
the command:
   javac SmoothHMM.java
This will compile the program SmoothHMM.

Running:

To run the program SmoothHMM, navigate to the folder that contains the file
SmoothHMM.class. Run the command:
   java SmoothHMM 10 0 1 0 1 0 1 0 1 0 1
This will run the program SmoothHMM with the evidence F, T, F, T, F, T, F, T,
F, T. The usage of this program is:
   java SmoothHMM <numEvidance> <sequence of evidence>
Another example:
   java SmoothHMM 10 0 0 0 1 1 1 1 0 0 0

Information:

This program computes and returns the smoothed estimates of the input evidence.