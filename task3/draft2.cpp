#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <cstring>
#include<string>
#include<windows.h>

using namespace std;

struct Edge{

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

struct Node{

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

class Signal{

    private:

    bool signalStatus;
    int signalTimer;
    char signalIntersection;

    public:

    Signal(char intersection,int time,bool status){
        addSignal(intersection,time);  
        setStatus(status);  
    }

    void addSignal(char intersection,int time){
        signalTimer=time;
        signalIntersection=intersection;
    }

    void setStatus(bool status){
        signalStatus=status;
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
        signalTimer+=10;
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

    void displayCongestion() {
        for (int i = 0; i < capacity; i++) {
            if(congestionLevel[i]!=0){
                cout << congestionMarker[i] << " has " 
                     << congestionLevel[i] << " vehicles. Congestion Level: " 
                     << congestionMessage[i] << endl;
            }
        }
        
    }
};

struct hazardNode{
    
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


class Hazard{

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

    void displayHazards(){
        
        cout << "\n--- Hazard List ---\n";
        
        hazardNode* temp=head;
        string status;
        
        while(temp!=nullptr) {
            
            if(temp->hazardStatus){
                status="Blocked";
            }

            else{
                status="Clear";
            }

            cout<<"Road from "<<temp->start<<" to "<<temp->end<<" is "<<status<<endl;
            temp=temp->next;
        }
    }

};

class TrafficNetwork
{
    public:
    
    Node* intersections;
    int capacity;
    int size;
    int roadCount;
    congestion* congestionLevels; 

    public:
    TrafficNetwork(int capacity1)
    {
        capacity=capacity1;
        size=0;
        intersections=new Node[capacity];
        roadCount=0;
        congestionLevels = new congestion(capacity);

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

    void addRoad(char start,char end,int weight)
    {
        Node* startNode=nullptr;
        Node* endNode=nullptr;
        string roadName="Road# "+to_string(roadCount+1);

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
        
        Edge* newEdge = new Edge(weight,end,roadName); 
        
        if(startNode->head==nullptr){ 
            startNode->head=newEdge; 
            startNode->tail=newEdge; 
        }

        else{ 
            startNode->tail->next=newEdge; 
            startNode->tail=newEdge; 
        } 

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
};

class Map
{
    TrafficNetwork graph; // single graph
    Vehicle* vehicles[100]; // multiple cars
    Hazard hazard;
    Signal* signal[100];
    
    int signalCount;
    int vehicleCount;
    
    public:
    Map() : graph(10)
    {
        vehicleCount = 0;
        signalCount=0;
        roadscsv();
        vehiclescsv();
        hazardCSV();
        signalCSV();
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

    void hazardCSV(){
        
        ifstream file("accidents_or_closures.csv");
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
        file.close();
    }

    void signalCSV(){
        
        ifstream file("traffic_signal_timings.csv");
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
                bool status=false;  
                
                if(count==1){
                    status=true;
                }
                char intersection=line[0];
                
                for(int i=2; i < line.length(); i++)
                {
                    timeString+=line[i];
                }
                
                int time=stoi(timeString);
                signal[signalCount]=new Signal(intersection,time,status);
                signalCount++;
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

    void setSignalStatus(){
        
    }

    void updateSignalTimesBasedOnCongestion() {
        for(int i=0;i<signalCount;i++){
            
            char intersection=signal[i]->getIntersection();
            
            for (int j=0;j<graph.size;j++) {
                Edge* edge = graph.intersections[j].head;

                while (edge != nullptr) {
                    if (edge->destination == intersection) {
                        int congestionLevel = graph.congestionLevels->getCongestionLevel(edge->name);

                        if(congestionLevel>6){
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
        moveVehicle();
        graph.congestionLevels->displayCongestion();
        updateSignalTimesBasedOnCongestion();

        updateSignal();

        cout<<"\n--- Signal Details ---\n";
        for(int i=0;i<signalCount;i++){
            string signalMessage;

            if(signal[i]->getSignalStatus()){
                signalMessage="GREEN";
            }

            else{
                signalMessage="RED";
            }

            cout<<"\nSignal at intersection " <<signal[i]->getIntersection() <<": "<<endl;
            cout<<"Status: "<<signalMessage<<" , Signal Time: "<<signal[i]->getSignalTimer()<<endl;
                
            } 

            //system("cls");
    }

    void updateSignal(){
        for(int i=0;i<signalCount;i++){
            
            if(signal[i]!=nullptr){
        
                if(signal[i]->getSignalTimer()>0 && signal[i]->getSignalStatus()){
                    signal[i]->decrementSignalTimer();
                } 
                
                if(signal[i]->getSignalTimer()==0){
                    
                    signal[i]->setStatus(false);
                    cout<<"Signal at intersection "<<signal[i]->getIntersection()<<" is now RED"<<endl;

                    if(i+1<signalCount && signal[i+1]!=nullptr){
                        signal[i+1]->setStatus(true);
                        cout<<"Signal at intersection "<<signal[i+1]->getIntersection()<<" is now GREEN"<<endl;
                        signal[i]->resetSignalTimer(signal[i+1]->getSignalTimer());
                    }
                }
            }
        }
    }
};

int main() 
{
    Map trafficMap;

    trafficMap.shortestDis();

    //while(true){
        //clrscr();
        trafficMap.displayMap();
        //Sleep(500);
        //system("cls");
    //}
    trafficMap.findAllPaths(); // Generate all paths for vehicles.

    return 0;
}