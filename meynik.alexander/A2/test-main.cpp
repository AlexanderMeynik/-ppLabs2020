#define BOOST_TEST_MODULE maintest

#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

const double ACCURACY_DOUBLE = 0.0001;


BOOST_AUTO_TEST_CASE(test_invalid_argument_rectangle)
{
  meynik::point_t pos{-2.0, 2.0};
  BOOST_CHECK_THROW(meynik::Rectangle rect(pos, -4.0, 9.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_rectangle_scale)
{
  meynik::point_t pos{-2.0, 2.0};
  meynik::Rectangle rect(pos, 4.0, 9.0);
  BOOST_CHECK_THROW(rect.scale(-2.5), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle)
{
  meynik::point_t pos{1.2, 2.1};
  BOOST_CHECK_THROW(meynik::Circle circle(pos, -2.28), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle_scale)
{ meynik::point_t pos{1.2, 2.1};
  meynik::Circle circle(pos, 2.28);
  BOOST_CHECK_THROW(circle.scale(-2.0), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_correct_move_rectangle)
{
  meynik::point_t pos{-2.0, 2.0};
  meynik::Rectangle rect(pos, 10.0, 10.0);
  const double x = 6,
      y = 6,
      primaryX = rect.getCentre().x,
      primaryY = rect.getCentre().y;
  rect.move(x, y);
  BOOST_CHECK_CLOSE(rect.getCentre().x, x + primaryX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect.getCentre().y, y + primaryY, ACCURACY_DOUBLE);
  rect.move({x, y});
  BOOST_CHECK_CLOSE(rect.getCentre().x, x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect.getCentre().y, y, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_correct_move_circle)
{
  meynik::point_t pos{1.2, 2.1};
  meynik::Circle circle(pos, 2.28);
  const double x = 2.1,
      y = 1.2,
      primaryX = circle.getCentre().x,
      primaryY= circle.getCentre().y;
  circle.move(x, y);
  BOOST_CHECK_CLOSE(circle.getCentre().x, x + primaryX, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle.getCentre().y, y + primaryY, ACCURACY_DOUBLE);
  circle.move({ x, y });
  BOOST_CHECK_CLOSE(circle.getCentre().x, x, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle.getCentre().y, y, ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_scale_rectangle_area)
{
  meynik::point_t pos{1.2, 2.1};
  meynik::Rectangle rect(pos, 2.0, 6.0);
  const double rect_area = rect.getArea(),
      scale = 2.5;
  rect.scale(scale);
  BOOST_CHECK_CLOSE(rect_area * scale * scale, rect.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_scale_circle_area)
{
  meynik::point_t pos{1.2, 2.1};
  meynik::Circle circle(pos, 10.0);
  const double circle_area = circle.getArea(),
      scale = 0.1;
  circle.scale(scale);
  BOOST_CHECK_CLOSE(circle_area * scale * scale, circle.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_permanency_move_rectange)
{
  meynik::point_t pos{-2, 2};
  meynik::Rectangle rect(pos, 10.0, 10.0);
  const meynik::rectangle_t frameRect = rect.getFrameRect();
  const double rect_area = rect.getArea();
  rect.move(meynik::point_t{2.0, -2.0});
  BOOST_CHECK_CLOSE(frameRect.height, rect.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, rect.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect_area, rect.getArea(), ACCURACY_DOUBLE);
  rect.move(-25.0, 25.0);
  BOOST_CHECK_CLOSE(frameRect.height, rect.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, rect.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(rect_area, rect.getArea(), ACCURACY_DOUBLE);
}

BOOST_AUTO_TEST_CASE(test_permanency_move_circle)
{
  meynik::point_t pos{1.2, 2.1};
  meynik::Circle circle(pos, 2.28);
  const meynik::rectangle_t frameRect = circle.getFrameRect();
  const double circle_area = circle.getArea();
  circle.move(2.1, 1.2);
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle_area, circle.getArea(), ACCURACY_DOUBLE);
  circle.move(meynik::point_t{0.0, 0.0});
  BOOST_CHECK_CLOSE(frameRect.height, circle.getFrameRect().height, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(frameRect.width, circle.getFrameRect().width, ACCURACY_DOUBLE);
  BOOST_CHECK_CLOSE(circle_area, circle.getArea(), ACCURACY_DOUBLE);
}
