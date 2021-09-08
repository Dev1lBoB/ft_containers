#ifndef SET_HPP
#define SET_HPP
#include <iostream>
#include "Utils.hpp"
#include "SetIterator.hpp"

namespace ft
{

	template < class T,                              // set::key_type/value_type
	class Compare = ft::less<T>,                   // set::key_compare/value_compare
	class Alloc = std::allocator<T> // set::allocator_type
	> class Set
	{

#define		RED 1
#define		BLACK 0
#define		ROOT Root
#define		LEAF Leaf
#define		LAST Last

		private:
			struct	Node;
			

		public:
			typedef		T										key_type;
			typedef		T										value_type;
			typedef		Compare									key_compare;
			typedef		Alloc									allocator_type;
			typedef		typename std::allocator<Node>			node_allocator;
			typedef		value_type&								reference;
			typedef		const value_type&						const_reference;
			typedef		value_type*								pointer;
			typedef		const value_type*						const_pointer;
			typedef		std::ptrdiff_t							difference_type;
			typedef		std::size_t								size_type;
			typedef		ft::SetIterator
						<key_type, value_type, Node>			iterator;
			typedef		ft::ReverseSetIterator
						<key_type, value_type, Node>			reverse_iterator;
			typedef		ft::SetIterator
						<key_type, value_type, const Node>		const_iterator;
			typedef		ft::ReverseSetIterator
						<key_type, value_type, const Node>		const_reverse_iterator;

			class value_compare
			{
				friend class Set;

			protected:

				key_compare comp;
				value_compare(Compare c) : comp(c) {}

			public:

				typedef bool        result_type;
				typedef value_type  first_argument_type;
				typedef value_type  second_argument_type;

				bool operator()(const value_type& x, const value_type& y) const
				{
					return comp(x, y);
				}
			};

		private:
			struct	Node
			{
				Node			*Left;
				Node			*Right;
				Node			*Parent;
				value_type		Pair;
				int				Flag;
				bool			Color;
			};

			Node			*Root;
			Node			*Leaf;
			Node			*Last;
			size_type		Size;
			allocator_type	Allocator;
			node_allocator	NodeAllocator;
			key_compare		Comp;



//
// External functions
//

			Node	*minNode(Node *node) const
			{
				if (!node)
					return LAST;
				while (node->Left->Flag == 0)
					node = node->Left;
				return node;
			}
			Node	*maxNode(Node *node) const
			{
				if (!node)
					return LAST;
				while (node->Right->Flag == 0)
					node = node->Right;
				return node;
			}

			Node	*findNode(Node *node, const key_type &k) const
			{
				Node *temp;
				
				if (Size == 0 || node->Flag != 0)
					return nullptr;
				if (Comp(k, node->Pair) == 0 && Comp(node->Pair, k) == 0)
					return node;
				if ((temp = findNode(node->Left, k)))
					return temp;
				return findNode(node->Right, k);
			}

			template<class T1, class T2>
			ft::pair<T1, T2> makePair(T1 key, T2 val) const
			{
				return ft::pair<T1, T2>(key, val);
			}

			Node *createNode(const value_type &pair)
			{
				Node *newNode = NodeAllocator.allocate(sizeof(Node));
				Allocator.construct(&newNode->Pair, pair);
				newNode->Flag = 0;
				newNode->Left = LEAF;
				newNode->Right = LEAF;
				newNode->Parent = nullptr;
				newNode->Color = RED;
				return newNode;
			}

			Node *insertNode(const key_type k, Node *node, const value_type &pair)
			{
				if (Size == 0)
				{
					Node *newNode = createNode(pair);
					newNode->Color = BLACK;
					ROOT = newNode;
					newNode->Left = LAST;
					newNode->Right = LAST;
					++Size;
					return newNode;
				}
				if (Comp(k, node->Pair) && node->Left->Flag == 0)
					return insertNode(k, node->Left, pair);
				if (!Comp(k, node->Pair) && node->Right->Flag == 0)
					return insertNode(k, node->Right, pair);

				Node *newNode = createNode(pair);

				if (Comp(k, node->Pair))
					node->Left = newNode;
				else
					node->Right = newNode;
				newNode->Parent = node;
				++Size;
				minNode(ROOT)->Left = LAST;
				maxNode(ROOT)->Right = LAST;
				insertNodeBalans(newNode);
				return newNode;
			}

			void rotateRight(Node *x)
			{
				Node *y = x->Left;

				x->Left = y->Right;
				if (y->Right->Flag == 0) y->Right->Parent = x;
				if (y->Flag == 0) y->Parent = x->Parent;
				if (x->Parent) {
					if (x == x->Parent->Right)
						x->Parent->Right = y;
					else
						x->Parent->Left = y;
				}
				else
				{
					ROOT = y;
				}
				y->Right = x;
				if (x->Flag == 0) x->Parent = y;
			}

			void rotateLeft(Node *x)
			{
				Node *y = x->Right;

				x->Right = y->Left;
				if (y->Left->Flag == 0) y->Left->Parent = x;
				if (y->Flag == 0) y->Parent = x->Parent;
				if (x->Parent) {
					if (x == x->Parent->Left)
						x->Parent->Left = y;
					else
						x->Parent->Right = y;
				}
				else
				{
					ROOT = y;
				}
				y->Left = x;
				if (x->Flag == 0) x->Parent = y;
			}



			void insertNodeBalans(Node *x)
			{
				while (x != ROOT && x->Parent->Color == RED)
				{
					if (x->Parent == x->Parent->Parent->Left)
					{
						Node *y = x->Parent->Parent->Right;

						if (y->Color == RED)
						{
							x->Parent->Color = BLACK;
							y->Color = BLACK;
							x->Parent->Parent->Color = RED;
							x = x->Parent->Parent;
						}
						else
						{
							if (x == x->Parent->Right)
							{
								x = x->Parent;
								rotateLeft(x);
							}
							x->Parent->Color = BLACK;
							x->Parent->Parent->Color = RED;
							rotateRight(x->Parent->Parent);
						}
					}
					else
					{
						Node *y = x->Parent->Parent->Left;

						if (y->Color == RED)
						{
							x->Parent->Color = BLACK;
							y->Color = BLACK;
							x->Parent->Parent->Color = RED;
							x = x->Parent->Parent;
						}
						else
						{
							if (x == x->Parent->Left)
							{
								x = x->Parent;
								rotateRight(x);
							}
							x->Parent->Color = BLACK;
							x->Parent->Parent->Color = RED;
							rotateLeft(x->Parent->Parent);
						}
					}
				}
				ROOT->Color = BLACK;
			}



			void deleteNodeBalans(Node *x)
			{
				while (x != ROOT && x->Color == BLACK)
				{
					if (x == x->Parent->Left)
					{
						Node *w = x->Parent->Right;
						if (w->Color == RED)
						{
							w->Color = BLACK;
							x->Parent->Color = RED;
							rotateLeft (x->Parent);
							w = x->Parent->Right;
						}
						if (w->Left->Color == BLACK && w->Right->Color == BLACK)
						{
							w->Color = RED;
							x = x->Parent;
						}
						else
						{
							if (w->Right->Color == BLACK)
							{
								w->Left->Color = BLACK;
								w->Color = RED;
								rotateRight (w);
								w = x->Parent->Right;
							}
							w->Color = x->Parent->Color;
							x->Parent->Color = BLACK;
							w->Right->Color = BLACK;
							rotateLeft (x->Parent);
							x = ROOT;
						}

					}
					else
					{
						Node *w = x->Parent->Left;
						if (w->Color == RED)
						{
							w->Color = BLACK;
							x->Parent->Color = RED;
							rotateRight (x->Parent);
							w = x->Parent->Left;
						}
						if (w->Right->Color == BLACK && w->Left->Color == BLACK)
						{
							w->Color = RED;
							x = x->Parent;
						}
						else
						{
							if (w->Left->Color == BLACK)
							{
								w->Right->Color = BLACK;
								w->Color = RED;
								rotateLeft (w);
								w = x->Parent->Left;
							}
							w->Color = x->Parent->Color;
							x->Parent->Color = BLACK;
							w->Left->Color = BLACK;
							rotateRight (x->Parent);
							x = Root;
						}
					}
				}
				x->Color = BLACK;
			}

			void deleteNodeWithoutChildren(Node *nodeToDelete)
			{
				if (nodeToDelete->Parent != nullptr)
				{
					if (nodeToDelete->Parent->Right == nodeToDelete)
						nodeToDelete->Parent->Right = LEAF;
					else
						nodeToDelete->Parent->Left = LEAF;	
				}
				--Size;
				LEAF->Parent = nodeToDelete->Parent;
				if (nodeToDelete->Color == BLACK && Size > 1)
					deleteNodeBalans(LEAF);
				LEAF->Parent = nullptr;
				if (Size == 0)
					ROOT = nullptr;
				else
				{
					maxNode(ROOT)->Right = LAST;
					minNode(ROOT)->Left = LAST;
				}
				NodeAllocator.deallocate(nodeToDelete, sizeof(Node));
			}

			void deleteNodeWithOneChild(Node *nodeToDelete, bool side)
			{
				if (nodeToDelete->Parent != nullptr)
				{
					if (nodeToDelete->Parent->Right == nodeToDelete)
						nodeToDelete->Parent->Right = side ? 
						nodeToDelete->Left : nodeToDelete->Right;
					else
						nodeToDelete->Parent->Left = side ?
						nodeToDelete->Left : nodeToDelete->Right;
				}
				else
					ROOT = side ? nodeToDelete->Left : nodeToDelete->Right;
				if (side)
					nodeToDelete->Left->Parent = nodeToDelete->Parent;
				else
					nodeToDelete->Right->Parent = nodeToDelete->Parent;
				--Size;
				if (nodeToDelete->Color == BLACK)
				{
					if (side)
						deleteNodeBalans(nodeToDelete->Left);
					else
						deleteNodeBalans(nodeToDelete->Right);
				}
				NodeAllocator.deallocate(nodeToDelete, sizeof(Node));
			}

			void deleteNodeWithBothChildren(Node *nodeToDelete)
			{
				Node *nodeToReplace = minNode(nodeToDelete->Right);
						
				value_type & a =
				( value_type &)(nodeToDelete->Pair);
				value_type & b =
				( value_type &)(nodeToReplace->Pair);
				std::swap(a, b);
				deleteNode(nodeToReplace);
			}

			void deleteNode(Node *nodeToDelete)
			{
				if (nodeToDelete->Left->Flag != 0 && nodeToDelete->Right->Flag != 0)
					deleteNodeWithoutChildren(nodeToDelete);
				else
				{
					if (nodeToDelete->Left->Flag != 0 &&
					nodeToDelete->Right->Flag == 0)
						deleteNodeWithOneChild(nodeToDelete, 0);
					else if (nodeToDelete->Left->Flag == 0 &&
					nodeToDelete->Right->Flag != 0)
						deleteNodeWithOneChild(nodeToDelete, 1);
					else
					{
						deleteNodeWithBothChildren(nodeToDelete);
						return ;
					}
					if (Size != 0)
					{
						maxNode(ROOT)->Right = LAST;
						minNode(ROOT)->Left = LAST;
					}
				}
			}
		public:
//
//	Constructor
//
			explicit Set (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			: Allocator(alloc), Comp(comp)
			{
				LAST = createNode(value_type());
				LEAF = createNode(value_type());
				LAST->Flag = 1;
				LAST->Left = LEAF;
				LAST->Right = LEAF;
				LAST->Parent = nullptr;
				LAST->Color = BLACK;

				LEAF->Flag = 2;
				LEAF->Left = nullptr;
				LEAF->Right = nullptr;
				LEAF->Parent = nullptr;
				LEAF->Color = BLACK;

				ROOT = nullptr;
				Size = 0;
			}
			
			template <class InputIterator>
			Set (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type(),
			char (*)[sizeof(*first)] = NULL)
			: Allocator(alloc), Comp(comp)
			{
				LAST = createNode(value_type());
				LEAF = createNode(value_type());
				LAST->Flag = 1;
				LAST->Left = LEAF;
				LAST->Right = LEAF;
				LAST->Parent = nullptr;
				LAST->Color = BLACK;

				LEAF->Flag = 2;
				LEAF->Left = nullptr;
				LEAF->Right = nullptr;
				LEAF->Parent = nullptr;
				LEAF->Color = BLACK;

				ROOT = nullptr;
				Size = 0;
				insert(first, last);
			}

			Set(const Set& x)
			{
				LAST = createNode(value_type());
				LEAF = createNode(value_type());
				LAST->Flag = 1;
				LAST->Left = LEAF;
				LAST->Right = LEAF;
				LAST->Parent = nullptr;
				LAST->Color = BLACK;

				LEAF->Flag = 2;
				LEAF->Left = nullptr;
				LEAF->Right = nullptr;
				LEAF->Parent = nullptr;
				LEAF->Color = BLACK;

				ROOT = nullptr;
				Size = 0;
				*this = x;
			}
//
//	Destructor
//
			~Set()
			{
				clear();
				NodeAllocator.deallocate(LAST, sizeof(LAST));
				NodeAllocator.deallocate(LEAF, sizeof(LEAF));
			}

//
//	Copy
//
	
			Set &operator=(const Set& x)
			{
				Allocator = x.Allocator;
				Comp = x.Comp;
				clear();
				iterator first = x.begin();
				iterator last = x.end();
				insert(first, last);
				return *this;
			}

//
//	Iterators
//

			iterator	begin()
			{
				return minNode(ROOT);
			}
			const_iterator	begin() const
			{
				return minNode(ROOT);
			}

			iterator	end()
			{
				return LAST;
			}
			const_iterator	end() const
			{
				return LAST;
			}

			reverse_iterator rbegin()
			{
				return maxNode(ROOT);
			}
			const_reverse_iterator rbegin() const
			{
				return maxNode(ROOT);
			}

			reverse_iterator	rend()
			{
				return LAST;
			}
			const_reverse_iterator	rend() const
			{
				return LAST;
			}
//
//	Capacity
//

			bool	empty() const
			{
				return !Size;
			}

			size_type	size() const
			{
				return Size;
			}

			size_type	max_size() const
			{
				return std::numeric_limits<size_type>::max() / sizeof(value_type);
			}

//
//	Modifier
//

			pair<iterator, bool> insert (const value_type& val)
			{
				Node *temp = findNode(ROOT, val);
				if (temp)
					return ft::pair<iterator, bool>(iterator(temp), false);
				temp = insertNode(val, ROOT, val);
				return ft::pair<iterator, bool>(iterator(temp), true);
			}

			iterator insert (iterator position, const value_type& val)
			{
				static_cast<void>(position);
				Node *temp = findNode(ROOT, val);
				if (temp)
					return temp;
				return insertNode(val, ROOT, val);
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL)
			{
				Node *temp;
				for (InputIterator i = first; i != last; i++)
				{
					temp = findNode(ROOT, *i);
					if (!temp)
						insertNode(*i, ROOT, *i);
				}
			}

			void erase (iterator position)
			{
				Node *temp = findNode(ROOT, *position);
				if (temp)
					deleteNode(temp);
			}
			size_type erase (const key_type& k)
			{
				Node *temp = findNode(ROOT, k);
				if (temp)
				{
					deleteNode(temp);
					return 1;
				}
				return 0;
			}
			void erase (iterator first, iterator last)
			{
				iterator iter;
				while (first != last)
				{
					iter = first;
					++first;
					erase(iter);
				}
			}

			void swap (Set &x)
			{
				std::swap(ROOT, x.ROOT);
				std::swap(LAST, x.LAST);
				std::swap(LEAF, x.LEAF);
				std::swap(Size, x.Size);
				std::swap(Comp, x.Comp);
				std::swap(Allocator, x.Allocator);
			}

			void clear()
			{
				while (Size)
					erase(begin());
			}

//
//	Observers
//

			key_compare key_comp() const
			{
				return key_compare();
			}

			value_compare value_comp() const
			{
				return value_compare();
			}

//
//	Operations
//

			iterator find (const key_type& k)
			{
				Node *temp = findNode(ROOT, k);
				if (!temp)
					return LAST;
				return temp;
			}
			const_iterator find (const key_type& k) const
			{
				Node *temp = findNode(ROOT, k);
				if (!temp)
					return LAST;
				return temp;
			}

			size_type count (const key_type& k) const
			{
				if (findNode(ROOT, k))
					return 1;
				return 0;
			}

			iterator lower_bound (const key_type& k)
			{
				Node *temp = findNode(ROOT, k);
				if (!temp)
				{
					iterator iter = begin();
					while (iter != LAST && Comp(k, *iter) <= 0 && Comp(*iter, k) >= 0)
						++iter;
					return iter;
				}
				return temp;
			}

			const_iterator lower_bound (const key_type& k) const
			{
				Node *temp = findNode(ROOT, k);
				if (!temp)
				{
					iterator iter = begin();
					while (iter != LAST && Comp(k, *iter) <= 0 && Comp(*iter, k) >= 0)
						++iter;
					return iter;
				}
				return temp;
			}

			iterator upper_bound (const key_type& k)
			{
				Node *temp = findNode(ROOT, k);
				if (!temp)
				{
					iterator iter = begin();
					while (iter != LAST && Comp(k, *iter) <= 0 && Comp(*iter, k) >= 0)
						++iter;
					return iter;
				}
					iterator iter = temp;
					++iter;
				return iter;
			}

			const_iterator upper_bound (const key_type& k) const
			{
				Node *temp = findNode(ROOT, k);
				if (!temp)
				{
					iterator iter = begin();
					while (iter != LAST && Comp(k, *iter) <= 0 && Comp(*iter, k) >= 0)
						++iter;
					return iter;
				}
					iterator iter = temp;
					++iter;
				return iter;
			}

			pair<iterator, iterator> equal_range (const key_type& k)
			{
				pair<iterator, iterator> Pair;
				Pair.first = lower_bound(k);
				Pair.second = upper_bound(k);
				return Pair;
			}
			pair<const_iterator, const_iterator> equal_range (const key_type& k) const
			{
				pair<const_iterator, const_iterator> Pair;
				Pair.first = lower_bound(k);
				Pair.second = upper_bound(k);
				return Pair;
			}

//
//	Allocator
//

			allocator_type get_allocator() const
			{
				return Allocator;
			}
	};

	template <class T, class Compare, class Alloc>
		void swap (Set<T, Compare, Alloc>& x, Set<T, Compare, Alloc>& y)
		{
			x.swap(y);
		}
	template <class T, class Compare, class Alloc>
		bool operator== ( const Set<T,Compare,Alloc>& lhs,
		const Set<T,Compare,Alloc>& rhs )
		{
			if (lhs.size() != rhs.size())
				return false;
			typename Set<T>::const_iterator lhs_b = lhs.begin();
			typename Set<T>::const_iterator lhs_e = lhs.end();
			typename Set<T>::const_iterator rhs_b = rhs.begin();
			typename Set<T>::const_iterator rhs_e = rhs.end();

			while (lhs_b != lhs_e && rhs_b != rhs_e)
			{
				if (lhs_b != rhs_b)
					return false;
				lhs_b++;
				rhs_b++;
			}
			return true;
		}

	template <class T, class Compare, class Alloc>
		bool operator!= ( const Set<T,Compare,Alloc>& lhs,
		const Set<T,Compare,Alloc>& rhs )
		{
			return !(lhs == rhs);
		}

	template <class T, class Compare, class Alloc>
		bool operator> ( const Set<T,Compare,Alloc>& lhs,
		const Set<T,Compare,Alloc>& rhs )
		{
			if (lhs.size() > rhs.size())
				return false;
			typename Set<T>::const_iterator lhs_b = lhs.begin();
			typename Set<T>::const_iterator lhs_e = lhs.end();
			typename Set<T>::const_iterator rhs_b = rhs.begin();
			typename Set<T>::const_iterator rhs_e = rhs.end();

			while (lhs_b != lhs_e && rhs_b != rhs_e)
			{
				if (lhs_b > rhs_b)
					return true;
				lhs_b++;
				rhs_b++;
			}
			return false;
		}

	template <class T, class Compare, class Alloc>
		bool operator>= ( const Set<T,Compare,Alloc>& lhs,
		const Set<T,Compare,Alloc>& rhs )
		{
			if (lhs.size() > rhs.size())
				return false;
			typename Set<T>::const_iterator lhs_b = lhs.begin();
			typename Set<T>::const_iterator lhs_e = lhs.end();
			typename Set<T>::const_iterator rhs_b = rhs.begin();
			typename Set<T>::const_iterator rhs_e = rhs.end();

			while (lhs_b != lhs_e && rhs_b != rhs_e)
			{
				if (lhs_b >= rhs_b)
					return true;
				lhs_b++;
				rhs_b++;
			}
			return false;
		}

	template <class T, class Compare, class Alloc>
		bool operator< ( const Set<T,Compare,Alloc>& lhs,
		const Set<T,Compare,Alloc>& rhs )
		{
			return !(lhs >= rhs);
		}

	template <class T, class Compare, class Alloc>
		bool operator<= ( const Set<T,Compare,Alloc>& lhs,
		const Set<T,Compare,Alloc>& rhs )
		{
			return !(lhs > rhs);
		}
}

#endif
