#include <iostream>
#include <string>
#include <vector>
#include "Bridges.h"
#include "DataSource.h"
#include "BSTElement.h"
#include <queue>
#include <unordered_map>
#include <random>
#include "GraphAdjList.h"
#include <SLelement.h>
#include <math.h>
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

    int nodeAmt;
    std::cout << "Enter the number of nodes to be generated from 10 to 100,000" << std::endl;
    while(true)
    {
        try{
            std::string input0;
            std::cin >> input0;
            nodeAmt = stoi(input0);
            break;
        }catch(...)
        {
            std::cout << "Enter a valid number:" << std::endl;
        }
    }


    int edgeAmt = nodeAmt * 2;

    for(int i = 0; i < nodeAmt; i++)
    {
        graph.addVertex(i);
    }

    int edgeCounter = 0;

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range [0, nodeAmt]
    std::uniform_int_distribution<> makeRand(0, nodeAmt - 1);


    //make check for if it is like 2 vertices then
    //or just make minumum like 10 nodes

    /*
    auto possibilities = tgamma(edgeAmt) / tgamma(edgeAmt - edgeAmt);

    if(possibilities < edgeAmt)
    {
        edgeAmt = possibilities;
    }
     */

    std::cout << "Generating Graph" << std::endl;

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    while((edgeAmt > edgeCounter))
    {
        int from = makeRand(gen);
        int to = makeRand(gen);
        //makes sure that there are no self loops
        while(to == from)
        {
            to = makeRand(gen);
        }
        if(!graph.isEdge(from, to))
        {

            graph.addEdge(from, to);
            edgeCounter++;
        }
    }

    std::cout.rdbuf(p_cout_streambuf);


    //bool test = graph.isEdge(0, 1);
    std::cout << edgeCounter << std::endl;

    /*
    for(int i = 0; i < 11; i++)
    {
        graph.addVertex(i);
    }

    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);
    */

    bridges.setDataStructure(&graph);


    //bfs method!


    std::queue<int> nodeChecker;

    std::unordered_map<int, bool> visited;
    //makes all distances from nodeFrom infinity to begin with
    std::vector<int> distance(nodeAmt, 1e9);
    //stores the parent node of each node
    std::vector<int> parentTracker(nodeAmt, -1);


    int nodeFrom;
    std::cout << "Enter the node number From:" << std::endl;
    //std::cin >> nodeFrom;
    while(true)
    {
        try{
            std::string input1;
            std::cin >> input1;
            nodeFrom = stoi(input1);
            break;
        }catch(...)
        {
            std::cout << "Enter a valid number:" << std::endl;
        }
    }

    int nodeTo;
    std::cout << "Enter the node number To:" << std::endl;
    //std::cin >> nodeTo;
    while(true)
    {
        try{
            std::string input2;
            std::cin >> input2;
            nodeTo = stoi(input2);
            break;
        }catch(...)
        {
            std::cout << "Enter a valid number:" << std::endl;
        }
    }

    visited[nodeFrom] = true;
    distance[nodeFrom] = 0;
    nodeChecker.push(nodeFrom);



    while(!nodeChecker.empty())
    {

        int currNode = nodeChecker.front();
        nodeChecker.pop();

        if(currNode == nodeTo)
        {
            std::cout << "Found node! Distance: " << distance[currNode] << std::endl;
            break;
        }

        auto adj = graph.getAdjacencyList(currNode);
        //loops through node's adjacency list
        while (adj != nullptr) {
            int num = stoi(adj->getLabel());

            if(!visited[num])
            {
                nodeChecker.push(num);
                visited[num] = true;
                distance[num] = distance[currNode] + 1;
                parentTracker[num] = currNode;
            }
            adj = adj->getNext();
        }

    }

    //checks if there is a path

    if(distance[nodeTo] == 1e9)
    {
        std::cout << "No path found" << std::endl;
    }else
    {
        //path method
        vector<int> path;
        path.push_back(nodeTo);
        int currentNode = nodeTo;
        while (parentTracker[currentNode] != -1) {
            path.push_back(parentTracker[currentNode]);

            graph.getLinkVisualizer(parentTracker[currentNode], currentNode)->setColor("red");

            currentNode = parentTracker[currentNode];
            graph.getVertex(currentNode)->setColor("yellow");
        }

        std::cout << "Path from " << nodeFrom << " to " << nodeTo << " is: ";
        for (int i = int(path.size() - 1); i > 0; i--) {
            std::cout << path[i] << " -> ";
        }
        std::cout << path[0] << std::endl;
    }

    graph.getVertex(nodeFrom)->setColor("green");
    graph.getVertex(nodeTo)->setColor("green");


    bridges.visualize();


    return 0;
}