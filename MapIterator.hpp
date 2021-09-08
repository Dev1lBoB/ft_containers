#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP
#include "Utils.hpp"

namespace ft
{
	template <class Data, class Val, class Node>
	class MapIterator
	{
		public:
			typedef Data		mapped_type;
			typedef	Node		*node_type;
			typedef	Val			&pair_ref;
			typedef Val const	&const_pair_ref;
			typedef Val			*pair_point;
			typedef mapped_type &mapped_ref;
		private:
			node_type Iter;
		public:

			~MapIterator() {}
			MapIterator() : Iter(0) {}
			MapIterator(MapIterator const &it) : Iter(it.Iter) {}
			MapIterator(node_type it) : Iter(it) {}

			MapIterator &operator=(MapIterator const &it)
			{
				Iter = it.Iter;
				return *this;
			}

			pair_ref operator*()
			{
				return Iter->Pair;
			}

			const_pair_ref operator*() const
			{
				return Iter->Pair;
			}

			pair_point operator->() const
			{
				return &Iter->Pair;
			}

			MapIterator &operator++()
			{
				if (Iter->Flag == 1)
				{
					Iter = Iter->Right;
					return *this;
				}
				if (Iter->Right->Flag != 2)
				{
					Iter = Iter->Right;
					while (Iter->Left->Flag == 0)
						Iter = Iter->Left;
				}
				else
				{
					while (Iter->Parent && Iter->Parent->Right == Iter)
						Iter = Iter->Parent;
					Iter = Iter->Parent;
				}
				return *this;
			}
			MapIterator operator++(int)
			{
				MapIterator tmp(*this);
				++(*this);
				return tmp;
			}

			MapIterator &operator--()
			{
				if (Iter->Flag == 1)
				{
					Iter = Iter->Left;
					return *this;
				}
				if (Iter->Right->Flag != 2)
				{
					Iter = Iter->Left;
					while (Iter->Right->Flag == 0)
						Iter = Iter->Right;
				}
				else
				{
					while (Iter->Parent && Iter->Parent->Left == Iter)
						Iter = Iter->Parent;
					Iter = Iter->Parent;
				}
				return *this;
			}

			MapIterator operator--(int)
			{
				MapIterator tmp(*this);
				--(*this);
				return tmp;
			}

			bool operator==(const MapIterator &it)
			{
				return Iter == it.Iter;
			}
			bool operator!=(const MapIterator &it)
			{
				return Iter != it.Iter;
			}
	};

	template <class Data, class Val, class Node>
	class ReverseMapIterator
	{
		public:
			typedef Data		mapped_type;
			typedef	Node		*node_type;
			typedef	Val			&pair_ref;
			typedef Val const	&const_pair_ref;
			typedef Val			*pair_point;
			typedef mapped_type &mapped_ref;
		private:
			node_type Iter;
		public:

			~ReverseMapIterator() {}
			ReverseMapIterator() : Iter(0) {}
			ReverseMapIterator(ReverseMapIterator const &it) : Iter(it.Iter) {}
			ReverseMapIterator(node_type it) : Iter(it) {}

			ReverseMapIterator &operator=(ReverseMapIterator const &it)
			{
				Iter = it.Iter;
				return *this;
			}

			pair_ref operator*()
			{
				return Iter->Pair;
			}

			const_pair_ref operator*() const
			{
				return Iter->Pair;
			}

			pair_point operator->() const
			{
				return &Iter->Pair;
			}

			ReverseMapIterator &operator--()
			{
				if (Iter->Flag == 1)
				{
					Iter = Iter->Right;
					return *this;
				}
				if (Iter->Right->Flag != 2)
				{
					Iter = Iter->Right;
					while (Iter->Left->Flag == 0)
						Iter = Iter->Left;
				}
				else
				{
					while (Iter->Parent && Iter->Parent->Right == Iter)
						Iter = Iter->Parent;
					Iter = Iter->Parent;
				}
				return *this;
			}
			ReverseMapIterator operator++(int)
			{
				ReverseMapIterator tmp(*this);
				++(*this);
				return tmp;
			}

			ReverseMapIterator &operator++()
			{
				if (Iter->Flag == 1)
				{
					Iter = Iter->Left;
					return *this;
				}
				if (Iter->Right->Flag != 2)
				{
					Iter = Iter->Left;
					while (Iter->Right->Flag == 0)
						Iter = Iter->Right;
				}
				else
				{
					while (Iter->Parent && Iter->Parent->Left == Iter)
						Iter = Iter->Parent;
					Iter = Iter->Parent;
				}
				return *this;
			}

			ReverseMapIterator operator--(int)
			{
				ReverseMapIterator tmp(*this);
				--(*this);
				return tmp;
			}

			bool operator==(const ReverseMapIterator &it)
			{
				return Iter == it.Iter;
			}
			bool operator!=(const ReverseMapIterator &it)
			{
				return Iter != it.Iter;
			}
	};
}

#endif
