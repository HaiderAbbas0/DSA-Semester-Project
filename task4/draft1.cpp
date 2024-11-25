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

struct graphNode{

    char value;
    Edge* head;
    Edge* tail;

    graphNode(char value1='\0'){
        value=value1;
        head=nullptr;
    }

};

struct queueNode{

    char value;
    queueNode* next;

    queueNode(char data){
        value=data;
        next=nullptr;
    }
};

struct linkedNode{
   
    int data;

    linkedNode* next;
   
    linkedNode(int value){
        data=value;
        next=nullptr;
    }
};

/***********************************
* We will use Queue for bfs purposes
***********************************/

class Queue{

    private:

    queueNode* front;
    queueNode* rear;

    public:

    Queue(){
        front=nullptr;
        rear=nullptr;
    }

    void Enqueue(){

    }

    void Dequeue(){
    }

    bool isEmpty(){

        if(front==nullptr && rear==nullptr){
            return true;
        }

        return false;
        

    }

    void Display(){
    }
};


/*********************************
* Using linked list for hash table
*********************************/


class LinkedList{
   
    private:
   
    linkedNode* head;
    
    public:
    LinkedList(){
        head=nullptr;
    }

    void insert(int value){
        linkedNode* newNode=new linkedNode(value);
       
        if(head==nullptr){
            head=newNode;
        }
       
        else{
            linkedNode* temp=head;
           
            while(temp->next!=nullptr){
                temp=temp->next;
            }
            temp->next=newNode;
        }
    }

    bool search(int value){
 
        linkedNode* temp=head;
        while(temp!=nullptr){
           
            if(temp->data==value){
                return true;
            }
            temp=temp->next;
        }
        return false;
    }

    void display(){
       
        linkedNode* temp=head;
       
        while(temp!=nullptr){
            cout<<temp->data<<" ";
            temp=temp->next;
        }
        cout<<endl;
    }

    bool search(int value){
       
        linkedNode* temp=head;

        while(temp!=nullptr) {
            if (temp->data == value) {
                return true; 
            }
            temp = temp->next;
        }
        return false; 
    }

    void Del(){
        linkedNode* temp=head;
        head=head->next;
        delete temp;

        return;
    }

    ~LinkedList(){

        while(head!=nullptr){
            Del();
        }
    
    }
};


class TrafficNetwork
{
    graphNode* intersections;
    int capacity;
    int size;

    public:
    TrafficNetwork(int capacity1)
    {
        capacity=capacity1;
        size=0;
        intersections=new graphNode[capacity];

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

        graphNode* startNode=nullptr;
        graphNode* endNode=nullptr;

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
        int* parent = new int[size];  // To track the predecessor of each node
    
        for (int i = 0; i < size; i++) 
        {
            distances[i] = 99999;
            visited[i] = false;
            parent[i] = -1;  // Initialize parent array
        }
    
        int startIndex = getNodeIndex(start);
        int endIndex = getNodeIndex(end);
    
        if (startIndex == -1 || endIndex == -1) 
        {
            cout << "Start or end intersection not found!" << endl;
            return {99999, nullptr};
        }
    
        distances[startIndex] = 0;
    
        while (true) 
        {
            int minDistance = 99999;
            int currentNode = -1;
    
            // Find the unvisited node with the smallest distance
            for (int i = 0; i < size; i++) 
            {
                if (!visited[i] && distances[i] < minDistance) 
                {
                    minDistance = distances[i];
                    currentNode = i;
                }
            }
    
            if (currentNode == -1) 
            {
                break; 
            }
    
            visited[currentNode] = true;
    
            if (currentNode == endIndex) 
            {
                break; // Reached the destination
            }
    
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
                        parent[neighborIndex] = currentNode;  
                    }
                }
                edge = edge->next;
            }
        }
    
        // Reconstruct the path from the parent array
        char* finalPath = new char[size + 1];
        int pathIndex = 0;
        int currentNode = endIndex;
    
        while (currentNode != -1) 
        {
            finalPath[pathIndex++] = intersections[currentNode].value;
            currentNode = parent[currentNode];
        }
    
        finalPath[pathIndex] = '\0';
    
        for (int i = 0; i < pathIndex / 2; i++) 
        {
            swap(finalPath[i], finalPath[pathIndex - i - 1]);
        }
    
        return {distances[endIndex], finalPath};
    }

};

class Vehicle
{
    public:
    
    string id;
    char start;
    char end;

    int dist;
    char* path;
    char current;
    int curIndex;
    
    Vehicle(string name, char st, char en)
    {
        id = name;
        start = st;
        end = en;
        
        dist = 0;
        path = NULL;
        current = start;
        curIndex = 0;
    }
    
    void shortestdis(TrafficNetwork& network)
    {
        pair<int, char*> result = network.shortestPath(start, end);
        int endpoint = network.getNodeIndex(end);
        
        int shortestDistance = result.first;
        path = result.second;
        
        dist = shortestDistance;
        cout << id << ": ";
        for(int i = 0; path[i] != '\0'; i++)
        {
            cout << path[i];
        }
        cout << endl;
    }
    
    void movecar() //current postion of the vehicle changes
    {
        curIndex++;
        current = path[curIndex];
        cout << id << ": " << current;    
        cout << endl;
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
        ifstream file("road_network.csv");
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
        ifstream file("vehicles.csv");
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
    
    void moveVehicle() 
    {
        for (int i = 0; i < vehicleCount; ) 
        { 
            vehicles[i]->movecar();
            if (vehicles[i]->current == vehicles[i]->end) 
            {
                cout << vehicles[i]->id << " has reached its destination\n";
    
                delete vehicles[i];
    
                for (int j = i; j < vehicleCount - 1; j++) 
                {
                    vehicles[j] = vehicles[j + 1];
                }
                vehicleCount--; 
            } 
            
            else 
            {
                i++; 
            }
            cout << endl;
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
        moveVehicle();
    }
};

class congestionMonitoring{

    /*****************************************************************************
    Logic:
    
    1- Our key is the path that a vehicle takes.
    2- Our value is the vehicle count for that
    specific path.
    3- The capacity is the total number of roads.
    4- The size is the current number of roads.
    5- Congestion Level is an array, which will tell
    us the level of congestion on each road.(we will
    set the levels ourselves).
    6- Congestion Marker is also an array, and it will
    display the level of congestion for example moderate
    low,high, we will set these values based on the congestion
    level value set in congestion level array for example if my
    congestion level for a specific road is in the range of 1-3
    then I will mark the congestion marker for that specific road
    as low, for 4-6 moderate, 7-9 high, anything above 10 as very
    high.
    7- we will link these two array together using their indexes,
    each index represents a specific road, for example for road number
    1 congestionLevel[1]=5, since it is in 4-6 range congestionMarker[1]="Moderate"  

    ******************************************************************************/

private:
    
    int capacity;
    int size;
    int* congestionLevel;
    string* congestionMarker;
    LinkedList* congestionTable;

public:

    congestionMonitoring(int capacity1){
        capacity=capacity1;
        size=0;
        congestionTable=new LinkedList[capacity];
    }

    int hashFunction(const string& key){   
    }

    void insert(const string& key, int value){
        int index=hashFunction(key);
        congestionTable[index].insert(value); 
    }

    int search(const string& key){
        int index=hashFunction(key);
        return congestionTable[index].search(index);
    }

    void display() {
        for (int i = 0; i < capacity; i++) {
            congestionTable[i].display();
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


