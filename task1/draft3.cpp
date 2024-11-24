#include<iostream>
#include<fstream>
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

class TrafficNetwork{

private:

    Node* intersections;
    int capacity;
    int size;

public:

    TrafficNetwork(int capacity1){

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
            cout<<"Maximum capacity reached can't add more intersections"<<endl;
            return;
        }

        if(searchNetwork(data)){
            cout<<"Cannot insert the intersection already exists in the network"<<endl;
            return;
        }

        intersections[size].value=data;
        cout<<"Intersection "<<data<<" added successfully!"<<endl;
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
            cout<<start<<" not found, can not add road!"<<endl;
            return;
        }

        if(endNode==nullptr){
            cout<<end<<" not found, can not add road!"<<endl;
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

    ~TrafficNetwork(){
        delete[] intersections;
    }

};

int main(){

    TrafficNetwork graph(10);
    int count=0;

    ifstream file("road_network.csv");
    string line;

    if(!file.is_open()){
        cout<<"Error opening file!"<<endl;
        return -1;
    }

    while (getline(file, line)) {
        string weight="";
        if(!line.empty() && count>0){
            char intersection1=line[0];
            char intersection2=line[2];
            
            for(int i=4;i<line.length();i++){
                weight+=line[i];
            }

            int travelTime=stoi(weight);  
            graph.addIntersection(intersection1);
            graph.addIntersection(intersection2);
            graph.addRoad(intersection1,intersection2,travelTime);
        }

        count++;
    }

    graph.displayNetwork();

    file.close();

    return 0;
}

