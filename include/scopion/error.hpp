/**
* @file error.hpp
*
* (c) copyright 2017 coord.e
*
* This file is part of scopion.
*
* scopion is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* scopion is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with scopion.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCOPION_ERROR_H_
#define SCOPION_ERROR_H_

#include <algorithm>
#include <iomanip>
#include <iostream>

#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/iterator_range.hpp>

#include "rang.hpp"

namespace scopion
{
using str_range_t = boost::iterator_range<std::string::const_iterator>;

enum class errorType { Parse, Translate, Internal, Bug };

static std::string getErrorTypeString(errorType et)
{
  switch (et) {
    case errorType::Parse:
      return "Parse Error";
    case errorType::Translate:
      return "Translate Error";
    case errorType::Internal:
      return "Internal Error";
    case errorType::Bug:
      return "Bug";
  }
}

struct locationInfo {
  static str_range_t line_range(str_range_t const where, str_range_t const code)
  {
    auto range = boost::make_iterator_range(code.begin(), where.begin());
    auto sol   = boost::find(range | boost::adaptors::reversed, '\n').base();
    auto eol   = std::find(where.begin(), code.end(), '\n');
    return boost::make_iterator_range(sol, eol);
  }
  uint32_t line_number_;
  uint32_t distance_;
  std::string line_;
  bool is_empty_;

public:
  locationInfo(str_range_t where, str_range_t code) : is_empty_(false)
  {
    line_number_ = static_cast<uint32_t>(std::count(code.begin(), where.begin(), '\n')) + 1;
    auto r       = line_range(where, code);
    line_        = std::string(r.begin(), r.end());
    distance_    = static_cast<uint32_t>(std::distance(r.begin(), where.begin()));
  }

  locationInfo() : is_empty_(true) {}

  uint32_t getLineNumber() const { return line_number_; }
  std::string getLineContent() const { return line_; }
  uint32_t getColumnNumber() const { return distance_; }
  bool isEmpty() const { return is_empty_; }
};

class error
{
  std::string message_;
  locationInfo location_;
  errorType type_;

public:
  error(std::string const& message, locationInfo const& where, errorType type)
      : message_(message), location_(where), type_(type)
  {
  }

  locationInfo& getLocInfo() { return location_; }
  locationInfo const& getLocInfo() const { return location_; }
  errorType getErrorType() const { return type_; }
  std::string getErrorString() const { return getErrorTypeString(type_); }
  std::string getMessage() const { return message_; }
};

template <class Char, class Traits>
std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& os, const error& e)
{
  auto const loc = e.getLocInfo();
  if (e.getErrorType() == errorType::Bug)
    os << rang::style::reset << rang::bg::red << rang::fg::gray << "[BUG]" << rang::style::reset
       << rang::fg::red
       << " Please submit a bug report to https://github.com/coord-e/scopion/issues with messages "
          "shown below."
       << std::endl;
  else
    os << rang::style::reset << rang::bg::red << rang::fg::gray << "[ERROR]" << rang::style::reset
       << " " << e.getErrorString() << ": ";
  if (!loc.isEmpty())
    os << rang::fg::magenta << "@" << loc.getLineNumber() << rang::style::reset << ": ";

  os << rang::style::reset << e.getMessage() << std::endl;
  if (!loc.isEmpty())
    os << loc.getLineContent() << std::endl
       << rang::fg::green << std::setw(static_cast<int>(loc.getColumnNumber()) + 1) << "^"
       << rang::style::reset;

  return os;
}
};  // namespace scopion

#endif  // SCOPION_EXCEPTIONS_H_
