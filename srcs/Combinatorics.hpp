
#ifndef COMBINATORICS_HPP
#define COMBINATORICS_HPP

#include <vector>
#include <set>


namespace Combinatorics
{

// =============================================================================
// Templated Functions
// =============================================================================
// - Combinations --------------------------------------------------------------
template<typename T>
std::vector<std::set<T>>
combinations(
	std::set<T> elements
)
{
	if (elements.empty())
	{
		return { {} };
	}

	T first = *elements.begin();
	elements.erase(first);

	std::vector<std::set<T>> without = combinations(elements);
	std::vector<std::set<T>> with;

	for (auto const & without_first : without)
	{
		auto with_first = without_first;
		with_first.insert(first);
		with.push_back(with_first);
	}

	auto & all = without;
	all.insert(all.end(), with.begin(), with.end());

	return all;
}

} // namespace Combinatorics

// =============================================================================
// Overload
// =============================================================================

#endif
