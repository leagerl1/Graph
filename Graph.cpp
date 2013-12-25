#include "Graph.h"


#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
#include <cctype>
#include <climits>

using namespace std;

		/* This holds the connected name and the corresponding weight 
		struct EdgeInfo{
			std::string name;
			int weight;
		};

		// This will hold the data members of the vertices, including an adjacency list
		struct VertexInfo{
			int value;
			std::vector<EdgeInfo> edges;
		};
		
		// A map is used so that the name is used as the index
		std::unordered_map<std::string, VertexInfo> vertices;
	*/

void clear_spaces(string& str){
	if(str.size() > 0){
		str.erase(0, 1);
	}
}

#include <sstream>
void Graph::readFromFile(string file){
	vertices.clear(); 
	fstream fin(file);
	string temp;
	getline(fin, temp);
	stringstream ss(temp);
	int N;
	ss >> N;
	for(int i = 0; i < N; i++){
		getline(fin, temp);
		stringstream vss(temp);
		string name, val;
		getline(vss, name, ',');
		getline(vss, val);
		// take care of comma at the end, using a self-made pop_back
		float value = ::atof(val.c_str());
		addVertex(name, value);
	}
	while(getline(fin, temp)){
		//if name1 exits, the line also has name2 and weight
		stringstream ess(temp);
		string name1, name2, _weight;
		getline(ess, name1, ',');
		getline(ess, name2, ',');
		getline(ess, _weight);
		//erase whitespaces in strings
		clear_spaces(name2);
		int weight = ::atoi(_weight.c_str());
		addEdge(name1, name2, weight);
	}
	fin.close();
}

void Graph::writeToFile(string file){
	unordered_map<string, unordered_map<string, bool> > visited;
	cout << vertices.size() << endl; 
	for(auto it = vertices.begin(); it != vertices.end(); it++){
		cout << it->first << ", " << (it->second).value << endl;
	}
	for(auto it = vertices.begin(); it != vertices.end(); it++){
		// mark this vertex as visited, but still go through it to see if any of it's edges aren't marked
		size_t size = ((it->second).edges).size();
		for(int i = 0; i < size; i++){	
			string name2 = ((it->second).edges)[i].name;
			if(!(visited[it->first][name2])){
				// don't print duplicates
				visited[it->first][name2] = 1;
				visited[name2][it->first] = 1;
				cout << it->first << ", " << name2 << ", " << ((it->second).edges)[i].weight << endl;
			}
		}
	}
}

bool Graph::empty(){ 
	return vertices.empty();
}

void Graph::addEdge(string v1, string v2, int weight){
	if(vertices.find(v1) == vertices.end() || vertices.find(v2) == vertices.end()){
		cout << "One or more of the vertices do not exist, can't create edge" << endl;
		return;
	}
	for(int i = 0; i < vertices[v1].edges.size(); i++){
		if(vertices[v1].edges[i].name == v2){
			// update weight
			vertices[v1].edges[i].weight = weight;
			//do same for v2
			for(int j = 0; j < vertices[v2].edges.size(); j++){
				if(vertices[v2].edges[j].name == v1){
					vertices[v2].edges[j].weight = weight;
					return;
				}
			}
		}
	}
	EdgeInfo e1(v2, weight);
	EdgeInfo e2(v1, weight);
	
	(vertices[v1].edges).push_back(e1);
	(vertices[v2].edges).push_back(e2);
}

void Graph::addVertex(string name, float val){ 
	if(val < 0){
		cerr << name << " has a negative value. IGNORED." << endl;
		return;
	}
	if(vertices.find(name) != vertices.end()){
		vertices[name].value = val;
		return;
	}
	VertexInfo vertex(val);
	vertices[name] = vertex;
}

int Graph::connectedNodes(string source, unordered_map<string, bool>& visited){
        queue<string> nodes;
        nodes.push(source);
        visited[source] = 1;
	int ret = 0;
        while(!nodes.empty()){
                source = nodes.front();
                nodes.pop();
		ret++;
                for(int i = 0; i < vertices[source].edges.size(); i++){
                        string edge = vertices[source].edges[i].name;
                        if(!visited[edge]++){
                                nodes.push(edge);
                        }
                }
        }
        return ret;
}


int Graph::numConnectedComponents(){
	unordered_map<string, bool> visited;
	int total = 0;
	int components = 0;
	while(total < vertices.size()){
		components++;
		string node;
		for(auto it = vertices.begin(); it != vertices.end(); it++){
			if(!visited[it->first]){
				node = it->first;
				break;
			}
		}
		total += connectedNodes(node, visited);
	}
	return components;
}

bool Graph::tree_aux(string node, string parent, unordered_map<string, bool>& visited){
	for(int i = 0; i < vertices[node].edges.size(); i++){
		string adj = (vertices[node].edges)[i].name;
		if(adj != parent && visited[adj]){
			return false;
		}
		visited[adj]++;
		if(adj != parent && !tree_aux(adj, node, visited))
			return false;
	}
	return true;
}

bool Graph::tree(){
	if(numConnectedComponents() > 1) return false;
	unordered_map<string, bool> visited;
	string node = (vertices.begin())->first;
	visited[node] = 1;
	for(int i = 0; i < vertices[node].edges.size(); i++){
		string adj = (vertices[node].edges)[i].name;
		if(!tree_aux(adj, node, visited))
			return false;
	}
	return true;
}

void Graph::minWeightComponent(string src){
	unordered_map<string, bool> totalhelp;
	int total = connectedNodes(src, totalhelp);
	int completed = 1;
	vector<string> minTree;
	vector<string> edges;
	minTree.push_back(src);
	
	unordered_map<string, unordered_map<string, bool> > visited;
	while(completed < total){
		//this will change to find smallest edge
		int min = INT_MAX;
		string smin1, smin2;
		for(int i = 0; i < minTree.size(); i++){
			string name1 = minTree[i];
			for(int j = 0; j < vertices[name1].edges.size(); j++){
				string name2 = vertices[name1].edges[j].name;
				if(!visited[name1][name2] && vertices[name1].edges[j].weight < min){
					min = vertices[name1].edges[j].weight;
					smin1 = name1;
					smin2 = name2;
				}
			}
		}
		minTree.push_back(smin2);
		edges.push_back(smin1);
		edges.push_back(smin2);
		visited[smin1][smin2] = 1;
		visited[smin2][smin1] = 1;
		completed++;
	}

	cout << "{{";
	for(int i = 0; i < minTree.size();i++){
	  cout << minTree[i];
	  if(i < minTree.size()-1)     
	    cout  << ", ";
	}
	cout << "}, {";
	for(int i = 0; i < edges.size(); i++){
		cout << "(" << edges[i] << ", ";
		i++;
		cout << edges[i] << ")";
		if(i < edges.size()-1)
		  cout << ",";
	}
	cout << "}}" << endl << endl;
	
}

bool Graph::DFS_aux(string node, string val, unordered_map<string, bool>& visited){
	if(node == val)
		return true;
	visited[node] = 1;
	bool ret = false;
	for(int i = 0; i < vertices[node].edges.size(); i++){
		string adj = (vertices[node].edges)[i].name;
		if(!visited[adj]){
			if(DFS_aux(adj, val, visited)){
				ret = true;
				break;
			}
		}
	}
	return ret;
	
}

bool Graph::DFS(string source, string val){
	// Makse sure that source is in the vertices
	if(vertices.find(source) == vertices.end())
		return false;
	unordered_map<string, bool> visited;
	
	return DFS_aux(source, val, visited);
}

bool Graph::BFS(string source, string val){
	if(vertices.find(source) == vertices.end())
		return false;
	unordered_map<string, bool> visited;
	queue<string> nodes;
	nodes.push(source);
	visited[source] = 1;
	while(!nodes.empty()){
		source = nodes.front();
		nodes.pop();
		if(source == val)
			return true;
		for(int i = 0; i < vertices[source].edges.size(); i++){
			string edge = vertices[source].edges[i].name;
			if(!visited[edge]++){
				nodes.push(edge);
			}
		}
	}
	return false;
}

int Graph::closeness(string v1, string v2){ }

bool Graph::partitionable_aux(string node, int side, unordered_map<string, int>& visited){
	for(int i = 0; i < vertices[node].edges.size(); i++){
		string name = vertices[node].edges[i].name;
		if(visited[name] == 0){
			visited[name] = -side;
			if(!partitionable_aux(name, -side, visited)){
				return false;
			}
		} else if(visited[name] == side){
			return false;
		} // else it has already been visited
	}
	return true;
}

bool Graph::partitionable(){
        if(numConnectedComponents() > 1) return false;
	// visited will hold the class of each element: 1 and -1
        unordered_map<string, int> visited;
        string node = (vertices.begin())->first;
	visited[node] = 1;
        return partitionable_aux(node, 1, visited);
}

bool Graph::isSubGraph(const Graph& g){
	// iterator through all vertices in g
	for(auto it = g.vertices.begin(); it != g.vertices.end(); it++){
		string v = it->first;
		//make sure v exists
		if(vertices.find(v) == vertices.end()){
			return false;
		}
		for(int i = 0; i < it->second.edges.size(); i++){
			string adj = it->second.edges[i].name;
			bool found = false;
			for(int j = 0; j < vertices[v].edges.size(); j++){
				if(adj == vertices[v].edges[j].name){
					found = true;
					break;
				}
			}
			if(!found)
				return false;
		}
	}
	return true;
}


#include <cfloat>

float Fabs(float v){
	if(v < 0)
		return -v;
	else
		return v;
} 


bool leftequals(float left, float right, float value){
	float l = Fabs(left - value);
	float r = Fabs(right - value);
	return l == r;
}

bool leftcloser(float left, float right, float value){
	float l = Fabs(left - value);
	float r = Fabs(right - value);
	return l < r;
}

/*struct nodepath{
	float total;
	vector<string> path;
	nodepath() : total(0.0), bool(0) {}
};*/

void Graph::CloseVal_aux(string name, nodepath npath, float value, nodepath& final){
	npath.path.push_back(name);
	npath.total += vertices[name].value;
	if(leftequals(npath.total, final.total, value)){
		final.path.push_back("\n---\n");
		final.path.insert(final.path.end(), npath.path.begin(), npath.path.end());
	} else if(leftcloser(npath.total, final.total, value)){
		final = npath;
	}

	for(int i = 0; i< vertices[name].edges.size(); i++){
		string nextstr = vertices[name].edges[i].name;
                bool visited = false;
                for(int j = 0; j < npath.path.size(); j++){
                        if(npath.path[j] == nextstr){
                                visited = true;
                                break;
                        }
                }
                if(!visited && leftcloser(npath.total + vertices[nextstr].value, npath.total, value)){
                        CloseVal_aux(nextstr, npath, value, final);
                }
	}
}

void Graph::printPathCloseVal(float value){
	nodepath final;
	final.total = FLT_MAX;
	for(auto it = vertices.begin(); it != vertices.end(); it++){
		nodepath path;
		CloseVal_aux(it->first, path, value, final);
	}
	for(int i = 0; i < final.path.size(); i++){
		cout << final.path[i] << " ";
		if(i < final.path.size()-1)
		  cout << "-> ";
	}
}


