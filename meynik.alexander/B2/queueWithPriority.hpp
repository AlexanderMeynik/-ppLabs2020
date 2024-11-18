#ifndef LAB2_QUEUEWITHPRIORITY_HPP
#define LAB2_QUEUEWITHPRIORITY_HPP

#include <list>
#include <stdexcept>
#include <memory>

template <typename T>
class QueueWithPriority
{
public:

  enum class elementPriority
  {
    LOW,
    NORMAL,
    HIGH
  };


  void putElementToQueue(const T& element, elementPriority priority);

  T getElementFromQueue();

  void popElementFromQueue();

  bool isEmpty() const noexcept;

  void accelerate();

private:
  static const size_t amountOfPriorities_ = static_cast<size_t>(elementPriority::HIGH) - static_cast<size_t>(elementPriority::LOW) + 1;
  std::list<T> listArray_[amountOfPriorities_];
};

template<typename T>
void QueueWithPriority<T>::putElementToQueue(const T& element, QueueWithPriority<T>::elementPriority priority)
{
  listArray_[static_cast<size_t>(priority)].push_back(element);
}

template<typename T>
void QueueWithPriority<T>::popElementFromQueue()
{
  int i = amountOfPriorities_ - 1;

  while (i >= 0 && listArray_[i].empty())
  {
    i--;
  }

  if (i >= 0)
  {
    listArray_[i].pop_front();
  }
  else
  {
    throw std::logic_error("Queue underflow");
  }
}

template<typename T>
T QueueWithPriority<T>::getElementFromQueue()
{

  int i = amountOfPriorities_ - 1;

  while (i >= 0 && listArray_[i].empty())
  {
    i--;
  }

  if (i >= 0)
  {
    const T temp = listArray_[i].front();
    return temp;
  }

  throw std::logic_error("Queue underflow");
}

template<typename T>
void QueueWithPriority<T>::accelerate()
{
  if (!listArray_[0].empty())
  {
    listArray_[amountOfPriorities_ - 1].splice(listArray_[amountOfPriorities_ - 1].end(), listArray_[0]);
  }
}

template<typename T>
bool QueueWithPriority<T>::isEmpty() const noexcept
{
  for (int i = amountOfPriorities_ - 1; i >= 0; i--)
  {
    if (!listArray_[i].empty())
    {
      return false;
    }
  }
  return true;
}

#endif
