// 250201009 SelahattinCeylan ------ 250201042 FurkanŞahin
#include<iostream> 
#include <list> 
#include <vector> 
#include <map> 
#include <sstream>
#include <string.h>
#include <ctype.h>
#include <algorithm>
using namespace std; 

// A directed graph using adjacency list representation 
class Graph 
{ 
    int V; // # of vertices in graph 
    list<int> *adj; // Pointer to an array containing adjacency lists 
    vector<vector<int>> pathList; // holds paths for given src to dest
    vector<vector<int>> pathWithCost; // holds all paths with their weights

  
    // A recursive function used by findAllPaths() 
    void findAllPathsUtil(int , int , bool [], int [], int &); 
  
public: 
    Graph(int V); // Constructor 
    void addEdge(int u, int v,int weight); 
    void findAllPaths(int s, int d); 
    void calculateCost(vector<int> path);
    void printMinCost();
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<int>[26];
} 
  
void Graph::addEdge(int u, int v, int weight) 
{ 
    adj[u].push_back(v); // Add v to u’s list.
    pathList.push_back({u,v,weight}); //Add u,v,weight to pathList which holds all paths with their weight like that (a,c,5) (c,d,13) (b,a,2) etc
} 
  
// Finds all paths from 's' to 'd' 
void Graph::findAllPaths(int s, int d) 
{ 
    // Mark all the vertices as not visited
    bool *visited = new bool[V]; 
  
    // Create array to hold paths 
    int *path = new int[V]; 
    int path_index = 0; // Initialize path[] as empty 
  
    // assign all vertices as not visited 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
  
    //recursive function to find all paths 
    findAllPathsUtil(s, d, visited, path, path_index); 
} 


  
// Find all paths from s to d
void Graph::findAllPathsUtil(int s, int d, bool visited[], 
                            int path[], int &path_index) 
{ 

    static const char * const alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    visited[s] = true; //keeps track of vertices in current path. 
    path[path_index] = s; // holds actual vertices, path_index is current 
    vector<int> p; // holds path as a int vector
    path_index++; 
  
    // If src = destination, calculate cost
    if (s == d) 
    { 
        for (int i = 0; i<path_index; i++)
        {
            cout<<alphabet[path[i]]<<" ";
            p.push_back(path[i]); // add path elements to p
        }

        calculateCost(p);
        cout << endl; 
          
    } 
    else 
    { 
        // Continue for vertices which is adjacent to current vertex 
        list<int>::iterator i; 
        for (i = adj[s].begin(); i != adj[s].end(); ++i) 
            if (!visited[*i]) 
                findAllPathsUtil(*i, d, visited, path, path_index); 
    } 
  
    // Remove current vertex from path[],make it unvisited 
    path_index--; 
    visited[s] = false; 
} 


//Traveling given path from printAllPathsUtil (example : a to d =  a c d) and according to pathLists paths calculates cost. 
// Example: given path a d c - pathList contains all paths with their cost like that (a,d,3) (d,c,2) - cost = 3+2 = 5 
void Graph::calculateCost(vector<int> path)
{   
    int cost = 0;
    for (int i = 0; i<path.size()-1; i++)
    {
        for(int j=0;j<pathList.size();j++)
        {
            if(path[i]==pathList.at(j).at(0) && path[i+1]==pathList.at(j).at(1))
            {   
                cost = cost + pathList.at(j).at(2);
            }
        }
    }
    cout<<" Cost : "<<cost;
    path.push_back(cost);
    pathWithCost.push_back(path);
    
}

//Traveling pathWithCost list (example : a to d =  a c d ,cost 3) and find the minimum cost for the given input line.
void Graph::printMinCost()
{
    int minIndex = 0;
    int min = pathWithCost.at(0).back();

    for (int i=0;i<pathWithCost.size();i++)
    {
        if( pathWithCost.at(i).back() < min)
        {
            min =   pathWithCost.at(i).back();
            minIndex = i;
        }
    }
    
    std::cout << pathWithCost.at(minIndex).back() << ' ';

}


//Transform letter to int according to alphabetical order
int c_to_n(char c)
{
    int n = -1;
    static const char * const alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *p = strchr(alphabet, toupper((unsigned char)c));

    if (p)
    {
        n = p - alphabet;
    }

    return n;
}

//print the paths and minimum cost of given src to dest
void print(Graph g, int s, int d)
{
    static const char * const alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    cout<<"\n";
    cout << "Paths " << alphabet[s]
        << " to " << alphabet[d] << ": \n";
    g.findAllPaths(s, d);

    cout << "Minimum cost of " << alphabet[s]
        << " to " << alphabet[d] << ": ";
    g.printMinCost();
    cout<<"\n";
}


//Remove duplicates in givenLetters
void removex(std::vector<char> &v)
{
	auto end = v.end();
	for (auto it = v.begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}

	v.erase(end, v.end());
}



// Driver program 
int main() 
{ 
    int V;
    cout << "Please enter an integer value: ";
    cin >> V;
    Graph g(V); 
    vector<char> givenLetters;
    
    for(int i=0;i<V;i++)
    {
        string input;
        cout << "Please enter as a,b,1,c,2 \n";
        cin >> input;

        //get a vector of elements of given input 
        stringstream ss(input);
        vector<string> result;
        while( ss.good() )
        {
            string substr;
            getline( ss, substr, ',' );
            result.push_back( substr );
        }
        
        //givenLetters holds the letters in input. I add first letter of input to givenLetters.
        givenLetters.push_back(result.at(0).at(0)); 
        

        // Create graph edges in that format addEdge(a,b,5) => addEdge(0,1,5), addEdge(x,c,2) => addEdge(23,2,2) 
        int j = 1;
        while(j<result.size())
        {   
            /*
            example :
            input : x,e,12,r,3

            x:0 - src
            e:j=1 - dest
            12:j=2 = k - weight
            addEdge(x,e,12) with alphabetical order => addEdge(23,4,12)

            r:j=3  - dest
            3:j=4 = k -weiht
            addEdge(x,r,3) with alphabetical order => addEdge(23,17,3)

            */
            int k;
            std::istringstream(result.at(j+1)) >> k; // get weight

            g.addEdge(c_to_n(result.at(0).at(0)),c_to_n(result.at(j).at(0)),k); //addEdge(int(input[0]),int(input[j]),int(input[j+1]))

            givenLetters.push_back(result.at(j).at(0));//I add letter of input to givenLetters
            j = j+2;
        }
        
        
    }
    removex(givenLetters);
   
   for(int c = 1; c<givenLetters.size();c++)
   {
    int s = c_to_n(givenLetters.at(0)), d= c_to_n(givenLetters.at(c));
    print(g,s,d);
   }
  
    
    return 0; 
} 
  
