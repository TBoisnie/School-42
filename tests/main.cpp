/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 22:00:18 by tboisnie          #+#    #+#             */
/*   Updated: 2021/01/04 16:40:12 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "../srcs/Utils.hpp"
#include "../srcs/Vector.hpp"
#include "../srcs/List.hpp"
#include "../srcs/Queue.hpp"
#include "../srcs/Stack.hpp"
#include "../srcs/Map.hpp"

/**
 * Tools
 */
template<typename T>
void printVector(const ft::Vector<T> & v)
{
	std::cout << v.size() << " / " << v.capacity() << " :: ";
	for (typename ft::Vector<T>::const_iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " | ";
	std::cout << std::endl;
}

template<typename T>
void printList(const ft::List<T> & l)
{
	std::cout << l.size() << " :: ";
	for (typename ft::List<T>::const_iterator it = l.begin(); it != l.end(); ++it)
		std::cout << *it << " | ";
	std::cout << std::endl;
}

template<typename K, typename M, typename C>
void printMap(const ft::Map<K, M, C> & m)
{
	std::cout << m.size() << " :: ";
	for (typename ft::Map<K, M, C>::const_iterator it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << " = " << it->second << " | ";
	std::cout << std::endl;
}

/**
 * Used functions to test
 */
bool list_remove_if(int a)
{
	return a > 105;
}

bool list_unique(int a, int b)
{
	return b - a > 2;
}

bool list_compare(int a, int b)
{
	if ((a % 2) == (b % 2))
		return a < b;
	return a % 2 == 0;
}

/**
 * Main
 */
int main ( void )
{
	/**
	 * Vector
	 */
	{
		std::cout << "-- -------------------------------------" << std::endl;
		std::cout << "-- Vector" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		typedef ft::Vector<int> vect;

		/**
		 * Constructors & Assignation
		 */
		vect v_a;
		vect v_b(5, 1);
		const vect v_c(++v_b.begin(), v_b.begin() + 3);
		const vect v_d(v_c);

		v_a = v_c;

		printVector(v_a);
		printVector(v_b);
		printVector(v_c);
		printVector(v_d);

		/**
		 * Iterators
		 */
		std::cout << std::endl;
		std::cout << "-- Iterator" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		for (vect::iterator it = v_a.begin(); it != v_a.end(); ++it)
			*it = -2;

		v_a.push_back(9);

		// Can not modify with const_iterator
		for (vect::const_iterator it = v_a.begin(); it != v_a.end(); ++it)
			std::cout << *it << " | "; // *it = -2;
		std::cout << std::endl;

		v_a.pop_back();

		for (vect::reverse_iterator it = v_a.rbegin(); it != v_a.rend(); ++it)
			*it = -3;

		v_a.push_back(9);

		// Can not modify with const_reverse_iterator
		for (vect::const_reverse_iterator it = v_a.rbegin(); it != v_a.rend(); ++it)
			std::cout << *it << " | "; // *it = -4;
		std::cout << std::endl;

		// Can not use iterator or reverse_iterator with const Vector
		// for (vect::iterator it = v_c.begin(); it != v_c.end(); ++it)
		// 	*it = -5;

		/**
		 * Capacity
		 */
		std::cout << std::endl;
		std::cout << "-- Capacity" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		std::cout << "Size: "		<< v_a.size()		<< std::endl;
		std::cout << "Max size: "	<< v_a.max_size()	<< std::endl;
		std::cout << "Capacity: "	<< v_a.capacity()	<< std::endl;
		std::cout << "Empty: "		<< v_a.empty()		<< std::endl;

		std::cout << "--Resize--" << std::endl;
		v_a.resize(15, 2);
			printVector(v_a);
		v_a.resize(10, 3);
			printVector(v_a);

		std::cout << "--Reserve--" << std::endl;
		v_a.reserve(20);
			printVector(v_a);

		/**
		 * Elements Access
		 */
		std::cout << std::endl;
		std::cout << "-- Elements Access" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		std::cout << "front(): "	<< v_a.front()	<< std::endl;
		std::cout << "back(): "		<< v_a.back()	<< std::endl;
		std::cout << "[2]: "		<< v_a[2]		<< std::endl;
		std::cout << "at(2): "		<< v_a.at(2)	<< std::endl;

		std::cout << "at(50): ";
		try
		{
			std::cout << v_a.at(50)	<< std::endl;
		}
		catch (const std::exception & e)
		{
			std::cout << e.what()	<< std::endl;
		}

		/**
		 * Modifiers
		 */
		std::cout << std::endl;
		std::cout << "-- Modifiers" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		std::cout << "--Assign--" << std::endl;
		v_a.assign(10, 4);
			printVector(v_a);
		v_a.assign(v_b.begin() + 1, v_b.end() - 2);
			printVector(v_a);

		std::cout << "--Insert--" << std::endl;
		v_a.insert(++v_a.begin(), 999);
			printVector(v_a);
		v_a.insert(v_a.begin() + 2, 4, 777);
			printVector(v_a);
		v_a.insert(v_a.end() - 2, ++v_b.begin(), v_b.begin() + 3);
			printVector(v_a);

		std::cout << "--Push/Pop Back--" << std::endl;
		v_a.push_back(555);
			printVector(v_a);
		v_a.pop_back();
			printVector(v_a);

		std::cout << "--Erase--" << std::endl;
		v_a.erase(--v_a.end());
			printVector(v_a);
		v_a.erase(v_a.begin() + 2, v_a.end() - 3);
			printVector(v_a);

		std::cout << "--Clear--" << std::endl;
		v_a.clear();
			printVector(v_a);

		/**
		 * Relational Operators
		 */
		std::cout << std::endl;
		std::cout << "-- Relational Operators" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		// v_a = v_c;

		std::cout << "v_a == v_c : " << (v_a == v_c) << std::endl;
		std::cout << "v_a != v_c : " << (v_a != v_c) << std::endl;
		std::cout << "v_a <  v_c : " << (v_a <  v_c) << std::endl;
		std::cout << "v_a <= v_c : " << (v_a <= v_c) << std::endl;
		std::cout << "v_a >  v_c : " << (v_a >  v_c) << std::endl;
		std::cout << "v_a >= v_c : " << (v_a >= v_c) << std::endl;

	}; // End - Vector tests

	/**
	 * List
	 */
	{
		std::cout << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;
		std::cout << "-- List" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		typedef ft::List<int> list;

		/**
		 * Constructors & Assignation
		 */
		list l_a;
		list l_b(5, 1);
		const list l_c(++l_b.begin(), --l_b.end());
		const list l_d(l_c);

		l_a = l_c;

		printList(l_a);
		printList(l_b);
		printList(l_c);
		printList(l_d);

		/**
		 * Iterators
		 */
		std::cout << std::endl;
		std::cout << "-- Iterator" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		for (list::iterator it = l_a.begin(); it != l_a.end(); ++it)
			*it = -1;

		l_a.push_back(9);

		// Can not modify with const_iterator
		for (list::const_iterator it = l_a.begin(); it != l_a.end(); ++it)
			std::cout << *it << " | "; // *it = -2;
		std::cout << std::endl;

		l_a.pop_back();

		for (list::reverse_iterator it = l_a.rbegin(); it != l_a.rend(); ++it)
			*it = -3;

		l_a.push_back(9);

		// Can not modify with const_reverse_iterator
		for (list::const_reverse_iterator it = l_a.rbegin(); it != l_a.rend(); ++it)
			std::cout << *it << " | "; // *it = -4;
		std::cout << std::endl;

		// Can not use iterator or reverse_iterator with const List
		// for (list::iterator it = l_c.begin(); it != l_c.end(); ++it)
		// 	*it = -7;

		/**
		 * Capacity
		 */
		std::cout << std::endl;
		std::cout << "-- Capacity" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		std::cout << "Max size: "	<< l_a.max_size()	<< std::endl;
		std::cout << "Size: "		<< l_a.size()		<< std::endl;
		std::cout << "Empty: "		<< l_a.empty()		<< std::endl;

		std::cout << "--Resize--" << std::endl;
		l_a.resize(15, 2);
			printList(l_a);

		/**
		 * Element Access
		 */
		std::cout << std::endl;
		std::cout << "-- Element Access" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		std::cout << "front(): "	<< l_a.front()		<< std::endl;
		std::cout << "back(): "		<< l_a.back()		<< std::endl;

		/**
		 * Modifiers
		 */
		std::cout << std::endl;
		std::cout << "-- Modifiers" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;
		list::iterator ret_it;

		std::cout << "--Assign--" << std::endl;
		l_a.assign(10, 4);
			printList(l_a);
		l_a.assign(++l_b.begin(), --l_b.end());
			printList(l_a);

		std::cout << "--Insert--" << std::endl;
		ret_it = l_a.insert(++l_a.begin(), 999);
		std::cout << "insert(++begin, 999): " << *ret_it << std::endl;
			printList(l_a);
		l_a.insert(l_a.begin(), 4, 777);
			printList(l_a);
		l_a.insert(l_a.end(), l_b.begin(), l_b.end());
			printList(l_a);

		std::cout << "--Push/Pop Front--" << std::endl;
		l_a.push_front(555);
			printList(l_a);
		l_a.pop_front();
			printList(l_a);

		std::cout << "--Push/Pop Back--" << std::endl;
		l_a.push_back(555);
			printList(l_a);
		l_a.pop_back();
			printList(l_a);

		std::cout << "--Erase--" << std::endl;
		ret_it = l_a.erase(++(++l_a.begin()));
		std::cout << "erase(begin+2): " << *ret_it << std::endl;
			printList(l_a);
		ret_it = l_a.erase(++l_a.begin(), --l_a.end());
		std::cout << "erase(++begin, --end): " << *ret_it << std::endl;
			printList(l_a);

		std::cout << "--Clear--" << std::endl;
		l_a.clear();
			printList(l_a);

		/**
		 * Operations
		 */
		std::cout << std::endl;
		std::cout << "-- Operations" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		// Modify l_a & l_b to "visualize" result
		for (int i = 110; i >= 100; i -= 2)
			l_a.push_front(i);
		// End - Modification

		std::cout << "--Splice--" << std::endl;
		l_a.splice(--l_a.end(), l_b, ++l_b.begin(), --l_b.end());
			printList(l_a);
		l_a.splice(l_a.begin(), l_b, ++l_b.begin());
			printList(l_a);
		l_a.splice(++l_a.begin(), l_b);
			printList(l_a);

		std::cout << "--Remove--" << std::endl;
		l_a.remove(104);
			printList(l_a);
		l_a.remove_if(&list_remove_if);
			printList(l_a);

		std::cout << "--Unique--" << std::endl;
		l_a.unique();
			printList(l_a);
		l_a.unique(&list_unique);
			printList(l_a);

		// Modify l_a & l_b to "visualize" result
		l_a.clear();
		for (int i = 110; i > 100; --i)
			l_a.push_front(i);
		l_b.clear();
		for (int i = 105; i > 100; --i)
			l_b.push_front(i);
		// End - Modification

		std::cout << "--Sort & Merge--" << std::endl;
		l_a.sort();
			printList(l_a);
		l_b.sort();
			printList(l_b);
		l_a.merge(l_b);
			printList(l_a);
			printList(l_b);

		std::cout << "--Sort & Merge Compare--" << std::endl;
		// Modify l_a & l_b to "visualize" result
		l_a.clear();
		for (int i = 110; i > 100; --i)
			l_a.push_front(i);
		l_b.clear();
		for (int i = 105; i > 100; --i)
			l_b.push_front(i);
		// End - Modification

		l_a.sort(&list_compare);
			printList(l_a);
		l_b.sort(&list_compare);
			printList(l_b);
		l_a.merge(l_b, &list_compare);
			printList(l_a);
			printList(l_b);

		std::cout << "--Reverse--" << std::endl;
		l_a.reverse();
			printList(l_a);

		/**
		 * Relational Operators
		 */
		std::cout << std::endl;
		std::cout << "-- Relational Operators" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		// l_a = l_c;

		std::cout << "l_a == l_c : " << (l_a == l_c) << std::endl;
		std::cout << "l_a != l_c : " << (l_a != l_c) << std::endl;
		std::cout << "l_a <  l_c : " << (l_a <  l_c) << std::endl;
		std::cout << "l_a <= l_c : " << (l_a <= l_c) << std::endl;
		std::cout << "l_a >  l_c : " << (l_a >  l_c) << std::endl;
		std::cout << "l_a >= l_c : " << (l_a >= l_c) << std::endl;

	}; // End - List tests

	/**
	 * Map
	 */
	{
		std::cout << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;
		std::cout << "-- Map" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		typedef ft::Map<int, std::string> map;
		typedef ft::Map<int, std::string, std::greater<int> > map_reversed;

		/**
		 * Constructors
		 */
		map m_a;
		map_reversed m_b;

		// Insert value
		m_b.insert(std::make_pair(3, "\"3\""));
		m_b.insert(std::make_pair(7, "\"7\""));
		m_b.insert(std::make_pair(-1, "\"-1\""));
		m_b.insert(std::make_pair(5, "\"5\""));
		m_b.insert(std::make_pair(4, "\"4\""));
		m_b.insert(std::make_pair(9, "\"9\""));

		const map m_c(++m_b.begin(), --m_b.end());
		const map_reversed m_d(m_b);

		m_a = m_c;

		printMap(m_a);
		printMap(m_b);
		printMap(m_c);
		printMap(m_d);

		/**
		 * Iterators
		 */
		std::cout << std::endl;
		std::cout << "-- Iterator" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		for (map::iterator it = m_a.begin(); it != m_a.end(); ++it)
			it->second += "(it)";

		// Can not modify with const_iterator
		for (map::const_iterator it = m_a.begin(); it != m_a.end(); ++it)
			std::cout << it->first << "=" << it->second << " | "; // it->second = "fail";
		std::cout << std::endl;

		for (map::reverse_iterator it = m_a.rbegin(); it != m_a.rend(); ++it)
			it->second += "(rit)";

		// Can not modify with const_reverse_iterator
		for (map::const_reverse_iterator it = m_a.rbegin(); it != m_a.rend(); ++it)
			std::cout << it->first << "=" << it->second << " | "; // it->second = "fail";
		std::cout << std::endl;

		// Can not use iterator or reverse_iterator with const Map
		// for (map::iterator it = m_c.begin(); it != m_c.end(); ++it)
		// 	it->second = "fail";

		/**
		 * Capacity
		 */
		std::cout << std::endl;
		std::cout << "-- Capacity" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		std::cout << "Size: "		<< m_a.size()		<< std::endl;
		std::cout << "Max size: "	<< m_a.max_size()	<< std::endl;
		std::cout << "Empty: "		<< m_a.empty()		<< std::endl;

		/**
		 * Element Access
		 */
		std::cout << std::endl;
		std::cout << "-- Element Access" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		std::cout << "[4]: "		<< m_a[4]		<< std::endl;
		std::cout << "[90] (does not exist): "		<< m_a[90]		<< std::endl;
		m_a[90] = "\"90\"";
		std::cout << "[90] (updated): "		<< m_a[90]		<< std::endl;

		/**
		 * Modifier
		 */
		std::cout << std::endl;
		std::cout << "-- Modifiers" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		std::cout << "--Insert--" << std::endl;
		std::pair<map::iterator, bool> res;
		map::iterator res_it;

		// Already exists, do nothing
		res = m_a.insert(std::make_pair(4, "\"4\""));
		std::cout << "insert(4): "  << res.second << " | " << res.first->first << "=" << res.first->second << std::endl;
			printMap(m_a);
		res = m_a.insert(std::make_pair(15, "\"15\""));
		std::cout << "insert(15): "  << res.second << " | " << res.first->first << "=" << res.first->second << std::endl;
			printMap(m_a);
		res_it = m_a.insert(++m_a.begin(), std::make_pair(-12, "\"-12\""));
		std::cout << "insert(pos, -12): " << res_it->first << "=" << res_it->second << std::endl;
			printMap(m_a);

		// Temporary container to test iterator
		ft::Vector<map::value_type> * ctnr = new ft::Vector<map::value_type>();
		ctnr->push_back(std::make_pair(19, "\"19\"(from list)"));
		ctnr->push_back(std::make_pair(-17, "\"-17\"(from list)"));

		m_a.insert(ctnr->begin(), ctnr->end());
			printMap(m_a);

		delete ctnr;

		/**
		 * Observers
		 */
		std::cout << std::endl;
		std::cout << "-- Observers" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		map::key_compare ret_kcmp = m_a.key_comp();
		map::value_compare ret_vcmp = m_a.value_comp();

		std::cout << "key_comp(): " << ret_kcmp(m_a.begin()->first, (--m_a.end())->first) << std::endl;
		std::cout << "value_comp(): " << ret_vcmp(*m_a.begin(), *--m_a.end()) << std::endl;

		/**
		 * Operations
		 */
		std::cout << std::endl;
		std::cout << "-- Operations" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		std::cout << "find(-12): "		<< m_a.find(-12)->second	<< std::endl;
		std::cout << "count(0): "		<< m_a.count(0)				<< std::endl;
		std::cout << "count(90): "		<< m_a.count(90)			<< std::endl;

		map::iterator lb;
		map::iterator ub;

		lb = m_a.lower_bound(3);
		std::cout << "lower_bound(3): " << lb->first << " = " << lb->second << std::endl;
		ub = m_a.upper_bound(3);
		std::cout << "upper_bound(3): " << ub->first << " = " << ub->second << std::endl;

		lb = m_a.lower_bound(1);
		std::cout << "lower_bound(1): " << lb->first << " = " << lb->second << std::endl;
		ub = m_a.upper_bound(1);
		std::cout << "upper_bound(1): " << ub->first << " = " << ub->second << std::endl;

		/**
		 * Modifier (2)
		 */
		std::cout << std::endl;
		std::cout << "-- Modifiers (2)" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		std::cout << "--Erase--" << std::endl;
		std::cout << "erase(9): " << m_a.erase(9) << std::endl;
			printMap(m_a);
		m_a.erase(++m_a.begin());
			printMap(m_a);
		m_a.erase(++m_a.begin(), --m_a.end());
			printMap(m_a);

		std::cout << "--Clear--" << std::endl;
		m_a.clear();
			printMap(m_a);

	}; // End - Map tests

	/**
	 * Stack
	 */
	{
		std::cout << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;
		std::cout << "-- Stack" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		typedef ft::Stack<std::string> stack;
		typedef ft::Stack<std::string, ft::Vector<std::string> > stack_vectored;

		/**
		 * Constructors & Assignation
		 */
		// Temporary container for copy
		ft::Vector<std::string> * tmp_vect = new ft::Vector<std::string>(6, "Vect Stack");
		ft::List<std::string> * tmp_list = new ft::List<std::string>(6, "List Stack");

		stack s_a;
		stack_vectored s_b(*tmp_vect);
		const stack s_c(*tmp_list);
		const stack_vectored s_d(s_b);

		delete tmp_vect;
		delete tmp_list;

		s_a = s_c;

		/**
		 * Capacity
		 */
		std::cout << std::endl;
		std::cout << "-- Capacity" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		std::cout << "Empty: "		<< s_a.empty()		<< std::endl;
		std::cout << "Size: "		<< s_a.size()		<< std::endl;

		/**
		 * Element Access & Modifiers
		 */
		std::cout << std::endl;
		std::cout << "-- Element Access & Modifiers" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		s_a.push("World");
		s_a.push("Hello");

		std::cout << "Size: "	<< s_a.size()		<< std::endl;
		std::cout << "top(): "	<< s_a.top()		<< std::endl;

		s_a.pop();

		std::cout << "Size: "	<< s_a.size()		<< std::endl;
		std::cout << "top(): "	<< s_a.top()		<< std::endl;

		s_a.pop();
		s_a.pop();
		s_a.pop();

		std::cout << "Size: "	<< s_a.size()		<< std::endl;
		std::cout << "top(): "	<< s_a.top()		<< std::endl;

		/**
		 * Relational Operators
		 */
		std::cout << std::endl;
		std::cout << "-- Relational Operators" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		// s_a = s_c;

		std::cout << "s_a == s_c : " << (s_a == s_c) << std::endl;
		std::cout << "s_a != s_c : " << (s_a != s_c) << std::endl;
		std::cout << "s_a <  s_c : " << (s_a <  s_c) << std::endl;
		std::cout << "s_a <= s_c : " << (s_a <= s_c) << std::endl;
		std::cout << "s_a >  s_c : " << (s_a >  s_c) << std::endl;
		std::cout << "s_a >= s_c : " << (s_a >= s_c) << std::endl;

	}; // End - Stack tests

	/**
	 * Queue
	 */
	{
		std::cout << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;
		std::cout << "-- Queue" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		typedef ft::Queue<std::string> queue;
		typedef ft::Queue<std::string, ft::Vector<std::string> > queue_vectored;

		/**
		 * Constructors & Assignation
		 */
		// Temporary container for copy
		ft::Vector<std::string> * tmp_vect = new ft::Vector<std::string>(6, "Vect Queue");
		ft::List<std::string> * tmp_list = new ft::List<std::string>(6, "List Queue");

		queue q_a;
		queue_vectored q_b(*tmp_vect);
		const queue q_c(*tmp_list);
		const queue_vectored q_d(q_b);

		delete tmp_vect;
		delete tmp_list;

		q_a = q_c;

		/**
		 * Capacity
		 */
		std::cout << std::endl;
		std::cout << "-- Capacity" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		std::cout << "Empty: "		<< q_a.empty()		<< std::endl;
		std::cout << "Size: "		<< q_a.size()		<< std::endl;

		/**
		 * Element Access & Modifiers
		 */
		std::cout << std::endl;
		std::cout << "-- Element Access & Modifiers" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		q_a.pop();
		q_a.pop();
		q_a.pop();
		q_a.pop();
		q_a.pop();
		q_a.push("World");
		q_a.push("Hello");

		std::cout << "Size: "		<< q_a.size()	<< std::endl;
		std::cout << "front(): "	<< q_a.front()	<< std::endl;
		std::cout << "back(): "		<< q_a.back()	<< std::endl;

		q_a.pop();

		std::cout << "Size: "		<< q_a.size()	<< std::endl;
		std::cout << "front(): "	<< q_a.front()	<< std::endl;
		std::cout << "back(): "		<< q_a.back()	<< std::endl;

		q_a.pop();

		std::cout << "Size: "		<< q_a.size()	<< std::endl;
		std::cout << "front(): "	<< q_a.front()	<< std::endl;
		std::cout << "back(): "		<< q_a.back()	<< std::endl;

		/**
		 * Relational Operators
		 */
		std::cout << std::endl;
		std::cout << "-- Relational Operators" << std::endl;
		std::cout << "-- -------------------------------------" << std::endl;

		// q_a = q_c;

		std::cout << "q_a == q_c : " << (q_a == q_c) << std::endl;
		std::cout << "q_a != q_c : " << (q_a != q_c) << std::endl;
		std::cout << "q_a <  q_c : " << (q_a <  q_c) << std::endl;
		std::cout << "q_a <= q_c : " << (q_a <= q_c) << std::endl;
		std::cout << "q_a >  q_c : " << (q_a >  q_c) << std::endl;
		std::cout << "q_a >= q_c : " << (q_a >= q_c) << std::endl;

	}; // End - Queue tests


	return 0;
}