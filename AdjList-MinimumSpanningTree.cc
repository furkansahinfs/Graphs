#include<bits/stdc++.h> 
using namespace std; 
  
// Creating an integer pair 
typedef  pair<int, int> intPair; 

// A graph with adjList
class Graph 
{ 
    int V,E; // # of vertices and edges in graph 
    vector< pair<int, intPair> > edges; // holds edges 

public: 
    Graph(int V,int E); // Constructor 
    void addEdge(int u, int v, int w);
    int minSpanTree();  // find minimum spanning tree
    
}; 


// Constructor 
Graph::Graph(int V, int E) 
{ 
    this->V = 26;
    this->E = E; 
} 

// add an edge 
void Graph::addEdge(int u, int v, int w) 
{ 
    edges.push_back({w, {u, v}}); 
} 

  
// To represent Disjoint Sets 
struct Disjoint 
{ 
    int *parent, *rank; 
    int n; 
  
    // Constructor. 
    Disjoint(int n) 
    { 
        this->n = n; 
        rank = new int[n+1]; 
        parent = new int[n+1]; 
        
  
        //Set initial values of rank and parent
        for (int i = 0; i <= n; i++) 
        { 
            rank[i] = 0; 
  
            //parent element equals itself
            parent[i] = i; 
        } 
    } 
  
    // Merge two value
    void mergeTwo(int a, int b) 
    { 
        a = findParent(a), b = findParent(b); 
  
        //Make tree with smaller height
        
        if (rank[a] < rank[b])
        {
            parent[a] = b; 
           
        }   
        else
        {
            parent[b] = a; 
        }
  
        if (rank[a] == rank[b]) 
        {
            rank[b]++; 
        }
    }

    // Find parent of a node
    int findParent(int u) 
    { 
        if (u != parent[u]) 
        {
            parent[u] = findParent(parent[u]); 
        }
        return parent[u]; 
    }  
}; 
  
 
  
int Graph::minSpanTree() 
{ 
    static const char * const alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int weight = 0;
    Disjoint ds(V);

    // Sort edges as increasing
    sort(edges.begin(), edges.end()); 
 
  
    // Iterate all edges 
    vector< pair<int, intPair> >::iterator it;

    for (it=edges.begin(); it!=edges.end(); it++) 
    { 
        int u = it->second.first; 
        int v = it->second.second; 
  
        int set_u = ds.findParent(u); 
        int set_v = ds.findParent(v); 
  
        // Check that chosen edge occurs a cycle 
        if (set_u != set_v) 
        { 
            cout << alphabet[u] << " - " << alphabet[v] << endl; 
            weight += it->first; 
  
            // Merge two sets 
            ds.mergeTwo(set_u, set_v); 
        } 
    } 
  
    return weight; 
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
  


int main() 
{ 
    int V;
    cout << "Please enter an integer value: ";
    cin >> V; 
    vector<vector<int>> givenEdges; // holds all edges to declare int E
    
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
            vector<int> edge;
            edge.push_back(c_to_n(result.at(0).at(0)));
            edge.push_back(c_to_n(result.at(j).at(0)));
            edge.push_back(k);
            givenEdges.push_back(edge); // push edge to givenEdges vector.

            j = j+2;
        }
        
        
    }
    int E = givenEdges.size();
    Graph g(V, E); // Create graph
  
    for(int i=0;i<E;i++)
    {
        g.addEdge(givenEdges.at(i).at(0),givenEdges.at(i).at(1),givenEdges.at(i).at(2)); // add edges which are in the givenEdges vector
    }
  
    cout << "\nMinimum Spanning Tree Edges \n"; 
    int weight = g.minSpanTree(); 
  
    cout << "\nWeight: " << weight; 
    
    return 0; 
} 
