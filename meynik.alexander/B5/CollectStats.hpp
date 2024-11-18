#ifndef LAB5_COLLECTSTATS_HPP
#define LAB5_COLLECTSTATS_HPP

#include <vector>
#include "Shape.hpp"

class CollectStats
{
public:

  CollectStats();

  void operator()(Shape & shape);

  void printStats(std::ostream &out) const;

private:
  size_t amountOfTriangles_;
  size_t amountOfSquares_;
  size_t amountOfRectangles_;
  size_t amountOfPoints_;
};

#endif //LAB5_COLLECTSTATS_HPP
