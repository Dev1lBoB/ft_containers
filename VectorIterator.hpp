#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

namespace ft
{
	template <class T>
	class iterator
	{
		public:
			typedef T	value_type;
			typedef T&	reference;
			typedef T*	pointer;
			typedef typename std::ptrdiff_t diff_type;
		protected:
			pointer Ptr;
		public:
			iterator(){}

			iterator(const iterator &it)
			{
				*this = it;
			}
			~iterator(){}

			iterator(pointer ptr): Ptr(ptr){}

			iterator &operator=(iterator const &it)
			{
				Ptr = it.Ptr;
				return *this;
			}

			iterator &operator++()
			{
				++Ptr;
				return *this;
			}
			iterator operator++(int)
			{
				iterator tmp(*this);
				++Ptr;
				return tmp;
			}

			iterator &operator--()
			{
				--Ptr;
				return *this;
			}
			iterator operator--(int)
			{
				iterator tmp(*this);
				--Ptr;
				return tmp;
			}

			bool operator==(iterator it)
			{
				return Ptr == it.Ptr;
			}

			bool operator!=(iterator it)
			{
				return Ptr != it.Ptr;
			}

			bool operator>=(iterator it)
			{
				return Ptr >= it.Ptr;
			}

			bool operator>(iterator it)
			{
				return Ptr > it.Ptr;
			}

			bool operator<=(iterator it)
			{
				return Ptr <= it.Ptr;
			}

			bool operator<(iterator it)
			{
				return Ptr < it.Ptr;
			}

			value_type &operator*()
			{
				return *Ptr;
			}

			value_type *operator->()
			{
				return Ptr;
			}

			iterator operator+(int n) const
			{
				iterator tmp(*this);
				tmp += n;
				return tmp;
			}

			iterator operator-(int n) const
			{
				iterator tmp(*this);
				tmp -= n;
				return tmp;
			}
			diff_type operator-(iterator n) const
			{
				return Ptr - n.Ptr;
			}

			iterator &operator+=(int n)
			{
				while (n < 0)
				{
					--(*this);
					++n;
				}
				while (n > 0)
				{
					++(*this);
					--n;
				}
				return *this;
			}

			iterator &operator-=(int n)
			{
				while (n > 0)
				{
					--(*this);
					--n;
				}
				while (n < 0)
				{
					++(*this);
					++n;
				}
				return *this;
			}
			value_type &operator[](int n) const
			{
				return *(*this + n);
			}
	};

	template <class T>
	class reverse_iterator
	{
		public:
			typedef T	value_type;
			typedef T&	reference;
			typedef T*	pointer;
		protected:
			pointer Ptr;
		public:
			reverse_iterator(){}

			reverse_iterator(const reverse_iterator &it)
			{
				*this = it;
			}
			~reverse_iterator(){}

			reverse_iterator(pointer ptr): Ptr(ptr){}

			reverse_iterator &operator=(reverse_iterator const &it)
			{
				Ptr = it.Ptr;
				return *this;
			}

			reverse_iterator &operator++()
			{
				--Ptr;
				return *this;
			}
			reverse_iterator operator++(int)
			{
				reverse_iterator tmp(*this);
				--Ptr;
				return tmp;
			}

			reverse_iterator &operator--()
			{
				++Ptr;
				return *this;
			}
			reverse_iterator operator--(int)
			{
				reverse_iterator tmp(*this);
				++Ptr;
				return tmp;
			}

			bool operator==(reverse_iterator it)
			{
				return Ptr == it.Ptr;
			}

			bool operator!=(reverse_iterator it)
			{
				return Ptr != it.Ptr;
			}

			bool operator>=(reverse_iterator it)
			{
				return Ptr >= it.Ptr;
			}

			bool operator>(reverse_iterator it)
			{
				return Ptr > it.Ptr;
			}

			bool operator<=(reverse_iterator it)
			{
				return Ptr <= it.Ptr;
			}

			bool operator<(reverse_iterator it)
			{
				return Ptr < it.Ptr;
			}

			value_type &operator*()
			{
				return *Ptr;
			}

			value_type *operator->()
			{
				return Ptr;
			}

			reverse_iterator operator+(int n) const
			{
				reverse_iterator tmp(*this);
				tmp += n;
				return tmp;
			}

			reverse_iterator operator-(int n) const
			{
				reverse_iterator tmp(*this);
				tmp -= n;
				return tmp;
			}

			reverse_iterator &operator+=(int n)
			{
				while (n < 0)
				{
					--(*this);
					++n;
				}
				while (n > 0)
				{
					++(*this);
					--n;
				}
				return *this;
			}

			reverse_iterator &operator-=(int n)
			{
				while (n > 0)
				{
					--(*this);
					--n;
				}
				while (n < 0)
				{
					++(*this);
					++n;
				}
				return *this;
			}
			value_type &operator[](int n) const
			{
				return *(*this + n);
			}
	};

	template <class T>
	class const_iterator
	{
		public:
			typedef T	value_type;
			typedef T&	reference;
			typedef T*	pointer;
		private:
			pointer Ptr;
		public:
			const_iterator(){}
			const_iterator(pointer ptr)
			{
				Ptr = ptr;
			}
			const_iterator(const_iterator const &it)
			{
				*this = it;
			}
			~const_iterator(){}
			const_iterator &operator=(const_iterator const &it)
			{
				Ptr = it.Ptr;
				return *this;
			}
			const value_type &operator*() 
			{
				return Ptr;
			}
			const value_type &operator[](int n) const
			{
				return *(*this + n);
			}

	};

	template <class T>
	class const_reverse_iterator
	{
		public:
			typedef T	value_type;
			typedef T&	reference;
			typedef T*	pointer;
		private:
			pointer Ptr;
		public:
			const_reverse_iterator(){}
			const_reverse_iterator(pointer ptr)
			{
				Ptr = ptr;
			}
			const_reverse_iterator(const_reverse_iterator const &it)
			{
				*this = it;
			}
			~const_reverse_iterator(){}
			const_reverse_iterator &operator=(const_reverse_iterator const &it)
			{
				Ptr = it.Ptr;
				return *this;
			}
			const value_type &operator*() 
			{
				return Ptr;
			}
			const value_type &operator[](int n) const
			{
				return *(*this + n);
			}

	};


	template <typename T>
	iterator<T>	operator+(int num, iterator<T> it){ return it + num; }
	template <typename T>
	const_iterator<T>	operator+(int num, const_iterator<T> it){ return it + num; }
	template <typename T>
	reverse_iterator<T>	operator+(int num, reverse_iterator<T> it){ return it + num; }
	template <typename T>
	const_reverse_iterator<T>	operator+(int num, const_reverse_iterator<T> it){ return it + num; }
}

#endif
