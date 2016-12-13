#include"network.h"
#include <iostream>

using namespace std;

int main()
{

	Network network;
	int input;
	Stack<int> paintedSquares, neighborSquares;

	/*
	 3 character code			  
	 1st character is backbone label. Values from 1-7					  
	 2nd character is neighbor label. Values from 1-7	
	 3rd character is node weight. All weights are 1.
    */
	
	string graph[] = {"121", "141", "211", "231", "241", "321", "341", "351", "361", "411", 
		"421", "431", "451", "531", "541", "561", "571", "631", "651", "671", "751", "761"};
	
	// 528 / 24 = 22 -> size
	int size = sizeof(graph) / sizeof(graph[0]);
    int n = 7;
    bool loopControl = true;
		
	// based on the input maze to make the network. 
	network.createNetwork(graph, size);	
	// print out the graph table
	network.printNetwork();

	// First Pick
	while(loopControl)
	{
 
		cout << "Choose a square between 1-7 to paint." << endl;;
		cin >> input;

		//put push input onto stack
		paintedSquares.push(input);

		//push any neighbors of input onto stack
		for(int i = 1; i <= n; i++)
		{
	  	  	NeighborNode *temp = network.findNeighbor(input,i);
	  
	  		if(temp && !paintedSquares.isInStack(temp->label))
			{
	      	  	neighborSquares.push(temp->label);
			}
		}

		if(network.calculateMove(paintedSquares, neighborSquares, input))
		{
	  		cout << "\nOpponent could beat you on next move. Pick another square to paint\n\n";
	  		while(!paintedSquares.isEmpty()) 
			{
				paintedSquares.pop();
			}
	  		while(!neighborSquares.isEmpty()) 
			{
				neighborSquares.pop();
			}
		}
		else
		{
	  		loopControl = false;
	  	}
	}

	// All other Picks
	while((paintedSquares.size() + neighborSquares.size()) < n)
    {
        cout << "\nPick a square from the following numbers: ";

		for(int i = 1; i <= n; i++)
		{
		  	if(!paintedSquares.isInStack(i) && !neighborSquares.isInStack(i))
		  	{
		  		cout << i << " ";
			}
		}
		cout << endl;
    
		cin >> input;

		if(paintedSquares.isInStack(input))
		{
		   cout << "\nInvalid choice. Please pick again\n";
	   	}
	   	else
	   	{
	   		// push input onto stack
	     	paintedSquares.push(input);

	     	// push any neighbors of input onto stack
	     	for(int i = 1; i <= size; i++)
	     	{
	       	 	NeighborNode *temp = network.findNeighbor(input, i);
	  
	       	 	if(temp && !neighborSquares.isInStack(temp->label))
				{
		 		   neighborSquares.push(temp->label);
			   	}

	     	}
		}
	}

	cout << "\nGame Ended" << endl;
	return 0;
}