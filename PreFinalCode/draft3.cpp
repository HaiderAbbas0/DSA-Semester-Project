#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <cstring>
#include<string>

#define INF 99999

using namespace std;

struct Edge
{

    char destination;
    int weight;
    Edge* next;
    int vehicleCount;
    string name;

    Edge(int weight1,char destination1,string name1)
    {
        weight=weight1;
        destination=destination1;
        next=nullptr;
        vehicleCount = 0;
        name=name1;
    }
};

struct Node
{

    char value;
    Edge* head;
    Edge* tail;

    Node(char value1='\0'){
        value=value1;
        head=nullptr;
        tail=nullptr;
    }

};

struct linkedNode
{
    int data;
    linkedNode* next;
   
    linkedNode(int value){
        data=value;
        next=nullptr;
    }
};

class LinkedList
{

    private:

    linkedNode* head;
    
    public:
    LinkedList()
    {
        head=nullptr;
    }

    linkedNode* getHead(){
        return head;
    }

    void insert(int value)
    {
        linkedNode* newNode = new linkedNode(value);
       
        if(head==nullptr)
        {
            head=newNode;
            return;
        }
       
            linkedNode* temp=head;
           
            while(temp->next!=nullptr)
            {
                temp=temp->next;
            }
            temp->next=newNode;
        
        return;
    }

    bool search(int value)
    {
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

    void Del()
    {
        linkedNode* temp=head;
        head=head->next;
        delete temp;
        return;
    }

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

class Signal
{

    private:

    bool signalStatus;
    int signalTimer;
    char signalIntersection;
    int congestion;

    public:

    Signal(char intersection,int time){
        addSignal(intersection,time);  
    }

    void addSignal(char intersection,int time){
        signalTimer=time;
        signalIntersection=intersection;
    }

    void setStatus(bool status){
        signalStatus=status;
    }

    void setCongestion(int k){
        congestion=k;
    }

    int getCongestion(){
        return congestion;
    }

    bool getSignalStatus(){
        return signalStatus;
    }

    int getSignalTimer(){
        return signalTimer;
    }

    void decrementSignalTimer(){
        if(signalTimer>0){
            signalTimer--;
        }
    }

    void resetSignalTimer(int nextSignalTime){
        signalTimer=nextSignalTime; 
    }

    char getIntersection(){
        return signalIntersection;
    }

    
    void reCalculateTime(){
        //signalTimer+=10;
    }

};

class congestion
{
    int capacity;
    int size;
    
    int* congestionLevel;
    string* congestionMarker;
    string* congestionMessage;
    LinkedList* congestionTable;

    public:

    congestion(int capacity1)
    {
        capacity=capacity1;
        size=0;
        congestionTable=new LinkedList[capacity];
        congestionMessage=new string[capacity];
        congestionLevel=new int[capacity];
        congestionMarker=new string[capacity];

        for (int i = 0; i < capacity; ++i) {
            congestionLevel[i] = 0;
            congestionMessage[i] = "";
            congestionMarker[i] = "";
        }
    }

    int hashFunction(const string& key)
    {   
        char lastChar=key[key.length()-1];
        int index=lastChar-'0';  
    
        return index%capacity;
    }
    
    int getCongestionLevel(string roadName){
        int index=hashFunction(roadName);

        return congestionLevel[index];
    }

    void insert(const string& key, int value)
    {
        int index=hashFunction(key);
        congestionTable[index].insert(value); 
        congestionMarker[index]=key;  
    }

    int search(const string& key)
    {
        int index=hashFunction(key);
        return congestionTable[index].search(index);
    }

    void updateCongestion(Edge* edge){

        int totalVehicles = edge->vehicleCount;  
        int index = hashFunction(edge->name);

        congestionLevel[index] = totalVehicles;

        if (totalVehicles <= 3) {
            congestionMessage[index] = "Low congestion";
        }
        else if (totalVehicles <= 6) {
            congestionMessage[index] = "Moderate congestion";
        }
        else {
            congestionMessage[index] = "High congestion";
        }

    }

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

struct hazardNode
{
    bool hazardStatus;
    char start;
    char end;
    hazardNode* next;

    hazardNode(bool status,char start1,char end1){
        hazardStatus=status;
        start=start1;
        end=end1;
        next=nullptr;
    }
};

class Hazard
{
    private:

    hazardNode* head;

    public:

        Hazard(){
        head=nullptr;
    }

    void insertHazard(bool status,char start,char end){
        hazardNode* newNode=new hazardNode(status,start,end);

        if(head==nullptr){
            head=newNode;
        } 
        
        else{

            hazardNode* temp=head;
            
            while(temp->next!=nullptr){
                temp=temp->next;
            }

            temp->next = newNode;
        }
    }

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

class PriorityQueue 
{
private:
    pair<int, char>* heap;  
    int capacity;           
    int size;               

    void swap(pair<int, char>& a, pair<int, char>& b)
    {
        pair<int, char> temp = a;
        a = b;
        b = temp;
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

class TrafficNetwork
{
    public:
    
    Node* intersections;
    int capacity;
    int size;
    Signal* signal[100];
    int roadCount;
    int signalCount;
    congestion* congestionLevels; 
    bool originalSignal[100]; // storing the original signal status as false representing that false means RED

    TrafficNetwork(int capacity1)
    {
        capacity=capacity1;
        size=0;
        intersections=new Node[capacity];
        roadCount=0;
        signalCount=0;
        congestionLevels = new congestion(capacity);

        for(int i=0; i<100; i++)
        {
            originalSignal[i]=false;
        }

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

    void addRoad(char start, char end, int weight) 
    {
        Node* startNode = nullptr;
        Node* endNode = nullptr;
        string roadName = "Road# " + to_string(roadCount + 1);
    
        // Find the start and end nodes
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
    
        // If either node is not found, return
        if (startNode == nullptr || endNode == nullptr) 
        {
            return;
        }
    
        // Create the edge from start to end
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
    
        // Create the edge from end to start
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
    
        // Increment the road count
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

    pair<int, string> emergencyrouteAStar(char start, char end) 
    {
    cout << "Starting A* search from " << start << " to " << end << endl;

    PriorityQueue pq1(size);
    
    int costFromStart[size];   
    int totalCost[size];       
    char previous[size];       
    bool visited[size];        

    
    for (int i = 0; i < size; i++) {
        costFromStart[i] = INF;
        totalCost[i] = INF;
        previous[i] = '\0';
        visited[i] = false;
    }

    int startIndex = getNodeIndex(start);
    int endIndex = getNodeIndex(end);

    if (startIndex == -1 || endIndex == -1) 
    {
        cout << "Start or end intersection not found!" << endl;
        return {INF, ""};
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
    if (visited[currentIndex]) continue;

        visited[currentIndex] = true;
        if (currentNode == end) break;  

        Edge* edge = intersections[currentIndex].head;
        while (edge != nullptr) 
        {
            int neighborIndex = getNodeIndex(edge->destination);
            if (neighborIndex != -1 && !visited[neighborIndex]) 
            {
                int newCost = currentCost + edge->weight;
                if (newCost < costFromStart[neighborIndex]) 
                {
                costFromStart[neighborIndex] = newCost;
                totalCost[neighborIndex] = newCost + heuristic(edge->destination, end);
                previous[neighborIndex] = currentNode;
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

    cout << "Final path: " << path << endl << endl;
    return {costFromStart[endIndex], path};
}

};

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
};

class EmergencyVehicle
{
    private:
    string vehicleID;
    char startIntersection;
    char endIntersection;
    string priority;

    public:
    EmergencyVehicle(string vID, char start, char end, string pLevel)
    {
        vehicleID = vID;
        startIntersection = start;
        endIntersection = end;
        priority = pLevel;
    }
    string getvehicleID() const 
    {
        return vehicleID;
    }

   void route(TrafficNetwork& network)
{
    //cout << "Overriding signal for intersection: " << startIntersection << endl;
    network.overrideSignal(startIntersection);
    
    pair<int, string> result = network.emergencyrouteAStar(startIntersection, endIntersection);
    string path = result.second; 

    if (result.first == INF) 
    {
        cout << "No valid route found from " << startIntersection << " to " << endIntersection << endl;
    } 
    network.restoreSignal();
}

};

class Map
{
    TrafficNetwork graph; // single graph
    Vehicle* vehicles[100]; // multiple cars
    Hazard hazard;
    Signal* signal[100];
    EmergencyVehicle* emergencyVehicles[100];
    int signalCount;
    int vehicleCount;
    int emergencyvehicleCount;

    public:
    Map() : graph(100)
    {
        vehicleCount = 0;
        emergencyvehicleCount=0;
        signalCount=0;
        roadscsv();
        vehiclescsv();
        hazardCSV();
        signalCSV();
        emergencyVehiclesCSV();

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
                heapifyUp(signalCount - 1);  
                signalCount++;
            }
            count++;
        }

        file.close();

    }

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


    void updateHazardCSV(char intersection1,char intersection2, string status){
        ofstream file("road_closures.csv",ios::app);

        if(!file.is_open()){
            cout<<"Unable to open road_closures.csv file!"<<endl;
            return;
        }

        file<<intersection1<<","<<intersection2<<","<<status<<"\n";
        hazard.insertHazard(true,intersection1,intersection2);

        file.close();

        cout<<"New data appended to road_closures.csv successfully"<<endl;
    }
    
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

        file2<<EV<<","<<intersection1<<","<<intersection2<<","<<level<<"\n";
        
        file2.close();
        file1.close();

        emergencyVehicles[emergencyvehicleCount] = new EmergencyVehicle(EV, intersection1, intersection2, level);
        emergencyvehicleCount++;


        cout<<"New data appended to emergency_vehicles.csv successfully"<<endl;
    }

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

        file2<<name<<","<<intersection1<<","<<intersection2<<"\n";
        
        file2.close();
        file1.close();

        vehicles[vehicleCount]=new Vehicle(name,intersection1,intersection2);
        vehicleCount++;

        cout<<"New data appended to vehicles.csv successfully"<<endl;
    }

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
    }

    void heapifyUp(int index)
    {
        int parent=(index-1)/2;

        if(index>0 && signal[index]->getCongestion()>signal[parent]->getCongestion()){
            
            Signal* temp=signal[parent];
            signal[parent]=signal[index];
            signal[index]=temp;
            heapifyUp(parent);
        }
    }

    void buildHeap()
    {
        for(int i=(signalCount/2)-1;i>=0;i--){
            heapifyDown(i);
        }
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

    void shortestDis()
    {
        for(int i = 0; i < vehicleCount; i++)
        {
            vehicles[i]->shortestdis(graph);
        }
    }

    void updateSignalTimesBasedOnCongestion() 
    {
        for (int i = 0; i < signalCount; i++) 
        {
            char intersection = signal[i]->getIntersection();

            for (int j = 0; j < graph.size; j++) 
            {
                Edge* edge = graph.intersections[j].head;

                while (edge != nullptr) {
                    if (edge->destination == intersection) {
                        int congestionLevel = graph.congestionLevels->getCongestionLevel(edge->name);

                        if (congestionLevel > 6) {
                            cout << "High congestion detected at " << edge->name
                                << ". Recalculating signal time for intersection " 
                                << intersection << "." << endl;

                            signal[i]->reCalculateTime();  // Increase the signal time once based on congestion
                        }
                    }
                    edge = edge->next;
                }
            }
        }

        setSignalStatus();  // After congestion-based updates, set signal statuses based on priority
    }

    void displayVehiclePath(string vehicleID) 
    {
        bool vehicleFound = false;
        for (int i = 0; i < vehicleCount; i++) 
        {
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
        char* bestpath;
        
        while (currentNode != nullptr) 
        {
            char* path = currentNode->path; // whole path array
            for (int i = 0; path[i] != '\0'; i++) 
            {
                char inter = path[i]; // each intersection
                if (inter == intersection)
                {
                    int remainingLength = strlen(path) - i;
                    char* tempPath = new char[remainingLength + 1]; 
                    strcpy(tempPath, path + i);
                    
                    int newTime = pathtime(tempPath);
                    int rtime = reroutetime(tempPath, newTime);
                    
                    if (rtime < min)
                    {
                        min = rtime;
                        bestpath = path;
                    }
                }
            }
            
            currentNode = currentNode->next;
        }
        return bestpath;
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
    
    void hazardcheck()
    {
        for (int i = 0; i < vehicleCount; i++)
        {
            char nextInterStart = vehicles[i]->path[vehicles[i]->curIndex];
            char nextInterEnd = vehicles[i]->path[vehicles[i]->curIndex + 1];

            string roadName = "Road# " + to_string(graph.getNodeIndex(nextInterStart) + 1);
            
            int congestionLevel = graph.congestionLevels->getCongestionLevel(roadName);
            
            cout << "start: " << nextInterStart;
            cout << "end: " << nextInterEnd << endl;
            
            if (hazard.checkHazard(nextInterStart, nextInterEnd))
            {
                cout  << "hazard found " << nextInterStart << endl;
                char* bestpath = reroutepath(congestionLevel, nextInterStart, vehicles[i]);
                
                if (reroute(bestpath, vehicles[i]))
                {
                    cout << "new route has been found";
                }
                
                else
                {
                    cout << "you have no other route available right now";
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
    
    void displaySignals()
    {
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
    
    void displayCongest()
    {
        for (int i = 0; i < vehicleCount; i++)
        {
            char currentIntersection = vehicles[i]->current;
            char nextIntersection = vehicles[i]->path[vehicles[i]->curIndex + 1];
            graph.currentroad(currentIntersection, nextIntersection);

            /*string roadName = "Road# " + to_string(graph.getNodeIndex(currentIntersection) + 1);
            int congestionLevel = graph.congestionLevels->getCongestionLevel(roadName);

            cout << currentIntersection << " to " << nextIntersection << " -> Vehicles: " << congestionLevel << endl;
            */
        }    
        graph.congestionLevels->displayCongestion();
    }
    
    void displayBlockage()
    {
        hazard.displayHazards();
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

};

int main() 
{
    Map trafficMap;
    trafficMap.shortestDis();
    trafficMap.findAllPaths();

    string priorityLevel,EV,vehicleName,addVehicle; 
    char a,b,c,d,start,end,vehicleStart,vehicleEnd;
    int id,vehicleID;

    //trafficMap.testEmergencyRoutes();
    
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
         << "11. Simulate Vehicle Routing\n"
         << "12. Exit Simulation\n\n";
         
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
                cout << "\nUpdating Signal...\n";
                trafficMap.updateSignal();
                break;
            case 4:
                cout << "Displaying Congestion Status...\n";
                trafficMap.displayCongest();
                break;
            case 5:
                cout << "Displaying Blocked Roads...\n";
                trafficMap.displayBlockage();
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
                break;

            case 11:
                cout << "Simulating Vehicle Routing...\n";
                cout << "Start & End Intersection: ";
                cin >> c >> d;
                
                trafficMap.simulVehicle(c, d);
                break;
            case 12:
                cout << "Exiting Simulation. Goodbye!\n";
                return 0; 
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        cout << endl;
    }
    return 0;
}