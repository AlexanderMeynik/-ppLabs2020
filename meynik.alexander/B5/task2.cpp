#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <functional>
#include "Shape.hpp"
#include "CollectStats.hpp"

void task2()
{
  std::vector<Shape> shapes((std::istream_iterator<Shape>(std::cin)),std::istream_iterator<Shape>());
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error while reading data");
  }

  CollectStats vectorStats;
  std::for_each(shapes.begin(),shapes.end(),std::ref(vectorStats));

  vectorStats.printStats(std::cout);

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(),
                              [](const Shape &sh) {return sh.points.size() == 5; }), shapes.end());

  std::vector<Point> points;
  points.reserve(shapes.size());
  std::transform(shapes.begin(), shapes.end(),
                 std::back_inserter(points), [](const Shape &sh) {return sh.points.front(); });

  std::cout << "Points:";
  std::copy(points.begin(),points.end(),std::ostream_iterator<Point>(std::cout));
  std::cout << '\n';

  std::sort(shapes.begin(),shapes.end(),[](const Shape&lShape,const Shape&rShape)
  {
    if(lShape.type==rShape.type)
    {
      return lShape.points[0].x < rShape.points[0].x;
    }
    return (lShape.type<rShape.type);
  });

  std::cout << "Shapes:\n";
  std::copy(shapes.begin(),shapes.end(),std::ostream_iterator<Shape>(std::cout));

}
