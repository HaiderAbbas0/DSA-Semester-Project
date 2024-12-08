/****************************************************************************************************************************
*                                       Data Structures Semester Project
*
*   Group Member Names: Hamd-Ul-Haq, Mohammad Haider Abbas, Mohammad Kumail
*   Group Member Roll#: 23i-0081, 23i-2558, 23i-2134
*   Course Instructor: Dr.M.Ishtiaq
*
****************************************************************************************************************************/


/*****************
Libraries Included 
*****************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <cstring>
#include<string>

using namespace std;


/**********
Edge Struct 
**********/

struct Edge
{
    /****************************************************************************
    The edge struct basically represents our road in the graph data structure,it
    consists of several members such as, destination, which represents the ending 
    intersection of our road, weight representing the travel time for a specific 
    road and the name is essentially a combination of the starting and ending 
    intersections for a specific road.  
    ****************************************************************************/

    char destination;
    int weight;
    Edge* next;
    int vehicleCount;
    string name;

    /**********
    Constructor
    **********/

    Edge(int weight1,char destination1,string name1)
    {
        weight=weight1;
        destination=destination1;
        next=nullptr;
        vehicleCount = 0;
        name=name1;
    }
};


/**********
Node Struct
**********/


struct Node
{
    /****************************************************************************
    Node struct represents the intersections in our traffic network, it contains
    several members such as value, which tells use the name of intersection, head
    and tail pointers, which are used to point to the next intersection in the
    entire path.
    ****************************************************************************/

    char value;
    Edge* head;
    Edge* tail;

    
    /**********
    Constructor
    **********/

    Node(char value1='\0'){
        value=value1;
        head=nullptr;
        tail=nullptr;
    }

};


/*****************
Linked Node Struct
******************/

struct linkedNode
{

    /************************************************************************************************
    The linked node struct is basically used in our implementation of the linked list data structure,
    it represents nodes in the entire linked list data structure.
    ************************************************************************************************/
    
    int data;
    linkedNode* next;
   
    linkedNode(int value){
        data=value;
        next=nullptr;
    }
};


/***************
LinkedList Class
***************/

class LinkedList
{
    /********************************************************************************************
    In this class we have covered the basic implementation of the linked list, the implementation
    consists of numerous methods such as insertion, search and deletion.
    ********************************************************************************************/

    private:

    linkedNode* head;
    
    public:

    /**********
    Constructor
    **********/

    LinkedList()
    {
        head=nullptr;
    }

    /****************************
    Accessing Head of Linked List
    ****************************/

    linkedNode* getHead(){
        return head;
    }

    /*********************************************************************
    Insertion in linked list, insertion is performed at end of linked list
    *********************************************************************/

    void insert(int value)
    {
        linkedNode* newNode = new linkedNode(value);

        /**************
        Empty List Case
        **************/
       
        if(head==nullptr)
        {
            head=newNode;
            return;
        }

        /*********************************************************
        Non Empty List Case, we traverse whole list, reach the end
        and then insert the new node in the linked list.
        *********************************************************/
       
        linkedNode* temp=head;
           
        while(temp->next!=nullptr)
            {
                temp=temp->next;
            }
        
        temp->next=newNode;
        
        return;
    }

    /********************
    Searching linked list
    ********************/

    bool search(int value)
    {
        /****************************************************
        We traverse the whole list until given value is found
        ****************************************************/

        linkedNode* temp=head;

        while(temp!=nullptr)
        {
            if(temp->data==value)
            {
                return true;
            }

            temp=temp->next;
        }

        return false;
    }

    /**********************************************************************
    Deletion in linked list, deletion is carried out at head of linked list
    **********************************************************************/

    void Del()
    {
        linkedNode* temp=head;
        head=head->next;
        delete temp;
        return;
    }

    /*********************
    Displaying Linked List
    *********************/

    void display()
    {
        linkedNode* temp=head;
       
        while(temp!=nullptr)
        {
            cout<<temp->data<<" ";
            temp=temp->next;
        }

        cout<<endl;
    }

};

/***********
Signal Class
***********/

class Signal
{
    /****************************************************************
    The signal class is used in controlling the operation of signals 
    in the traffic network, it consists of several members such as
    signal timer representing green time of a signal, signal status
    which indicates if a signal is GREEN or RED, and congestion,
    which tells us the congestion level on the specific intersection
    at which the signal is located.
    ****************************************************************/

    private:

    bool signalStatus;
    int signalTimer;
    char signalIntersection;
    int congestion;

    /**********
    Constructor
    **********/

    public:

    Signal(char intersection,int time){
        addSignal(intersection,time);  
    }

    /******************
    Adding a new signal
    ******************/

    void addSignal(char intersection,int time){
        signalTimer=time;
        signalIntersection=intersection;
    }

    /********************
    Setting signal status
    ********************/

    void setStatus(bool status){
        signalStatus=status;
    }

    /***************************
    Setting congestion of signal
    ***************************/

    void setCongestion(int k){
        congestion=k;
    }

    /******************************
    Getting congestion for a signal
    ******************************/

    int getCongestion(){
        return congestion;
    }

    /*********************************
    Getting signal status for a signal
    *********************************/

    bool getSignalStatus(){
        return signalStatus;
    }

    /******************************
    Getting green time for a signal
    ******************************/

    int getSignalTimer(){
        return signalTimer;
    }

    /*******************
    Updating signal time
    *******************/

    void decrementSignalTimer(){
        if(signalTimer>0){
            signalTimer--;
        }
    }

    /*********************
    Resetting signal timer
    *********************/

    void resetSignalTimer(int nextSignalTime){
        signalTimer=nextSignalTime; 
    }

    /**************************
    Getting signal intersection
    **************************/

    char getIntersection(){
        return signalIntersection;
    }

    /***************************
    Recalulating the signal time
    ***************************/

    void reCalculateTime(){
        signalTimer+=10;
    }

};


/***************
Congestion Class
***************/

class Congestion
{
    /************************************************************************
    The congestion class is major player in our traffic network system, it is 
    responsible for the occurence of many complex operations such as vehicle
    rerouting, updating of signal timer and signal priority. It is a hash 
    which outlines the congestion level for a specified road. The congestion
    level is an array representing the amount of congestion for every road in
    hash, congestionMarker 
    ************************************************************************/

    int capacity;
    int size;
    
    int* congestionLevel;
    string* congestionMarker;
    string* congestionMessage;
    LinkedList* congestionTable;

    public:

    /**********
    Constructor
    **********/
    
    Congestion(int capacity1)
    {
        capacity=capacity1;
        size=0;
        congestionTable=new LinkedList[capacity];
        congestionMessage=new string[capacity];
        congestionLevel=new int[capacity];
        congestionMarker=new string[capacity];

        for (int i = 0; i < capacity; i++) {
            congestionLevel[i] = 0;
            congestionMessage[i] = "";
            congestionMarker[i] = "";
        }
    }

    /************
    Hash Function
    ************/

    int hashFunction(const string& key)
    {   
        char lastChar=key[key.length()-1];
        int index=lastChar-'0';  
    
        return index%capacity;
    }

    /***********************
    Getting Congestion Level
    ***********************/

    int getCongestionLevel(string roadName){
        int index=hashFunction(roadName);

        return congestionLevel[index];
    }

    /**********************
    Inserting Key and Value
    **********************/

    void insert(const string& key, int value)
    {
        int index=hashFunction(key);
        congestionTable[index].insert(value); 
        congestionMarker[index]=key;  
    }

    /**********************
    Searching Key and Value
    **********************/

    int search(const string& key)
    {
        int index=hashFunction(key);
        return congestionTable[index].search(index);
    }

    /*****************************
    Updating congestion for a road
    *****************************/

    void updateCongestion(Edge* edge){

        int totalVehicles=edge->vehicleCount;  
        int index=hashFunction(edge->name);

        congestionLevel[index] = totalVehicles;

        /****************************************************
        Generating congestion message based on our very own
        congestion threshold, the congestion threshold is 
        set according to the number of vehicles on a specific
        road.
        ****************************************************/

        if (totalVehicles<=3){
            congestionMessage[index] = "Low congestion";
        }

        else if (totalVehicles<=6){
            congestionMessage[index] = "Moderate congestion";
        }

        else{
            congestionMessage[index] = "High congestion";
        }

    }

    /********************
    Displaying Congestion
    ********************/

    void displayCongestion() 
    {
        for (int i = 0; i < capacity; i++) {
            if(congestionLevel[i]!=0)
            {
                cout << congestionMarker[i] << " -> (Vehicles: " 
                     << congestionLevel[i] << "), (Congestion Level: " 
                     << congestionMessage[i] << ")" << endl;
            }
        }
        
    }
};

/*****************
Hazard Node Struct
*****************/

struct hazardNode
{
    /********************************************************
    Hazard status indicates if their is hazard, start and end 
    represent starting and ending intersections respectively,
    the next pointer points to the next hazard.
    ********************************************************/

    bool hazardStatus;
    char start;
    char end;
    hazardNode* next;

    /**********
    Constructor
    **********/

    hazardNode(bool status,char start1,char end1){
        hazardStatus=status;
        start=start1;
        end=end1;
        next=nullptr;
    }
};

/***********
Hazard Class
***********/

class Hazard
{
    private:

    hazardNode* head;

    public:

    /**********
    Constructor
    **********/

    Hazard(){
        head=nullptr;
    }

    /***************
    Inserting hazard
    ***************/

    void insertHazard(bool status,char start,char end){

        hazardNode* newNode=new hazardNode(status,start,end);

        /**************
        Empty List Case
        **************/

        if(head==nullptr){
            head=newNode;
        } 

        /******************
        Non Empty List Case
        ******************/
        
        else{

            hazardNode* temp=head;
            
            while(temp->next!=nullptr){
                temp=temp->next;
            }

            temp->next = newNode;
        }
    }

    /**************************************
    Checking for hazard in a specified road
    **************************************/

    bool checkHazard(char start,char end){
        
        hazardNode* temp=head;
        
        while(temp!=nullptr){
            
            if(temp->start==start && temp->end==end && temp->hazardStatus){
                return true;
            }
            
            temp=temp->next;
        }

        return false;
    }
    
    /*****************
    Displaying Hazards
    *****************/

    void displayHazards()
    {

        hazardNode* temp=head;
        string status;
        
        while(temp!=nullptr) 
        {
            if(temp->hazardStatus)
            {
                status="Blocked";
            }

            else
            {
                status="Clear";
            }

            if (status == "Blocked")
            {
                cout << temp->start << " to " << temp->end << " is " << status << endl;
            }

            temp=temp->next;
        }
    }
};

/*******************
Priority Queue Class
*******************/

class PriorityQueue 
{

    private:
    
    pair<int, char>* heap;  
    int capacity;           
    int size;               

    void swap(pair<int, char>& a,pair<int, char>& b)
    {
        pair<int, char> temp=a;
        a=b;
        b=temp;
    }

    void queueheapifyUp(int index)
    {
        int parent = (index - 1) / 2;
        if (index > 0 && heap[index].first < heap[parent].first) 
        {
            swap(heap[index], heap[parent]);
            queueheapifyUp(parent);
        }
    }

    void queueheapifyDown(int index) 
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && heap[left].first < heap[smallest].first) 
        {
            smallest = left;
        }

        if (right < size && heap[right].first < heap[smallest].first) 
        {
            smallest = right;
        }

        if (smallest != index) 
        {
            swap(heap[index], heap[smallest]);
            queueheapifyDown(smallest);
        }
    }

    public:
    
    PriorityQueue(int cap) 
    {
        capacity = cap;
        size = 0;
        heap = new pair<int, char>[capacity];
    }


    ~PriorityQueue()
    {
        delete[] heap;
    }

    void push(pair<int, char> element) 
    {
        if (size == capacity) 
        {
            cout << "Priority Queue is full!" << endl;
            return;
        }

        heap[size] = element;
        queueheapifyUp(size);
        size++;
    }

    pair<int, char> top() 
    {
        if (size == 0) 
        {
            return {2147483647, '\0'};  
        }
        return heap[0];
    }

    void pop() 
    {
        if (size == 0) 
        {
            cout << "Priority Queue is empty!" << endl;
            return;
        }
        heap[0] = heap[size - 1];
        size--;
        queueheapifyDown(0);
    }

    bool empty() 
    {
        return size == 0;
    }
};


/********************
Traffic Network Class
*********************/

class TrafficNetwork
{
    /**********************************************************
    This class implements the full traffic network, 
    encompassing various key components. It includes 
    an array of intersection pointers, representing all 
    available intersections within the system, an array 
    of traffic signals indicating the presence of signals 
    at multiple locations, and an array of congestion levels 
    that track the traffic density on each road in the network.
    **********************************************************/

    public:
    
    Node* intersections;
    int capacity;
    int size;
    Signal* signal[100];
    int roadCount;
    int signalCount;
    Congestion* congestionLevels; 
    bool originalSignal[100];
    Hazard hazard;

    /**********
    Constructor
    **********/

    TrafficNetwork(int capacity1)
    {
        capacity=capacity1;
        size=0;
        intersections=new Node[capacity];
        roadCount=0;
        signalCount=0;
        congestionLevels = new Congestion(capacity);

        for(int i=0; i<100; i++)
        {
            originalSignal[i]=false;
        }

    }

    /****************
    Searching Network
    ****************/

    bool searchNetwork(char data){

    /*****************************************
    Checking if an intersection already exists
    in our traffic network system.
    *****************************************/

        for(int i=0;i<size;i++){
            if(intersections[i].value==data){
                return true;
            }
        }

        return false;
    }

    /*********************************************
    Adding new intersection in our traffic network
    *********************************************/

    void addIntersection(char data){

        /*********************************************
        Handling cases, where network capacity is full
        and no more intersections can be added. If an 
        intersection already exists in our network it 
        shall not be added again.
        *********************************************/

        if(size>=capacity){
            return;
        }

        if(searchNetwork(data)){
            return;
        }

        /*******************************
        Updating intersections and count
        *******************************/

        intersections[size].value=data;
        size++;

    }

    /***********************************
    Adding a road in the traffic network
    ***********************************/

    void addRoad(char start,char end,int weight) 
    {
        Node* startNode=nullptr;
        Node* endNode=nullptr;
        string roadName="Road# "+to_string(roadCount+1);
    
        /**************************
        Finding start and end nodes
        **************************/

        for (int i = 0; i < size; i++) 
        {
            if (intersections[i].value == start) 
            {
                startNode = &intersections[i];
            }
    
            if (intersections[i].value == end) 
            {
                endNode = &intersections[i];
            }
        }
    
        /***************************************
        If either road is not found then no need
        to add to the traffic network.
        ***************************************/

        if (startNode == nullptr || endNode == nullptr) 
        {
            return;
        }
    
        /*********************************
        Creating an edge from start to end
        *********************************/

        Edge* newEdge1 = new Edge(weight, end, roadName);
        
        if (startNode->head == nullptr) 
        {
            startNode->head = newEdge1;
            startNode->tail = newEdge1;
        } 

        else 
        {
            startNode->tail->next = newEdge1;
            startNode->tail = newEdge1;
        }
    
        /*********************************
        Creating an edge from end to start
        **********************************/

        Edge* newEdge2 = new Edge(weight, start, roadName);
        
        if (endNode->head == nullptr) 
        {
            endNode->head = newEdge2;
            endNode->tail = newEdge2;
        }

        else 
        {
            endNode->tail->next = newEdge2;
            endNode->tail = newEdge2;
        }
    
        /**********************
        Updating the road count
        **********************/

        roadCount++;
    
        return;

    }

    void currentroad(char start, char end) 
    {

        for (int i = 0; i < size; i++) 
        {
            if (intersections[i].value == start) 
            { 
                Edge* edge = intersections[i].head;
                while (edge != nullptr) 
                { 
                    if (edge->destination == end) 
                    { 
                        edge->vehicleCount++; 
                        congestionLevels->insert(edge->name, edge->vehicleCount);
                        congestionLevels->updateCongestion(edge); 
                        return; 
                    }
                    edge = edge->next; 
                }
            }
        }
    }

    /*************************
    Displaying Traffic Network
    *************************/

    void displayNetwork()
    { 
        for(int i=0;i<size;i++)
        { 
            cout<<"Intersection "<<intersections[i].value<<": "; 
            Edge* current=intersections[i].head; 
            
            while(current!=nullptr)
            { 
                cout << "("<<current->destination<<", "<< current->weight << ")"; 
                current=current->next; 
                cout << " ";
            } 
            cout<<endl; 
        } 
        return;
    }
    
    int getSize()
    {
        return size;
    }

    /*******************************************
    Getting location of a specified intersection
    *******************************************/

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
        int* parent = new int[size];  
    
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

    void overrideSignal(char intersection) 
    {
        for (int i = 0; i < signalCount; i++) {
            originalSignal[i] = signal[i]->getSignalStatus();
            if (signal[i]->getIntersection() == intersection) {
                signal[i]->setStatus(true);
            } else {
                signal[i]->setStatus(false);
            }
        }
    }

    void restoreSignal()
    {
        for(int i=0; i<signalCount; i++)
        {
            signal[i]->setStatus(originalSignal[i]);
        }
    }

    int heuristic(char start, char end)
    {
          return abs(end - start);
    }

    pair<int, string> emergencyrouteAStar(char start, char end, string p)
    {
        cout << "Starting A* search from " << start << " to " << end << endl;

        PriorityQueue pq1(size);

        int costFromStart[size];
        int totalCost[size];
        char previous[size];
        bool visited[size];

        for (int i = 0; i < size; i++)
        {
            costFromStart[i] = 99999;
            totalCost[i] = 99999;
            previous[i] = '\0';
            visited[i] = false;
        }

        int startIndex = getNodeIndex(start);
        int endIndex = getNodeIndex(end);

        if (startIndex == -1 || endIndex == -1)
        {
            cout << "Start or end intersection not found!" << endl;
            return {99999, ""};
        }

        costFromStart[startIndex] = 0;
        totalCost[startIndex] = heuristic(start, end);
        pq1.push({totalCost[startIndex], start});

        while (!pq1.empty())
        {
            pair<int, char> current = pq1.top();
            pq1.pop();

            int currentCost = current.first;
            char currentNode = current.second;

            int currentIndex = getNodeIndex(currentNode);
            if (visited[currentIndex])
            {
                continue;
            }
            visited[currentIndex] = true;
            if (currentNode == end)
            {
                break;
            }

            Edge *edge = intersections[currentIndex].head;
            while (edge != nullptr)
            {
                if(hazard.checkHazard(currentNode, edge->destination))
                {
                    cout << "Blocked road detected from " << currentNode << " to " << edge->destination << endl;
                    edge = edge->next;
                    continue;
                }

                int neighborIndex = getNodeIndex(edge->destination);
                if (neighborIndex != -1 && !visited[neighborIndex])
                {
                    int newCost = currentCost + edge->weight;
                    if (newCost < costFromStart[neighborIndex])
                    {
                        costFromStart[neighborIndex] = newCost;
                        totalCost[neighborIndex] = newCost + heuristic(edge->destination, end);
                        previous[neighborIndex] = currentNode;
                        
                        if(p == "High")
                        {
                            totalCost[neighborIndex] -= 10; 
                        }
                        pq1.push({totalCost[neighborIndex], edge->destination});
                    }
                }
                edge = edge->next;
            }
        }

        string path;
        for (char current = end; current != '\0'; current = previous[getNodeIndex(current)])
        {
            path = current + path;
        }

        cout << "Final path: " << path << endl
             << endl;
        return {costFromStart[endIndex], path};
    }

};

/****************
Vehicle Path Node
****************/

class VehiclePathNode 
{
    public:

    char* path; 
    int travelTime; 
    VehiclePathNode* next; 

    VehiclePathNode(char* p, int time) 
    {
        path = p;
        travelTime = time;
        next = nullptr;
    }
};

/************
Vehicle Class
************/

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
    
    VehiclePathNode* head;
    
    Vehicle(string name, char st, char en)
    {
        id = name;
        start = st;
        end = en;
        
        dist = 0;
        path = NULL;
        current = start;
        curIndex = 0;
        
        head = NULL;
    }
    
    void shortestdis(TrafficNetwork& network)
    {
        pair<int, char*> result = network.shortestPath(start, end);
        int endpoint = network.getNodeIndex(end);
        
        int shortestDistance = result.first;
        path = result.second;
        
        dist = shortestDistance;
    }
    
    void movecar() //current postion of the vehicle changes
    {
        curIndex++;
        current = path[curIndex];
        cout << id << ": " << current;    
        cout << endl;
    }
    
    void addVehiclePath(char* path, int travelTime) 
    {
        VehiclePathNode* newNode = new VehiclePathNode(path, travelTime);

        if (head == nullptr) 
        {
            head = newNode;
        } 
        
        else 
        {
            VehiclePathNode* current = head;
            while (current->next != nullptr) 
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    
    void displayVehPath()
    {
        VehiclePathNode* current = head;
        while (current != nullptr) 
        {
            cout << "(Path: " << current->path << "), (Travel Time: " << current->travelTime << ")" << endl;
            current = current->next;
        }
        cout << endl;
    }    

    int getTravelTime(){
        return dist;
    }
};


/**********************
Emergency Vehicle Class
**********************/

class EmergencyVehicle
{
    public:
    string vehicleID;
    char startIntersection;
    char endIntersection;
    string priority;
    char current;
    string path;
    
    EmergencyVehicle(string vID, char start, char end, string pLevel)
    {
        vehicleID = vID;
        startIntersection = start;
        endIntersection = end;
        priority = pLevel;
        current = start;
    }
    
    string getvehicleID() const 
    {
        return vehicleID;
    }

   void route(TrafficNetwork &network)
    {
        network.overrideSignal(startIntersection);

        pair<int, string> result = network.emergencyrouteAStar(startIntersection, endIntersection, priority);
        string path = result.second;

        if (result.first == 99999)
        {
            cout << "No valid route found from " << startIntersection << " to " << endIntersection << endl;
        }
        else
        {
            cout<<"Route Found: "<<path<<endl;
        }

        network.restoreSignal();
    }

};

/********
Map Class
********/

class Map
{
    
    /**************************************************************************************
    This is the core class of our traffic management system, designed to efficiently manage 
    and simulate traffic network operations. It serves as the central hub where all other 
    components of the system interact, enabling the simulation of complex traffic events 
    and behaviors. By coordinating the various system modules, this class plays a pivotal 
    role in ensuring smooth and dynamic traffic management.
    **************************************************************************************/

    TrafficNetwork graph;
    Vehicle* vehicles[100]; 
    Hazard hazard;
    Signal* signal[100];
    EmergencyVehicle* emergencyVehicles[100];

    int signalCount;
    int vehicleCount;
    int emergencyvehicleCount;
    int resolvedCount;

    public:

    /**********
    Constructor
    **********/

    Map() : graph(100)
    {
        vehicleCount=0;
        emergencyvehicleCount=0;
        signalCount=0;
        resolvedCount=0;
        roadCSV();
        vehicleCSV();
        hazardCSV();
        signalCSV();
        emergencyVehiclesCSV();

    }

    /***************
    Reading Road CSV
    ***************/
    
    void roadCSV()
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

    /******************
    Reading Vehicle CSV
    ******************/
    
    void vehicleCSV()
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

    /*****************
    Reading Hazard CSV
    *****************/

    void hazardCSV()
    {
        ifstream file("road_closures.csv");
        string line;
        int count=0;

        if(!file.is_open())
        {
            cout<<"Error opening file!"<<endl;
        }
    
        while (getline(file, line)) 
        {
            string message;   
            if(!line.empty() && count>0)
            {
                bool status=false;
                char intersection1=line[0];
                char intersection2=line[2];
                
                for(int i=4; i < line.length(); i++)
                {
                    message+=line[i];
                }
    
                if(message=="Blocked"){
                    status=true;
                }
                
                hazard.insertHazard(status,intersection1,intersection2);
            }

            count++;

        }

        setSignalStatus();
        file.close();

    }
    
    /*****************
    Reading Signal CSV
    *****************/

    void signalCSV()
    {
        
        ifstream file("traffic_signals.csv");
        string line;
        int count=0;

        if(!file.is_open())
        {
            cout<<"Error opening file!"<<endl;
        }
    
        while (getline(file, line)) 
        {
             
            if(!line.empty() && count>0)
            {
                string timeString="";
        
                char intersection=line[0];
                
                for(int i=2; i < line.length(); i++)
                {
                    timeString+=line[i];
                }
                
                int time=stoi(timeString);
                signal[signalCount]=new Signal(intersection,time);
                heapifyUp(signalCount);  
                signalCount++;
            }

            count++;

        }

        file.close();

    }
    
    /*****************************
    Reading Emergency Vehicles CSV
    *****************************/

    void emergencyVehiclesCSV()
    {
        ifstream file("emergency_vehicles.csv");
        string line;
        int count = 0;

        if(!file.is_open())
        {
            cout << "Error opening file: emergency_vehicles.csv" << endl;
            return; 
        }

        while (getline(file, line)) 
        {
            if (line.empty() || count == 0) 
            {
                count++;
                continue;
            }

            stringstream ss(line);
            string vehID, startStr, endStr, priorityStr;

            getline(ss, vehID, ',');
            getline(ss, startStr, ',');
            getline(ss, endStr, ',');
            getline(ss, priorityStr, ',');

            emergencyVehicles[emergencyvehicleCount] = new EmergencyVehicle(vehID, startStr[0], endStr[0], priorityStr);
            emergencyvehicleCount++;
        }

        file.close();
    
    }

    /******************
    Updating Hazard CSV
    ******************/

    void updateHazardCSV(char intersection1,char intersection2, string status){
        ofstream file("road_closures.csv",ios::app);

        if(!file.is_open()){
            cout<<"Unable to open road_closures.csv file!"<<endl;
            return;
        }

        /**********************
        Writing new data to CSV
        **********************/

        file<<intersection1<<","<<intersection2<<","<<status<<"\n";
        hazard.insertHazard(true,intersection1,intersection2);

        file.close();

        cout<<"New data appended to road_closures.csv successfully"<<endl;

    }

    /******************************
    Updating Emergency Vehicles CSV
    ******************************/
    
    void updateEmergencyCSV(string EV,char intersection1,char intersection2, string level){
        
        ifstream file1("emergency_vehicles.csv");
        
        if(!file1.is_open()){
            cout<<"Unable to open emergency_vehicles.csv\n";
            return ;
        }

        string line;

        while(getline(file1,line)){
            
            int commaPos=-1;
            
            for(int i=0;i<line.length();i++){
                if(line[i]==','){
                    commaPos=i;
                    break;
                }
            }

            if(commaPos!=-1){
                string firstColumn="";

                for(int i=0;i<commaPos;i++){
                    firstColumn+=line[i];
                }

                if(firstColumn==EV){
                    cout<<EV<<" already exists in CSV can not append it again!"<<endl;
                    file1.close();
                    return;
                }
            }
        }

        ofstream file2("emergency_vehicles.csv",ios::app);

        if(!file2.is_open()){
            cout<<"Unable to open emergency_vehicles.csv file!"<<endl;
            return;
        }

        /**********************
        Writing new data to CSV
        **********************/

        file2<<EV<<","<<intersection1<<","<<intersection2<<","<<level<<"\n";
        
        file2.close();
        file1.close();

        emergencyVehicles[emergencyvehicleCount] = new EmergencyVehicle(EV, intersection1, intersection2, level);
        emergencyvehicleCount++;


        cout<<"New data appended to emergency_vehicles.csv successfully"<<endl;

    }

    /*******************
    Updating Vehicle CSV
    *******************/

    void updateVehicleCSV(string name,char intersection1,char intersection2){
        
        ifstream file1("vehicles.csv");
        
        if(!file1.is_open()){
            cout<<"Unable to open vehicles.csv\n";
            return ;
        }

        string line;

        while(getline(file1,line)){
            
            int commaPos=-1;
            
            for(int i=0;i<line.length();i++){
                if(line[i]==','){
                    commaPos=i;
                    break;
                }
            }

            if(commaPos!=-1){
                string firstColumn="";

                for(int i=0;i<commaPos;i++){
                    firstColumn+=line[i];
                }

                if(firstColumn==name){
                    cout<<name<<" already exists in CSV can not append it again!"<<endl;
                    file1.close();
                    return;
                }
            }
        }

        ofstream file2("vehicles.csv",ios::app);

        if(!file2.is_open()){
            cout<<"Unable to open vehicles.csv file!"<<endl;
            return;
        }

        /**********************
        Writing new data to CSV
        **********************/

        file2<<name<<","<<intersection1<<","<<intersection2<<"\n";
        
        file2.close();
        file1.close();

        vehicles[vehicleCount]=new Vehicle(name,intersection1,intersection2);
        

        cout<<"New data appended to vehicles.csv successfully"<<endl;

        vehicles[vehicleCount]->shortestdis(graph);

    
       // dfs(start, end, visited, "", distance, vehicles[i]); 
        //checkAndUpdatePath(name);
        vehicleCount++;

        return;
    }

    /**********************************************************
    Heapify Functions, these functions are used for replicating
    the max heap. The purpose of the max heap was to adjust the
    priority of signal activation.
    **********************************************************/

    void heapifyDown(int index)
    {
        int parent=index;
        int left=2*index+1;
        int right=2*index+2;

        if(left<signalCount && signal[left]->getCongestion()>signal[parent]->getCongestion()){
            parent=left;
        }

        if(right<signalCount && signal[right]->getCongestion()>signal[parent]->getCongestion()) {
            parent=right;
        }

        if(parent!=index){
            Signal* temp=signal[parent];
            signal[parent]=signal[index];
            signal[index]=temp;
            heapifyDown(parent);
        }

        return;
    }

    void heapifyUp(int index)
    {
        int parent=(index)/2;

        if(index>0 && signal[index]->getCongestion()>signal[parent]->getCongestion()){
            
            Signal* temp=signal[parent];
            signal[parent]=signal[index];
            signal[index]=temp;
            heapifyUp(parent);
        }

        return;
    }

    void buildHeap()
    {
        for(int i=(signalCount/2)-1;i>=0;i--){
            heapifyDown(i);
        }

        return;
    }
    
    void setSignalStatus()
    {
        if(signalCount>0){
            for (int i=0;i<signalCount;i++){

                char intersection=signal[i]->getIntersection();
                int congestionLevel=0;

                for(int j=0;j<graph.size;j++){
                    
                    Edge* edge=graph.intersections[j].head;
                    
                    while(edge!=nullptr){
                        
                        if(edge->destination==intersection){
                            congestionLevel+=graph.congestionLevels->getCongestionLevel(edge->name);
                        }

                        edge=edge->next;
                    }
                }

                signal[i]->setCongestion(congestionLevel);
            }

            buildHeap();

            signal[0]->setStatus(true);  
            cout << "Signal at intersection " << signal[0]->getIntersection()
                << " is now GREEN (Congestion: " << signal[0]->getCongestion() << ")" << endl;

            for(int i=1;i<signalCount;i++){
                signal[i]->setStatus(false);
                cout<<"Signal at intersection "<<signal[i]->getIntersection()
                    <<" is now RED (Congestion: "<<signal[i]->getCongestion()<<")"<<endl;
            }
        }
    }

    /**********************************************
    Calculating the shortest path for every vehicle
    **********************************************/

    void shortestDis()
    {
        for(int i = 0; i < vehicleCount; i++)
        {
            vehicles[i]->shortestdis(graph);
        }
    }

    /*********************************************
    Updating Signal Time Based on Congestion Level
    *********************************************/

    void updateSignalTimesBasedOnCongestion() 
    {
            
        /************************************
        Locating the road where signal exists
        ************************************/

        for (int i = 0; i < signalCount; i++) 
        {
            char intersection = signal[i]->getIntersection();

            for (int j = 0; j < graph.size; j++) 
            {
                Edge* edge = graph.intersections[j].head;

                while (edge != nullptr) {
                    if (edge->destination == intersection) {
                                            
                        /************************************
                        Checking congestion on the road found
                        ************************************/

                        int congestionLevel = graph.congestionLevels->getCongestionLevel(edge->name);

                        /***********************************************************
                        Recalculating time for signal if high congestion is detected
                        ***********************************************************/

                        if (congestionLevel > 6) {
                            cout << "High congestion detected at " << edge->name
                                << ". Recalculating signal time for intersection " 
                                << intersection << "." << endl;

                            signal[i]->reCalculateTime();
                        }

                    }

                    edge = edge->next;
                }
            }
        }

        /********************
        Setting Signal Status
        ********************/

        setSignalStatus();
    }

    /**************************************
    Displaying path for a specified vehicle
    **************************************/

    void displayVehiclePath(string vehicleID) 
    {
        /******************************************
        Traversing until specified vehicle is found
        ******************************************/

        bool vehicleFound = false;

        for (int i = 0; i < vehicleCount; i++) 
        {
            /*************************
            Displaying Vehicle Details
            *************************/

            if (vehicles[i]->id==vehicleID) 
            {
                cout << "Vehicle ID: " << vehicles[i]->id 
                    << ", Path: " << vehicles[i]->path 
                    << ", Distance: " << vehicles[i]->dist << endl;
                vehicleFound = true;
                break;
            }
        }

        if (!vehicleFound) 
        {
            cout << "Vehicle with ID " << vehicleID << " not found." << endl;
        }

    }

    int pathtime(char* path) 
    {
        int totalTime = 0;
    
        for (int i = 0; path[i] != '\0' && path[i + 1] != '\0'; i++) 
        {
            char current = path[i];
            char next = path[i + 1];
    
            int currentIndex = graph.getNodeIndex(current);
            if (currentIndex == -1) 
            {
                return -1; 
            }
    
            Edge* edge = graph.intersections[currentIndex].head;
            bool found = false;
    
            while (edge != nullptr) 
            {
                if (edge->destination == next) 
                {
                    totalTime += edge->weight; 
                    found = true;
                    break;
                }

                edge = edge->next;
            }

        }

        return totalTime;
    }
    
    int reroutetime(char* path, int traveltime)
    {
        int penalty = 0;
        for (int i = 0; path[i + 1] != '\0'; i++) 
        {
            char currentIntersection = path[i];
            char nextIntersection = path[i + 1];
            string roadName = "Road# " + to_string(graph.getNodeIndex(currentIntersection) + 1);
            
            int congestionlevel = graph.congestionLevels->getCongestionLevel(roadName);

            penalty += congestionlevel;
        }    

        penalty += traveltime;

        return penalty;
    }
    
    char* reroutepath(int congestLevel, char intersection, Vehicle* vehicle)
    {
        VehiclePathNode* currentNode = vehicle->head;
        int min = 999;
        char* bestPath = nullptr;
    
        while (currentNode != nullptr)
        {
            char* path = currentNode->path;
            for (int i = 0; path[i] != '\0'; i++)
            {
                char inter = path[i];
                if (inter == intersection)
                {
                    int remainingLength = strlen(path) - i;
                    char* tempPath = new char[remainingLength + 1];
                    strcpy(tempPath, path + i);
    
                    bool hazarddead = false;
                    for (int j = 0; tempPath[j] != '\0' && tempPath[j + 1] != '\0'; j++)
                    {
                        if (hazard.checkHazard(tempPath[j], tempPath[j + 1]))
                        {
                            hazarddead = true;
                            break;
                        }
                    }
    
                    if (hazarddead)
                    {
                        delete[] tempPath;
                        continue;
                    }
    
                    int newTime = pathtime(tempPath);
                    int rtime = reroutetime(tempPath, newTime);
    
                    if (rtime < min)
                    {
                        min = rtime;
                        bestPath = path;
                    }
    
                    delete[] tempPath;
                }
            }
    
            currentNode = currentNode->next;
        }
    
        return bestPath;
    }
    
    bool reroute(char* bestpath, Vehicle* vehicle)
    {
        if (reroutetime(vehicle->path, vehicle->dist) == reroutetime(bestpath, pathtime(bestpath)))
        {
            return false;
        }
        
        else
        {
            vehicle->path = bestpath;
            vehicle->dist = pathtime(bestpath);
            return true;
        }
    }

    void move(string vehicleID) {
        for (int i = 0; i < vehicleCount; i++) {
            if (vehicles[i]->id == vehicleID) {
                char currentIntersection = vehicles[i]->current;
                char nextIntersection = vehicles[i]->path[vehicles[i]->curIndex + 1];

                string roadName = "Road# " + to_string(graph.getNodeIndex(currentIntersection) + 1);
                int congestionLevel = graph.congestionLevels->getCongestionLevel(roadName);

                if (congestionLevel > 6) {
                    cout << "Congestion detected on road between " << currentIntersection
                        << " and " << nextIntersection << " Rerouting vehicle " << vehicles[i]->id << endl;

                    char* bestPath = reroutepath(congestionLevel, nextIntersection, vehicles[i]);
                    if (reroute(bestPath, vehicles[i])) {
                        cout << "New route has been found for vehicle " << vehicleID << endl;
                        resolvedCount++;
                    } else {
                        cout << "No alternate route available for vehicle " << vehicleID << " right now" << endl;
                    }
                } else {
                    // Move the vehicle to the next intersection if no congestion
                    graph.currentroad(currentIntersection, nextIntersection);
                    vehicles[i]->movecar();

                    if (vehicles[i]->current == vehicles[i]->end) {
                        cout << vehicles[i]->id << " reached its destination" << endl;

                        
                        for (int j = i; j < vehicleCount - 1; j++) {
                            vehicles[j] = vehicles[j + 1];
                        }
                        vehicleCount--;
                    }
                }
                return; 
            }
        }
        
        cout << vehicleID << " not found!" << endl;
    }

    
    void moveVehicle()
    {
        for (int i = 0; i < vehicleCount;)
        {
            char currentIntersection = vehicles[i]->current;
            char nextIntersection = vehicles[i]->path[vehicles[i]->curIndex + 1];

            string roadName = "Road# " + to_string(graph.getNodeIndex(currentIntersection) + 1);
            int congestionLevel = graph.congestionLevels->getCongestionLevel(roadName);

            if (congestionLevel > 6) 
            {
                cout << "Congestion detected on road between " << currentIntersection
                    << " and " << nextIntersection << ". Rerouting vehicle " << vehicles[i]->id << endl;

                char* bestpath = reroutepath(congestionLevel, nextIntersection, vehicles[i]);
                
                if (reroute(bestpath, vehicles[i]))
                {
                    cout << "new route has been found";
                }
                
                else
                {
                    cout << "you have no other route available right now";
                }
            }
            else
            {
                // Move the vehicle to the next intersection if no congestion
                graph.currentroad(currentIntersection, nextIntersection);
                vehicles[i]->movecar();
                if (vehicles[i]->current == vehicles[i]->end) 
                {
                    cout << vehicles[i]->id << " reached its destination." << endl;

                    // Remove the vehicle once it has reached its destination
                    for (int j = i; j < vehicleCount - 1; j++) 
                    {
                        vehicles[j] = vehicles[j + 1];
                    }
                    vehicleCount--;
                }
                else
                {
                    i++; // Move to the next vehicle
                }
            }

            cout << endl;
        }
    }
    
    void checkAndUpdatePath(string vehicleId)
    {
        Vehicle* vehicle = nullptr;
        for (int i = 0; i < vehicleCount; i++)
        {
            if (vehicles[i]->id == vehicleId)
            {
                vehicle = vehicles[i];
                break;
            }
        }
    
        for (int i = 1; i < strlen(vehicle->path) - 1; i++)
        {
            char start = vehicle->path[i];
            char reroutestart = vehicle->path[i - 1];
            char end = vehicle->path[i + 1];
    
            if (hazard.checkHazard(start, end))
            {
                cout << "Hazard found in vehicle " << vehicleId << " route: (" << start << "," << end << ")" << endl;
                cout << "Current path: " << vehicle->path << endl;

                resolvedCount++;
                char* bestPath = reroutepath(graph.congestionLevels->getCongestionLevel("Road#"), reroutestart, vehicle);
    
                if (bestPath != nullptr)
                {
                    vehicle->path = bestPath;
                    vehicle->curIndex = 0;
                    vehicle->dist = pathtime(bestPath);
                    cout << "New Path: " << bestPath << endl << endl;
                }
                else
                {
                    cout << "No alternative path available for vehicle: " << vehicleId << endl << endl;
                }
                break;
            }
        }
    }

    void hazardcheck()
    {
        for (int i = 0; i < vehicleCount; i++)
        {
            Vehicle* vehicle = vehicles[i];
            for (int j = vehicle->curIndex; j < strlen(vehicle->path) - 1; j++)
            {
                char currentIntersection = vehicle->path[j];
                char nextIntersection = vehicle->path[j + 1];
    
                if (hazard.checkHazard(currentIntersection, nextIntersection))
                {
                    cout << vehicles[i]->id << " current Route: " << vehicles[i]->path << endl;
                    cout << "Intersection found: " << currentIntersection << "->" << nextIntersection << endl;
                    
                    string roadName = "Road# " + to_string(graph.getNodeIndex(currentIntersection) + 1);
                    int congestionLevel = graph.congestionLevels->getCongestionLevel(roadName);
    
                    char* bestpath = reroutepath(congestionLevel, currentIntersection, vehicle);
                    
                    if (reroute(bestpath, vehicle))
                    {
                        cout << "New route: " << bestpath << endl << endl; 
                    }
                    
                    else
                    {
                        cout << "No alternative route available for Vehicle: " << vehicles[i]->id << "(road: " 
                             << currentIntersection << " -> " << nextIntersection << ")" << endl << endl;
                    }
                }
            }
        }
    }
    
    void dfs(char current, char end, bool visited[], string currentPath, int distance, Vehicle* vehicle) 
    {
        int currentIndex = graph.getNodeIndex(current);
        if (currentIndex == -1) 
        {
            return; 
        }
    
        visited[currentIndex] = true;
        currentPath += current; 
        
        if (current == end) 
        {
            char* pathArray = new char[currentPath.length() + 1];
            strcpy(pathArray, currentPath.c_str());
            vehicle->addVehiclePath(pathArray, distance); 
        } 
        else 
        {
            Edge* edge = graph.intersections[currentIndex].head;
            while (edge != nullptr) 
            {
                int neighborIndex = graph.getNodeIndex(edge->destination);
                if (neighborIndex != -1 && !visited[neighborIndex]) 
                {
                    dfs(edge->destination, end, visited, currentPath, distance + edge->weight, vehicle);
                }
                edge = edge->next;
            }
        }
        visited[currentIndex] = false; 
    }
    
    void findAllPaths() 
    {
        for (int i = 0; i < vehicleCount; i++) 
        {
            char start = vehicles[i]->start;
            char end = vehicles[i]->end;
            int distance = 0;
            int size = graph.getSize();
            bool* visited = new bool[size];
            
            for (int j = 0; j < size; j++) 
            {
                visited[j] = false; 
            }
            
            
            dfs(start, end, visited, "", distance, vehicles[i]); 
            checkAndUpdatePath(vehicles[i]->id);
        }
        
    }
    
    void testEmergencyRoutes() 
    {
        cout << "Total emergency vehicles: " << emergencyvehicleCount << endl; // Debugging line
        for (int i = 0; i < emergencyvehicleCount; ++i) 
        {
            cout << "Emergency vehicle: " << emergencyVehicles[i]->getvehicleID() << endl; 
            emergencyVehicles[i]->route(graph);  
        }
        cout << "Emergency routing complete." << endl;
    }
    
    void blockroad(char a, char b)
    {
        bool status = true;
        hazard.insertHazard(status, a, b);
        displayBlockage();
    }
    
    void updateSignal() 
    {
        for (int i = 0; i < signalCount; i++) {
            if (signal[i] != nullptr) {
    
                if (signal[i]->getSignalStatus() && signal[i]->getSignalTimer() > 0) {
                    signal[i]->decrementSignalTimer();
                    cout << "Signal at intersection " << signal[i]->getIntersection()
                        << " timer decremented. Remaining time: "
                        << signal[i]->getSignalTimer() << " seconds." << endl;
                }

                if (signal[i]->getSignalTimer() == 0 && signal[i]->getSignalStatus()) {
                    signal[i]->setStatus(false);
                    cout << "Signal at intersection " << signal[i]->getIntersection()
                        << " is now RED." << endl;

                    buildHeap();  

                    if (i + 1 < signalCount) 
                    {
                        signal[i + 1]->setStatus(true); 
                        signal[i + 1]->resetSignalTimer(signal[i + 1]->getSignalTimer());  
                        cout << "Signal at intersection " << signal[i + 1]->getIntersection()
                            << " is now GREEN." << endl;
                        break;
                    }
                }
            }
        }
    }
    
    void simulVehicle(char a, char b)
    {
        string vehID =  "User Car";
        int i = vehicleCount;
        
        vehicles[i] = new Vehicle(vehID, a, b);
        
        vehicles[i]->shortestdis(graph);

        //finding paths
        char start = vehicles[i]->start;
        char end = vehicles[i]->end;
        int distance = 0;
        int size = graph.getSize();
        bool* visited = new bool[size];
            
        for (int j = 0; j < size; j++) 
        {
            visited[j] = false; 
        }
    
        dfs(start, end, visited, "", distance, vehicles[i]); 
        vehicles[i]->displayVehPath();
        
        cout << "Shortest Path: (" << vehicles[i]->path << "), (Time: " << vehicles[i]->dist << ")" << endl;
        vehicleCount++;
    }
    
    void displayRoads()
    {
        graph.displayNetwork();
    }

    /*************************************************
    Displaying all the vehicles in the traffic network
    *************************************************/
    
    void displayVehicles()
    {
        for (int i = 0; i < vehicleCount; i++) 
        {
            cout << "Vehicle ID: " << vehicles[i]->id 
                 << ", (Start: " << vehicles[i]->start 
                 << ", End: " << vehicles[i]->end 
                 << "), (shortest distance: " << vehicles[i]->dist <<  ") " << endl;
                 
        }
    }

    /*****************
    Displaying Signals
    *****************/
    
    void displaySignals()
    {
        for(int i=0;i<signalCount;i++)
        {
            cout << "Intersection: " <<signal[i]->getIntersection() <<" Green Time: "<<signal[i]->getSignalTimer()<<endl;
        }
    }
    
    void displayCongest()
    {
        for (int i = 0; i < vehicleCount; i++)
        {
            char currentIntersection = vehicles[i]->current;
            char nextIntersection = vehicles[i]->path[vehicles[i]->curIndex + 1];
            graph.currentroad(currentIntersection, nextIntersection);
        }    

        graph.congestionLevels->displayCongestion();
    }
    
    void displayBlockage()
    {
        hazard.displayHazards();
    }

    /*******************************************
    Displaying the entire traffic network system
    *******************************************/
    
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
        hazard.displayHazards();
        
        hazardcheck();
        moveVehicle();
        moveVehicle();
    
        graph.congestionLevels->displayCongestion();
        updateSignalTimesBasedOnCongestion();

        updateSignal();

        for(int i=0;i<signalCount;i++)
        {
            string signalMessage;

            if(signal[i]->getSignalStatus())
            {
                signalMessage="GREEN";
            }

            else
            {
                signalMessage="RED";
            }

            cout << "Intersection " <<signal[i]->getIntersection() <<": ";
            cout << "(Green Time: " << signal[i]->getSignalTimer() <<"), (Signal Status: " << signalMessage << ")" <<endl;
        } 
    }

    void moveEmergencyVehicle(string emergencyVehicleID)
    {
        for (int i = 0; i < emergencyvehicleCount; i++)
        {
            if (emergencyVehicles[i]->vehicleID == emergencyVehicleID)
            {
                char currentIntersection = emergencyVehicles[i]->current;
                pair<int, string> result = graph.emergencyrouteAStar(currentIntersection, emergencyVehicles[i]->endIntersection,emergencyVehicles[i]->priority);
                string path = result.second;

                if (path.length() < 2)
                {
                    cout << "No valid path found for emergency vehicle " << emergencyVehicleID << endl;
                    return;
                }

                cout << "\nOverriding signals for emergency vehicle " << emergencyVehicleID << "..." << endl;
                for (int j = 0; j < path.length(); j++)
                {
                    graph.overrideSignal(path[j]);
                }

                for (int j = 0; j < path.length() - 1; j++)
                {
                    char currentInter = path[j];
                    char nextInter = path[j + 1];
                    graph.currentroad(currentInter, nextInter);
                    emergencyVehicles[i]->current = nextInter;
                    cout << emergencyVehicleID << ": reached intersection " << nextInter << endl;
                }

                if (emergencyVehicles[i]->current == emergencyVehicles[i]->endIntersection)
                {
                    cout << emergencyVehicleID << " reached its destination" << endl;

                    for (int j = i; j < emergencyvehicleCount - 1; j++)
                    {
                        emergencyVehicles[j] = emergencyVehicles[j + 1];
                    }
                    emergencyvehicleCount--;
                }

                cout << "\nRestoring normal signal operations..." << endl;
                graph.restoreSignal();

                return;
            }
        }
        cout << "Emergency vehicle " << emergencyVehicleID << " not found!" << endl;
    }
    
    /*********************************
    Calculation of performance metrics
    **********************************/

    void performanceMetrics(){
        int sumOfTime=0;
        int averageTravelTime;

        for(int i=0;i<vehicleCount;i++){
            sumOfTime+=vehicles[i]->getTravelTime();
        }

        averageTravelTime=sumOfTime/vehicleCount;

        cout<<"Average Vehicle Travel Time: "<<averageTravelTime<<endl;
        cout<<"Number of Resolved Congestion Events: "<<resolvedCount<<endl;
    }

};


/************
Main Function
************/

int main() 
{

    /*************************************
    Intializing Map object,calculating the 
    shortest distance and all possible
    paths.
    *************************************/

    Map trafficMap;
    trafficMap.shortestDis();
    trafficMap.findAllPaths();

    /************************************
    List of variables used in switch case
    ************************************/

    string priorityLevel,EV,vehicleName,addVehicle,moveVehicle; 
    char a,b,c,d,start,end,vehicleStart,vehicleEnd;
    int id,vehicleID,moveVehicleID;

    /*******************
    Simulation Dashboard
    *******************/
    
    while(true)
    {
        int ans;
        cout << "------ Simulation Dashboard ------" << endl;
        cout << "1.  Display City Traffic Network\n"
         << "2.  Display All Vehicles\n"
         << "3.  Display Traffic Signal Status\n"
         << "4.  Display Congestion Status\n"
         << "5.  Display Blocked Roads\n"
         << "6.  Handle Emergency Vehicle Routing\n"
         << "7.  Block Road due to Accident\n"
         << "8.  Add an Emergency Vehicle\n"
         << "9.  Display Path for a Specific Vehicle\n"
         << "10. Add a new Vehicle\n"
         << "11. Move a Vehicle\n"
         << "12. Display Performance Metrics\n"
         << "13. Simulate Vehicle Routing\n"
         << "14. Bonus Case\n"
         << "15. Move Emergency Vehicle\n"
         << "16. Exit Simulation\n\n";
         
        cout << "Enter you choice: ";
        cin >> ans;
        
        switch (ans) 
        {

            case 1:

                cout << "Displaying City Traffic Network...\n";
                trafficMap.displayRoads();
                break;

            case 2:

                cout << "Displaying All Vehicles...\n";
                trafficMap.displayVehicles();
                break;

            case 3:

                cout << "Displaying Traffic Signal Status...\n";
                trafficMap.displaySignals();
                break;

            case 4:

                cout << "Displaying Congestion Status...\n";
                trafficMap.displayCongest();
                break;

            case 5:

                cout << "Displaying Blocked Roads...\n";
                trafficMap.displayBlockage();
                cout << "Roads are not find for the below blocked roads";
                
                break;

            case 6:

                cout << "Handling Emergency Vehicle Routing...\n";
                trafficMap.testEmergencyRoutes();
                break;

            case 7:

                cout << "Blocking Road due to Accident...\n";
                cout << "Start & End Intersection: ";
                cin >> a >> b;
                
                trafficMap.blockroad(a, b);
                trafficMap.updateHazardCSV(a,b,"Blocked");
                break;
            
            case 8:

                cout<<"Adding Emergency Vehicle...\n";
                cout<<"Enter Emergency Vehicle ID #: ";
                cin>>id;

                EV="EV"+to_string(id);

                cout<<"Enter Start & End Intersection: ";
                cin>>start>>end;

                cout<<"Enter Priority Level: ";
                cin>>priorityLevel;

                trafficMap.updateEmergencyCSV(EV,start,end,priorityLevel);
            
                break;

            case 9:

                cout<<"Displaying Path for a Specific Vehicle...\n";
                cout<<"Enter name of the vehicle whose path you want to displayed: ";
                cin>>vehicleName;

                trafficMap.checkAndUpdatePath(vehicleName);
                trafficMap.displayVehiclePath(vehicleName);
                break; 

            case 10:

                cout<<"Adding New Vehicle...\n";
                cout<<"Enter Vehicle ID #: ";
                cin>>vehicleID;

                addVehicle="V"+to_string(vehicleID);

                cout<<"Enter Start & End Intersection: ";
                cin>>vehicleStart>>vehicleEnd;

                trafficMap.updateVehicleCSV(addVehicle,vehicleStart,vehicleEnd);
                //trafficMap.findAllPaths();
                break;

            case 11:

                cout<<"Moving A Vehicle...\n";
                cout<<"Enter Vehicle ID #: ";
                cin>>moveVehicleID;

                moveVehicle="V"+to_string(moveVehicleID);
                trafficMap.checkAndUpdatePath(moveVehicle);
                trafficMap.move(moveVehicle);

                break;

            case 12:

                cout<<"Getting Performance Metrics...\n";
                trafficMap.performanceMetrics();

                break;

            case 13:

                cout << "Simulating Vehicle Routing...\n";
                cout << "Start & End Intersection: ";
                cin >> c >> d;
                
                trafficMap.simulVehicle(c, d);
                break;
            
            case 14:

                cout<<"Starting Bonus Case...\n";
                trafficMap.moveVehicle();
                break;

            case 15:

                cout << "Moving Emergency Vehicle...\n";
                cout << "Enter Emergency Vehicle ID #: ";
                cin >> id;
        
                EV = "EV" + to_string(id);
                trafficMap.moveEmergencyVehicle(EV);
                break;

            case 16:

                cout << "Exiting Simulation. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        
        }

        cout << endl;
    
    }
    
    return 0;

}
