#include <iostream>
#include <string>
#include <vector>
#include "Bridges.h"
#include "DataSource.h"
#include "BSTElement.h"
#include <queue>
#include "GraphAdjList.h"
using namespace std;
using namespace bridges;

/*
  Step 1: Get the Bridges USER ID and API KEY for your program
          by creating an account and signing up (You can use any
          email): https://bridges-cs.herokuapp.com/login

  Step 2: User ID (Username) and Key (API Sha1 Key) can be
          found under Profile on the top left
*/


int main(int argc, char **argv)
{

    // Step 3: Test if the following print statement is being run
    cout << "Bridges: Graph\n";

    Bridges bridges (1, "JHooth", "221647721744");

    // set a title
    bridges.setTitle("A Simple Adjacency list based Graph Example.");

    // set  description
    bridges.setDescription("Demonstrate how to create a graph with a few nodes and display it");

    // create a graph with key values of type string. See the
    // the documentation for GraphAdjList for its full capabilities
    GraphAdjList<int> graph;

    for(int i = 0; i < 10; i++)
    {
        graph.addVertex(i);
    }

    graph.addEdge(0, 1);
    graph.addEdge(2, 3);
    graph.addEdge(1, 4);
    graph.addEdge(3, 0);
    graph.addEdge(5, 6);
    graph.addEdge(8, 5);
    graph.addEdge(4, 8);

    bridges.setDataStructure(&graph);

    bridges.visualize();

    return 0;
}