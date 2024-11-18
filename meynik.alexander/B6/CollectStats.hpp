#ifndef LABB6_COLLECTSTATS_HPP
#define LABB6_COLLECTSTATS_HPP

#include <iostream>

class CollectStats
{
public:
  CollectStats();

  void operator()(int value);

  void printStats(std::ostream &out) const;

private:
  int max_, min_, positive_, negative_, first_, last_, numElements_;
  long long oddSum_, evenSum_;
};

#endif //LABB6_COLLECTSTATS_HPP
