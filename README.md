# ft_containers
Recreation of standard STL containers

The main goal of this project was to reimplement following containers:
- Vector
- Stack
- Map
And one bonus container
- Set

Inner data structure for each container must be justified (using a simple array
for a map is not ok). Because of that Vector uses dynamic array and Map with Set uses Red-Black trees. Stack uses Vector class as default underlaying container.

Vector, Map and Set has iterator system implemented.

There is two test files with original and mine containers. To compile them use "make" command.
