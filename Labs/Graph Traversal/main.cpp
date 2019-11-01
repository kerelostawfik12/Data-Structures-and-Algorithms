#include <iostream>
#include <iomanip>
#include "graph.h"

int main(){
	
	std::cout << std::boolalpha;
	
	graph g(4);
	
	g.add_edge(0,1);
	g.add_edge(0,2);
	g.add_edge(1,2);
	g.add_edge(1,3);
	
	graph t = g.spanning_tree(0);
	
	int num_edges = 0;
	
	for (int i = 0; i < 4; i++){
		for (int j = i + 1; j < 4; j++){
			num_edges += t.is_adjacent(i,j)? 1 : 0;
		}
	}
	
	std::cout << "Number of edges in the tree: " << num_edges << std::endl;
	std::cout << "Are original non-edges now edges?" << std::endl;
	std::cout << "0-3? " << t.is_adjacent(0,3) << std::endl;
	std::cout << "2-3? " << t.is_adjacent(2,3) << std::endl;
	std::cout << "Is the edge 1-3 present? " << t.is_adjacent(1,3) << std::endl;
}
