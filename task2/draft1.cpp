#include<iostream>
#include<fstream>
#include<sstream>
#include<utility>

using namespace std;

struct Edge{

    char destination;
    int weight;
    Edge* next;

    Edge(int weight1,char destination1){
        weight=weight1;
        destination=destination1;
        next=nullptr;
    }

};

struct Node{

    char value;
    Edge* head;
    Edge* tail;

    Node(char value1='\0'){
        value=value1;
        head=nullptr;
    }

};

class TrafficNetwork
{
    Node* intersections;
    int capacity;
    int size;

    public:
    TrafficNetwork(int capacity1)
    {
        capacity=capacity1;
        size=0;
        intersections=new Node[capacity];

    }

    bool searchNetwork(char data){

        for(int i=0;i<size;i++){
            if(intersections[i].value==data){
                return true;
            }
        }

        return false;

    }

    void addIntersection(char data){

        if(size>=capacity){
            return;
        }

        if(searchNetwork(data)){
            return;
        }

        intersections[size].value=data;
        size++;

    }

    void addRoad(char start,char end,int weight){

        Node* startNode=nullptr;
        Node* endNode=nullptr;

        for(int i=0;i<size;i++){
            if(intersections[i].value==start){
                startNode=&intersections[i];
            }

            if(intersections[i].value==end){
                endNode=&intersections[i];
            }
        }

        if(startNode==nullptr){
            return;
        }

        if(endNode==nullptr){
            return;
        }
        
        Edge* newEdge = new Edge(weight,end); 
        
        if(startNode->head==nullptr){ 
            startNode->head=newEdge; 
            startNode->tail=newEdge; 
        }

        else{ 
            startNode->tail->next=newEdge; 
            startNode->tail=newEdge; 
        } 
        
        cout<<"Road added from "<<start<<" to "<<end<<" with time interval "<<weight<<endl;

        return;
    }

    void displayNetwork(){ 
        
        cout<<"\nTraffic Network:"<<endl; 
        
        for(int i=0;i<size;i++){ 
            
            cout<<"Intersection "<<intersections[i].value<<" is connected to:"; 
            Edge* current=intersections[i].head; 
            
            while(current!=nullptr){ 
                cout<<" -> "<<current->destination<<" (time interval: "<<current->weight<<")"; 
                current=current->next; 
            } 

            cout<<endl; 
        }

        return;

    }
    
    int getSize()
    {
        return size;
    }

    int getNodeIndex(char value) 
    {
        for (int i = 0; i < size; i++) 
        {
            if (intersections[i].value == value)
            {
                    return i;
            }
        }
        return -1; 
    }    
    
    pair<int, char*> shortestPath(char start, char end) 
    {
        int* distances = new int[size];
        bool* visited = new bool[size];
        char* tempPath = new char[size];  // Temporary path array
        char* finalpath = new char[size]; // Final path array
        int tempIndex = 0;
        int minDist = 99999;
    
        for (int i = 0; i < size; i++) 
        {
            distances[i] = 99999;
            visited[i] = false;
        }
    
        int startIndex = getNodeIndex(start);
        int endIndex = getNodeIndex(end);
    
        if (startIndex == -1 || endIndex == -1) 
        {
            cout << "Start or end intersection not found!" << endl;
            return {99999, nullptr};
        }
    
        distances[startIndex] = 0;
        tempPath[tempIndex++] = start;
    
        for (int i = 0; i < size; i++) 
        {
            int minDistance = 99999;
            int currentNode = -1;
    
            // Find the unvisited node with the smallest distance
            for (int j = 0; j < size; j++) 
            {
                if (!visited[j] && distances[j] < minDistance) 
                {
                    minDistance = distances[j];
                    currentNode = j;
                }
            }
    
            if (currentNode == -1) 
            {
                break; // No more reachable nodes
            }
    
            visited[currentNode] = true;
    
            if (currentNode == endIndex) 
            {
                if (distances[endIndex] < minDist) 
                {
                    minDist = distances[endIndex];
                    for (int k = 0; k < tempIndex; k++) 
                    {
                        finalpath[k] = tempPath[k];
                    }
                    finalpath[tempIndex] = '\0';
                }
            }
    
            // Explore neighbors
            Edge* edge = intersections[currentNode].head;
            while (edge != nullptr) 
            {
                int neighborIndex = getNodeIndex(edge->destination);
                if (neighborIndex != -1 && !visited[neighborIndex]) 
                {
                    int newDistance = distances[currentNode] + edge->weight;
                    if (newDistance < distances[neighborIndex]) 
                    {
                        distances[neighborIndex] = newDistance;
    
                        // Copy current path to tempPath
                        for (int k = 0; k < tempIndex; k++) 
                        {
                            tempPath[k] = finalpath[k];
                        }
    
                        tempPath[tempIndex] = edge->destination;
                        tempPath[tempIndex + 1] = '\0'; // Null-terminate
                    }
                }
                edge = edge->next;
            }
        }
    
        return {minDist, finalpath};
    }
};

class Vehicle
{
    public:
    
    string id;
    char start;
    char end;
    char current;
    
    int dist;
    
    Vehicle(string name, char st, char en)
    {
        id = name;
        start = st;
        end = en;
        dist = 0;
    }
    
    void shortestdis(TrafficNetwork& network)
    {
        pair<int, char*> result = network.shortestPath(start, end);
        int endpoint = network.getNodeIndex(end);
        
        int shortestDistance = result.first;
        char* finalpath = result.second;
        
        dist = shortestDistance;
        cout << "Shortest path from " << start << " to " << end << ": ";
    for (int i = 0; finalpath[i] != '\0'; i++)
    {
        cout << finalpath[i];
        if (finalpath[i + 1] != '\0')
        {
            cout << " -> ";
        }
    }
    cout << "\nTotal travel time: " << dist << " units." << endl;
    }
    
};

class Map
{
    TrafficNetwork graph; // single graph
    Vehicle* vehicles[100]; // multiple cars
    
    int vehicleCount;
    
    public:
    Map() : graph(10)
    {
        vehicleCount = 0;
        roadscsv();
        vehiclescsv();
    }
    
    void roadscsv()
    {
        ifstream file("/uploads/road_network.csv");
        string line;
        int count = 0;

        if(!file.is_open())
        {
            cout<<"Error opening file!"<<endl;
        }
    
        while (getline(file, line)) 
        {
            string weight="";
            
            if(!line.empty() && count>0)
            {
                char intersection1=line[0];
                char intersection2=line[2];
                
                for(int i=4; i < line.length(); i++)
                {
                    weight+=line[i];
                }
    
                int travelTime = stoi(weight);  
                graph.addIntersection(intersection1);
                graph.addIntersection(intersection2);
                graph.addRoad(intersection1,intersection2,travelTime);
            }
            count++;
        }
        file.close();
    }
    
    void vehiclescsv()
    {
        ifstream file("/uploads/vehicles.csv");
        string line;
        int count = 0;

        if(!file.is_open())
        {
            cout<<"Error opening file!"<<endl;
        }
    
        while (getline(file, line)) 
        {
            if(!line.empty() && count>0)
            {
                stringstream ss(line);
                string vehID, startStr, endStr;
 
                getline(ss, vehID, ',');
                getline(ss, startStr, ',');
                getline(ss, endStr, ',');
                
                vehicles[vehicleCount] = new Vehicle(vehID, startStr[0], endStr[0]);
                vehicleCount++; 
            }
            count++;
        }
        file.close();
    }
    
    void shortestDis()
    {
        for(int i = 0; i < vehicleCount; i++)
        {
            vehicles[i]->shortestdis(graph);
        }
    }
    
    void displayMap()
    {
        cout << "\n--- Traffic Network Details ---\n";
        graph.displayNetwork();

        cout << "\n--- Vehicle Details ---\n";
        for (int i = 0; i < vehicleCount; i++) 
        {
            
            cout << "Vehicle ID: " << vehicles[i]->id 
                 << ", Start: " << vehicles[i]->start 
                 << ", End: " << vehicles[i]->end 
                 << ",shortest distance: " << vehicles[i]->dist << endl;
                 
        }
    }
};

int main() 
{
    Map trafficMap;
    trafficMap.shortestDis();
    trafficMap.displayMap();
    return 0;
}



