#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <iostream>

/* 
 * Yuval Shafir -- Lab Section A52
 * Lucas Eager Leavitt -- Lab Section A52
 *
 * Yuval will handle the constructor, input/output, searching, and the Subgraph
 *    Test
 * Lucas will handle the Partition, Tree Check, Minimum Weight components and 
 *    Print Valued Path
 *
*/

//This class will be used to create a graph library.

/**Whenever paths are to be printed, they should be printed with 
	v1 -> v2 -> v3 -> ...
where v1, v2, and v3 are replaced with the names of the vertex **/

/**Whenever trees are to be printed, they should be printed with
	{V, E} 
where V is the set of vertices, and E is the set of edges 
(note: V and E are sets and should be enclosed in brackets)**/

#include <string>
#include <unordered_map>
#include <vector>

class Graph{
	private:
		// This holds the connected name and the corresponding weight 
		struct EdgeInfo{
			std::string name;
			int weight;
			EdgeInfo() { }
			EdgeInfo(std::string n, int w) : name(n), weight(w) { }
		};

		// This will hold the data members of the vertices, including an adjacency list
		struct VertexInfo{
			float value;
			std::vector<EdgeInfo> edges;
			VertexInfo() { }
			VertexInfo(float v) : value(v) { }
		};

		struct nodepath{
	        	float total;
		        std::vector<std::string> path;
		        nodepath() : total(0.0) {}
		};
		
		// A map is used so that the name is used as the index
		std::unordered_map<std::string, VertexInfo> vertices;

		int connectedNodes(std::string source, std::unordered_map<std::string, bool>& visited);
		bool DFS_aux(std::string source, std::string val, std::unordered_map<std::string, bool>& visited);
		bool tree_aux(std::string node, std::string parent, std::unordered_map<std::string, bool>& visited);
		bool partitionable_aux(std::string node, int side, std::unordered_map<std::string, int>& visited);
		
	//	void printPathHelper(std::vector<std::string>& path, float& closestVal, std::string current, float value, std::unordered_map<std::string, bool>& visited, std::unordered_map<std::string, float>& pathVal);
	//void CloseVal_aux(std::string, float, std::vector<std::string>, float&, std::vector<std::string>&);
		void CloseVal_aux(std::string name, nodepath npath, float value, nodepath& final);
	public:
		Graph() { }
		//Read input from a file
		void readFromFile(std::string file);
		//Write A Graph To A File -- Prints out based on the data members in the correct format
		void writeToFile(std::string file);
		//Empty -- checks if vertices map is empty
		bool empty();
		//Add Edge -- pushes back to the adjacency list
		void addEdge(std::string v1, std::string v2, int weight);
		//Add Vertex -- adds to the map the name as the key and constructs the vertexInfo
		void addVertex(std::string name, float val);
		//Count Connected Components -- Traverse the vertices and check that each vertex has a path to all other vertices
		int numConnectedComponents();
		//Tree Check -- Include a visited map. Use first vertex, traverse its edge list recursively and check that it does not visit an already visited node.
		bool tree();
		//Minimum Weight Components -- Check that it is a tree, then traverse all paths and find the minimum weigth
		void minWeightComponent(std::string src);
		//Depth First Search -- search using DFS
		bool DFS(std::string source, std::string val);
		//Breadth First Search -- search using BFS
		bool BFS(std::string source, std::string val);
		//Closeness -- traverse the edge list recursively and find the shortest path
		int closeness(std::string v1, std::string v2);
		//Partition -- check if there is alternating connections
		bool partitionable();
		//* Subgraph Test -- check that g's vertices are in this object's vertices and the same for the edges
		bool isSubGraph(const Graph& g);
		//Print Valued Path -- Use Djikstra's algorithm to find the path to make the value
		void printPathCloseVal(float value);
};

#endif
