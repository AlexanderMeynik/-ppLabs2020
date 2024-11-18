#include "Point.hpp"

std::istream& skipSpaces(std::istream& in)
{
  while(!in.eof()&&std::isblank(in.peek()))
  {
    in.ignore();
  }
  return in;
}

std::istream&expect(std::istream &in,const char C)
{
  if ((in >> skipSpaces).peek() == C)
  {
    in.ignore();
  }
  else
  {
    in.clear(in.failbit);
  }
  return (in>>skipSpaces);
}

std::istream&operator>>(std::istream&in,Point&point)
{

  in.unsetf(std::ios_base::skipws);
  expect(in,'(');
  in>>point.x;
  expect(in,';');
  in>>point.y;
  expect(in,')');
  in.setf(std::ios_base::skipws);
  return in;
}

std::ostream&operator<<(std::ostream&out,const Point&point)
{
  out << " (" << point.x << ";" << point.y << ")";
  return out;
}
