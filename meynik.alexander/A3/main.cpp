#include<iostream>
#include <memory>
#include"circle.hpp"
#include"rectangle.hpp"
#include "composite-shape.hpp"

int main()
{
  try
  {
    meynik::point_t point1{ 2.0, 3.0 };
    meynik::point_t point2{ 1.2, 2.1 };
    meynik::point_t mover{ 1.0, 2.9 };

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

    meynik::CompositeShape compShape1(2);
    std::shared_ptr<meynik::Shape> circ1
        = std::make_shared<meynik::Circle>(meynik::point_t{ -1.0,-1.0 }, 3.0);
    std::shared_ptr<meynik::Shape> rect1 
        = std::make_shared<meynik::Rectangle>(meynik::Rectangle(point1, 4.0, 9.0));
    std::shared_ptr<meynik::Shape> rect2 
        = std::make_shared<meynik::Rectangle>(meynik::Rectangle(point2, 6.0, 19.0));
    compShape1.insertShape(circ1);
    compShape1.insertShape(rect1);
    compShape1.insertShape(rect2);
    std::cout << "First composite shape data:\n";
    compShape1.printInfo(std::cout);
    meynik::rectangle_t frame_rect(compShape1.getFrameRect());
    std::cout << "First composite shape frame rectangle:\nWidth: " << frame_rect.width 
        << "\nHeight: " << frame_rect.width << "\nCentre(" << frame_rect.pos.x 
        << ',' << frame_rect.pos.y << ")\n\n";
    compShape1.scale(2.0);
    std::cout << "First composite shape after scaling by 2.0:\n";
    compShape1.printInfo(std::cout);
    compShape1.move(meynik::point_t{ 2.0,0.5 });
    std::cout << "First composite shape after moving in point(2.0, 0.5):\n";
    compShape1.printInfo(std::cout);
    compShape1.move( -2.0,-0.5 );
    std::cout << "First composite shape after moving by -2.0(x) and -0.5(y):\n";
    compShape1.printInfo(std::cout);
    meynik::CompositeShape compShape2(compShape1);
    std::cout << "Second composite shape initialised by first composite shape:\n";
    compShape2.printInfo(std::cout);
    compShape2.deleteShape(2);
    std::cout << "Second composite shape after deleting last element:\n";
    compShape2.printInfo(std::cout);
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
