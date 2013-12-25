#include <iostream>
#include "Graph.h"

using namespace std;

int main(){
	Graph y;
	y.readFromFile("input2.txt");
	y.writeToFile("dfadd");
	cout << "Test DFS" << endl;
	cout << y.DFS("Philadelphia", "Trenton") << endl;
	cout << y.DFS("Trenton", "Boston") << endl;
	cout << y.DFS("Philadelphia", "Palo Alto") << endl;

	cout << "Test BFS" << endl;
	cout << y.BFS("Philadelphia", "Trenton") << endl;
	cout << y.BFS("Trenton", "Boston") << endl;
	cout << y.BFS("Philadelphia", "Palo Alto") << endl;

	cout << "Test Tree property" << endl;
	cout << y.tree() << endl << endl;

	cout << "Number of Components" << endl;
	cout << y.numConnectedComponents() << endl << endl;

	cout << "Partionable" << endl;
	cout << y.partitionable() << endl << endl;

	cout << "Minimum Weight Components" << endl;
	y.minWeightComponent("Los Angeles");
	y.minWeightComponent("New York");
	cout << endl << endl;

	cout << "Print Path Close Val" << endl;
	y.printPathCloseVal(41.7);
	cout << endl << endl;
	Graph x;
	x.readFromFile("input.txt");
	cout << "Test sub-graph" << endl;
	cout << y.isSubGraph(x) << endl;
	return 0;

}
