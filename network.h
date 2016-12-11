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

// constructor
Network::Network()
{
	start = NULL;
}

void Network::createNetwork(string* graph, int& size)
{
	string entry;
	// holds values at positon 2 and 3 of entry
	string backboneStringLabel;
	// holds values at position 3 and 4 of entry
	string neighborStringLabel; 
	// holds value at position 5 of entry
	string weightString; 
	// holding the backbone label, which is parsed out from input
	int backboneLabel;
	// holding the neighbor label, which is parsed out from input
	int neighborLabel;
	// hodling weight, which is parsed out from input
	int weight;           

	for(int i = 0; i < size; ++i)
	{
		entry = graph[i];
		
		// substr(start position, number of characters)
		backboneStringLabel = entry.substr(0,1);
		backboneLabel = atoi(backboneStringLabel.c_str());

		neighborStringLabel = entry.substr(1,1);
		neighborLabel = atoi(neighborStringLabel.c_str());
		
		weightString = entry.substr(2,1);
		weight = atoi(weightString.c_str());

		createNeighborNode(backboneLabel, weight, neighborLabel);
	}
}

// print the Network
void Network::printNetwork()
{
	cout << "Graph Table:" << endl;
	BackboneNode* tempBackbone = start;
	NeighborNode* tempNeighbor;
	while(tempBackbone)
	{
		cout << tempBackbone->label;
		tempNeighbor = tempBackbone->neighbor;
		while(tempNeighbor)
		{
		  	//cout << tempNeighbor->label << " ";
			//cout << "( with weight: " << tempNeighbor->weight << ")  ";
		    cout << " -> " << tempNeighbor->label << "  weight(" << tempNeighbor->weight << ")";
			tempNeighbor = tempNeighbor->neighbor;
		}
		cout << endl;
		tempBackbone = tempBackbone->nextbone;
	}
	cout << endl;
}

bool Network::inStack(int& bLabel, int& nLabel, Stack<Edge*>& pathStack)
{
	Edge* temp;
	int n = pathStack.size();
	// the first one in the pathStack is always the source record, which does not have parent.
	// There is no need to match that one. Following record will always have parent
	for(int i = 2; i <= n; ++i)
	{
		temp = pathStack.peekIndex(i);
		if(nLabel == temp->node->label && bLabel == temp->parent->node->label)
		{
			return true;
		}
	}
	return false;
}

// insert a new backbone, the label cannot be duplicated with existed ones
bool Network:: insertBackbone(const int& label)
{
    // duplicated backbone label; no insertion
    if(findBackbone(label))
	{
		return false;
	}

	// non duplicate, insert a new backbone with this label
	BackboneNode* current = new BackboneNode;
	current->nextbone = NULL;
	current->neighbor = NULL;
	current->label = label;

	if(!start)
	{
		start = current;
	}
	else
	{
		// insert at the tail
		BackboneNode* temp = start;
		while(temp->nextbone)
		{
			temp =  temp->nextbone;
		}
		temp->nextbone = current;
	}
	return true;
}

bool Network:: createNeighborNode(const int& pLabel, const int& weight, const int& nLabel)
{
	// if backbone with plabel does not exsist, create it
	BackboneNode* backbone = findBackbone(pLabel);
	if(!backbone)
	{
		insertBackbone(pLabel);
	}
	
	// if backbone with nLabel does not exsist, create it
    backbone = findBackbone(nLabel);
	if(!backbone)
	{
		insertBackbone(nLabel);
	}

	// set backbone to plabel node
	backbone = findBackbone(pLabel);
	
	// check to make sure you do not insert neighbor twice
	if(findNeighbor(pLabel, nLabel))
	{
		cout << "\nErr: Cannot insert neighbor. It already exists" << endl;
		return false;
	}

	// insert new neighbor to current backbone
	NeighborNode* current = new NeighborNode;
	current->neighbor = NULL;
	current->weight = weight;
	current->label = nLabel;
	
	// when backbone has not had neighbor yet, directly link the current to this back bone
	if(!backbone->neighbor)
	{
		backbone->neighbor = current;
	}
	else
	{
		NeighborNode* temp = backbone->neighbor;
		while(temp->neighbor)
		{
			temp = temp->neighbor;
		}
		temp->neighbor = current;
	}
	return true;
}

BackboneNode* Network:: findBackbone(const int& label)
{
	if(!start)
	{
		return NULL;
	}
	
	BackboneNode* temp = start;
	while(temp && temp->label != label)
	{
		temp = temp->nextbone;
	}
	return temp;
}

NeighborNode* Network:: findNeighbor(const int& plabel, const int& nlabel)
{
	if(!start)
	{
		return NULL;
	}
	
	BackboneNode* backbone = findBackbone(plabel);
	
	if(!backbone)
	{
		return NULL;
	}
	
	NeighborNode* firstNeighbor = backbone->neighbor;
	
	while(firstNeighbor && firstNeighbor->label != nlabel)
	{
		firstNeighbor = firstNeighbor -> neighbor;
	}
	return firstNeighbor;
}

bool Network:: calculateMove(Stack<int>& painted, Stack<int>& neighbor, int& n)
{
	// stacks for deep copy
	Stack<int> stackP, stackNB;
	// hold squares remaining
  	Stack<int> remaining;

    for(int i = 1; i <= 7; i++)
	{
	 	// deep copy painted
		for(int k = 0; k < painted.size(); k++)
		{
	   	 	stackP.push(painted.peekIndex(k));
		}

	 	// deep copy neighbor	 
        for(int k = 0; k< neighbor.size(); k++)
		{
	   		stackNB.push(neighbor.peekIndex(k));
   		}

	 	// if i is not in either stack, push onto stackP	 
	 	if(!stackP.isInStack(i) && !stackNB.isInStack(i))
		{

            // push input onto stack
	    	stackP.push(i);

	   	 	// push any neighbors of i onto stack
	   	 	for(int j = 1; j <= n; j++)
	   	 	{

	    		NeighborNode *temp = findNeighbor(i,j);

	     	   	if(temp && !stackP.isInStack(temp->label))
			   	{
	        		stackNB.push(temp->label);
			   	}

		   	}
	 
	   	 	// push any squares not in p or nb stack onto remaining stack
	   	 	for(int j = 1; j <= n; j++)
			{
	     		if(!stackP.isInStack(j) && !stackNB.isInStack(j)) 
			   	{
					remaining.push(j);
			   	}
		   	}

	   	 	// if any of squares in remaining are not neighbors retun false
	   		for(int j = 0; j < remaining.size(); j++)
	   	 	{
	     	   	int num = remaining.peekIndex(j);
				
	     		for(int k = 1; k <= remaining.size(); k++)
		 	   	{
	     			NeighborNode *temp = findNeighbor(j,k);
	       			if(temp)
					{ 
						return false;
					}
         	   }
	   		}  
   		}
		
	 	if(!stackP.isEmpty()) 
	 	{
			stackP.pop();
	 	}
		if(!stackNB.isEmpty())
		{ 
			stackNB.pop();
		}
        if(!remaining.isEmpty()) 
		{
			remaining.pop();
		}
	}
	return true;
}