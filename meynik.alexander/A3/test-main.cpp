#define BOOST_TEST_MODULE maintest

#include <memory>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

const double ACCURACY_DOUBLE = 0.0001;

BOOST_AUTO_TEST_CASE(test_invalid_argument_scale_composite_shape)
{
  meynik::CompositeShape compShape;
  BOOST_CHECK_THROW(compShape.scale(-10), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_index_operator_composite_shape)
{
  meynik::CompositeShape compShape;
  BOOST_CHECK_THROW(compShape[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_insert_composite_shape)
{
  meynik::CompositeShape compShape;
  std::shared_ptr<meynik::Shape>nullPointer = nullptr;
  BOOST_CHECK_THROW(compShape.insertShape(nullPointer), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_argument_delete_composite_shape)
{
  meynik::CompositeShape compShape;
  BOOST_CHECK_THROW(compShape.deleteShape(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_insert_composite_shape)
{
  meynik::CompositeShape compShape;
  std::shared_ptr<meynik::Shape> rect
      = std::make_shared<meynik::Rectangle>(meynik::Rectangle(meynik::point_t{ 1.2,2.1 }, 5.0,3.0));
  compShape.insertShape(rect);
  BOOST_CHECK(compShape[0] == rect);
}

BOOST_AUTO_TEST_CASE(test_delete_composite_shape)
{
  meynik::CompositeShape compShape;
  std::shared_ptr<meynik::Shape> circle
      = std::make_shared<meynik::Circle>(meynik::Circle(meynik::point_t{ 1.2,2.1 }, 5.0));
  compShape.insertShape(circle);
  BOOST_CHECK(compShape.getSize() == 1);
  compShape.deleteShape(0);
  BOOST_CHECK(compShape.getSize() == 0);
}

BOOST_AUTO_TEST_CASE(test_get_capacity_composite_shape)
{
  const int capacity = 13;
  meynik::CompositeShape compShape(capacity);
  BOOST_CHECK(compShape.getCapacity() == capacity);
}

BOOST_AUTO_TEST_CASE(test_get_size_composite_shape)
{
  meynik::CompositeShape compShape;
  std::shared_ptr<meynik::Shape> rectangle
      = std::make_shared<meynik::Rectangle>(meynik::Rectangle(meynik::point_t{ 1.2,2.1 }, 5.0, 7.0));
  compShape.insertShape(rectangle);
  BOOST_CHECK(compShape.getSize() == 1);
}

BOOST_AUTO_TEST_CASE(test_get_frame_composite_shape)
{
  meynik::CompositeShape compShape(1);
  std::shared_ptr<meynik::Shape> rect1
     = std::make_shared<meynik::Rectangle>(meynik::Rectangle(meynik::point_t{ 1.2, 2.1 }, 3.0, 4.0));
  std::shared_ptr<meynik::Shape> rect2
     = std::make_shared<meynik::Rectangle>(meynik::Rectangle(meynik::point_t{ 2.1, 1.2 }, 3.0, 3.0));
  std::shared_ptr<meynik::Shape> circ1
     = std::make_shared<meynik::Circle>(meynik::Circle(meynik::point_t{ -2.0, -3.0 },4.0));
  compShape.insertShape(rect1);
  compShape.insertShape(rect2);
  compShape.insertShape(circ1);
  const double width = 9.6,
      height = 11.1;
  BOOST_CHECK_CLOSE(compShape.getFrameRect().width, width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(compShape.getFrameRect().height, height, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_area_composite_shape)
{
  std::shared_ptr<meynik::Shape> rect
      = std::make_shared<meynik::Rectangle>(meynik::Rectangle(meynik::point_t{ 3.3, 2.2 }, 3.0, 5.0));
  std::shared_ptr<meynik::Shape> circle = std::make_shared<meynik::Circle>(meynik::Circle(meynik::point_t{ 1.2,2.1 }, 5.0));
  meynik::CompositeShape compShape;
  compShape.insertShape(circle);
  compShape.insertShape(rect);
  const double comp_area = circle->getArea() + rect->getArea();
  BOOST_CHECK_CLOSE(compShape.getArea(), comp_area, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_move_composite_shape)
{
  std::shared_ptr<meynik::Shape> rect
    = std::make_shared<meynik::Rectangle>(meynik::Rectangle(meynik::point_t{ 3.3, 4.1 }, 3.0, 5.0));
  std::shared_ptr<meynik::Shape> circle
    = std::make_shared<meynik::Circle>(meynik::Circle(meynik::point_t{ 0.0,0.0 }, 3));
  meynik::CompositeShape compShape;
  compShape.insertShape(circle);
  compShape.insertShape(rect);
  const double x = 3.0,
      y = 4.0,
      rectangle_oldX = rect->getCentre().x,
      rectangle_oldY = rect->getCentre().y,
      circle_oldX = circle->getCentre().x,
      circle_oldY = circle->getCentre().y;
  compShape.move(x, y);
  BOOST_CHECK_CLOSE(circle->getCentre().x, x + circle_oldX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle->getCentre().y, y + circle_oldY, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect->getCentre().x, x + rectangle_oldX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect->getCentre().y, y + rectangle_oldY, ACCURACY_DOUBLE);
  compShape.move({ x, y });
  BOOST_CHECK_CLOSE(circle->getCentre().x, 2.1, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle->getCentre().y, 2.2, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect->getCentre().x, 5.4, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect->getCentre().y, 6.3, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_scale_composite_shape)
{
  std::shared_ptr<meynik::Shape> rect
      = std::make_shared<meynik::Rectangle>(meynik::Rectangle(meynik::point_t{ 2.1, 1.2 }, 3.0, 4.0));
  std::shared_ptr<meynik::Shape> circle
      = std::make_shared<meynik::Circle>(meynik::Circle(meynik::point_t{ 0.0,0.0 },2.28));
  meynik::CompositeShape compShape;
  compShape.insertShape(circle);
  compShape.insertShape(rect);
  const double area_rect = rect->getArea(),
      scale = 1.6,
      area_circle = circle->getArea();
  compShape.scale(scale);
  BOOST_CHECK_CLOSE(area_circle * scale * scale, circle->getArea(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(area_rect * scale * scale, rect->getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_copy_composite_shape)
{
  std::shared_ptr<meynik::Shape> circle
      = std::make_shared<meynik::Circle>(meynik::Circle(meynik::point_t{ 0.0,1.0 },2.28));
  meynik::CompositeShape compShape;
  compShape.insertShape(circle);
  meynik::CompositeShape compShape1 = compShape;
  BOOST_CHECK_CLOSE(compShape[0]->getArea(), compShape[0]->getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_semantics_move_composite_shape)
{
  std::shared_ptr<meynik::Shape> circle
      = std::make_shared<meynik::Circle>(meynik::Circle(meynik::point_t{ 3.0,1.0 }, 2.28));
  meynik::CompositeShape compShape;
  compShape.insertShape(circle);
  const double area_circle = circle->getArea();
  meynik::CompositeShape compShape1(std::move(compShape));
  BOOST_CHECK_CLOSE(compShape1[0]->getArea(), area_circle, ACCURACY_DOUBLE);
  BOOST_CHECK_THROW(compShape[0], std::out_of_range);
}
