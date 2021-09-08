#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include "VectorIterator.hpp"

namespace ft
{
	template < typename T, typename A = std::allocator<T> >
	class Vector
	{
		public:
			typedef T			value_type;
			typedef T*			pointer;
			typedef T&			reference;
			typedef const T&	const_reference;
			typedef size_t		size_type;
			typedef A			allocator_type;
			typedef ft::iterator<T> iterator;
			typedef ft::reverse_iterator<T> reverse_iterator;
			typedef ft::iterator<T> const_iterator;
			typedef ft::reverse_iterator<T> const_reverse_iterator;
		private:
			pointer Container;
			size_type Capacity;
			size_type Size;
			allocator_type Allocator;

		public:

//
//	Constructor
//
			explicit Vector(const allocator_type &alloc = allocator_type()) : Capacity(0), Size(0), Allocator(alloc)
			{
				Container = Allocator.allocate(0);
			};
			explicit Vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) : Capacity(0), Size(0), Allocator(alloc)
			{
				Container = Allocator.allocate(Capacity);
				assign(n, val);
			}
			template <class InputIterator>
			Vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type(), char [sizeof(*first)] = NULL) : Capacity(0), Size(0), Allocator(alloc)
			{
				Container = Allocator.allocate(Capacity);
				assign(first, last);
			}
			Vector (const Vector& x) : Capacity(0), Size(0)
			{
				Container = Allocator.allocate(Capacity);
				*this = x;
			}

//
//	Destructor
//

			~Vector()
			{
				Allocator.deallocate(Container, Capacity);
			}
//
//	Copy
//
			Vector &operator=(Vector const &x)
			{
				clear();
				insert(begin(), x.begin(), x.end());
				return *this;
			}
//
//	Iterators
//

			iterator begin()
			{
				return iterator(Container);
			}
			const_iterator begin() const
			{
				return iterator(Container);
			}
			iterator end() 
			{
				return iterator(Container + Size);
			}
			const_iterator end() const
			{
				return iterator(Container + Size);
			}

			reverse_iterator rbegin() const
			{
				return reverse_iterator(Container + Size - 1);
			}
			reverse_iterator rend() const
			{
				return reverse_iterator(Container - 1);
			}

//
// Capacity
//

			size_type size() const
			{
				return Size;
			}

			size_type max_size() const
			{
				return std::numeric_limits<size_type>::max() / sizeof(value_type);
			}

			void resize(size_type n, value_type val = value_type())
			{
				while (n < Size)
					pop_back();
				while (n > Size)
				{
					if (Size + 1 > Capacity)
						reserve(Capacity + 1);
					Container[Size] = val;
					++Size;
				}
			}
			
			size_type capacity()
			{
				return Capacity;
			}

			bool empty() const
			{
				return !Size;
			}

			void reserve(size_type n)
			{
				if (n > Capacity)
				{
					pointer tmp;
					tmp = Allocator.allocate(n);
					std::memcpy(tmp, Container, Size * sizeof(value_type));
					Allocator.deallocate(Container, Capacity);
					Capacity = n;
					Container = tmp;
				}
			}


//
// Element access
//

			reference operator[](size_type pos)
			{
				return Container[pos];
			}

			reference at(size_type n)
			{
				if (n >= Size || n < 0)
					throw std::length_error("vector");
				return Container[n];
			}
			const_reference at(size_type n) const
			{
				if (n >= Size || n < 0)
					throw std::length_error("vector");
				return Container[n];
			}

			reference front()
			{
				return Container[0];
			}
			const_reference front() const
			{
				return Container[0];
			}

			reference back()
			{
				return Container[Size - 1];
			}
			const_reference back() const
			{
				return Container[Size - 1];
			}

//
// Modifiers
//

			template <class InputIterator>
  			void assign(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), char [sizeof(*first)] = NULL )
			{
				static_cast<void>(alloc);
				clear();
				insert(begin(), first, last);
			}
			
			void assign(size_type n, const value_type &val)
			{
				clear();
				insert(begin(), n, val);
			}

			void push_back(const value_type &val)
			{
				if (Size + 1 > Capacity)
				{
					reserve(Capacity ? Capacity << 1 : 1);
				}
				Allocator.construct(&Container[Size], val);
				++Size;
			};

			void pop_back()
			{
				if (Size)
				{
					Container[Size - 1].~T();
					--Size;
				}
			}
			
			iterator insert(iterator position, const value_type &val)
			{
				size_type i = 0;
				iterator it_begin = begin();
				i = &(*position) - &(*Container);
				if (Size == Capacity)
					reserve(Capacity == 0 ? 1 : Capacity << 1);
				std::memmove(Container + i + 1, Container + i, (Size - i) * sizeof(value_type));
				Allocator.construct(&Container[i], val);
				++Size;
				return iterator(Container + i);
			}

			void insert(iterator position, size_type n, const value_type &val)
			{
				while (n--)
					position = insert(position, val);
			}

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), char [sizeof(*first)] = NULL)
			{
				static_cast<void>(alloc);
				while (first != last)
				{
					position = insert(position, *first);
					++position;
					++first;
				}
			}

			iterator erase(iterator position)
			{
				int pos = &(*position) - &(*begin());
				position->~value_type();
				std::memmove(Container + pos, Container + pos + 1, sizeof(value_type) * (Size - pos));
				--Size;
				return position;
			}

			iterator erase(iterator first, iterator last)
			{
				while (first != last)
				{
					erase(first);
					--last;
				}
				return first;
			}

			void swap(Vector &x)
			{
				if (Allocator != x.Allocator)
					throw std::exception();

				
				size_type tmp = Size;
				Size = x.Size;
				x.Size = tmp;

				tmp = Capacity;
				Capacity = x.Capacity;
				x.Capacity = tmp;

				pointer Tmp = Container;
				Container = x.Container;
				x.Container = Tmp;
			}

			void clear()
			{
				while (Size)
					erase(end());
			}

//
//	Allocator
//

			allocator_type get_allocator() const
			{
				return Allocator;
			}

//
//	Operators overloads
//

		bool operator==(Vector const &x)
		{
			if (Size != x.size())
				return false;

			size_type i = -1;
			while (++i < Size)
				if (at(i) != x.at(i))
					return false;
			return true;
		}
		
		bool operator!=(Vector const &x)
		{
			return !(*this == x);
		}

		bool operator>(Vector const &x)
		{
			int size = Size > x.size() ? Size : x.size();
			int i = -1;

			while (++i < size)
				if (at(i) != x.at(i))
					return at(i) > x.at(i);
			return Size < x.size();
		}
		bool operator>=(Vector const &x)
		{
			return *this == x || *this > x;
		}
		bool operator<(Vector const &x)
		{
			return !(*this >= x);
		}
		bool operator<=(Vector const &x)
		{
			return !(*this > x);
		}
	};

//
//	Non member function overload
//

	template <class T, class A>
	void swap(Vector<T, A> &x, Vector<T, A> &y)
	{
		x.swap(y);
	}
}

#endif
