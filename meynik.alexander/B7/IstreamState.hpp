#ifndef LABB7_ISTREAMSTATE_HPP
#define LABB7_ISTREAMSTATE_HPP

#include <istream>
class IstreamState
{
public:

  explicit IstreamState(std::istream & in);

  ~IstreamState();

private:
  std::istream & in_;
  std::ios_base::fmtflags flags_;

};


#endif //LABB7_ISTREAMSTATE_HPP
