
#ifndef READY_SET_BOOLE_HPP
#define READY_SET_BOOLE_HPP

#include <utility> // Pair
#include <string>
#include <vector>
#include <set>
#include "Types.hpp"

namespace ReadySetBoole
{

u32 adder(u32 a, u32 b) noexcept;
u32 multiplier(u32 a, u32 b) noexcept;
u32 gray_code(u32 n) noexcept;

bool eval_formula(std::string const & formula);
void print_truth_table(std::string const & formula);

std::string negation_normal_form(std::string const & formula);
std::string conjunctive_normal_form(std::string const & formula);

bool sat(std::string const & formula);

std::vector<std::set<i32>> powerset(std::set<i32> const & set);
std::set<i32> eval_set(std::string const & formula, std::vector<std::set<i32>> const & sets);

f64 map(u16 x, u16 y);
std::pair<u16, u16> reverse_map(f64 n);

} // End - Namespace

#endif
