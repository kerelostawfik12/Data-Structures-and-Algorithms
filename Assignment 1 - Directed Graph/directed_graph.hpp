#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

//A large selection of data structures from the standard
//library. You need not feel compelled to use them all,
//but as you can't add any, they're all here just in case.
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <array>
#include <list>
#include <forward_list>
#include <deque>
#include <map>
#include <cstddef>
#include <string>

//Forward declarations for classes below so they can be used below without worrying too much about the ordering.
template<typename vertex> class vertex_iterator;

template<typename vertex> class neighbour_iterator;

template<typename vertex> class directed_graph;


template<typename vertex>
class directed_graph {

private:
    std::vector<std::vector<int> > adj_matrix;
    std::vector<vertex> vertices;
    std::size_t number_of_edges;

public:


    directed_graph(); //A constructor for directed_graph. The graph should start empty.
    ~directed_graph(); //A destructor. Depending on how you do things, this may
    //not be necessary.

    bool contains(const vertex &) const; //Returns true if the given vertex is in the graph, false otherwise.

    bool adjacent(const vertex &, const vertex &) const; //Returns true if the first vertex is adjacent to the second, false otherwise.
    long unsigned int get_index(const vertex &) const; //Returns index of vertex in verticies vector.

    void add_vertex(const vertex &); //Adds the passed in vertex to the graph (with no edges).
    void add_edge(const vertex &, const vertex &); //Adds an edge from the first vertex to the second.

    void remove_vertex(const vertex &); //Removes the given vertex. Should also clear any incident edges.
    void remove_edge(const vertex &, const vertex &); //Removes the edge between the two vertices, if it exists.

    std::size_t in_degree(const vertex &) const; //Returns number of edges coming in to a vertex.
    std::size_t out_degree(const vertex &) const; //Returns the number of edges leaving a vertex.
    std::size_t degree(const vertex &) const; //Returns the degree of the vertex (both in and out edges).

    std::size_t num_vertices() const; //Returns the total number of vertices in the graph.
    std::size_t num_edges() const; //Returns the total number of edges in the graph.

    std::vector<vertex> get_vertices(); //Returns a vector containing all the vertices.
    std::vector<vertex> get_neighbours(const vertex &); //Returns a vector containing the neighbours of the given vertex.
    std::vector<vertex> get_neighbours_in(const vertex &u); //Returns a vector containing the neighbours pointing inward to given vertex;
    vertex_iterator<vertex> begin(); //Returns a graph_iterator pointing to the start of the vertex set.
    vertex_iterator<vertex> end(); //Returns a graph_iterator pointing to one-past-the-end of the vertex set.

    neighbour_iterator<vertex> nbegin(const vertex &); //Returns a neighbour_iterator pointing to the start of the neighbour set for the given vertex.
    neighbour_iterator<vertex> nend(const vertex &); //Returns a neighbour_iterator pointing to one-past-the-end of the neighbour set for the given vertex.

    std::vector<vertex> depth_first(const vertex &); //Returns the vertices of the graph in the order they are visited in by a depth-first traversal starting at the given vertex.
    std::vector<vertex> breadth_first(const vertex &); //Returns the vertices of the graph in the order they are visisted in by a breadth-first traversal starting at the given vertex.

    directed_graph<vertex> out_tree(const vertex &); //Returns a spanning tree of the graph starting at the given vertex using the out-edges.
    directed_graph<vertex> in_tree(const vertex &); //Returns a spanning tree of the graph starting at the given vertex using the in-edges.

    bool reachable(const vertex &, const vertex &) const; //Returns true if the second vertex is reachable from the first (can you follow a path of out-edges to get from the first to the second?). Returns false otherwise.

};

//The vertex_iterator class provides an iterator
//over the vertices of the graph.
//This is one of the harder parts, so if you're
//not too comfortable with C++ leave this for last.
//If you are, there are many ways of doing this,
//as long as it passes the tests, it's okay.
//You may want to watch the videos on iterators before starting.
template<typename vertex>
class vertex_iterator {
private:
    directed_graph<vertex> graph;
    std::vector<vertex> vertices;
    std::size_t position;
public:
    vertex_iterator(const vertex_iterator<vertex> &);

    vertex_iterator(const directed_graph<vertex> &, std::size_t);

    ~vertex_iterator();

    vertex_iterator<vertex> operator=(const vertex_iterator<vertex> &);

    bool operator==(const vertex_iterator<vertex> &) const;

    bool operator!=(const vertex_iterator<vertex> &) const;

    vertex_iterator<vertex> operator++();

    vertex_iterator<vertex> operator++(int);

    vertex operator*();

    vertex *operator->();
};

//The neighbour_iterator class provides an iterator
//over the neighbours of a given vertex.

template<typename vertex>
class neighbour_iterator {

private:
    directed_graph<vertex> graph;
    std::vector<vertex> neighbours;
    vertex u;
    std::size_t position;

public:
    neighbour_iterator(const neighbour_iterator<vertex> &); //neighbour_iterator constructor with neighbour iterator argument.

    neighbour_iterator(const directed_graph<vertex> &, const vertex &, std::size_t);  //neighbour_iterator constructor that takes in a graph, vertex and position.

    ~neighbour_iterator();

    neighbour_iterator<vertex> operator=(const neighbour_iterator<vertex> &); /*neighbour_iterator operator overload of '=' equates arra*/

    bool operator==(const neighbour_iterator<vertex> &) const;
    
    bool operator!=(const neighbour_iterator<vertex> &) const;

    neighbour_iterator<vertex> operator++();

    neighbour_iterator<vertex> operator++(int);

    vertex operator*();

    vertex *operator->();
};


//Define all your methods down here (or move them up into the header, but be careful you don't double up). If you want to move this into another file, you can, but you should #include the file here.
//Although these are just the same names copied from above, you may find a few more clues in the full
//method headers. Note also that C++ is sensitive to the order you declare and define things in - you
//have to have it available before you use it.

template<typename vertex> directed_graph<vertex>::directed_graph() {
    number_of_edges = 0;
    adj_matrix = std::vector<std::vector<int> >(5000, std::vector<int>(5000,0)); //initialises adjacency matrix to 5000x5000 matrix
}

template<typename vertex> directed_graph<vertex>::~directed_graph() {}

template<typename vertex> bool directed_graph<vertex>::contains(const vertex &u) const {

    for (auto i : vertices) {
        if (i == u) {
            return true;
        }
    }
    return false;
}

template<typename vertex> bool directed_graph<vertex>::adjacent(const vertex &u, const vertex &v) const {
    long unsigned int index1 = get_index(u);
    long unsigned int index2 = get_index(v);
    if (index1 >= 0 && index2 >= 0 && index1 < 5000 && index2 < 5000 && u != v) {
        return adj_matrix[index1][index2] == 1;
    }
    return false;
}

template<typename vertex> void directed_graph<vertex>::add_vertex(const vertex &u) {
    vertices.push_back(u);

} 

template<typename vertex> long unsigned int directed_graph<vertex>::get_index(const vertex &u) const {
    long unsigned int index = 0;
    for (auto i : vertices) {
        if (i == u) {
            return index;
        } else {
            index++;
        }
    }
    return index;
}

template<typename vertex> void directed_graph<vertex>::add_edge(const vertex &u, const vertex &v) {
    long unsigned int index1 = get_index(u);
    long unsigned int index2 = get_index(v);
    if (index1 >= 0 && index2 >= 0 && index1 < 5000 && index2 < 5000 && u != v) {
        adj_matrix[index1][index2] = 1;
        number_of_edges++;
    }
}

template<typename vertex> void directed_graph<vertex>::remove_vertex(const vertex &u) {
    for (auto itr = vertices.begin(); itr < vertices.end(); ++itr) {
        if (*itr == u)
            vertices.erase(itr);
    }
}

template<typename vertex> void directed_graph<vertex>::remove_edge(const vertex &u, const vertex &v) {
    long unsigned int index1 = get_index(u);
    long unsigned int index2 = get_index(v);
    if (index1 >= 0 && index2 >= 0 && u != v && index1 < 5000 && index2 < 5000 && u != v) {
        adj_matrix[index1][index2] = 0;
        number_of_edges--;
    }
}

template<typename vertex> std::size_t directed_graph<vertex>::in_degree(const vertex &u) const {
    long unsigned int index1 = get_index(u);
    long unsigned int in_degree = 0;
    for (int i = 0; i < 5000; i++) {
        if (adj_matrix[i][index1] == 1)
            in_degree++;
    }
    return in_degree;
}

template<typename vertex> std::size_t directed_graph<vertex>::out_degree(const vertex &u) const {
    long unsigned int index1 = get_index(u);
    long unsigned int out_degree = 0;
    for (int i = 0; i < 5000; i++) {
        if (adj_matrix[index1][i] == 1) {
            out_degree++;
        }
    }
    return out_degree;
}

template<typename vertex> std::size_t directed_graph<vertex>::degree(const vertex &u) const {
    long unsigned int degree = out_degree(u) + in_degree(u);

    return degree;
}

template<typename vertex> std::size_t directed_graph<vertex>::num_vertices() const { 
    return vertices.size(); 
}

template<typename vertex> std::size_t directed_graph<vertex>::num_edges() const { 
    return number_of_edges; 
}

template<typename vertex> std::vector<vertex> directed_graph<vertex>::get_vertices() { 
    return vertices; 
}

template<typename vertex> std::vector<vertex> directed_graph<vertex>::get_neighbours(const vertex &u) {
    std::vector<vertex> neighbours;
    for (auto v : vertices) {
        if (u != v && adjacent(u, v)) {
            neighbours.push_back(v);
        }
    }

    return neighbours;
}

template<typename vertex> std::vector<vertex> directed_graph<vertex>::get_neighbours_in(const vertex &u) {
    std::vector<vertex> neighbours;
    for (auto v : vertices) {
        if (u != v && adjacent(v, u)) {
            neighbours.push_back(v);
        }
    }

    return neighbours;
}

template<typename vertex> vertex_iterator<vertex> directed_graph<vertex>::begin() {

    return vertex_iterator<vertex>(*this, 0);
}

template<typename vertex> vertex_iterator<vertex> directed_graph<vertex>::end() {
    return vertex_iterator<vertex>(*this, num_vertices());
}

template<typename vertex> neighbour_iterator<vertex> directed_graph<vertex>::nbegin(const vertex &u) {
    return neighbour_iterator<vertex>(*this, u, 0);
}

template<typename vertex> neighbour_iterator<vertex> directed_graph<vertex>::nend(const vertex &u) {
    return neighbour_iterator<vertex>(*this, u, out_degree(u));
}

template<typename vertex> std::vector<vertex> directed_graph<vertex>::depth_first(const vertex &u) {
    
    //bool array marks visited verticies as true.
    bool visited[num_vertices()];
    for (unsigned i = 0; i < num_vertices(); i++) {
        visited[i] = false;
    }
    
    //creates stack holding vertices
    std::stack<vertex> unprocessed;
    
    //adds u to start of queue
    unprocessed.push(u);
    
    std::vector<vertex> ordered;
    
    //adds n to top of stack then removes because it is about to be visted.
    while (!unprocessed.empty()) {
        vertex n = unprocessed.top(); 
        unprocessed.pop();
        if (!visited[n]) {
            visited[n] = true;
            ordered.push_back(n);    //vertex is marked when it is visited then added
            for (unsigned i = num_vertices(); i != 0; i--) {
                if (adj_matrix[n][i - 1] == 1) {
                    unprocessed.push(i - 1); //pushes all neighbours of n to start of queue. Then backtracks to other edge. Cycle continues for all n 
                }
            }
        }
    }

    return ordered;
}

template<typename vertex> std::vector<vertex> directed_graph<vertex>::breadth_first(const vertex &u) {
    
    //bool array marks visited verticies as true.
    bool visited[num_vertices()];
    for (unsigned i = 0; i < num_vertices(); i++) {
        visited[i] = false;
    }
    
    //queue that stores all adjacent vertices
    std::queue<vertex> unprocessed;
    
    //adds vertex to end of queue
    unprocessed.push(u);
    
    std::vector<vertex> ordered;
    //adds n to front of queue then removes it from the end because it is about to get marked.
    while (!unprocessed.empty()) {
        vertex n = unprocessed.front();
        unprocessed.pop();
        if (!visited[n]) {
            visited[n] = true;
            ordered.push_back(n);
            for (unsigned i = 0; i < num_vertices(); i++) {
                if (adj_matrix[n][i] == 1) {
                    unprocessed.push(i);
                }
            }
        }
    }


    return ordered;
}

template<typename vertex> directed_graph<vertex> directed_graph<vertex>::out_tree(const vertex &u) {
    directed_graph<vertex> tree;

    bool visited[num_vertices()];   
    for (unsigned i = 0; i < num_vertices(); i++) {
        visited[i] = false;        
    }
    
    //creates queue holding edges
    std::queue<std::pair<vertex, vertex> > unprocessed;
    
    //inserts vertex u (self-edge) at end.
    unprocessed.push({u, u});                              
    
    //edge placed at front of queue and removes previously visited value.
    while (!unprocessed.empty()) {
        std::pair<vertex, vertex> n = unprocessed.front();    
        unprocessed.pop();
        if (!visited[n.first]) {
            tree.add_vertex(n.first);
            visited[n.first] = true;
            if (n.first != n.second) {
                tree.add_edge(n.second, n.first);
            }
            //finds all vertices pointing away from n.first.
            for (auto v : get_neighbours(n.first)) {
                if (adjacent(n.first, v)) {
                    //adds all edges to end of queue repeats for all unvisited out-edges.
                    unprocessed.push({v, n.first});     
                }
            }
        }
    }
    return tree;
}


template<typename vertex> directed_graph<vertex> directed_graph<vertex>::in_tree(const vertex &u) {
    directed_graph<vertex> trees;

    //bool array marks visited verticies as true.
    bool visited[num_vertices()];    
    for (unsigned i = 0; i < num_vertices(); i++) {
        visited[i] = false;
    }
    
    //creates a queue holding edges
    std::queue<std::pair<vertex, vertex> > unprocessed;
    
    //inserts vertex u (self-edge) at end.
    unprocessed.push({u, u});

    //edge placed at front of queue and removes previously visited value.
    while (!unprocessed.empty()) {
        std::pair<vertex, vertex> n = unprocessed.front();
        unprocessed.pop();
        if (!visited[n.first]) {
            if (!trees.contains(n.first)) {
                trees.add_vertex(n.first);
            }
            if (!trees.contains(n.second)) {
                //adds both vertices in the case that the first is an out_edge. 
                trees.add_vertex(n.second);  
            }
            visited[n.first] = true;
            if (n.first != n.second) {
                trees.add_edge(n.first, n.second);       
            }
            //finds all vertices pointing in to n.first.
            for (auto le : get_neighbours_in(n.first)) {    
                if (adjacent(le, n.first)) {
                    //adds all edges to end of queue repeats for all unvisited out-edges.
                    unprocessed.push({le, n.first});
                }
            }
        }
    }
    return trees;
}

/**********************************************************************************************************
* Boolean function is_reachable. 
* Uses a breadth first traversal through the vertices between u and v and checks if v is visited. 
* If so, then v is reachable
**********************************************************************************************************/
template<typename vertex> bool directed_graph<vertex>::reachable(const vertex &u, const vertex &v) const {
    
    bool visited[num_vertices()];
    for (unsigned i = 0; i < num_vertices(); i++) {
        visited[i] = false;
    }

    std::queue<vertex> unprocessed;
    unprocessed.push(u);

    std::vector<vertex> ordered;

    while (!unprocessed.empty()) {
        vertex n = unprocessed.front();
        unprocessed.pop();
        if (!visited[n]) {
            visited[n] = true;
            if (n == v) {
                return true;  
            }
            ordered.push_back(n);
            
            for (unsigned i = 0; i < num_vertices(); i++) {
                if (adj_matrix[n][i] == 1) {
                    unprocessed.push(i);
                }
            }
        }
    }


    return false;
}

template<typename vertex> vertex_iterator<vertex>::vertex_iterator(const vertex_iterator<vertex> &other) {
    graph = other.graph;
    vertices = other.vertices;
    position = other.position;
}

template<typename vertex> vertex_iterator<vertex>::vertex_iterator(const directed_graph<vertex> &graph, std::size_t position) {
    this->graph = graph;
    vertices = this->graph.get_vertices();
    this->position = position;
}

template<typename vertex> vertex_iterator<vertex>::~vertex_iterator() {}

template<typename vertex> vertex_iterator<vertex> vertex_iterator<vertex>::operator=(const vertex_iterator<vertex> &other) {
    return vertex_iterator<vertex>(other.graph, other.position);
}

template<typename vertex> bool vertex_iterator<vertex>::operator==(const vertex_iterator<vertex> &other) const {
    return (graph.num_vertices() == other.graph.num_vertices() && position == other.position);
}

template<typename vertex> bool vertex_iterator<vertex>::operator!=(const vertex_iterator<vertex> &other) const {
    return !(*this == other);
}

template<typename vertex> vertex_iterator<vertex> vertex_iterator<vertex>::operator++() {
    ++position;
    return *this;
}

template<typename vertex> vertex_iterator<vertex> vertex_iterator<vertex>::operator++(int) {
    auto temp = this;
    ++position;
    return temp;
}

template<typename vertex> vertex vertex_iterator<vertex>::operator*() {
    return vertices.at(position);
}

template<typename vertex> vertex *vertex_iterator<vertex>::operator->() {
    return *(vertices.at(0) + position);
}

template<typename vertex> neighbour_iterator<vertex>::neighbour_iterator(const neighbour_iterator<vertex> &other) {
    graph = other.graph;
    u = other.u;
    neighbours = other.neighbours;
    position = other.position;
}

template<typename vertex>
neighbour_iterator<vertex>::neighbour_iterator(const directed_graph<vertex> &graph, const vertex &u, std::size_t position) {
    this->graph = graph;
    this->u = u;
    neighbours = this->graph.get_neighbours(u);
    this->position = position;
}

template<typename vertex> neighbour_iterator<vertex>::~neighbour_iterator() {}

template<typename vertex> neighbour_iterator<vertex>
neighbour_iterator<vertex>::operator=(const neighbour_iterator<vertex> &other) {
    return neighbour_iterator<vertex>(other.graph, other.u, other.position);
}

//neighbour_iterator operator overload of '==' operator to boolean operation that compares the equality of one neighbour_iterator to another. 
template<typename vertex> bool neighbour_iterator<vertex>::operator==(const neighbour_iterator<vertex> &other) const {
    return (neighbours == other.neighbours && u == other.u && position == other.position); 
}

template<typename vertex> bool neighbour_iterator<vertex>::operator!=(const neighbour_iterator<vertex> &other) const {
    return !(*this == other);
}

template<typename vertex> neighbour_iterator<vertex> neighbour_iterator<vertex>::operator++() {
    ++position;
    return *this;
}

template<typename vertex> neighbour_iterator<vertex> neighbour_iterator<vertex>::operator++(int) {
    auto temp = this;
    ++position;
    return temp;
}

template<typename vertex> vertex neighbour_iterator<vertex>::operator*() {
    return neighbours.at(position);
}

template<typename vertex> vertex *neighbour_iterator<vertex>::operator->() {
    return *(neighbours.at(0) + position);
}


#endif
