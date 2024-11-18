#include "IstreamState.hpp"

IstreamState::IstreamState(std::istream & in) :
    in_(in),
    flags_(in.flags())
{}

IstreamState::~IstreamState()
{
  in_.flags(flags_);
}
