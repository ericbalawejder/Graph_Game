#include"network.h"
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

// constructor
Network::Network()
{
	start = NULL;
}

void Network::createNetwork(string* graph, int& size)
{
	string entry;
	// holds values at positon 2 and 3 of entry
	string bboneLbl;
	// holds values at position 3 and 4 of entry
	string ngbLbl; 
	// holds value at position 5 of entry
	string weight; 
	// holding the backbone label, which is parsed out from input
	int backboneLabel;
	// holding the neighbor label, which is parsed out from input
	int neighborLabel;
	// hodling weight, which is parsed out from input
	int wt;           

	for(int i = 0; i < size; ++i)
	{
		entry = graph[i];
		
		// substr(start position, number of characters)
		bboneLbl = entry.substr(0,1);
		backboneLabel = atoi(bboneLbl.c_str());

		ngbLbl = entry.substr(1,1);
		neighborLabel = atoi(ngbLbl.c_str());
		
		weight = entry.substr(2,1);
		wt = atoi(weight.c_str());

		createNeighborNode(backboneLabel, wt, neighborLabel);
	}
}

// print the Network
void Network::printNetwork()
{
	cout << "Graph Table:" << endl;
	BackboneNode* tmpBB = start;
	NeighborNode* tmpNbr;
	while(tmpBB)
	{
		cout << tmpBB->label;
		tmpNbr = tmpBB->neighbor;
		while(tmpNbr)
		{
		  	//cout<<tmpNbr->label<<" ";cout<<"( with weight: "<< tmpNbr->weight<<")  ";
		    cout << "->" << tmpNbr->label << " weight(" << tmpNbr->weight << ")";
			tmpNbr = tmpNbr->neighbor;
		}
		cout << endl;
		tmpBB = tmpBB->nextbone;
	}
	cout << endl;
}


bool Network::inStack(int& bLabel, int& nLabel, Stack<Edge*>& pathStack)
{
	Edge* tmp;
	int n = pathStack.size();
	//the first one in the pathStack is always the source record, which does not have parent.
	// There is no need to match that one. Following record will always have parent
	for(int i=2; i<=n; ++i)
	{
		tmp = pathStack.peekIndex(i);
		if(nLabel == tmp->node->label && bLabel == tmp->parent->node->label)
			return true;
	}
	return false;
}


//insert a new backbone, the label cannot be duplicated with existed ones
bool Network:: insertBackbone(const int& label)
{
    //duplicated backbone label; no insertion
    if(findBackbone(label))
		return false;

	//non duplicate, insert a new backbone with this label
	BackboneNode* current = new BackboneNode;
	current->nextbone = NULL;
	current->neighbor = NULL;
	current->label = label;

	if(!start)
		start = current;
	else{
		// insert at the tail
		BackboneNode* tmp = start;
		while(tmp->nextbone)
			tmp =  tmp->nextbone;
		tmp->nextbone = current;
	}
	return true;
}

bool Network:: createNeighborNode(const int& pLabel, const int& weight, const int& nLabel)
{
	//if backbone with plabel does not exsist, create it
	BackboneNode* backbone = findBackbone(pLabel);
	if(!backbone)
		insertBackbone(pLabel);
	
	//if backbone with nLabel does not exsist, create it
    backbone = findBackbone(nLabel);
	if(!backbone)
		insertBackbone(nLabel);

	//set backbone to plabel node
	backbone = findBackbone(pLabel);
	

	//check to make sure you do not insert neighbor twice
	if(findNeighbor(pLabel, nLabel))
	{
		cout<<"\nErr: Cannot insert neighbor. It already exists"<<endl;
		return false;
	}

	//insert new neighbor to current backbone
	NeighborNode* current = new NeighborNode;
	current->neighbor = NULL;
	current->weight = weight;
	current->label = nLabel;
	//when backbone has not had neighbor yet, directly link the current to this back bone
	if(!backbone->neighbor)
		backbone->neighbor = current;
	else
	{
		NeighborNode* tmp = backbone->neighbor;
		while(tmp->neighbor)
			tmp = tmp->neighbor;
		tmp->neighbor = current;
	}
	return true;
}

BackboneNode* Network:: findBackbone(const int& label)
{
	if(!start)
		return NULL;

	BackboneNode* tmp = start;
	while(tmp && tmp->label != label)
		tmp = tmp->nextbone;

	return tmp;
}

NeighborNode* Network:: findNeighbor(const int& plabel, const int& nlabel)
{
	if(!start)
		return NULL;

	BackboneNode* backbone = findBackbone(plabel);
	if(!backbone)
		return NULL;

	NeighborNode* firstNb = backbone->neighbor;
	while(firstNb && firstNb->label != nlabel)
		firstNb = firstNb -> neighbor;

	return firstNb;
}

bool Network:: calculateMove(Stack<int>& painted, Stack<int>& neighbor, int& n)
{
	Stack<int> p, nb;//stacks for deep copy
  	Stack<int>remaining;//hold squares remaining

    for(int i = 1; i <= 7; i++)
	{

	 	//deep copy painted
		for(int k = 0; k < painted.size(); k++)
		{
	   	 	p.push(painted.peekIndex(k));
		}

	 	//deep copy neighbor	 
        for(int k = 0; k< neighbor.size(); k++)
		{
	   		nb.push(neighbor.peekIndex(k));
   		}

	 	//if i is not in either stack, push onto p	 
	 	if(!p.isInStack(i) && !nb.isInStack(i))
		{

            //push input onto stack
	    	p.push(i);

	   	 	//push any neighbors of i onto stack
	   	 	for(int j = 1; j <= n; j++)
	   	 	{

	    		NeighborNode *tmp = findNeighbor(i,j);
	  

	     	   if(tmp && !p.isInStack(tmp->label))
			   {
	        	   nb.push(tmp->label);
			   }

		   	}//end for
	 
	   	 	//push any squares not in p or nb stack onto remaining stack
	   	 	for(int j = 1; j<=n; j++)
			{
	     	   if(!p.isInStack(j) && !nb.isInStack(j)) 
			   {
				   remaining.push(j);
			   }
		   	}

	   	 		//if any of squares in remaining are not neighbors retun false
	   		for(int j = 0; j < remaining.size(); j++)
	   	 	{
	     	   	int num = remaining.peekIndex(j);
	     		for(int k = 1; k <= remaining.size(); k++)
		 	   	{
	     			NeighborNode *tmp = findNeighbor(j,k);
	       			if(tmp)
					{ 
						return false;
					}
         	   }//end k for
	   		}//end j for  
   		}//end if
		
	 	if(!p.isEmpty()) 
	 	{
			p.pop();
	 	}
		if(!nb.isEmpty())
		{ 
			nb.pop();
		}
        if(!remaining.isEmpty()) 
		{
			remaining.pop();
		}
	}
	return true;
}