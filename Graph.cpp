#include "Graph.hpp"

//setting up constructor for the edge class
Edge::Edge(string alabel_, string blabel_, unsigned long w_){
	alabel = alabel_; //set value for edge 1
	blabel = blabel_;	//set value for edge 2
	w = w_;	//weight of the edge
}

//deallocating dynamic memory through deconstructor
Graph::~Graph()
{
	for(unsigned int i = 0; i < vertices.size(); ++i)
    {
        delete vertices[i]; //delete all vertices using iteration
    }

	for(unsigned int i = 0; i < vertices.size(); ++i)
    {
        delete edges[i];	//delete all adges connected to it
    }

    vertices.clear();
	edges.clear(); 	//clear the space occupied by the variable
}

void Graph::addVertex(string label)
{
	Vertex *newVertex = new Vertex; //add Vertex
	newVertex->value = label;	//set value of the vertex point
	newVertex->minDist = 0x3f3f3f3f;  //setting the distance to infinity because it is not yet connected to anything
	newVertex->shortestPath = { "" };	//returns empty string
	newVertex->visited = false;	//flag variable turned off as it is not yet visited
	vertices.push_back(newVertex);	//add to the vertices vector
}

//method to remove or delete the given vertex
void Graph::removeVertex(string label)
{
	for (unsigned int i = 0; i < vertices.size(); i++) {
		if (vertices.at(i)->value == label) {
			vertices.erase(vertices.begin() + i);	//erase the given vertex with the label
		}
	}
//remove all the edges connected to the vertex
	for (unsigned int i = 0; i < edges.size(); i++) {
		if ((edges.at(i)->alabel == label) || (edges.at(i)->blabel == label)) {
			edges.erase(edges.begin() + i);
		}
	}
}

//method to connect the edges
void Graph::addEdge(string label1, string label2, unsigned long weight)
{//connect edge to vertex
	Edge *Edge1 = new Edge(label1, label2, weight);
	edges.push_back(Edge1);
//connect the different end of the vertex
	Edge *Edge2 = new Edge(label2, label1, weight);
	edges.push_back(Edge2);
}

//method to remove the edge
void Graph::removeEdge(string label1, string label2)
{
	for (unsigned int i = 0; i < edges.size(); i++) {
		if ((edges.at(i)->alabel == label1) && (edges.at(i)->blabel == label2)) {
			edges.erase(edges.begin() + i);
		}
	}
}

//traversing through the shortest path dijkstra's algor
unsigned long Graph::shortestPath(string start, string end, vector<string>& path)
{
	unsigned long shortestDist;

//set the start point to the value inserted by the user
	for (unsigned int i = 0; i < vertices.size(); i++) {
		if (vertices.at(i)->value == start) {
			vertices.at(i)->minDist = 0;
			vertices.at(i)->shortestPath.clear();
			vertices.at(i)->shortestPath.push_back(start); //start ipoint set with distance 0
		}
	}

//put the paths visited in the priority queue
	priority_queue<pair<unsigned long, string>, vector<pair<unsigned long, string>>, greater<pair<unsigned long, string>>> shortPaths;
//make the first pair
	shortPaths.push(make_pair(0, start));

	do {
		string minElem = shortPaths.top().second;//move to the top
		shortPaths.pop();	//remove it

		int minVertexIndex;
		for (unsigned int i = 0; i < vertices.size(); i++) {
			if (vertices.at(i)->value == minElem) {
				minVertexIndex = i;
			}
		}

		for (unsigned int j = 0; j < edges.size(); j++) {
			if (edges.at(j)->alabel == minElem) {
				for (unsigned int k = 0; k < vertices.size(); k++) { //if the smallest path is available then update the current weight to the new weight and add the min distance to the weight
					if ((edges.at(j)->blabel == vertices.at(k)->value) && ((vertices.at(minVertexIndex)->minDist + edges.at(j)->w) < vertices.at(k)->minDist) && (vertices.at(k)->visited == false)) {
						vertices.at(k)->minDist = vertices.at(minVertexIndex)->minDist + edges.at(j)->w;
						if (minElem == start) {
							vertices.at(k)->shortestPath.clear();
							vertices.at(k)->shortestPath.push_back(start);
						}
						else {
							vertices.at(k)->shortestPath.clear();
							vertices.at(k)->shortestPath = vertices.at(minVertexIndex)->shortestPath;
							vertices.at(k)->shortestPath.push_back(vertices.at(minVertexIndex)->value);
						}
						shortPaths.push(make_pair(vertices.at(k)->minDist, vertices.at(k)->value));
					}
				}
			}
		}
		vertices.at(minVertexIndex)->visited = true; //once the node/vertex is visited it is added to the list of shortest path and never visited again
	}while (!shortPaths.empty()); //do this until the list is complete


	for (unsigned int i = 0; i < vertices.size(); i++) {
		if (end == vertices.at(i)->value) {
			shortestDist = vertices.at(i)->minDist;
			vertices.at(i)->shortestPath.push_back(end);
			path = vertices.at(i)->shortestPath;
		}
	}


	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices.at(i)->minDist = 0x3f3f3f3f;
		vertices.at(i)->shortestPath = { "" };
		vertices.at(i)->visited = false;
	}

	return shortestDist;
}
