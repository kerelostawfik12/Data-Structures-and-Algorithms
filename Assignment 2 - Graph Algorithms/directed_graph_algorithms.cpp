/*
 * Notice that the list of included headers has
 * expanded a little. As before, you are not allowed
 * to add to this.
 */
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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
#include <utility>
#include <algorithm>
#include <limits>
#include <optional>
#include <exception>
#include <stdexcept>
#include "directed_graph.hpp"

/*
 * Computes whether the input is a Directed Acyclic Graph (DAG).
 * A digraph is a DAG if there is no vertex that has a cycle.
 * A cycle is a non-empty set of [out-]edges that starts at one
 * vertex, and returns to it.
 */

template<typename vertex>
bool is_dag(const directed_graph<vertex> &d) {
    std::list<vertex> topo_sort = topological_sort(d);
    //checks if there is a valid topological sort 
    if (topo_sort.size() == d.num_vertices() || d.num_vertices() == 1) {
        return true;
    }
    return false;
}

/*
 * Computes a topological ordering of the vertices.
 * For every vertex u in the order, and any of its
 * neighbours v, v appears later in the order than u.
 */


template<typename vertex>
std::list<vertex> topological_sort(const directed_graph<vertex> &d) {
    std::list<vertex> topo_sort;
    std::unordered_map<vertex, bool> visited;
    std::set<vertex> vertices;
    directed_graph<vertex> graph = directed_graph<vertex>(d);
    
    //populates set  empty list for empty graph
    if (d.num_vertices() == 0) {
        return topo_sort;
    }
    
    //returns all vertices in graph
    for (auto vitr = d.begin(); vitr != d.end(); vitr++) {
        if (d.in_degree(*vitr) == 0) {
            vertices.insert(*vitr);
        }
    }
    
    //removes all outedges of indegree 0 
    while (!vertices.empty()) {
        for (auto v = vertices.begin(); v != vertices.end(); ++v) {
            topo_sort.push_back(*v);
            for (auto nitr = d.nbegin(*v); nitr != d.nend(*v); ++nitr) {
                graph.remove_edge(*v, *nitr);
                if (graph.in_degree(*nitr) == 0) {
                    vertices.insert(*nitr);
                }
            }
            vertices.erase(*v);
        }
    }
    return topo_sort;
}

/*
 * Given a DAG, computes whether there is a Hamiltonian path.
 * a Hamiltonian path is a path that visits every vertex
 * exactly once.
 */

template<typename vertex>
bool is_hamiltonian_dag(const directed_graph<vertex> &d) {
    std::list<vertex> topo_sort = topological_sort(d);
    if (!topo_sort.empty() && !is_dag(d)) {
        return false;
    }
    
    //checks if contiguous vertices are connected.
    std::vector<vertex> listvec(topo_sort.begin(), topo_sort.end());
    for (int i = 1; i < listvec.size(); i++) {
        if (!d.adjacent(listvec[i - 1], listvec[i])) {
            return false;
        }
    }
    
    return true;
}


template<typename vertex>
std::vector<vertex> weakconnect(const vertex &u, std::unordered_map<vertex, bool> &visited,
                                directed_graph<vertex> &undirected_graph) {

    std::vector<vertex> ordered;

    //adds u to start of queue
    std::stack<vertex> unprocessed;
    unprocessed.push(u);

    //traverses through neighbours, adds all neighbours to component, looks for their neighbours
    while (!unprocessed.empty()) {
        auto n = unprocessed.top();
        unprocessed.pop();
        if (!visited[n]) {
            visited[n] = true;
            ordered.push_back(n);
            for (auto nitr = undirected_graph.nbegin(n); nitr != undirected_graph.nend(n); ++nitr) {
                unprocessed.push(*nitr);
            }
        }
    }
    return ordered;

}

/*
 * Computes the weakly connected components of the graph.
 * A [weak] component is the smallest subset of the vertices
 * such that the in and out neighbourhood of each vertex in
 * the set is also contained in the set.
 */

template<typename vertex>
std::vector<std::vector<vertex>> components(const directed_graph<vertex> &d) {
    directed_graph<vertex> undirected_graph = directed_graph<vertex>(d);
    std::vector<std::vector<vertex>> wcc;
    std::unordered_map<vertex, bool> visited;

    //initialises visited, must be initialised here as visitation is permanent
    for (auto itr = d.begin(); itr != d.end(); ++itr) {
        visited.insert(std::make_pair(*itr, false));
    }

    //Creates undirected graph so that in and out neighbourhood can be received from one DFT.
    for (auto vitr = undirected_graph.begin(); vitr != undirected_graph.end(); ++vitr) {
        for (auto nitr = undirected_graph.nbegin(*vitr); nitr != undirected_graph.nend(*vitr); ++nitr)
            undirected_graph.add_edge(*nitr, *vitr);
    }


    for (auto vitr = d.begin(); vitr != d.end(); ++vitr) {
        if (visited[*vitr] == false) {
            wcc.push_back(weakconnect(*vitr, visited, undirected_graph));
        }
    }

    return wcc;
}

/*
 * Computes the strongly connected components of the graph.
 * A strongly connected component is a subset of the vertices
 * such that for every pair u, v of vertices in the subset,
 * v is reachable from u and u is reachable from v.
 */

template<typename vertex>
void strongconnect(const vertex &u, std::unordered_map<vertex, bool> &visited,
                   std::unordered_map<vertex, int> &index, std::unordered_map<vertex, int> &low,
                   directed_graph<vertex> &graph, std::vector<std::vector<vertex>> &scc) {
    //each vertex has its own index (depth traversal count) and components
    static int count = 0;
    //stack containing vertices of a strongly component after they are found
    static std::stack<vertex> st;
    std::vector<vertex> vertices;
    //contains the index of vertex u
    index[u] = count;
    //index of lowest depth vertex reachable from u
    low[u] = count;
    count++;
    st.push(u);
    visited[u] = true;


    //guard for single vertex
    if (graph.num_vertices() == 1) {
        vertices.push_back(u);
        scc.push_back(vertices);
    }


    //finds how many traversals are needed to
    for (auto itr = graph.nbegin(u); itr != graph.nend(u); ++itr) {
        if (index[*itr] == -1) {
            strongconnect(*itr, visited, index, low, graph, scc);
            low[u] = low[u] < low[*itr] ? low[u] : low[*itr];
        } else if (visited[*itr]) {
            low[u] = low[u] < index[*itr] ? low[u] : index[*itr];
        }
    }

    //vertices of the same depth index form a strongly connected component
    if (index[u] == low[u]) {
        std::vector<vertex> vertices;
        vertex v;
        do {
            v = st.top();
            visited[v] = false;
            vertices.push_back(v);
            st.pop();
        } while (u != v);
        scc.push_back(vertices);
    }
}

template<typename vertex>
std::vector<std::vector<vertex>> strongly_connected_components(const directed_graph<vertex> &d) {
    directed_graph<vertex> graph = directed_graph<vertex>(d);
    std::vector<std::vector<vertex>> scc;
    std::unordered_map<vertex, int> index;
    std::unordered_map<vertex, bool> visited;
    std::unordered_map<vertex, int> low;

    for (auto itr = d.begin(); itr != d.end(); ++itr) {
        visited.insert(std::make_pair(*itr, false));
        index.insert(std::make_pair(*itr, -1));
        low.insert(std::make_pair(*itr, -1));
    }

    //if it is a directed acyclic graph then every vertex is a strongly connected component
    if (is_dag(d)) {
        for (auto vitr = d.begin(); vitr != d.end(); ++vitr) {
            std::vector<vertex> vertices;
            vertices.push_back(*vitr);
            scc.push_back(vertices);
        }
        return scc;
    }

    //Gives each vertex an index (that aren't equal to -1), components of the same index form a strongly connected component
    for (auto itr = d.begin(); itr != d.end(); ++itr) {
        if (index[*itr] == -1) {
            strongconnect(*itr, visited, index, low, graph, scc);
        }
    }


    return scc;
}


/*
 * Computes the shortest distance from u to every other vertex
 * in the graph d. The shortest distance is the smallest number
 * of edges in any path from u to the other vertex.
 * If there is no path from u to a vertex, set the distance to
 * be the number of vertices in d plus 1.
 */
 
template<typename vertex>
std::unordered_map<vertex, std::size_t> shortest_distances(const directed_graph<vertex> &d, const vertex &u) {
    std::unordered_map<vertex, std::size_t> dist;
    std::unordered_map<vertex, bool> visited;

    //intialises visited map for every vertex
    for (auto itr = d.begin(); itr != d.end(); ++itr) {
        visited.insert(std::make_pair(*itr, false));
        dist.insert(std::make_pair(*itr, d.num_vertices() + 1));
    }
    
    //set distance from source to 0
    dist[u] = 0;

    std::queue<vertex> unprocessed;

    //push u into queue
    unprocessed.push(u);
    std::vector<vertex> ordered;
    
    while (!unprocessed.empty()) {
        auto n = unprocessed.front();
        unprocessed.pop();
        if (!visited[n]) {
            for (auto itr = d.nbegin(n); itr != d.nend(n); ++itr) {
                if (dist[*itr] > dist[n] + 1) {
                    dist[*itr] = dist[n] + 1;
                }
            }
            visited[n] = true;
            auto max = n;
            for (auto itr = d.nbegin(n); itr != d.nend(n); ++itr) {
                if (dist[*itr] > dist[n]) {
                    max = *itr;
                }
                unprocessed.push(max);
            }
        }
    }


    return dist;
}



