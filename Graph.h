// ----------------------
// projects/graph/Graph.h
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector
#include <list>
#include <deque>
#include <functional>
#include <numeric>
#include "PFD.h"

// -----
// Graph
// -----
// template <typename V = int, typename VC = std::set<V>, typename E = int, typename EC = std::deque<E>, bool DIRECTED = true>
class Graph {
    public:
        // --------
        // typedefs
        // --------

        typedef int vertex_descriptor;  // fix! DONE
        typedef std::pair<vertex_descriptor, vertex_descriptor> edge_descriptor;    // fix! DONE

        typedef std::vector<vertex_descriptor>::const_iterator vertex_iterator;    // fix! DONE
        typedef std::vector<edge_descriptor>::const_iterator edge_iterator;      // fix! DONE
        typedef std::set<vertex_descriptor>::const_iterator adjacency_iterator; // fix! DONE

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * <your documentation> DONE
         add edge (u, v) to graph g
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor u, vertex_descriptor v, Graph& g) {
            // <your code> DONE
            edge_descriptor ed = std::make_pair(u, v);
            // bool            b;

            // ae is a pair returning the iterator of the inserted vertext v2 and bool whether v2 was inserted
            std::pair<adjacency_iterator,bool> ae = g._g[u].insert(v);
            if(ae.second == true) 
                g._ec.push_back(ed);
            // assert(valid());
            return std::make_pair(ed, ae.second);}

        // ----------
        // add_vertex
        // ----------

        /**
         * <your documentation> DONE
         add a vertex v to graph g 
         */
        friend vertex_descriptor add_vertex (Graph& g) {
            // <your code> DONE 
            vertex_descriptor v = g._g.size();
            g._vc.push_back(v);
            g._g.push_back(std::set<vertex_descriptor>());
            // assert(valid());
            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * <your documentation> DONE
         returns first and last+1 iterators for vertices adjacent to vertex v in graph g
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor v, const Graph& g) {
            // <your code> DONE

            adjacency_iterator b = g._g[v].begin();
            adjacency_iterator e = g._g[v].end();
            return std::make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         * <your documentation> DONE
         returns the edge_descriptor for the given vertices u & v in graph g and if the edge exists
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor u, vertex_descriptor v, const Graph& g) {
            // <your code> DONE
            edge_descriptor ed = std::make_pair(u, v);
            // bool            b;

            // find(g._ec.begin(), g._ec.end(), v) != g._ec.end();
            return std::make_pair(ed, find(g._ec.begin(), g._ec.end(), ed) != g._ec.end());}

        // -----
        // edges
        // -----

        /**
         * <your documentation> DONE
         returns first and last+1 iterators to edges in graph g
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& g) {
            // <your code> DONE
            edge_iterator b = g._ec.begin();
            edge_iterator e = g._ec.end();
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * <your documentation> DONE
         returns the number of edges in graph g
         */
        friend edges_size_type num_edges (const Graph& g) {
            // <your code> DONE
            // edges_size_type s;
            return g._ec.size();}

        // ------------
        // num_vertices
        // ------------

        /**
         * <your documentation> DONE
         returns the number of vertices in graph g
         */
        friend vertices_size_type num_vertices (const Graph& g) {
            // <your code> DONE
            // vertices_size_type s;
            return g._vc.size();}

        // ------
        // source
        // ------

        /**
         * <your documentation> DONE
         returns the source vertex of edge ed
         */
        friend vertex_descriptor source (edge_descriptor ed, const Graph& g) {
            // <your code> DONE
            // vertex_descriptor v;
            return ed.first;}

        // ------
        // target
        // ------

        /**
         * <your documentation> DONE
         returns the target vertex of edge ed
         */
        friend vertex_descriptor target (edge_descriptor ed, const Graph& g) {
            // <your code> DONE
            // vertex_descriptor v;
            return ed.second;}

        // ------
        // vertex
        // ------

        /**
         * <your documentation> DONE
         returns the vertex_descriptor corresponding to s in graph g
         */
        friend vertex_descriptor vertex (vertices_size_type s, const Graph& g) {
            // <your code> DONE
            // vertex_descriptor vd;
            return g._vc[s];}

        // --------
        // vertices
        // --------

        /**
         * <your documentation> DONE
         return first and last+1 iterators for vertices in graph g
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& g) {
            // <your code> DONE
            vertex_iterator b = g._vc.begin();
            vertex_iterator e = g._vc.end();
            return std::make_pair(b, e);}

    private:
        // ----
        // data
        // ----

        std::vector<std::set<vertex_descriptor> > _g; // vector of vertices containing set of adjacent vertices
        std::vector<vertex_descriptor> _vc;  // vector of  vertices for a graph
        std::vector<edge_descriptor> _ec; //  vector of edges for the graph

        // -----
        // valid
        // -----

        /**
         * <your documentation>
         */
        bool valid () const {
            // <your code>

            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Graph (std::vector<std::set<vertex_descriptor> > g = std::vector<std::set<vertex_descriptor> >(), std::vector<vertex_descriptor> vc = std::vector<vertex_descriptor>(), std::vector<edge_descriptor> ec = std::vector<edge_descriptor> ()) :
                _g(g),
                _vc(vc),
                _ec(ec)
            {
            // <your code>
            assert(valid());
        }

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };


// ----------------
// dfs_recursive
// ----------------

/** 
 * three color dfs
 * 
 */
 template <typename G, typename RI>
 bool dfs_recursive(const G& g, typename G::vertex_descriptor currVert, RI it, bool has_cycle = false){
    it[currVert] = 1;
    auto itPair = adjacent_vertices(g, currVert);
    typename G::adjacency_iterator begin = itPair.first();
    typename G::adjacency_iterator end = itPair.second();
    while(begin != end){
        
        if(it[*begin] == 1)
            has_cycle = true;

        if(it[*begin] == 0){
            has_cycle = has_cycle || dfs_recursive(g,*begin,it);}
            ++begin;}
    
    it[currVert] = 2;
    
    return has_cycle;}

// ---------
// has_cycle
// ---------

/**
 * depth-first traversal
 * three colors
 * <your documentation>
 */
template <typename G>
bool has_cycle (const G& g) {
    auto edgeItPair = g.edges(g);
    typename G::edge_iterator edgesBegin = edgeItPair.first();
    typename G::edge_iterator edgesEnd = edgeItPair.second();
    int verts[const_cast<size_t>(g.num_vertices())] = {0};
    do {
        typename G::vertex_descriptor beginVert = *(edgesBegin).source();
        if(dfs_recursive(g,beginVert,verts))
            return true;
        ++edgesBegin;} while(edgesBegin != edgesEnd && (std::accumulate(verts,verts+g.num_vertices(),0,std::plus<int>()) != 2*g.num_vertices())); 
    return false;}

// ----------------
// topological_sort
// ----------------

/**
 * depth-first traversal
 * two colors
 * <your documentation>
 * @throws Boost's not_a_dag exception if has_cycle()
 */
template <typename G, typename OI>
void topological_sort (const G& g, OI x) {
    if(has_cycle(g))
        throw boost::not_a_dag("");
    auto vertsItPair = vertices(g);
    typename G::vert_iterator vertBegin = vertsItPair.first();
    typename G::vert_iterator vertEnd = vertsItPair.second();
    std::stringstream in;
    typename G::edges_size_type numRules = 0;
    typename G::vertices_size_type numVerts = num_vertices(g);
    while(vertBegin!=vertEnd){
        auto itPair = adjacent_vertices(g, *vertBegin);
        typename G::adjacency_iterator begin = itPair.first();
        typename G::adjacency_iterator end = itPair.second();
        typename G::vertices_size_type numAdj = std::distance(begin,end);
        if(numAdj){
            ++numRules;
            in<<*vertBegin<<" "<<numAdj;
            while(begin!=end){
                in<<" "<<*begin;
                ++begin;}
            in<<std::endl;}
        ++vertBegin;}
    
    std::vector<node> graph = PFD_read(numVerts, numRules, in);
    std::vector<int> result = PFD_eval(graph);
    std::copy(result.begin(),result.end(),x);
    // *x = 2;
    // ++x;
    // *x = 0;
    // ++x;
    // *x = 1;
    }

#endif // Graph_h
