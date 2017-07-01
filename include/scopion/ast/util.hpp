#ifndef SCOPION_AST_UTIL_H_
#define SCOPION_AST_UTIL_H_

#include "scopion/ast/attribute.hpp"
#include "scopion/ast/expr.hpp"
#include "scopion/ast/value_wrapper.hpp"

#include <boost/variant.hpp>

#include <string>

namespace scopion {
namespace ast {

struct set_lval_visitor : boost::static_visitor<expr> {
  const bool v;

  set_lval_visitor(bool v_) : v(v_) {}

  template <typename Op> expr operator()(single_op<Op> val) const {
    attr(val).lval = v;
    val.value = boost::apply_visitor(*this, val.value);
    return val;
  }

  template <typename Op> expr operator()(binary_op<Op> val) const {
    attr(val).lval = v;
    val.lhs = boost::apply_visitor(*this, val.lhs);
    val.rhs = boost::apply_visitor(*this, val.rhs);
    return val;
  }

  template <typename Op> expr operator()(ternary_op<Op> val) const {
    attr(val).lval = v;
    val.first = boost::apply_visitor(*this, val.first);
    val.second = boost::apply_visitor(*this, val.second);
    val.third = boost::apply_visitor(*this, val.third);
    return val;
  }

  template <typename T> expr operator()(T val) const {
    attr(val).lval = v;
    return val;
  }

  ast::expr operator()(expr val) const {
    return boost::apply_visitor(*this, val);
  }

  ast::expr operator()(value val) const {
    return boost::apply_visitor(*this, val);
  }

  ast::expr operator()(operators val) const {
    return boost::apply_visitor(*this, val);
  }
};

struct set_to_call_visitor : boost::static_visitor<expr> {
  const bool v;

  set_to_call_visitor(bool v_) : v(v_) {}

  template <typename Op> expr operator()(single_op<Op> val) const {
    attr(val).to_call = v;
    val.value = boost::apply_visitor(*this, val.value);
    return val;
  }

  template <typename Op> expr operator()(binary_op<Op> val) const {
    attr(val).to_call = v;
    val.lhs = boost::apply_visitor(*this, val.lhs);
    val.rhs = boost::apply_visitor(*this, val.rhs);
    return val;
  }

  template <typename Op> expr operator()(ternary_op<Op> val) const {
    attr(val).to_call = v;
    val.first = boost::apply_visitor(*this, val.first);
    val.second = boost::apply_visitor(*this, val.second);
    val.third = boost::apply_visitor(*this, val.third);
    return val;
  }

  template <typename T> expr operator()(T val) const {
    attr(val).to_call = v;
    return val;
  }

  ast::expr operator()(expr val) const {
    return boost::apply_visitor(*this, val);
  }

  ast::expr operator()(value val) const {
    return boost::apply_visitor(*this, val);
  }

  ast::expr operator()(operators val) const {
    return boost::apply_visitor(*this, val);
  }
};

struct set_survey_visitor : boost::static_visitor<expr> {
  const bool v;

  set_survey_visitor(bool v_) : v(v_) {}

  template <typename Op> expr operator()(single_op<Op> val) const {
    attr(val).survey = v;
    val.value = boost::apply_visitor(*this, val.value);
    return val;
  }

  template <typename Op> expr operator()(binary_op<Op> val) const {
    attr(val).survey = v;
    val.lhs = boost::apply_visitor(*this, val.lhs);
    val.rhs = boost::apply_visitor(*this, val.rhs);
    return val;
  }

  template <typename Op> expr operator()(ternary_op<Op> val) const {
    attr(val).survey = v;
    val.first = boost::apply_visitor(*this, val.first);
    val.second = boost::apply_visitor(*this, val.second);
    val.third = boost::apply_visitor(*this, val.third);
    return val;
  }

  template <typename T> expr operator()(T val) const {
    attr(val).survey = v;
    return val;
  }

  ast::expr operator()(expr val) const {
    return boost::apply_visitor(*this, val);
  }

  ast::expr operator()(value val) const {
    return boost::apply_visitor(*this, val);
  }

  ast::expr operator()(operators val) const {
    return boost::apply_visitor(*this, val);
  }
};

struct set_attr_visitor : boost::static_visitor<expr> {
  std::string const &key;
  std::string const &val;

  set_attr_visitor(std::string const &key_, std::string const &val_)
      : key(key_), val(val_) {}

  template <typename T> expr operator()(T value) const {
    attr(value).attributes[key] = val;
    return value;
  }

  ast::expr operator()(expr val) const {
    return boost::apply_visitor(*this, val);
  }

  ast::expr operator()(value val) const {
    return boost::apply_visitor(*this, val);
  }

  ast::expr operator()(operators val) const {
    return boost::apply_visitor(*this, val);
  }
};

template <typename T> T &val(value_wrapper<T> &w) { return w.value; }

template <typename T> const T &val(value_wrapper<T> const &w) {
  return w.value;
}

template <typename T> attribute &attr(T &w) { return w.attr; }
template <typename T> const attribute &attr(T const &w) { return w.attr; }

template <typename T> expr set_lval(T t, bool val) {
  return set_lval_visitor(val)(t);
}

template <typename T> expr set_to_call(T t, bool val) {
  return set_to_call_visitor(val)(t);
}

template <typename T> expr set_survey(T t, bool val) {
  return set_survey_visitor(val)(t);
}

template <typename T>
expr set_attr(T t, std::string const &key, std::string const &val) {
  return set_attr_visitor(key, val)(t);
}

template <typename T, typename RangeT> T set_where(T val, RangeT range) {
  attr(val).where = range;
  return val;
}

template <typename Dest,
          std::enable_if_t<std::is_convertible<Dest, value>::value> * = nullptr>
Dest unpack(expr t) {
  return boost::get<Dest>(boost::get<ast::value>(t));
}

template <
    typename Dest,
    std::enable_if_t<std::is_convertible<Dest, operators>::value> * = nullptr>
Dest unpack(expr t) {
  return boost::get<Dest>(boost::get<ast::operators>(t));
}

}; // namespace ast
}; // namespace scopion

#endif
