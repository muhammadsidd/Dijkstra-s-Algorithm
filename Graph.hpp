#ifndef GRAPH_H
#define GRAPH_H

#include"GraphBase.hpp"
#include <vector>
#include <string>
#include <queue>

using namespace std;


class Vertex {
public:
	string value;
	unsigned long minDist;
	vector<string> shortestPath;
	bool visited;
};


class Edge {
public:
	Edge(string a, string b, unsigned long w);
	string alabel;
	string blabel;
	unsigned long w;
};

class Graph : public GraphBase {
	friend class Vertex;
	friend class Edge;
public:
	~Graph();
	void addVertex(string label);
	void removeVertex(string label);
	void addEdge(string label1, string label2, unsigned long weight);
	void removeEdge(string label1, string label2);
	unsigned long shortestPath(string startLabel, string endLabel, vector<std::string> &path);

private:
	vector<Vertex*> vertices;
	vector<Edge*> edges;
};

#endif
