/**
 * Brian Norman
 * ID: 4332223
 * Short Writing Assignment 1
 * popquiz.cpp
 */

#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>
#include <iostream>
using namespace std;

#include <boost/random.hpp>
using namespace boost;

/**
 * This program will calculate and then randomize whether there will be a pop
 * quiz during a specific lecture or not.
 *
 * Given a control file this program will calculate what the probability is of
 * having a pop quiz based off how many there are left in a semester and how
 * many lectures there are remaining. The control file must be in the working
 * directory and have the name "popquiz_control.txt". The program will then
 * create a random number and compare it with the probability and show whether
 * there is a pop quiz or not.
 *
 * If there is a pop quiz, the pop quiz question will be printed as well. The
 * pop quiz question needs to be in a file that is in the working directory and
 * named "popquiz_question.txt". If there is not a pop quiz, a question will
 * not be printed out.
 *
 * To use this program, simple type "./popquiz.o" without the quotations and
 * make sure that the two required files, "popquiz_control.txt" and
 * "popquiz_quesiton.txt" are in your working directory.
 * E.x.
 *     norma272$ ./popquiz.o
 *
 *
 */
int main()
{
  fstream controlFile;    // Control file for this program
  ifstream questionFile;  // File that contains the pop-quiz question
  int remainingQuestions; // Number of remaining pop-quizzes to give
  int remainingLectures;  // Number of remaining lectures
  double probability;     // Probability there will be a pop quiz
  bool isQuiz;            // If there is going to be a pop quiz

  // Reads in two values from popquiz_conter.txt
  controlFile.open("popquiz_control.txt", ios::in);
  controlFile >> remainingQuestions;
  controlFile >> remainingLectures;
  controlFile.close();

  // Calculate probability of pop quiz
  probability = static_cast<double> (remainingQuestions)
      / static_cast<double> (remainingLectures);

  // Set up random generator on range [0..1)
  // See http://www.boost.org/doc/libs/1_44_0/doc/html/boost_random.htmlf for
  // details
  static mt11213b engine(static_cast<unsigned> (time(0)));
  uniform_real<double> distribution(0, 1);
  variate_generator<mt11213b&, uniform_real<double> > sampler(engine,
                                                              distribution);

  isQuiz = (probability > sampler());

  // Edit probabilities and write them back out to the file
  remainingLectures -= 1;
  if (isQuiz) {
    remainingQuestions -= 1;
  }
  controlFile.open("popquiz_control.txt", ios::out | ios::trunc);
  controlFile << remainingQuestions << " " << remainingLectures << endl;
  controlFile.close();

  // If pop quiz, print out question
  if (isQuiz) {
    string line;

    questionFile.open("popquiz_question.txt", ios::in);

    cout << "Pop Quiz today!" << endl;
    cout << "--------------------------------------" << endl;
    while (!questionFile.eof()) {
      getline(questionFile, line);
      cout << line << endl;
    }
    cout << "--------------------------------------" << endl;

    questionFile.close();
  }
  else {
    cout << "Not today." << endl;
  }

  return 0;
}
