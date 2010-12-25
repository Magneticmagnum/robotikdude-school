#include "KeyValuePair.h"
#include "KeyValueComparator.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define BUFFER_SIZE 256

int main(int argc, char* argv[])
{
  void usage(char* prog);

  std::map<std::string, int> strmap;
  std::map<std::string, int>::iterator mapit;

  std::vector<KeyValuePair> pairvec;
  std::vector<KeyValuePair>::iterator vecit;
  KeyValueComparator comparator;

  std::ifstream input;
  std::ofstream output;

  char buffer[BUFFER_SIZE];

  if (argc != 3) {
    usage(argv[0]);
    exit(1);
  }
  else if (argc == 3) { // else
    input.open(argv[1]);
    if (input.fail()) {
      usage(argv[0]);
      exit(1);
    }

    output.open(argv[2]);
    if (output.fail()) {
      usage(argv[0]);
      exit(1);
    }
  }

  std::cout << "building map..." << std::endl;
  while (!input.eof()) {
    input.getline(buffer, BUFFER_SIZE);
    if (strmap.find(buffer) == strmap.end()) {
      std::string* string = new std::string(buffer);
      strmap[*string] = 1;
    }
    else {
      strmap[buffer]++;
    }
  }

  std::cout << "building vector..." << std::endl;
  KeyValuePair kvp;
  for (mapit = strmap.begin(); mapit != strmap.end(); mapit++) {
    kvp.count = mapit->second;
    kvp.str = mapit->first;
    pairvec.push_back(kvp);
  }

  std::cout << "sorting vector..." << std::endl;
  sort(pairvec.begin(), pairvec.end(), comparator);

  std::cout << "printing vector..." << std::endl;
  for (vecit = pairvec.begin(); vecit != pairvec.end(); vecit++) {
    output << vecit->str << " - " << vecit->count << std::endl;
  }

  std::cout << "done!" << std::endl;
  return 0;
}

void usage(char* prog)
{

}
