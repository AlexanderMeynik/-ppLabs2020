#include "CollectStats.hpp"
#include <iomanip>
#include <limits>


CollectStats::CollectStats():
    max_(std::numeric_limits<int>::min()),
    min_(std::numeric_limits<int>::max()),
    positive_(0),
    negative_(0),
    numElements_(0),
    oddSum_(0),
    evenSum_(0)
{
}

void CollectStats::operator() (int value)
{
  max_ = std::max(max_, value);
  min_ = std::min(min_, value);

  if (value > 0)
  {
    positive_++;
  }
  else if (value < 0)
  {
    negative_++;
  }

  if (value % 2 == 0)
  {
    evenSum_ += value;
  }
  else
  {
    oddSum_ += value;
  }

  if (numElements_ == 0)
  {
    first_ = value;
  }

  last_ = value;
  numElements_++;
}

void CollectStats::printStats(std::ostream &out) const
{
  if (numElements_ == 0)
  {
    out << "No Data\n";
    return;
  }

  out << "Max: " << max_ << "\nMin: " << min_ << '\n';

  double mean = static_cast<double>(evenSum_ + oddSum_) / static_cast<double>(numElements_);
  
  out << "Mean: " << std::setprecision(1) << std::fixed << mean << "\nPositive: " << positive_
      << "\nNegative: " << negative_ << "\nOdd Sum: " << oddSum_ << "\nEven Sum: " << evenSum_
      << "\nFirst/Last Equal: " << (first_ == last_ ? "yes" : "no") << '\n';

}
