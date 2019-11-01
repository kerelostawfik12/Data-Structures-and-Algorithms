#include <iostream>
#include "bst.hpp"

int main(){
	
	std::cout << std::boolalpha;
	
	bst<int> t;
	
	t.insert(1);
	t.insert(3);
	t.insert(10);
	t.insert(13);
	t.insert(11);
	t.insert(12);
	t.insert(15);
	
	std::cout << "Does the tree contain the value " << 10 << ": " << t.contains(10) << " at position " << t.index_of(10) << std::endl;
	std::cout << "Does the tree contain the value " << 13 << ": " << t.contains(13) << " at position " << t.index_of(13) <<  std::endl;
	std::cout << "Does the tree contain the value " << 3 << ": " << t.contains(3) << " at position " << t.index_of(3) <<  std::endl;
	std::cout << "Does the tree contain the value " << 1 << ": " << t.contains(1) << " at position " << t.index_of(1) <<  std::endl;
	std::cout << "Does the tree contain the value " << 11 << ": " << t.contains(11) << " at position " << t.index_of(11) <<  std::endl;
	std::cout << "Does the tree contain the value " << 12 << ": " << t.contains(12) << " at position " << t.index_of(12) <<  std::endl;
	std::cout << "Does the tree contain the value " << 15 << ": " << t.contains(15) << " at position " << t.index_of(15) <<  std::endl;
	std::cout << "Does the tree contain the value " << 9 << ": " << t.contains(9) << " at position " << t.index_of(9) <<  std::endl;
	std::cout << "Does the tree contain the value " << 2 << ": " << t.contains(2) << " at position " << t.index_of(2) <<  std::endl;

	std::cout << "Removing the values 10, 13 and 12" << std::endl;
	
	t.remove(10);
	t.remove(13);
	t.remove(12);

	std::cout << "Does the tree contain the value " << 10 << ": " << t.contains(10) << " at position " << t.index_of(10) << std::endl;
	std::cout << "Does the tree contain the value " << 13 << ": " << t.contains(13) << " at position " << t.index_of(13) <<  std::endl;
	std::cout << "Does the tree contain the value " << 3 << ": " << t.contains(3) << " at position " << t.index_of(3) <<  std::endl;
	std::cout << "Does the tree contain the value " << 1 << ": " << t.contains(1) << " at position " << t.index_of(1) <<  std::endl;
	std::cout << "Does the tree contain the value " << 11 << ": " << t.contains(11) << " at position " << t.index_of(11) <<  std::endl;
	std::cout << "Does the tree contain the value " << 12 << ": " << t.contains(12) << " at position " << t.index_of(12) <<  std::endl;
	std::cout << "Does the tree contain the value " << 15 << ": " << t.contains(15) << " at position " << t.index_of(15) <<  std::endl;

}
