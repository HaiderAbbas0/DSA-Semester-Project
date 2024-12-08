# Smart Traffic Management System Simulator

## Introduction
The **Smart Traffic Management System Simulator** is an interactive console-based application designed to model and simulate a city's traffic management system. It offers functionalities to manage vehicles, traffic signals, blocked roads, and emergency vehicle routing while providing real-time updates on the city traffic network. This system can help visualize and optimize urban traffic flow under various scenarios, including emergencies and road hazards.

---

## Importance
In growing urban landscapes, efficient traffic management is crucial for reducing travel time, minimizing congestion, and ensuring emergency vehicle priority. The simulator serves as a practical tool for:
1. **Optimizing Traffic Flow**: Enhances the efficiency of road usage by rerouting vehicles and dynamically managing signals.
2. **Emergency Preparedness**: Prioritizes emergency vehicles, ensuring quick response times.
3. **Congestion Management**: Identifies the density of the traffic and reroutes the traffic. 
4. **Finding the Best Route**: Finds the route that has the least penalty (congestion level and travel time).
5. **Roads Closure**: Reroutes a vehicle path if road closure is found.
---

## Approach
1. **City Traffic Network Representation**: The city is represented as a weighted, directed graph where nodes are intersections and edges are roads. Weights are dynamically updated based on travel times or congestion levels.
2. **Real-Time Routing**: Vehicle routes are recalculated dynamically using algorithms like Dijkstra's and A*.
3. **Congestion Handling**: The system continuously monitors vehicle density and redirects traffic using DFS to reduce bottlenecks.
4. **Emergency Management**: Priority routing for emergency vehicles overrides normal traffic operations.
5. **Interactive Dashboard**: A console based interface enables users to visualize, manage, and simulate traffic scenarios.

---

## Features
1. **City Traffic Network (Graph Representation)**:
   - Dynamic addition/removal of roads and intersections.
   - Visualized as a weighted, directed graph.
2. **Vehicle Routing System**:
   - Optimal route calculation using Dijkstra’s algorithm.
   - Re-routes vehicles dynamically based on network changes.
3. **Traffic Signal Management**:
   - Dynamic green signal adjustments based on vehicle density.
   - Emergency overrides for critical scenarios.
4. **Congestion Monitoring**:
   - Tracks road congestion in real-time using hash tables.
   - Displays congestion levels and provides alternative paths.
5. **Emergency Vehicle Handling**:
   - Implements A* for emergency routing.
   - Restores normal flow after emergency vehicle clearance.
6. **Accident and Road Closure Simulation**:
   - Blocks roads/intersections dynamically.
   - Updates vehicle routes and recalculates traffic flow.
7. **Simulation Dashboard**:
   - Displays real-time traffic data and vehicle movement.
   - Logs all system actions for performance analysis.

---

## Classes and Their Use
## **1. Edge Struct**

### **Purpose**  
Represents a road or connection between two intersections in the traffic network.

### **Data Members**  
1. **Destination**: Specifies the destination intersection for the road.  
2. **Weight**: Represents the travel time or cost associated with the road.  
3. **Next**: Points to the next edge in a linked list of edges, enabling connectivity.  
4. **Vehicle Count**: Tracks the number of vehicles currently on the road.  
5. **Name**: Provides a unique identifier for the road.

### **Member Functions**  
- **Constructor**: Initializes the edge with specific destination, weight, and name.

---

## **2. Node Struct**

### **Purpose**  
Represents an intersection in the traffic network.

### **Data Members**  
1. **Value**: The identifier or label of the intersection.  
2. **Head**: Points to the first edge (road) connected to the intersection.  
3. **Tail**: Points to the last edge connected to the intersection.

### **Member Functions**  
- **Constructor**: Initializes the node with a given value.

---

## **3. Linked Node Struct**

### **Purpose**  
A fundamental building block for linked lists used in various data structures within the network.

### **Data Members**  
1. **Data**: The information stored in the node.  
2. **Next**: Pointer to the next node in the list.

### **Member Functions**  
- **Constructor**: Initializes the node with specific data.

---

## **4. LinkedList Class**

### **Purpose**  
Implements a linked list data structure for storing and managing sequences of elements.

### **Data Members**  
1. **Head**: Points to the first node in the linked list.

### **Member Functions**  
1. **Constructor**: Creates an empty linked list.  
2. **Get Head**: Retrieves the head node of the list.  
3. **Insert**: Adds a new node at the end of the list.  
4. **Search**: Locates a specific value in the list.  
5. **Delete**: Removes the first node from the list.  
6. **Display**: Prints all elements in the list.

---

## **5. Signal Class**

### **Purpose**  
Represents a traffic signal at an intersection.

### **Data Members**  
1. **Signal Status**: Indicates whether the signal is green or red.  
2. **Signal Timer**: Tracks the remaining time for the current signal state.  
3. **Signal Intersection**: Identifies the intersection controlled by the signal.  
4. **Congestion**: Represents the level of congestion at the intersection.

### **Member Functions**  
1. **Constructor**: Initializes the signal with a specific intersection and timer.  
2. **Add Signal**: Adds a new signal to the system.  
3. **Set Status**: Updates the signal status (green or red).  
4. **Set Congestion**: Updates congestion levels at the intersection.  
5. **Get Congestion**: Returns the current congestion level.  
6. **Get Signal Status**: Retrieves the signal’s status.  
7. **Get Signal Timer**: Retrieves the remaining signal time.  
8. **Decrement Signal Timer**: Decreases the signal timer.  
9. **Reset Signal Timer**: Resets the signal timer.  
10. **Get Intersection**: Identifies the intersection controlled by the signal.  
11. **Recalculate Time**: Adjusts the signal timer based on congestion.

---

## **6. Congestion Class**

### **Purpose**  
Manages congestion levels for roads in the traffic network.

### **Data Members**  
1. **Capacity**: Maximum number of roads the class can handle.  
2. **Size**: Tracks the current number of roads.  
3. **Congestion Levels**: Stores congestion data for each road.  
4. **Congestion Markers**: Maintains identifiers for roads.  
5. **Congestion Messages**: Provides status messages for each road.  
6. **Congestion Table**: A hash table for efficient congestion data storage.

### **Member Functions**  
1. **Constructor**: Initializes the class with specific capacity.  
2. **Hash Function**: Generates a hash code for road names.  
3. **Get Congestion Level**: Retrieves congestion for a specific road.  
4. **Insert**: Adds road congestion data to the hash table.  
5. **Search**: Locates a road in the table.  
6. **Update Congestion**: Adjusts congestion levels and generates messages.  
7. **Display Congestion**: Outputs congestion data for all roads.

---

## **7. Hazard Node Struct**

### **Purpose**  
Represents a hazard (e.g., blockage) on a road.

### **Data Members**  
1. **Hazard Status**: Indicates whether the road is blocked or clear.  
2. **Start**: The starting intersection of the affected road.  
3. **End**: The ending intersection of the affected road.  
4. **Next**: Points to the next hazard in the list.

### **Member Functions**  
- **Constructor**: Initializes a hazard node with specific details.

---

## **8. Hazard Class**

### **Purpose**  
Manages hazards in the traffic network.

### **Data Members**  
1. **Head**: Points to the first hazard in the list.

### **Member Functions**  
1. **Constructor**: Creates an empty hazard list.  
2. **Insert Hazard**: Adds a new hazard to the list.  
3. **Check Hazard**: Verifies if a road is blocked by a hazard.  
4. **Display Hazards**: Outputs all hazards in the network.

---

## **9. PriorityQueue Class**

### **Purpose**  
Implements a priority queue for efficient selection of the next intersection during pathfinding algorithms.

### **Data Members**  
1. **Heap**: An array used as a min-heap to store elements.  
2. **Capacity**: The maximum number of elements the heap can hold.  
3. **Size**: Tracks the current number of elements in the heap.

### **Member Functions**  
1. **Constructor**: Initializes the priority queue with a given capacity.  
2. **Swap**: Exchanges two elements in the heap.  
3. **Heapify Up**: Maintains the heap property by moving an element up.  
4. **Heapify Down**: Maintains the heap property by moving an element down.  
5. **Push**: Adds a new element to the heap.  
6. **Top**: Retrieves the highest-priority element without removing it.  
7. **Pop**: Removes and returns the highest-priority element.  
8. **Empty**: Checks if the heap is empty.

---

## **10. TrafficNetwork Class**

### **Purpose**  
Represents the entire traffic network, including intersections, roads, signals, and congestion.

### **Data Members**  
1. **Intersections**: An array of intersection nodes.  
2. **Capacity**: The maximum number of intersections the network can hold.  
3. **Size**: The current number of intersections.  
4. **Signal**: An array of traffic signals in the network.  
5. **Road Count**: Tracks the total number of roads.  
6. **Signal Count**: Tracks the total number of signals.  
7. **Congestion Levels**: A `Congestion` object for managing congestion.  
8. **Original Signal**: Stores the original state of signals for restoration.

### **Member Functions**  
1. **Constructor**: Initializes the network with a given capacity.  
2. **Search Network**: Verifies if a specific intersection exists in the network.  
3. **Add Intersection**: Adds a new intersection to the network.  
4. **Add Road**: Creates a road between two intersections.  
5. **Current Road**: Updates vehicle count and congestion on a road.  
6. **Display Network**: Prints the structure of the network.  
7. **Get Size**: Returns the number of intersections in the network.  
8. **Get Node Index**: Finds the index of an intersection in the array.  
9. **Shortest Path**: Implements Dijkstra’s algorithm to find the shortest path between two intersections.  
10. **Override Signal**: Temporarily modifies signal timings for emergency routes.  
11. **Restore Signal**: Reverts signals to their original states.  
12. **Heuristic**: Calculates a heuristic for the A* search algorithm.  
13. **Emergency Route A* Search**: Finds the shortest path for emergency vehicles.

---

## **11. VehiclePathNode Struct**

### **Purpose**  
Represents a node in a linked list of paths associated with a vehicle.

### **Data Members**  
1. **Path**: Stores the path taken by the vehicle.  
2. **Travel Time**: Estimated travel time for the path.  
3. **Next**: Points to the next path node in the list.

### **Member Functions**  
- **Constructor**: Initializes the path node with specific details.

---

## **12. Vehicle Class**

### **Purpose**  
Represents a vehicle in the traffic network.

### **Data Members**  
1. **ID**: A unique identifier for the vehicle.  
2. **Start**: The starting intersection for the vehicle.  
3. **End**: The destination intersection.  
4. **Distance**: The shortest distance between the start and end.  
5. **Path**: The shortest path for the journey.  
6. **Current Position**: The vehicle’s current location.  
7. **Current Index**: Tracks the vehicle’s progress along the path.  
8. **Head**: Points to the head of a linked list of paths (if storing multiple paths).

### **Member Functions**  
1. **Constructor**: Initializes the vehicle with its ID, start, and end points.  
2. **Shortest Distance**: Calculates the shortest path using Dijkstra’s algorithm.  
3. **Move Car**: Moves the vehicle to the next intersection along the path.  
4. **Add Vehicle Path**: Stores a path and its travel time.  
5. **Display Vehicle Path**: Outputs all stored paths for the vehicle.  
6. **Get Travel Time**: Returns the shortest travel time.

---

## **13. EmergencyVehicle Class**

### **Purpose**  
Represents an emergency vehicle with higher routing priority.

### **Data Members**  
1. **Vehicle ID**: A unique identifier for the emergency vehicle.  
2. **Start Intersection**: The starting point of the emergency vehicle.  
3. **End Intersection**: The destination of the vehicle.  
4. **Priority**: Priority level for routing.  
5. **Current Position**: The vehicle's current location.  
6. **Path**: Shortest path to the destination.

### **Member Functions**  
1. **Constructor**: Initializes the emergency vehicle with its ID, start, end, and priority.  
2. **Get Vehicle ID**: Retrieves the vehicle’s ID.  
3. **Route**: Calculates the shortest path using A* search, overrides signal timings, and restores them afterward.

---

## **14. Map Class**

### **Purpose**  
Serves as the core class for managing and simulating the traffic network.

### **Data Members**  
1. **Graph**: A `TrafficNetwork` object representing the road network.  
2. **Vehicles**: An array of `Vehicle` objects in the simulation.  
3. **Hazard**: A `Hazard` object to manage road hazards.  
4. **Signal**: An array of `Signal` objects in the network.  
5. **Emergency Vehicles**: An array of `EmergencyVehicle` objects.  
6. **Signal Count**: Tracks the number of traffic signals.  
7. **Vehicle Count**: Tracks the total number of vehicles.  
8. **Emergency Vehicle Count**: Tracks the total number of emergency vehicles.  
9. **Resolved Count**: Counts rerouted vehicles due to hazards or congestion.

### **Member Functions**  
1. **Constructor**: Reads input data from CSV files and initializes the network.  
2. **Update CSVs**: Updates hazard, emergency, and vehicle data in CSV files.  
3. **Build Heap**: Prepares a max heap of signals based on congestion.  
4. **Set Signal Status**: Updates signal status using congestion levels.  
5. **Shortest Distance**: Calculates the shortest path for vehicles using Dijkstra’s algorithm.  
6. **Reroute**: Finds alternate routes for vehicles when congestion or hazards occur.  
7. **Move Vehicles**: Simulates vehicle movement and handles congestion.  
8. **Display Functions**: Outputs details about roads, vehicles, signals, congestion, blockages, and the overall map.  
9. **Find All Paths**: Uses DFS to determine all possible paths between intersections.  
10. **Emergency Route Testing**: Verifies emergency vehicle routing.  
11. **Block Road**: Adds a new hazard to the road network.

---

## Data Structures and Algorithms

| **DSA Used**            | **Purpose**                                              |
|--------------------------|----------------------------------------------------------|
| **Graph**                | Represent the city’s traffic network.                   |
| **Priority Queue**       | Manage traffic signal priority based on vehicle density. |
| **Min-Heap**             | Efficiently find the road with the most congestion.     |
| **Hash Table**           | Track real-time vehicle counts on roads.                |
| **Dijkstra’s Algorithm** | Calculate shortest paths for vehicles.                  |
| **A* Algorithm**         | Emergency vehicle routing with heuristic optimization.  |
| **BFS/DFS**              | Detect congestion zones or inaccessible paths.          |

---

## Outputs
| **Case Number** | **Case Description**                       | **Expected Output**                                                                                     |
|------------------|-------------------------------------------|---------------------------------------------------------------------------------------------------------|
| **1**            | **Display City Traffic Network**         | Outputs all  intersections and roads with travel times.             |
| **2**            | **Display All Vehicles**                 | Lists all vehicles in the network, showing their current location, destination, and shortest distance.       |
| **3**            | **Display Traffic Signal Status**        | Displays the green signal durations for all intersections.
| **4**            | **Display Congestion Status**            | Highlights roads with congestion levels, showing vehicle counts and congestion labels.              |
| **5**            | **Display Blocked Roads**                | Lists all roads that are currently blocked.                       |
| **6**            | **Handle Emergency Vehicle Routing**     | Displays the fastest route for emergency vehicles  |
| **7**            | **Block Road due to Accident**           | Simulates an accident by marking a road as blocked and recalculates routes for affected vehicles.         |
| **8**            | **Add an Emergency Vehicle**             | Allows adding a new emergency vehicle, specifying its ID, start and end intersections, and priority.     |
| **9**            | **Display Path for a Specific Vehicle**  | Shows the shortest path, travel time, and the current location of the specified vehicle.                 |
| **10**           | **Add a New Vehicle**                    | Adds a new vehicle to the system, specifying its ID, start intersection, and destination intersection.    |
| **11**           | **Move a Vehicle**                       | Simulates the movement of a specified vehicle to its next location along the shortest path.              |
| **12**           | **Display Performance Metrics**          | Outputs metrics such as average travel times and congestion reduction efficiency.       |
| **13**           | **Simulate Vehicle Routing**             | Simulates all vehicle routing paths, showing the vehicles paths, travel times and shortest path in the end |
| **14**           | **Bonus Case**                           | Reserved for moving all the vehicles an intersection at once.         |
| **15**           | **Move Emergency Vehicle**               | Moves a specified emergency vehicle along its priority route, showing updated paths and travel times.    |
| **16**           | **Exit Simulation**                      | Terminates the simulation and saves any final data if required.                                          |
---

### **Conclusion**  
The Smart Traffic Management System Simulator offers a robust solution for optimizing urban traffic flow, managing congestion, and prioritizing emergency routes in real-time. By leveraging advanced algorithms and dynamic data structures, it creates an interactive platform to address modern traffic challenges. With future enhancements, this simulator has the potential to become a comprehensive tool for urban traffic planning and management.

