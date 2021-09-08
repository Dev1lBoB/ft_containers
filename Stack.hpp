#ifndef STACK_HPP
# define STACK_HPP
# include <iostream>
# include "Vector.hpp"

namespace ft
{
	template < class T, class Container = ft::Vector<T> >
	class Stack
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;
		protected:
			container_type c;
		public:

//
// Constructor
//
		explicit Stack(const container_type &ctnr = container_type()): c(ctnr){}

		Stack(Stack const &st)
		{
			*this = st;
		}
//
// Destructor
//
		~Stack(){}

//
// Copy
//
		Stack &operator=(Stack const &st)
		{
			c = st.c;
			return *this;
		}
//
// Member Functions
//
		bool empty() const
		{
			return c.empty();
		}

		size_type size() const
		{
			return c.size();
		}

		value_type &top()
		{
			return c.back();
		}
		const value_type &top() const
		{
			return c.back();
		}
		
		void push(const value_type &val)
		{
			c.push_back(val);
		}

		void pop()
		{
			c.pop_back();
		}

//
// Operators overloads
//
		bool operator==(Stack const &st)
		{
			return c == st.c;
		}
		bool operator!=(Stack const &st)
		{
			return c != st.c;
		}
		bool operator>(Stack const &st)
		{
			return c > st.c;
		}
		bool operator<(Stack const &st)
		{
			return c < st.c;
		}
		bool operator>=(Stack const &st)
		{
			return c >= st.c;
		}
		bool operator<=(Stack const &st)
		{
			return c <= st.c;
		}
	};
}

#endif
