#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{

	template <class T> struct less : std::binary_function <T,T,bool> {
	   bool operator() (const T& x, const T& y) const {return x<y;}
	};
	template <class Key, class Val>
	class	pair
	{
		public:
			Key	first;
			Val	second;
			pair(const Key &key, const Val &val): first(key), second(val){}
			pair(): first(), second(){}
		template<class P1, class P2>
		pair(const pair<P1, P2> &other): first(other.first), second(other.second){}
		pair &operator=(const pair& x)
		{
			first = x.first;
			second = x.second;
			return *this;
		}
		~pair(){};
	};

	template <class T1, class T2>
		bool operator==(const ft::pair<T1, T2> &l, const ft::pair<T1, T2> &r)
		{
			return l.first == r.first && l.second && r.second;
		}

	template <class T1, class T2>
		bool operator!=(const ft::pair<T1, T2> &l, const ft::pair<T1, T2> &r)
		{
			return !(l == r);
		}
}
#endif
