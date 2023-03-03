// This program generates a graph with given parameters of size, edge density, minimum and maximum cost.
//
//After the graph generation, Dijkstra's algorithm can be used to calculate the shortest path cost to each node from the starting node 0.
#include <iostream>
#include <cstdlib>
#include <ctime>

const int N = 50;

using namespace std;

const int size = 5;

class graph
{
	public:
		graph(int size = 10, float probability = 0.1, float min_cost = 1.0, float max_cost = 10.0)://Number of nodes, edge density, minimum cost, maximum cost
			size(size), probability(probability), min_cost(min_cost),max_cost(max_cost) {init();} //initalises at creation of class -default size of graph:10
	
		
	private:// private Class varriables
			int size;	
			float **matrix;	
			float *Distances;
			bool distances_calculated;
			float probability;
			float min_cost;
			float max_cost;
		
	//public functions
	//////*********************************************************************************//////
	public: void print()  //use to print the graph
	{
		for(int i=0;i<size;i++)
		{
			for(int j=0;j<size;j++)
			{
				cout <<"   " << matrix[i][j];
			}
			cout << endl;
		}
	}
	
	public: void print_distance_table() // use to print the update distance table
	{
		if(distances_calculated)
		{
			for(int i=0;i< size;i++)
			{
				if(Distances[i]<1000.0)
					cout <<"Shortest distance to "<< i<<"): "<< Distances[i]<<endl<<endl;
				else
					cout <<"No path leading to node"<< " ("<< i << ") " <<endl<<endl;
			}
				
			cout<< endl<<endl;
		}
		else
			cout<< "No distance was calculated yet! Use function Shortest_path() first."<<endl<<endl;
	}
	
	
	public: void Shortest_path() //Use to calculate the shortest path between nodes using Dijkstra's algorithm
	{							
		bool Reached[size]; //init reached, not reached arrays
		for(int i=0;i<size;i++)
			Reached[i] = false;
		Reached[0] = true;
		
		Distances= new float[size];//init Distances as very large
		for(int i=0;i<size;i++)
			Distances[i] = 1000.0;
		Distances[0] = 0.0;
		
		int min=0;
		for(int i=1;i<size;i++) // for all elements 
		{
			if(matrix[0][i]>0) // if is a neighbour
			{
				Distances[i]=matrix[0][i]; // create distance table for neighbours of 0
				if(Distances[i]<Distances[min])
					min = i;
			}
		}
		Reached[min] = true;//set the min node from initialisation as Reached
		
		
		
		for(int i=1;i<size;i++) // for all elements of Reached nodes
		{
				
			if( Reached[i] == false) //if an unreached node exists ----> search for a minimum value in Distances from it
			{
				min = i; //init value of first unreached node for min
				
				for( int k =0; k < size ; k++ ) // search for smallest value in Distances table in all elements
				{
					
					if(Reached[k]== false && Distances[k]<Distances[min] ) // if the node is yet unreached and its distance is less than min
					{																
						
						min = k;// set new min index
			
					}
					
				}
				Reached[min] = true; // the smallest dist value is now Reached
				
				for(int k = 0;k<size;k++)//search for neighbours of min
				{
					if(Reached[k] == false && matrix[min][k]>0 )  //if it is a neighbour and it is unreached 
					{
						if(Distances[k]> Distances[min]+matrix[min][k]) //if its value is smaller than node's value + edge
						{
							Distances[k] = Distances[min]+matrix[min][k]; //update new Distance as node's value + edge
						}
					}
				}	
			}			
		}
		
		distances_calculated = 1; // Update the status of the distances as calculated
		
	}
	
	
		
		
	//private functions	
	//////*********************************************************************************//////	
	
	private: void init() // Initialises the graph 
	{
		srand(time(0));// seed random numbers
		
		distances_calculated = 0; //init distances as uncalculated
		
		matrix = new float*[size]; //create graph dynamically
		for(int i=0;i<size;i++)
			matrix[i] = new float[size];
		
		
		for(int i=0;i<size;i++) // generate a graph with given probability
		{
			for(int j=i;j<size;j++)
			{
				if( RandomGenerator(1.0)<=probability && i!=j)
				{
					float cost = RandomGenerator(max_cost,min_cost);
					//float cost = j;
					matrix[i][j] = cost;
					matrix[j][i] = cost;
				}
				else 
				{
					matrix[i][j] = 0;
					matrix[j][i] = 0;
				}
			}
		}

	}	
	
	private: float RandomGenerator(float max = 1.0, float offset = 0.0) //generate random positive float from offset
	{
		return offset+ static_cast <float> (rand()/(static_cast<float>( RAND_MAX/(max-offset))));
	}
	
	
};
		





int main(void) {
	 
	
	graph g1(N,0.1);
//	g1.print(); // use to print small graphs
	g1.Shortest_path();
	g1.print_distance_table();


}




