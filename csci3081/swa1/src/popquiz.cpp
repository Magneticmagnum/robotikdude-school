// Pop Quiz machine
// Your job is to document it and change names to make it clearly understandable.

#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>
#include <iostream>
using namespace std;

#include <boost/random.hpp>
using namespace boost;

/**
 * Explain in some detail (2-3 paragraphs) what this program does and how it works.
 */
int main()
{

  fstream cf; // What is this? count/chance file
  ifstream qf; // What is this? question file, input only
  int rq; //
  int rl; //
  double p; // probability
  bool q; // question?

  cf.open("pc.txt", ios::in);
  cf >> rq;
  cf >> rl;
  cf.close();

  p = static_cast<double> (rq) / static_cast<double> (rl);

  // Set up random generator on range [0..1)
  // See http://www.boost.org/doc/libs/1_44_0/doc/html/boost_random.html
  // for details
  static mt11213b engine(static_cast<unsigned> (time(0)));
  uniform_real<double> distribution(0, 1);
  variate_generator<mt11213b&, uniform_real<double> > sampler(engine,
                                                              distribution);

  q = (p < sampler());

  rl -= 1;
  if (q) {
    rq -= 1;
  }

  cf.open("pc.txt", ios::out | ios::trunc);
  cf << rq << " " << rl << endl;
  cf.close();

  if (q) {
    string line;

    qf.open("pq.txt", ios::in);

    cout << "Pop Quiz today!" << endl;
    cout << "--------------------------------------" << endl;
    while (!qf.eof()) {
      getline(qf, line);
      cout << line << endl;
    }
    cout << "--------------------------------------" << endl;

    qf.close();
  }
  else {
    cout << "Not today." << endl;
  }

  return 0;
}
