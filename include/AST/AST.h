#ifndef SCOPION_AST_H_
#define SCOPION_AST_H_

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_LIST_SIZE 50

#include <boost/variant.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace scopion {

namespace ast {

struct add;
struct sub;
struct mul;
struct div;
struct rem;
struct shl;
struct shr;
struct iand;
struct ior;
struct ixor;
struct land;
struct lor;
struct eeq;
struct neq;
struct gt;
struct lt;
struct gtq;
struct ltq;
struct assign;
struct call;
struct at;
struct load;

template <class Op> struct binary_op;
class variable;
class array;
class function;

using value = boost::variant<int, bool, boost::recursive_wrapper<std::string>,
                             boost::recursive_wrapper<variable>,
                             boost::recursive_wrapper<array>,
                             boost::recursive_wrapper<function>>;

using expr = boost::variant<value, boost::recursive_wrapper<binary_op<add>>,
                            boost::recursive_wrapper<binary_op<sub>>,
                            boost::recursive_wrapper<binary_op<mul>>,
                            boost::recursive_wrapper<binary_op<div>>,
                            boost::recursive_wrapper<binary_op<rem>>,
                            boost::recursive_wrapper<binary_op<shl>>,
                            boost::recursive_wrapper<binary_op<shr>>,
                            boost::recursive_wrapper<binary_op<iand>>,
                            boost::recursive_wrapper<binary_op<ior>>,
                            boost::recursive_wrapper<binary_op<ixor>>,
                            boost::recursive_wrapper<binary_op<land>>,
                            boost::recursive_wrapper<binary_op<lor>>,
                            boost::recursive_wrapper<binary_op<eeq>>,
                            boost::recursive_wrapper<binary_op<neq>>,
                            boost::recursive_wrapper<binary_op<gt>>,
                            boost::recursive_wrapper<binary_op<lt>>,
                            boost::recursive_wrapper<binary_op<gtq>>,
                            boost::recursive_wrapper<binary_op<ltq>>,
                            boost::recursive_wrapper<binary_op<assign>>,
                            boost::recursive_wrapper<binary_op<call>>,
                            boost::recursive_wrapper<binary_op<at>>,
                            boost::recursive_wrapper<binary_op<load>>>;

class variable {
public:
  std::string name;
  bool lval;
  bool isFunc;
  variable(std::string const &n, bool lval_, bool isfunc)
      : name(n), lval(lval_), isFunc(isfunc) {}
};

class array {
public:
  std::vector<expr> elements;
  array(std::vector<expr> const &elms_) : elements(elms_) {}
};

class function {
public:
  std::vector<expr> lines;
  function(std::vector<expr> const &lines_) : lines(lines_) {}
};

template <class Op> struct binary_op {
  expr lhs;
  expr rhs;
  bool lval;

  binary_op(expr const &lhs_, expr const &rhs_, bool lval_ = false)
      : lhs(lhs_), rhs(rhs_), lval(lval_) {}
};

std::ostream &operator<<(std::ostream &os, expr const &tree);

}; // namespace ast
}; // namespace scopion

#endif // SCOPION_AST_H_
