#include<iostream>
#include<fstream>
using namespace std;

struct Edge{

    int weight;
    Edge* next;

    Edge(int weight1){
        weight=weight1;
        next=nullptr;
    }
};

struct Node{

    char value;
    Edge* head;

    Node(char value1){
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

        for(int i=0;i<capacity;i++){
            intersections[i].value=new Node('');
        }

    }

    void addIntersection(){
        
        if(size>=capacity){
            cout<<"Maximum capacity reached, can't add more intersections"<<endl;
            return;
        }     
    }

    void addRoad(){

    }

    void displayNetwork(){

    }

    ~TrafficNetwork(){
        
    }
};


int main(){

    TrafficNetwork graph;

    ifstream file("road_network.csv");
    string line;

    if(!file.is_open()){
        cout<<"Error opening file!"<<endl;
        return -1;
    }


    cout<<"Hello"<<endl;
    while(getline(file,line)){
        cout<<line<<endl;
    }

    file.close();

    return 0;

}
