#include "matrix.hpp"

namespace meynik
{
  Matrix::Matrix() :
    rows_(0),
    columns_(0),
    matrix_(nullptr)
  {}

  Matrix::Matrix(const Matrix& anotherMatrix) :
    rows_(anotherMatrix.rows_),
    columns_(anotherMatrix.columns_),
    matrix_(new std::shared_ptr<Shape>[anotherMatrix.rows_ * anotherMatrix.columns_])
  {
    for (size_t i = 0; i < (columns_ * rows_); i++)
    {
      matrix_[i] = anotherMatrix.matrix_[i];
    }
  }

  Matrix::Matrix(Matrix&& anotherMatrix) noexcept :
    rows_(anotherMatrix.rows_),
    columns_(anotherMatrix.columns_),
    matrix_(std::move(anotherMatrix.matrix_))
  {
    anotherMatrix.rows_ = 0;
    anotherMatrix.columns_ = 0;
    anotherMatrix.matrix_.reset();
  }

  Matrix& Matrix::operator=(const Matrix& anotherMatrix)
  {
    if (&anotherMatrix == this)
    {
      return *this;
    }
    if (anotherMatrix.rows_ != rows_ || anotherMatrix.columns_ != columns_)
    {
      arrayPtr temp(std::make_unique<std::shared_ptr<Shape>[]>(anotherMatrix.rows_ * anotherMatrix.columns_));
      for (size_t i = 0; i < (anotherMatrix.rows_ * columns_); i++)
      {
        temp[i] = anotherMatrix.matrix_[i];
      }
      rows_ = anotherMatrix.rows_;
      columns_ = anotherMatrix.columns_;
      matrix_ = std::move(temp);
    }
    else
    {
      for (size_t i = 0; i < (anotherMatrix.rows_ * columns_); i++)
      {
        matrix_[i] = anotherMatrix.matrix_[i];
      }
    }
    return *this;
  }

  Matrix& Matrix::operator=(Matrix&& anotherMatrix) noexcept
  {
    if (&anotherMatrix == this)
    {
      return *this;
    }
    rows_ = anotherMatrix.rows_;
    columns_ = anotherMatrix.columns_;
    matrix_ = std::move(anotherMatrix.matrix_);
    anotherMatrix.rows_ = 0;
    anotherMatrix.columns_ = 0;
    anotherMatrix.matrix_.reset();
    return *this;
  }

  Matrix::Layer Matrix::operator[](const size_t row)
  {
    if (rows_ == 0 || row > rows_ - 1)
    {
      throw std::invalid_argument(std::string("Index of row is out of range! Index value ") + std::to_string(row)
          + ". Index of row must be less than " + std::to_string(rows_) + ".\n");
    }
    return Layer(&matrix_[columns_ * row], columns_);
  }

  void Matrix::addShape(const std::shared_ptr<Shape>& shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Attempt to insert empty shape pointer!");
    }
    size_t freeColumns = 0;
    size_t rowForInsert = 1;

    for (size_t i = 0; i < rows_; i++)
    {
      size_t j = i * columns_;
      while (j < (i + 1) * columns_ && matrix_[j] != nullptr)
      {
        if (areShapesIntersected(matrix_[j], shape))
        {
          rowForInsert = i + 2;
          break;
        }
        j++;
      }
    }

    size_t tempRows = rows_;
    size_t tempColumns = columns_;

    if (rowForInsert > rows_)
    {
      tempRows++;
      freeColumns = columns_;
    }
    else
    {
      size_t i = (rowForInsert)*columns_ - 1;
      while (i >= (rowForInsert - 1) * columns_ && matrix_[i] == nullptr)
      {
        i--;
        freeColumns++;
      }
    }

    if (freeColumns == 0)
    {
      tempColumns++;
      freeColumns = 1;
    }

    if (rows_ == tempRows && columns_ == tempColumns)
    {
      matrix_[(rowForInsert)*tempColumns - freeColumns] = shape;
    }
    else
    {
      arrayPtr tempMatrixElem = std::make_unique<std::shared_ptr<Shape>[]>(tempRows * tempColumns);
      for (size_t i = 0; i < tempRows; i++)
      {
        for (size_t j = 0; j < tempColumns; j++)
        {
          if (i >= rows_ || j >= columns_)
          {
            tempMatrixElem[i * tempColumns + j] = nullptr;
            continue;
          }
          tempMatrixElem[i * tempColumns + j] = matrix_[i * columns_ + j];
        }
      }
      tempMatrixElem[(rowForInsert)*tempColumns - freeColumns] = shape;
      matrix_ = std::move(tempMatrixElem);
      rows_ = tempRows;
      columns_ = tempColumns;
    }
  }

  bool Matrix::areShapesIntersected(const std::shared_ptr<Shape>& firstShape, const std::shared_ptr<Shape>& secondShape) const noexcept
  {
    if (firstShape == nullptr || secondShape == nullptr)
    {
      return false;
    }
    meynik::rectangle_t rect1 = firstShape->getFrameRect();
    meynik::rectangle_t rect2 = secondShape->getFrameRect();
    double firstLeftSide = rect1.pos.x - (rect1.width / 2);
    double firstUpSide = rect1.pos.y + (rect1.height / 2);
    double firstRightSide = rect1.pos.x + (rect1.width / 2);
    double firstDownSide = rect1.pos.y - (rect1.height / 2);
    double secondLeftSide = rect2.pos.x - (rect2.width / 2);
    double secondUpSide = rect2.pos.y + (rect2.height / 2);
    double secondRightSide = rect2.pos.x + (rect2.width / 2);
    double secondDownSide = rect2.pos.y - (rect2.height / 2);
    return(!(firstLeftSide >= secondRightSide || firstUpSide <= secondDownSide || secondUpSide <= firstDownSide || secondLeftSide >= firstRightSide));
  }

  size_t Matrix::getAmountOfRows()const noexcept
  {
    return rows_;
  }

  size_t Matrix::getAmountOfColoumns()const noexcept
  {
    return columns_;
  }

  void Matrix::printInfo(std::ostream& out) const noexcept
  {
    for (size_t row = 0; row < rows_; row++)
    {
      for (size_t coloumn = 0; coloumn < columns_; coloumn++)
      {
        if (!matrix_[row * columns_ + coloumn])
        {
          break;
        }
        else
        {
          out << "Element of " << row << " row and " << coloumn << " coloumn\n";
          matrix_[row * columns_ + coloumn]->printInfo(out);
          out << '\n';
        }
      }
    }
    out << '\n';
  }

  Matrix::Layer::Layer(shapePtr* shapes, size_t size) :
    shapes_(shapes),
    size_(size)
  {}

  Matrix::shapePtr& Matrix::Layer::operator[](size_t column)
  {
    if (column > size_ - 1 || size_ == 0)
    {
      throw std::invalid_argument(std::string("Index of column is out of range! Index value ") + std::to_string(column)
          + ". Index of row must be less than " + std::to_string(size_) + ".\n");
    }
    return shapes_[column];
  }

}
