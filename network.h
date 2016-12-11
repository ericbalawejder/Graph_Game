#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

#include"stack.h"

// neighbor node for the network
struct NeighborNode
{
	int label;
	//distance from its parent
	int weight;
	NeighborNode* neighbor;
};

// backbone node for the network
struct BackboneNode
{
	int label;
	BackboneNode* nextbone;
	NeighborNode* neighbor;
};

// use to find shortest path
struct Edge
{
	int length;
	Edge* parent;
	BackboneNode* node;
};

class Network
{
	public:
		// constructor
		Network();
        void createNetwork(string[], int&);
		bool insertBackbone(const int&);
		bool shortestPath(const int&, const int&);
		// print out the network
		void printNetwork();
        // create neighbor
		bool createNeighborNode(const int&, const int&, const int&); 
		// find backbone
		BackboneNode* findBackbone(const int&);  
		// find neighbor 
		NeighborNode* findNeighbor(const int&, const int&);
		//see if in stack  
        bool inStack(int&, int&, Stack<Edge*>&);
        bool calculateMove(Stack<int>&, Stack<int>&, int&);
		
	private:
		BackboneNode* start;
};

#endif