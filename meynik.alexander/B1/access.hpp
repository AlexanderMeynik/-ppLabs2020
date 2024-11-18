#ifndef ACCESS_HPP
#define ACCESS_HPP

#include <forward_list>
#include <vector>
#include <cstddef>

template < typename container >
class IndexAccess
{
public:
  static size_t begin(container&)
  {
    return 0;
  }

  static size_t end(container& data)
  {
    return data.size();
  }

  static typename container::reference element(container& data, size_t index)
  {
    return data[index];
  }

  static size_t next(size_t index)
  {
    return ++index;
  }
};

template < typename container >
class AtAccess
{
public:
  static size_t begin(container&)
  {
    return 0;
  }

  static size_t end(container& data)
  {
    return data.size();
  }

  static typename container::reference element(container& data, size_t index)
  {
    return data.at(index);
  }

  static size_t next(size_t index)
  {
    return ++index;
  }
};

template < typename container >
class IteratorAccess
{
public:

  typedef typename container::iterator iterator;

  static iterator begin(container& data)
  {
    return data.begin();
  }

  static iterator end(container& data)
  {
    return data.end();
  }

  static typename container::reference element(container&, iterator index)
  {
    return *index;
  }

  static iterator next(iterator index)
  {
    return ++index;
  }
};

#endif
