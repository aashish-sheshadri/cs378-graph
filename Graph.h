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
         * add edge (u, v) to graph g
         * @param u is a vertex_descriptor by value
         * @param v is a vertex descriptor by value
         * @param g is a Graph taken by reference
         * @return a Pair of edge_descriptor and bool indicating sucess of edge creation
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor u, vertex_descriptor v, Graph& g) {
            // <your code> DONE
            edge_descriptor ed = std::make_pair(u, v);
            // bool            b;

            // ae is a pair returning the iterator of the inserted vertext v2 and bool whether v2 was inserted
            std::pair<adjacency_iterator,bool> ae = g._g[u].insert(v);
            if(ae.second == true) 
                g._ec.push_back(ed);
            assert(g._g.size() == g._vc.size());
            return std::make_pair(ed, ae.second);}

        // ----------
        // add_vertex
        // ----------

        /**
         * add a vertex v to graph g 
         * @param g is a Graph taken by reference
         * @return vertex_descriptor for newly added vertex
         */
        friend vertex_descriptor add_vertex (Graph& g) {
            // <your code> DONE 
            vertex_descriptor v = g._g.size();
            g._vc.push_back(v);
            g._g.push_back(std::set<vertex_descriptor>());
            assert(g._g.size() == g._vc.size());
            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * returns begin and end iterators over adjacent vertices of input vertex
         * @param v is a vertex descriptor by value
         * @param g is a Graph taken by reference
         * @return Pair of begin and end iterators over adjacent vertices
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor v, const Graph& g) {
            // <your code> DONE

            adjacency_iterator b = g._g[v].begin();
            adjacency_iterator e = g._g[v].end();
            assert(g._g.size() == g._vc.size());
            return std::make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         * Finds edge_descriptor for the input vertices graph
         * @param u is a vertex_descriptor by value
         * @param v is a vertex_descriptor by value
         * @param g is a Graph taken by reference
         * @return Pair of edge_descriptor and bool for the input vertices, false is edge not present
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor u, vertex_descriptor v, const Graph& g) {
            // <your code> DONE
            edge_descriptor ed = std::make_pair(u, v);
            assert(g._g.size() == g._vc.size());
            return std::make_pair(ed, find(g._ec.begin(), g._ec.end(), ed) != g._ec.end());}

        // -----
        // edges
        // -----

        /**
         * begin and end iterators to edges in graph
         * @param g is Graph by reference
         * @return a pair of begin and end iterators over edges in graph
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& g) {
            // <your code> DONE
            edge_iterator b = g._ec.begin();
            edge_iterator e = g._ec.end();
            assert(g._g.size() == g._vc.size());
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * Number of edges in graph g
         * @param g is a Graph by reference
         * @return number of edges in graph
         */
        friend edges_size_type num_edges (const Graph& g) {
            // <your code> DONE
            // edges_size_type s;
            assert(g._g.size() == g._vc.size());
            return g._ec.size();}

        // ------------
        // num_vertices
        // ------------

        /**
         * Number of vertices in graph g
         * @param g is a Graph by reference
         * @return number of vertices in graph
         */
        friend vertices_size_type num_vertices (const Graph& g) {
            // <your code> DONE
            // vertices_size_type s;
            assert(g._g.size() == g._vc.size());
            return g._vc.size();}

        // ------
        // source
        // ------

        /**
         * Source vertex of edge
         * @param ed is a edge_descriptor by value
         * @param g is a Graph by reference
         * return source vertex of edge
         */
        friend vertex_descriptor source (edge_descriptor ed, const Graph& g) {
            // <your code> DONE
            // vertex_descriptor v;
            assert(g._g.size() == g._vc.size());
            return ed.first;}

        // ------
        // target
        // ------

        /**
         * Target vertex of edge
         * @param ed is a edge_descriptor by value
         * @param g is a Graph by reference
         * return target vertex of edge
         */
        friend vertex_descriptor target (edge_descriptor ed, const Graph& g) {
            // <your code> DONE
            // vertex_descriptor v;
            assert(g._g.size() == g._vc.size());
            return ed.second;}

        // ------
        // vertex
        // ------

        /**
         * vertex_descriptor to corresponding vertex in graph
         * @param s is vertices_size_type taken by value
         * @param g is a Graph taken by refrence
         * @return vextex_descriptor for vertex
         */
        friend vertex_descriptor vertex (vertices_size_type s, const Graph& g) {
            // <your code> DONE
            // vertex_descriptor vd;
            assert(g._g.size() == g._vc.size());
            return g._vc[s];}

        // --------
        // vertices
        // --------

        /**
         * begin and end iterators over vertices in graph
         * @param g is Graph by reference
         * @return pair of iterators over vertices in graph
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& g) {
            // <your code> DONE
            vertex_iterator b = g._vc.begin();
            vertex_iterator e = g._vc.end();
            assert(g._g.size() == g._vc.size());
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
            return (_g.size() == _vc.size());}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * Constructor
         * g is a vector of sets of type vertex_descriptor by value (defaulted)
         * vc is a vector of vertex_descriptor by value (defaulted)
         * ec is a vector of edge_descriptor by value (defaulted)
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
 * @param g is Graph by reference
 * @param currVert is a vertex_descriptor by value
 * @param it is a Random Access iterator
 * @param topSort is a deque by reference
 * @param has_cycle is a bool by value
 * @return bool indicating presence of a back edge
 */
 template <typename G, typename RI>
 bool dfs_recursive(const G& g, typename G::vertex_descriptor currVert, RI it, std::deque<typename G::vertex_descriptor>& topSort, bool has_cycle = false){
    if(it[currVert] == 0)
        it[currVert] = 1;
    else
        return has_cycle;
    
    auto itPair = adjacent_vertices(currVert, g);
    typename G::adjacency_iterator begin = itPair.first;
    typename G::adjacency_iterator end = itPair.second;
    while(begin != end){
        
        if(it[*begin] == 1)
            has_cycle = true;

        if(it[*begin] == 0){
            has_cycle = has_cycle || dfs_recursive(g,*begin,it, topSort);}
        ++begin;}
    
    
    if(has_cycle){
        topSort.clear();
    } else {
        if(it[currVert]!=2)
            topSort.push_front(currVert);}
    it[currVert] = 2;
    return has_cycle;}

// ---------
// has_cycle
// ---------

/**
 * Detects cycle in graph
 * @param g is a Graph by reference
 * @return bool indicating presence of cycle in the graph
 */
template <typename G>
bool has_cycle (const G& g) {
    auto edgeItPair = edges(g);
    typename G::edge_iterator edgesBegin = edgeItPair.first;
    typename G::edge_iterator edgesEnd = edgeItPair.second;
    int numVerts = num_vertices(g);
    assert(numVerts!=0);
    std::vector<int> verts(numVerts,0);
    std::deque<typename G::vertex_descriptor> topSort;
    do {  
        typename G::vertex_descriptor beginVert = source(*(edgesBegin),g);
        if(dfs_recursive(g,beginVert,verts.begin(), topSort))
            return true;
        ++edgesBegin;} while(edgesBegin != edgesEnd && (std::accumulate(verts.begin(),verts.end(),0,std::plus<int>()) != 2*numVerts)); 
    return false;}

// ----------------
// topological_sort
// ----------------

/**
 * Performs a topological sort
 * @param g is Graph by reference
 * @param x is an output iterator  
 * @throws Boost's not_a_dag exception if has_cycle()
 */
template <typename G, typename OI>
void topological_sort (const G& g, OI x) {
    auto edgeItPair = edges(g);
    typename G::edge_iterator edgesBegin = edgeItPair.first;
    typename G::edge_iterator edgesEnd = edgeItPair.second;
    int numVerts = num_vertices(g);
    assert(numVerts!=0);
    std::vector<int> verts(numVerts,0);
    std::deque<typename G::vertex_descriptor> topSort;
    do {  
        typename G::vertex_descriptor beginVert = source(*(edgesBegin),g);
        if(dfs_recursive(g,beginVert,verts.begin(), topSort))
            throw boost::not_a_dag();
        ++edgesBegin;} while(edgesBegin != edgesEnd && (std::accumulate(verts.begin(),verts.end(),0,std::plus<int>()) != 2*numVerts)); 
    std::copy(topSort.begin(),topSort.end(),x);}

#endif // Graph_h
