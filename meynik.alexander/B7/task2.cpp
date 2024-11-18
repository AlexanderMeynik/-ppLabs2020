#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <memory>
#include <map>
#include <functional>
#include "IstreamState.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"
#include "Square.hpp"


template<class ShapeType>
std::shared_ptr<Shape> makeShared(int x, int y)
{
  return std::make_shared<ShapeType>(x, y);
}

static const std::map<std::string,std::function<std::shared_ptr<Shape>(int,int)>> createMap
{
  {"TRIANGLE", makeShared<Triangle>},
  {"SQUARE", makeShared<Square>},
  {"CIRCLE", makeShared<Circle>}
};

std::istream& skipSpaces(std::istream& in)
{
  while(!in.eof()&&std::isblank(in.peek()))
  {
    in.ignore();
  }
  return in;
}

std::istream& operator >> (std::istream& in, std::shared_ptr<Shape>& shape)
{
  if((in>>std::ws).peek() == EOF)
  {
    return in;
  }
  int x, y;
  std::string name;
  in >> skipSpaces;
  std::getline(in,name,'(');

  while (!isalpha(name.back())&&isblank(name.back()))
  {
    name.pop_back();
  }

  {
    IstreamState inState(in);

    in.unsetf(std::ios_base::skipws);
    char delimeter = '\0';

    in >> skipSpaces >> x >> skipSpaces >> delimeter;

    if (delimeter != ';')
    {
      in.clear(std::ios::failbit);
      return in;
    }

    in >> skipSpaces >> y >> skipSpaces >> delimeter;
    if (delimeter != ')')
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }

  auto iter = createMap.find(name);
  if(iter == createMap.end())
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  shape=iter->second(x,y);
  return in;
}

std::ostream& operator << (std::ostream& out, const std::shared_ptr<Shape>& shape)
{
  shape->draw(out);
  return out;
}

void task2()
{
  std::vector<std::shared_ptr<Shape>> shapes((std::istream_iterator<std::shared_ptr<Shape>>(std::cin)),
                                             std::istream_iterator<std::shared_ptr<Shape>>());
  if(std::cin.fail() &&!std::cin.eof() )
  {
    throw std::invalid_argument("Error while reading data!");
  }

  std::cout << "Original:\n";

  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));
  std::sort(shapes.begin(), shapes.end(),std::bind(&Shape::isMoreLeft,
                                                  std::bind(& std::shared_ptr<Shape>::operator*, std::placeholders::_1),
                                                  std::bind(&std::shared_ptr<Shape>::operator*, std::placeholders::_2)));

  std::cout << "Left-Right:\n";

  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::cout << "Right-Left:\n";

  std::copy(shapes.rbegin(), shapes.rend(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::sort(shapes.begin(), shapes.end(),std::bind(&Shape::isUpper,
                                                   std::bind(& std::shared_ptr<Shape>::operator*, std::placeholders::_1),
                                                   std::bind(&std::shared_ptr<Shape>::operator*, std::placeholders::_2)));
  std::cout << "Top-Bottom:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::cout << "Bottom-Top:\n";
  std::copy(shapes.rbegin(), shapes.rend(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));
}
