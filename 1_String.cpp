#include <cstddef>   // std::size_t
#include <cstring>   // std::strlen, std::memcpy
#include <iostream>  // std::cout, std::ostream
#include <stdexcept> // std::invalid_argument
#include <utility>   // std::move

class String {
  char *data_;
  std::size_t length_;

public:
  String() : data_(new char[1]{'\0'}), length_(0) {}
  String(const char *str) : data_(nullptr), length_(0) {
    if (str == nullptr) {
      throw std::invalid_argument("Null String");
    }
    length_ = std::strlen(str);
    data_ = new char[length_ + 1];
    std::memcpy(data_, str, length_ + 1);
  }

  String(const String &other)
      : data_(new char[other.length_ + 1]), length_(other.length_) {
    if (other.data_ != nullptr) {
      std::memcpy(data_, other.data_, length_ + 1);
    } else {
      data_[0] = '\0';
    }
  }

  String(String &&other) noexcept : data_(other.data_), length_(other.length_) {
    other.data_ = nullptr;
    other.length_ = 0;
  }

  String &operator=(const String &other) {
    if (this != &other) {
      char *newData = new char[other.length_ + 1];
      if (other.data_ != nullptr) {
        std::memcpy(newData, other.data_, other.length_ + 1);
      } else {
        newData[0] = '\0';
      }
      delete[] data_;
      data_ = newData;
      length_ = other.length_;
    }
    return *this;
  }

  String &operator=(String &&other) noexcept {
    if (this != &other) {
      delete[] data_;
      data_ = other.data_;
      length_ = other.length_;
      other.data_ = nullptr;
      other.length_ = 0;
    }
    return *this;
  }

  const char *c_str() const noexcept {
    return data_ != nullptr ? data_ : "";
  }

  ~String() {
    delete[] data_;
  }
};

// Called when the left operand is an output stream and the right operand is a String.
std::ostream &operator<<(std::ostream &out, const String &str) {
  // This forwards the character data to the standard const char* stream overload.
  return out << str.c_str();
}

int main() {
  // Calls String() (the default constructor).
  String empty;

  // Calls String(const char*) (the C-string constructor).
  String original("Hello");

  // Calls String(const String&) (the copy constructor).
  String copied(original);

  // Calls String(String&&) (the move constructor); std::move makes original
  // eligible to be moved from.
  String moved(std::move(original));

  // Calls operator=(const String&) (copy assignment).
  empty = copied;

  // Calls operator=(String&&) (move assignment).
  String moveAssigned;
  moveAssigned = std::move(moved);

  // Calls c_str() and prints the returned const char*.
  std::cout << "c_str(): " << moveAssigned.c_str() << '\n';

  // Calls the custom operator<<(std::ostream&, const String&).
  std::cout << "stream output: " << moveAssigned << '\n';

  // The destructor is called automatically for each object when main exits.
}