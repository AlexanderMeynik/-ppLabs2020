#include<iostream>
#include"circle.hpp"
#include"rectangle.hpp"

int main()
{
  try
  {
    meynik::point_t point1{ 2.0, 3.0 };
    meynik::point_t point2{ 1.2, 2.1 };
    meynik::point_t mover{ 1.5, 2.9 };
    double scale1 = 2.0;
    double scale2 = 3.0;
    meynik::Shape* shape1 = new meynik::Rectangle(point1, 4.0, 9.0);
    std::cout << "Shape pointer initialised by rectangle object:\n"
        << "Rectangle before moving:\n";
    shape1->printInfo(std::cout);
    shape1->move(mover);
    std::cout << "Rectangle after moving:\n";
    shape1->printInfo(std::cout);
    std::cout << "Rectangle area: " << shape1->getArea() << '\n';
    shape1->move(-mover.x, -mover.y);
    std::cout << "Rectangle moved to center of coordinates plane:\n"; 
    shape1->printInfo(std::cout);
    std::cout << "Rectangle area: " << shape1->getArea() << '\n';
    shape1->scale(scale1);
    std::cout << "Rectangle after scaling by " << scale1 << ":\n";
    shape1->printInfo(std::cout);
    std::cout << "Rectangle area: " << shape1->getArea() << "\n\n";
    delete shape1;
    meynik::Rectangle rect(point1, 4.0, 9.0);
    std::cout << "Object of rectangle class:\n"
        << "Rectangle before moving:\n";
    rect.printInfo(std::cout);
    rect.move(mover);
    std::cout << "Rectangle after moving:\n";
    rect.printInfo(std::cout);
    std::cout << "Rectangle area: " << rect.getArea() << '\n';
    rect.move(-mover.x, -mover.y);
    std::cout << "Rectangle moved to center of coordinates plane:\n";
    std::cout << "Rectangle area: " << rect.getArea() << '\n';
    rect.printInfo(std::cout);
    rect.scale(scale1);
    std::cout << "Rectangle after scaling by " << scale1 << ":\n";
    rect.printInfo(std::cout);
    std::cout << "Rectangle area: " << rect.getArea() << "\n\n";
    meynik::Shape* shape2 = new meynik::Circle(point2, 2.281336);
    std::cout << "Shape pointer initialised by circle object:\n"
        << "Circle before moving:\n";
    shape2->printInfo(std::cout);
    shape2->move(mover);
    std::cout << "Circle after moving:\n";
    shape2->printInfo(std::cout);
    std::cout << "Circle area: " << shape2->getArea() << '\n';
    shape2->move(-mover.x, -mover.y);
    std::cout << "Circle moved to center of coordinates plane:\n";
    shape2->printInfo(std::cout);
    std::cout << "Circle area: " << shape2->getArea() << '\n';
    shape2->scale(scale2);
    std::cout << "Circle after scaling by " << scale2 << ":\n";
    shape2->printInfo(std::cout);
    std::cout << "Circle area: " << shape2->getArea() << "\n\n";
    delete shape2;
    meynik::Circle circ(point2, 2.281336);
    std::cout << "Object of circle class:\n"
        << "Circle before moving:\n";
    circ.printInfo(std::cout);
    circ.move(mover);
    std::cout << "Circle after moving:\n";
    circ.printInfo(std::cout);
    std::cout << "Circle area: " << circ.getArea() << '\n';
    circ.move(-mover.x, -mover.y);
    std::cout << "Circle moved to center of coordinates plane:\n";
    circ.printInfo(std::cout);
    std::cout << "Circle area: " << circ.getArea() << '\n';
    circ.scale(scale2);
    std::cout << "Circle after scaling by " << scale2 << ":\n";
    circ.printInfo(std::cout);
    std::cout << "Circle area: " << circ.getArea() << "\n\n";
  }
  catch (const std::invalid_argument & exception)
  {
    std::cerr << exception.what() <<'\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Error:Unknown problem\n";
    return -1;
  }
  return 0;
}
