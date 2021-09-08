#ifndef HEADER_HPP
# define HEADER_HPP
# include "Vector.hpp"
# include "vector"
#include <sstream>

	template <class T>
	std::stringstream	&PrintContainer(T &Con, std::stringstream &out)
	{
		typename T::iterator start = Con.begin();
		typename T::iterator end = Con.end();

		out.str("");
		while (start != end)
		{
			out << *start << ' ';
			start++;
		}
		out << std::endl;
		return out;
	}

	template <class T>
	std::stringstream	&PrintMap(T &Map, std::stringstream &out)
	{
		typename T::iterator start = Map.begin();
		typename T::iterator end = Map.end();

		out.str("");
		while (start != end)
		{
			out << "<" << start->first << ':' << start->second << "> ";
			start++;
		}
		out << std::endl;
		return out;
	}

#endif
