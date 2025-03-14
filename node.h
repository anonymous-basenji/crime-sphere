#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

/*

    NOTE: All distances in miles

*/
class Node {
    public:
        Node(string descrip, int lat, int longit);
        string description; // this is column "j" if you open the database as a spreadsheet
        int latitude;
        int longitude;
        vector<pair<Node*, int>> connectedNodes; // node in each pair is node curr node is connected to, 
                                                 // int is distance from curr node to that node

        void addConnection(Node* node); // distance calculated in this function
        float calcDist(Node* node); // gets distance w/out connecting both nodes
};
