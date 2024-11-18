#include "CollectStats.hpp"

CollectStats::CollectStats():
    amountOfTriangles_(0),
    amountOfSquares_(0),
    amountOfRectangles_(0),
    amountOfPoints_(0)
{}

void CollectStats::operator()(Shape & shape)
{
  if (shape.type==Shape::TRIANGLE)
  {
    ++amountOfTriangles_;
  }
  else if (shape.type==Shape::RECTANGLE)
  {
    ++amountOfRectangles_;
  }
  else if(shape.type==Shape::SQUARE)
  {
    ++amountOfRectangles_;
    ++amountOfSquares_;
  }
  amountOfPoints_ += shape.points.size();
}

void CollectStats::printStats(std::ostream &out) const
{
  out << "Vertices: " << amountOfPoints_ << "\nTriangles: " << amountOfTriangles_
      << "\nSquares: " << amountOfSquares_ << "\nRectangles: "
      << amountOfRectangles_ << '\n';
}

