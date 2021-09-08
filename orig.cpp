#include "Header.hpp"
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <sys/time.h>

void	VectorTest()
{
	std::cout << std::endl << "======================== Vector ========================" << std::endl << std::endl;
	std::stringstream out;
	std::vector<std::string> Vector;
	std::vector<std::string>::iterator it;

	Vector.push_back("lol");
	Vector.push_back("kek");
	Vector.push_back("rofl");

	std::cout << "Vector: " << PrintContainer(Vector, out).str();
	std::cout << std::endl << "<<<<<<<<<<< Capacity >>>>>>>>>>>" << std::endl << std::endl;

	std::cout << "Vector.size() = " << Vector.size() << std::endl;
	std::cout << "Vector.max_size() = " << Vector.max_size() << std::endl;
	std::cout << "Vector.capacity() = " << Vector.capacity() << std::endl;
	Vector.resize(9);
	std::cout << "After resize(9): Vector.capacity() = " << Vector.capacity() << std::endl;
	Vector.resize(5);
	std::cout << "After resize(5): Vector.capacity() = " << Vector.capacity() << std::endl;
	std::cout << "Vector.empty() = " << Vector.empty() << std::endl;
	Vector.reserve(10);
	std::cout << "After reserve(10): Vector.capacity() = " << Vector.capacity() << std::endl;
	Vector.reserve(4);
	std::cout << "After reserve(4): Vector.capacity() = " << Vector.capacity() << std::endl;

	std::cout << std::endl << "<<<<<<<<<<< Element access >>>>>>>>>>>" << std::endl << std::endl;

	std::cout << "Vector[0] = " << Vector[0] << std::endl;
	std::cout << "Vector[1] = " << Vector[1] << std::endl;
	std::cout << "Vector.at(1) = " << Vector.at(1) << std::endl;
	try
	{
		std::cout << "Vector.at(-10) = " << Vector.at(10) << std::endl;
	}
	catch ( std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "Vector.front() = " << Vector.front() << std::endl;
	std::cout << "Vector.back() = " << Vector.back() << std::endl;

	std::cout << std::endl << "<<<<<<<<<<< Modifiers >>>>>>>>>>>" << std::endl << std::endl;
	Vector.assign(5, "lmao");
	std::cout << "After assign(5, \"lmao\"): " << PrintContainer(Vector, out).str();
	std::vector<std::string> Vector2;
	Vector2.push_back("aaa");
	Vector2.push_back("bbb");
	Vector2.push_back("ccc");
	std::cout << "Vector 2: " << PrintContainer(Vector2, out).str();
	Vector.assign(Vector2.begin(), Vector2.end());
	std::cout << "After assign(Vector2.begin(), Vector2.end()): " << PrintContainer(Vector, out).str();
	Vector.push_back("azaz");
	std::cout << "After push_back(\"azaz\"): " << PrintContainer(Vector, out).str();
	Vector.pop_back();
	std::cout << "After pop_back(): " << PrintContainer(Vector, out).str();
	it = ++++Vector.begin();
	std::cout << "it = ++++Vector.begin()" << std::endl;
	it = Vector.insert(it, "azaz");
	std::cout << "After insert(it, \"azaz\"): " << PrintContainer(Vector, out).str();
	Vector.insert(it, 5, "kek");
	std::cout << "After insert(it, 5, \"kek\"): " << PrintContainer(Vector, out).str();
	Vector.insert(it, Vector2.begin(), Vector2.end());
	std::cout << "After insert(it, Vector2.begin(), Vector2.end()): " << PrintContainer(Vector, out).str();
	it = ++++Vector.begin();
	Vector.erase(it);
	std::cout << "After erase(it): " << PrintContainer(Vector, out).str();
	Vector.erase(it, Vector.end());
	std::cout << "After erase(it, Vector.end()): " << PrintContainer(Vector, out).str();
	Vector.swap(Vector2);
	std::cout << "Vector after swap(Vector2): " << PrintContainer(Vector, out).str();
	std::cout << "Vector2 after swap(Vector2): " << PrintContainer(Vector2, out).str();
	Vector.clear();
	std::cout << "Vector after clear(): " << PrintContainer(Vector, out).str();
}

void	StackTest()
{
	std::cout << std::endl << "======================== Stack ========================" << std::endl << std::endl;
	std::stack<std::string> Stack;
	std::cout << "empty(): " << Stack.empty() << std::endl;
	Stack.push("lol");
	Stack.push("kek");
	std::cout << "After push(\"lol\"), push(\"kek\"): empty(): " << Stack.empty() << std::endl;
	std::cout << "size(): " << Stack.size() << std::endl;
	std::cout << "top(): " << Stack.top() << std::endl;
	Stack.pop();
	std::cout << "After pop(): top(): " << Stack.top() << std::endl;
}

void	MapTest()
{
	std::cout << std::endl << "======================== Map ========================" << std::endl << std::endl;
	std::stringstream out;
	std::map<int, int> Map;	
	std::map<int, int> Map2;	

	Map[11] = 228;
	Map[13] = 1337;
	Map[15] = 101;
	Map[17] = 404;
	Map[10] = 42;

	std::cout << "Map: " << PrintMap(Map, out).str();
	std::cout << "empty(): " << Map.empty() << std::endl;
	std::cout << "size(): " << Map.size() << std::endl;
	std::cout << "max_size(): " << Map.max_size() << std::endl;
	std::pair<int, int> Pair(33, 41);
	Map.insert(Pair);
	std::pair<int, int> Pair2(1, -1);
	std::cout << "After insert(pair(33, 41)): " << PrintMap(Map, out).str();
	Map.insert(Map.begin(), Pair2);
	std::cout << "After insert(begin(), pair(1, -1)): " << PrintMap(Map, out).str();
	Map2[-5] = 5;
	Map2[-10] = 9;
	std::cout << "Map2: " << PrintMap(Map2, out).str();
	Map.insert(Map2.begin(), Map2.end());
	std::cout << "After insert(Map2.begin(), Map2.end()): " << PrintMap(Map, out).str();
	Map.erase(13);
	std::cout << "After erase(13)): " << PrintMap(Map, out).str();
	Map.erase(Map.begin());
	std::cout << "After erase(begin())): " << PrintMap(Map, out).str();
	Map.erase(Map.begin(), Map.find(15));
	std::cout << "After erase(begin(), find(15))): " << PrintMap(Map, out).str();
	Map.swap(Map2);
	std::cout << "After swap(Map2): Map: " << PrintMap(Map, out).str();
	std::cout << "Map2: " << PrintMap(Map2, out).str();
	Map.clear();
	std::cout << "After clear(): Map: " << PrintMap(Map, out).str();
	std::cout << "size(): " << Map.size() << std::endl;
	Map.swap(Map2);
	std::cout << "After swap(Map2): Map: " << PrintMap(Map, out).str();
	std::cout << "Map2: " << PrintMap(Map2, out).str();
	std::cout << "count(17): " << Map.count(17) << " count(99): " << Map.count(99) << std::endl;
	std::cout << "lower_bound(0): " << Map.lower_bound(0)->first << std::endl;
	std::cout << "lower_bound(15): " << Map.lower_bound(15)->first << std::endl;
	std::cout << "lower_bound(1000): " << Map.lower_bound(1000)->first << std::endl;
	std::cout << "upper_bound(0): " << Map.upper_bound(0)->first << std::endl;
	std::cout << "upper_bound(15): " << Map.upper_bound(15)->first << std::endl;
	std::cout << "upper_bound(1000): " << Map.upper_bound(1000)->first << std::endl;
	std::cout << "equal_range(15): <" << Map.equal_range(15).first->first
		<< ":" << Map.equal_range(15).second->first << ">" << std::endl;

}

void	SetTest()
{
	std::set<int> Set;	
	std::set<int> Set2;	
	std::stringstream out;

	Set.insert(11);
	Set.insert(13);
	Set.insert(15);
	Set.insert(17);
	Set.insert(10);
	std::cout << "Set: " << PrintContainer(Set, out).str();
	std::cout << "empty(): " << Set.empty() << std::endl;
	std::cout << "size(): " << Set.size() << std::endl;
	std::cout << "max_size(): " << Set.max_size() << std::endl;
	Set.insert(33);
	std::cout << "After insert(33): " << PrintContainer(Set, out).str();
	Set.insert(Set.begin(), 1);
	std::cout << "After insert(begin(), 1): " << PrintContainer(Set, out).str();
	Set2.insert(-5);
	Set2.insert(-10);
	std::cout << "Set2: " << PrintContainer(Set2, out).str();
	Set.insert(Set2.begin(), Set2.end());
	std::cout << "After insert(Set2.begin(), Set2.end()): " << PrintContainer(Set, out).str();
	Set.erase(13);
	std::cout << "After erase(13)): " << PrintContainer(Set, out).str();
	Set.erase(Set.begin());
	std::cout << "After erase(begin())): " << PrintContainer(Set, out).str();
	Set.erase(Set.begin(), Set.find(15));
	std::cout << "After erase(begin(), find(15))): " << PrintContainer(Set, out).str();
	Set.swap(Set2);
	std::cout << "After swap(Set2): Set: " << PrintContainer(Set, out).str();
	std::cout << "Set2: " << PrintContainer(Set2, out).str();
	Set.clear();
	std::cout << "After clear(): Set: " << PrintContainer(Set, out).str();
	std::cout << "size(): " << Set.size() << std::endl;
	Set.swap(Set2);
	std::cout << "After swap(Set2): Set: " << PrintContainer(Set, out).str();
	std::cout << "Set2: " << PrintContainer(Set2, out).str();
	std::cout << "count(17): " << Set.count(17) << " count(99): " << Set.count(99) << std::endl;
	std::cout << "lower_bound(0): " << *Set.lower_bound(0) << std::endl;
	std::cout << "lower_bound(15): " << *Set.lower_bound(15) << std::endl;
	std::cout << "lower_bound(1000): " << *Set.lower_bound(1000) << std::endl;
	std::cout << "upper_bound(0): " << *Set.upper_bound(0) << std::endl;
	std::cout << "upper_bound(15): " << *Set.upper_bound(15) << std::endl;
	std::cout << "upper_bound(1000): " << *Set.upper_bound(1000) << std::endl;
	std::cout << "equal_range(15): <" << *Set.equal_range(15).first
		<< ":" << *Set.equal_range(15).second << ">" << std::endl;
}

int		main(void)
{
	VectorTest();
	StackTest();
	MapTest();
	SetTest();
}
