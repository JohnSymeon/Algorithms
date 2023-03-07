//This script calculates the MST of a given graph with positive integer costs
//using the greedy Kruskal and Prim algorithms.
//The graph is scanned from a text file in the format of
//first line = total number of nodes
//the rest of the lines contain the edges of the graph as;
//edge_starting_node edge_pointing_node edge_cost


#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

struct edge                                     //directed edge with starting node, end node, and cost
{
	edge(int start=0, int end=0,int cost=0):		//Init Struct
		start(start),end(end),cost(cost){}
	//Struct Variables
	int start;
	int end;
	int cost;
};
class graph                                  //Graph Class
{
	public:
	graph(void){init_file();}		//Init Class
	//public functions
	void print();     			   	   //use to display all edges	
	void Kruskal();    				    //call to calculate the MST using the Kruskal algorithm
	void Prim();       				   //call to calculate the MST using the Prim algorithm
	//private functions
	private:
	void init_file();                  //initialisation by scanning data from data.txt in format; 
										//edge_starting_node edge_pointing_node edge_cost 
										//and then sorting the edges by ascending cost
	static bool comp(edge e1, edge e2);//compare function for sort
	int find_set(int i, int* Parent);  // used for DFS search in order to determine if testing edge creates cycle
 	//Class variables
	edge* edge_matrix;	            //contains all edges
	int matrix_size;				//stores the size of the edges' container
	int GraphSize;					//stores the size of the Graph given from first int in data.txt
};

void graph::init_file() 							
{
	ifstream fp("data.txt");
	istream_iterator<int> start(fp), end;
	vector<int> Values(start,end); 				//scan the data from file and put then into an integer vector
	
	GraphSize = Values.at(0);					//store the Graph's size from first element
	matrix_size = Values.size()/3;
	edge_matrix = new edge[matrix_size]; 		//generate an array of edge objects
	
	int counter=0;	
	for(int i =1;i<Values.size();i+=3) 			 //populate the values of all edges with the scanned data
	{
		edge_matrix[counter].start = Values.at(i);
		edge_matrix[counter].end = Values.at(i+1);
		edge_matrix[counter].cost = Values.at(i+2);
		counter++;
	}
					
	sort(&edge_matrix[0],&edge_matrix[matrix_size],comp);		//sort edges by ascending cost
}	
bool graph::comp(edge e1, edge e2){return (e1.cost<e2.cost);} 
void graph::print()
{
	for(int i=0;i<matrix_size;i++)
		cout<< edge_matrix[i].start<<" "<< edge_matrix[i].end <<" "<< edge_matrix[i].cost<<endl;
}	
void graph::Kruskal()
{
	int Sum=0;	
	int Parent[GraphSize];								//create parents array for every node
	for(int i=0;i<GraphSize;i++)						//and init it with itself
		Parent[i] = i;
	Sum = edge_matrix[0].cost; 							//init Sum	with first edge
	Parent[edge_matrix[0].end] = edge_matrix[0].start;	//init the first node's parent
	cout<< "The selected edges for the MST are;"<<endl<<endl;
	cout<< edge_matrix[0].start << " "<< edge_matrix[0].end<< " "<< edge_matrix[0].cost<< endl;
	
	for(int i=0;i<matrix_size;i++) 					//for all edges
	{	
													//check if the selected edge creates cycle
		int source = find_set(edge_matrix[i].start,Parent);
		int destination = find_set(edge_matrix[i].end,Parent);

		if(source!= destination)					//if the parents of testing edge's nodes are not the same there is no cycle
		{	
			Sum += edge_matrix[i].cost; 			//add the cost
			Parent[source] = destination;			//Update parents
			cout<< edge_matrix[i].start << " "<< edge_matrix[i].end<< " "<< edge_matrix[i].cost<< endl;
		}
	}
	cout<<"\nKruskal MST cost is: "<< Sum<<endl<<endl;
}
void graph::Prim()
{
	vector<bool> reached_bool_matrix(matrix_size);		// keep track of all reached nodes to avoid cycles
	for(int i=0;i<GraphSize;i++)						//init them all as false meaning unreached
		reached_bool_matrix[i] = false;
	
	int Sum=0;
	Sum = edge_matrix[0].cost; 							//init with first edge
	reached_bool_matrix.at(edge_matrix[0].start)=true;	//both nodes of first edge are now reached
	reached_bool_matrix.at(edge_matrix[0].end)=true;
	
	int pos =0;
	
	cout<< "The selected edges for the MST are;"<<endl<<endl;
	cout<< edge_matrix[0].start << " "<< edge_matrix[0].end<< " "<< edge_matrix[0].cost<< endl;
	
	//for all reached nodes check if an edge 
	//leads away from them into an unreached node and pick smallest
	// search as many times as there are edges
	for(int k=0;k<matrix_size;k++)  //for all edges
	{	
		int min = 1000;										//sets a large init value for min
		bool FoundEdge = false;
		
		for(int i=1;i<reached_bool_matrix.size();i++) 	//for all nodes
		{
			if(reached_bool_matrix.at(edge_matrix[i].start)&& 
			!reached_bool_matrix.at(edge_matrix[i].end) && 
			edge_matrix[i].cost<min)		
			{
				//if the node at start is reached and
				//if it points to an unreached node and
 				//if the cost is smaller than minimum

				FoundEdge = true; 								//an edge was found(used to avoid adding min 
																//of edge that does not exist)
				pos = i; 										//save the position of edge 
				min = edge_matrix[i].cost;						//save minimal cost
			}
		}
		if(FoundEdge)													//if an edge was found
		{
			Sum+=edge_matrix[pos].cost; 								//add to sum the smallest cost
			reached_bool_matrix.at(edge_matrix[pos].end)=true;			//add to reached the end of the edge
			cout<< edge_matrix[pos].start << " "<< edge_matrix[pos].end<< " "<< edge_matrix[pos].cost<< endl;
		}
	}
	cout<< "\nPrim MST cost is: "<< Sum<< endl;
}
int graph::find_set(int i, int* Parent)
{
	if(i==Parent[i])							//if parent of itself return self
		return i;
	return find_set(Parent[i],Parent);			//else call again with i's parent
}

int main(void) {	
	graph g1;	
	g1.Kruskal();
	g1.Prim();
}
