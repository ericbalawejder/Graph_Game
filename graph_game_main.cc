#include"network.h"
#include <iostream>

using namespace std;

int main()
{

	Network test;
	int input;
	Stack<int> paintedSquares, neighborSquares;

	/*
	 3 character code			  
	 1st character is backbone label. Values from 1-7					  
	 2nd character is neighbor label. Values from 1-7	
	 3rd character is node weight. All weights are 1.
    */
	
	string graph[] = 
		{"121", "141", "211","231","241","321","341","351","361","411","421","431","451","531","541","561","571","631","651","671","751","761"};
	int size = sizeof(graph) / sizeof(graph[0]);
	cout << sizeof(graph) << endl;
	cout << sizeof(graph[0]) << endl;
	cout << size << endl;
    int n = 7;
    bool testPick = true;
	
	cout << "-------------------------------------------------------------------------" << endl;
	
	//based on the input maze to make the network. Then print out the graph table
	test.createNetwork(graph, size);	
	test.printNetwork();
	cout << endl;

	// First Pick
	while(testPick)
	{
 
		cout << "\nPick a square between 1-7 to paint." << endl;;
		cin >> input;

		//put push input onto stack
		paintedSquares.push(input);

		//push any neighbors of input onto stack
		for(int i = 1; i <= n; i++)
		{
	  	  	NeighborNode *tmp = test.findNeighbor(input,i);
	  
	  		if(tmp && !paintedSquares.isInStack(tmp->label))
			{
	      	  	neighborSquares.push(tmp->label);
			}
		}

		if(test.calculateMove(paintedSquares, neighborSquares, input))
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
	  		testPick = false;
	  	}
 	
	}

	// All other Picks
	while((paintedSquares.size() + neighborSquares.size()) < n)
    {
        cout<<"\nPick a square from the following numbers: ";

		for(int i = 1; i<= n; i++)
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
	   		//put push input onto stack
	     	paintedSquares.push(input);

	     	//push any neighbors of input onto stack
	     	for(int i = 1; i <= size; i++)
	     	{
	       	 	NeighborNode *tmp = test.findNeighbor(input,i);
	  
	       	 	if(tmp && !neighborSquares.isInStack(tmp->label))
				{
		 		   neighborSquares.push(tmp->label);
			   	}

	     	}
		}
	}

	cout << "\nGame Over" << endl;
}