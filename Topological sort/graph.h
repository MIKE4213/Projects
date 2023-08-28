#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <list>
#include <queue>
#include <sstream>
#include <fstream>

using namespace std;

//edits to this are likely not needed
template <class T>
struct Vertex {
  T label; // unique int for a vertex
  vector<T> adj_list;
  int indegree; // Part 2: number of nodes pointing in
  int top_num; // Part 2: topological sorting number
  Vertex(T l) : label(l) {top_num = 0;} //Part 1
  Vertex(){};
  // You may include default constructor optionally.
};

// optional, but probably helpful
// template <class T>
// ostream& operator<<(ostream &o, Vertex<T> v){};

// std::priority_queue may take takes three template parameters: <Type, ContainerType, Functor>
// syntax for custom compare functor follows
// Refer the instructions PDF last section for more information

template<class T>
 class VertexCompare{
 public:
   bool operator()(Vertex<T> v1, Vertex<T> v2){
     //todo - implement here
     if(v1.top_num > v2.top_num){
			return true;
		}
     return false;
   }
 };

template <class T>
class Graph {
private:
  //c++ stl hash table
  std::unordered_map<T, Vertex<T> > node_set;

  // alternatively:
  //c++ balanced binary tree (probably red-black but may be compiler dependent)
  //std::map<T, Vertex<T> > node_set;
  //  using this may negatively impact your runtime

  //Use other data fields if needed
public:
  Graph() {};  //No modification needed to default constructor. Can be used optionally if needed.
  ~Graph() {}; //No modification needed to destructor. Can be used optionally if needed.

  // build a graph - refer the instructions PDF for more information.
  void buildGraph(istream &input){
    T data;
		T l1;
		string line;
		while(getline(input, line)){
			stringstream ss (line);
			ss >> l1;
			Vertex<T> v = Vertex<T>(l1);
			node_set.insert(std::make_pair(l1 , v));
			while (ss>>data){
				node_set[l1].adj_list.push_back(data);
			}		
		}
  }

  // display the graph into o - refer the instructions PDF for more information.
  void displayGraph(ostream& o){
    for(auto& element: node_set) {
			o << element.first << ": ";
			for (auto i = 0; i < element.second.adj_list.size(); i++){
				o << element.second.adj_list[i] << " ";
			}
			o << std::endl;
		}
  }

  //return the vertex at label, else throw any exception  - refer the instructions PDF for more information.
  Vertex<T> at(T label){
    return node_set.at(label);
  }

  //return the graph size (number of verticies)
  int size(void){
    return node_set.size();
  }

  // topological sort
  // return true if successful, false on failure (cycle)
  bool topological_sort(void){
    priority_queue <  T , vector <T> , VertexCompare <T> > pq ;
			int count = 0;

			for(auto& element: node_set) {
				if (element.second.indegree == 0){
					pq.push(element.first);
				}
			}
			
			while(pq.size() != 0){
				Vertex<T> v = node_set.at(pq.top());
				v.top_num = ++count;
				node_set.at(pq.top()) = v;
				pq.pop();
				queue<T> q;	
				for(auto& element: node_set) {
					if(element.second.label == v.label){
						for(auto i = 0; i < element.second.adj_list.size(); i++){
							q.push(element.second.adj_list[i]);
						}
					}
				}
				while(q.size() != 0){
					T d1 = q.front();
					for(auto& element: node_set) {
						if(element.second.label == d1){
							if (--element.second.indegree == 0){
								pq.push(element.first);
							}
						}
					}
				q.pop();
			}
		}	
			if (count != size()){
				return false;
			}
			else{
				return true;
			}
  } // Part 2

  // find indegree
  void compute_indegree(void){
   queue<T> q;
		for(auto& element: node_set) {
			element.second.indegree = 0;
			for(auto i = 0; i < element.second.adj_list.size(); i++){
				q.push(element.second.adj_list[i]);
			}
		}	
		while (!q.size() == 0){
			T d2 = q.front();
				
			for(auto& element: node_set) {
				if(element.second.label == d2){
					element.second.indegree ++;
				}
			}
			q.pop();
		}
  } // Part 2


  // print topological sort into o
  //  if addNewline is true insert newline into stream
  void print_top_sort(ostream& o, bool addNewline=true){ 
    //TODO - implement things herefor(auto& element: node_set) {
     priority_queue<Vertex<T>, vector<Vertex<T>>, VertexCompare<T>> q;
        for (auto i = node_set.begin(); i != node_set.end(); i++) {
            q.push(i->second);
        }
        while (!q.empty()) {
            o << q.top().label << " ";
            q.pop();
        }
    if(addNewline){
     o << '\n';
    };
  } // Part 2
};

#endif
