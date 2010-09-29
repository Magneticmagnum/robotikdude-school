Brian Norman
ID: 4332223
Short Writing Assignment 1

	Program set-up

The first thing that you will need to do before running this program, is make
sure that you have the control and question files set-up correctly. To do so,
navigate to the directory that you will be compiling the program to using
either a terminal or file explorer. Then, create the first file
"popquize_control.txt". Edit it so that it contains two numbers on the same
line separated by a space. The first being the remaining number of pop quizzes
for the semester. The second being the remaining number of lectures for the
semester. You will also need a second file "popquiz_question.txt" which
contains the text for the pop quiz.

  Compiling

To compile this program, simply navigate to the directory that contains the
popquiz.cpp file and run the following command:
      $ g++ popquiz.cpp -o popquiz.o

  Running

To run this program, navigate to the directory that contains the popquiz.o file
and the control and question test files and run the following command:
      $ ./popquiz.o