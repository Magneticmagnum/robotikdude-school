#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>
#include <iostream>
using namespace std;

#include <boost/random.hpp>
using namespace boost;

/**
 * TODO : comment, program comment
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
  controlFile.open("popquiz_conter.txt", ios::in);
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

  isQuiz = (probability < sampler());

  // Edit probabilities and write them back out to the file
  remainingLectures -= 1;
  if (isQuiz) {
    remainingQuestions -= 1;
  }
  controlFile.open("popquiz_conter.txt", ios::out | ios::trunc);
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
