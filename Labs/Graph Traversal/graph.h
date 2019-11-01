#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <stack>
#include <queue>
#include <utility>

class graph {
	
	private:
	
	std::vector<std::vector<bool> > adj_matrix;
	size_t size;
	
	public:
	
	graph(const size_t&);
	~graph();
	
	void add_edge(const int&, const int&);
	void remove_edge(const int&, const int&);
	
	bool is_adjacent(const int&, const int&);
	
	std::vector<int> dft(const int&) const;
	std::vector<int> bft(const int&) const;
	
	//The new method. Given a starting vertex,
	//this should return a spanning tree as another
	//graph.
	graph spanning_tree(const int&) const;
	
};

#endif
