#define BOOST_TEST_MODULE maintest

#include <memory>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double ACCURACY_DOUBLE = 0.0001;

BOOST_AUTO_TEST_CASE(test_empty_shape_matrix_add_shape)
{
  meynik::Matrix testMatrix;
  std::shared_ptr<meynik::Shape> nullPointer = nullptr;
  BOOST_CHECK_THROW(testMatrix.addShape(nullPointer), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_index_matrix_get_shape)
{
  meynik::Matrix testMatrix;
  BOOST_CHECK_THROW(testMatrix[100][11], std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_rotate_circle)
{
  meynik::Circle circle({ 0, 0 }, 9);
  double startArea = circle.getArea();
  meynik::point_t startCenter = circle.getCentre();
  circle.rotate(180);
  BOOST_CHECK_CLOSE(startArea, circle.getArea(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(startCenter.x, circle.getCentre().x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(startCenter.y, circle.getCentre().y, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_rotate_rectangle)
{
  meynik::Rectangle rectangle({ 0, 0 }, 10, 5);
  double startArea = rectangle.getArea();
  meynik::point_t center = rectangle.getCentre();
  rectangle.rotate(45);
  BOOST_CHECK_CLOSE(startArea, rectangle.getArea(), ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(center.x, rectangle.getCentre().x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(center.y, rectangle.getCentre().y, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rectangle.getAngle(), 45, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_rotate_composite_shape)
{
  meynik::CompositeShape compositeShape(2);
  std::shared_ptr<meynik::Shape> circle
    = std::make_shared<meynik::Circle>(meynik::Circle(meynik::point_t{ -7, 8 }, 9));
  std::shared_ptr<meynik::Shape> rectangle
    = std::make_shared<meynik::Rectangle>(meynik::Rectangle(meynik::point_t{ 5, 25 }, 9, 10));
  compositeShape.insertShape(circle);
  compositeShape.insertShape(rectangle);
  compositeShape.move({ 0.0,0.0 });
  meynik::point_t startPoint1 = compositeShape[0]->getCentre();
  meynik::point_t startPoint2 = compositeShape[1]->getCentre();
  compositeShape.rotate(180);
  BOOST_CHECK_CLOSE(compositeShape[0]->getCentre().x, -startPoint1.x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(compositeShape[0]->getCentre().y, -startPoint1.y, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(compositeShape[1]->getCentre().x, -startPoint2.x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(compositeShape[1]->getCentre().y, -startPoint2.y, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_add_two_not_intersecting_shapes)
{
  std::shared_ptr<meynik::Shape> circle
    = std::make_shared<meynik::Circle>(meynik::Circle(meynik::point_t{ 0, 0 }, 2.28));
  meynik::Matrix matrix;
  matrix.addShape(circle);
  std::shared_ptr<meynik::Shape> rectangle
    = std::make_shared<meynik::Rectangle>(meynik::Rectangle(meynik::point_t{ 100, 0 }, 5, 10));
  matrix.addShape(rectangle);
  BOOST_CHECK(matrix.getAmountOfColoumns() == 2);
  BOOST_CHECK(matrix.getAmountOfRows() == 1);
  BOOST_CHECK(matrix[0][0] == circle);
  BOOST_CHECK(matrix[0][1] == rectangle);
}

BOOST_AUTO_TEST_CASE(test_add_two_intersecting_shapes)
{
  std::shared_ptr<meynik::Shape> circle
    = std::make_shared<meynik::Circle>(meynik::Circle(meynik::point_t{ 0, 0 }, 15));
  meynik::Matrix matrix;
  matrix.addShape(circle);
  std::shared_ptr<meynik::Shape> rectangle
    = std::make_shared<meynik::Rectangle>(meynik::Rectangle(meynik::point_t{ 0, 0 }, 10, 5));
  matrix.addShape(rectangle);
  BOOST_CHECK(matrix.getAmountOfColoumns() == 1);
  BOOST_CHECK(matrix.getAmountOfRows() == 2);
  BOOST_CHECK(matrix[0][0] == circle);
  BOOST_CHECK(matrix[1][0] == rectangle);
}

BOOST_AUTO_TEST_CASE(test_layer_forming_matrix)
{
  meynik::Matrix matrix;
  std::shared_ptr<meynik::Shape> circle
    = std::make_shared<meynik::Circle>(meynik::Circle(meynik::point_t{ -10, 0 }, 2.28));
  std::shared_ptr<meynik::Shape> rectangle
    = std::make_shared<meynik::Rectangle>(meynik::Rectangle(meynik::point_t{ 10, 0 }, 5, 4));
  std::shared_ptr<meynik::Shape> rectangle1
    = std::make_shared<meynik::Rectangle>(meynik::Rectangle(meynik::point_t{ 0, 0 }, 210, 50));
  matrix.addShape(circle);
  matrix.addShape(rectangle);
  matrix.addShape(rectangle1);
  BOOST_CHECK(matrix[1][1] == nullptr);
  BOOST_CHECK(matrix[0][0] == circle);
  BOOST_CHECK(matrix[0][1] == rectangle);
  BOOST_CHECK(matrix[1][0] == rectangle1);
}
