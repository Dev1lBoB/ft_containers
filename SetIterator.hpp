#ifndef SETITERATOR_HPP
#define SETITERATOR_HPP
#include "Utils.hpp"

namespace ft
{
	template <class Data, class Val, class Node>
	class SetIterator
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

			~SetIterator() {}
			SetIterator() : Iter(0) {}
			SetIterator(SetIterator const &it) : Iter(it.Iter) {}
			SetIterator(node_type it) : Iter(it) {}

			SetIterator &operator=(SetIterator const &it)
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

			SetIterator &operator++()
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
			SetIterator operator++(int)
			{
				SetIterator tmp(*this);
				++(*this);
				return tmp;
			}

			SetIterator &operator--()
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

			SetIterator operator--(int)
			{
				SetIterator tmp(*this);
				--(*this);
				return tmp;
			}

			bool operator==(const SetIterator &it)
			{
				return Iter == it.Iter;
			}
			bool operator!=(const SetIterator &it)
			{
				return Iter != it.Iter;
			}
	};

	template <class Data, class Val, class Node>
	class ReverseSetIterator
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

			~ReverseSetIterator() {}
			ReverseSetIterator() : Iter(0) {}
			ReverseSetIterator(ReverseSetIterator const &it) : Iter(it.Iter) {}
			ReverseSetIterator(node_type it) : Iter(it) {}

			ReverseSetIterator &operator=(ReverseSetIterator const &it)
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

			ReverseSetIterator &operator--()
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
			ReverseSetIterator operator++(int)
			{
				ReverseSetIterator tmp(*this);
				++(*this);
				return tmp;
			}

			ReverseSetIterator &operator++()
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

			ReverseSetIterator operator--(int)
			{
				ReverseSetIterator tmp(*this);
				--(*this);
				return tmp;
			}

			bool operator==(const ReverseSetIterator &it)
			{
				return Iter == it.Iter;
			}
			bool operator!=(const ReverseSetIterator &it)
			{
				return Iter != it.Iter;
			}
	};
}

#endif
