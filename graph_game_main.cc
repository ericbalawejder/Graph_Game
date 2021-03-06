#include "network.h"
#include <iostream>

using namespace std;

int main()
{
    // Create network.
    Network network;
    int choice;
    // Create two int stacks.
    Stack<int> paintedSquares, neighborSquares;

    // Three character code for graph table.
    // First character is backbone label. Values from 1-7.
    // Second character is neighbor label. Values from 1-7.
    // Third character is node weight. All weights = 1.

    // Array to hold graph table encoding.
    string graph[] = {"121", "141", "211", "231", "241", "321", "341", "351", "361", "411", 
        "421", "431", "451", "531", "541", "561", "571", "631", "651", "671", "751", "761"};

    // 528 / 24 = 22 -> size
    int size = sizeof(graph) / sizeof(graph[0]);
    int n = 7;
    bool loopControl = true;

    // Based graph game picture to make the network.
    network.createNetwork(graph, size);
    // Print out the graph table.
    network.printNetwork();

    // First choice.
    while(loopControl)
    {
        cout << "Given squares between 1-7 to paint, picking square 3 " 
            "will always allow you to win." << endl;;
        cin >> choice;

        // Pseudo code for feature implementation.
        /**if (choice == 3)
        {
            cout << "You win!" << endl;
            loopControl = false;
            return 0;
        }**/

        // Push input onto stack.
        paintedSquares.push(choice);
        // Push any neighbors of input onto stack.
        for(int i = 1; i <= n; i++)
        {
            NeighborNode *temp = network.findNeighbor(choice, i);

            if(temp && !paintedSquares.isInStack(temp->label))
            {
                neighborSquares.push(temp->label);
            }
        }

        if (network.calculateMove(paintedSquares, neighborSquares, choice))
        {
            cout << "\nThe opponent can beat you on next move."
                " Pick another square to paint\n\n";
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

    // All other selections.
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
        cin >> choice;

        if(paintedSquares.isInStack(choice))
        {
            cout << "\nAlready chosen. Select again.\n";
        }
        else
        {
            // Push input onto stack.
            paintedSquares.push(choice);
            // Push any neighbors of input onto stack.
            for(int i = 1; i <= size; i++)
            {
                NeighborNode *temp = network.findNeighbor(choice, i);

                if(temp && !neighborSquares.isInStack(temp->label))
                {
                    neighborSquares.push(temp->label);
                }
            }
        }
    }
    cout << "\nYou win" << endl;
    return 0;
}
