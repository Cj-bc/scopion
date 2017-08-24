/**
* @file module.hpp
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

#ifndef SCOPION_ASSEMBLY_MODULE_H_
#define SCOPION_ASSEMBLY_MODULE_H_

#include "scopion/assembly/context.hpp"
#include "scopion/assembly/translator.hpp"
#include "scopion/assembly/value.hpp"

#include "scopion/parser/parser.hpp"

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/Module.h>

namespace scopion
{
namespace assembly
{
class module
{
  std::shared_ptr<llvm::Module> module_;

public:
  value* val;

  static std::unique_ptr<module> create(parser::parsed const& tree,
                                        context& ctx,
                                        std::string const& name = "");

  std::string irgen();
  void optimize(uint8_t optLevel = 3, uint8_t sizeLevel = 0);

private:
  module(std::shared_ptr<llvm::Module>& module, value* val_) : module_(std::move(module)), val(val_)
  {
  }
};

};  // namespace assembly
};  // namespace scopion

#endif
