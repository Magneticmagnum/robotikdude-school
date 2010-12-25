#ifndef RANDOM_H_
#define RANDOM_H_

// TODO user23: comment all
class Random
{
  public:
    Random();

    virtual void seed(int seed);

    virtual int random();

    double normal();

    double getRandomMax() const;

  private:
    double randomMax_;
};

#endif /* RANDOM_H_ */
