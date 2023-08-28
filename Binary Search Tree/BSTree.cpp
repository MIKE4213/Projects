#include "BSTree.h"
#include <queue>
#include <math.h>

#include <iostream>

using namespace std;

///////////////////////////////////
// Already Implemented Functions //
///////////////////////////////////

// These functions are already implemented for you. Scroll below to
// see the functions that you have to implement 


// constructors
BSTree::BSTree() : size(0), root(nullptr) {}

// input / output operators
ostream& operator<<(ostream& out, BSTree& tree)
{
    tree.print_level_by_level(out);
    return out;
}

ostream& operator<<(ostream& out, Node& node)
{
    return out << node.value << "[" << node.search_time << "]";
}

istream& operator>>(istream& in, BSTree& tree)
{
    /*
      take input from the in stream, and build your tree
      input will look like
      4 
      2 
      6 
      1 
      3 
      5 
      7
    */
    int next;
    while(in >> next) {
        tree.insert(next);
    }
    return in;
}

// Example recursive function
// If you try to use it without care, you will get a memory leak.
void BSTree::copy_helper(Node*& newNode, const Node* sourceNode) {
    //Don't copy if the node is nullptr
    if(sourceNode == nullptr)
        return;

    //Change the new node to a copy of sourceNode
    newNode = new Node(sourceNode->value);
    //Copy over the search cost
    newNode->search_time = sourceNode->search_time;

    //Copy left subtree
    if (sourceNode->left != nullptr)
        copy_helper(newNode->left, sourceNode->left);
    //Copy right subtree
    if(sourceNode->right != nullptr)
        copy_helper(newNode->right, sourceNode->right);
}

// recursive function
int BSTree::get_total_search_time(Node* node)
{
  if (node != nullptr) {
    return node->search_time + get_total_search_time(node->left) + get_total_search_time(node->right);
  }
  return 0;
}

// implemented
float BSTree::get_average_search_time()
{
  int total_search_time = get_total_search_time(root);
  if(total_search_time == 0)
    return -1;
	
  return ((float)total_search_time)/size;
}


///////////////////////////////////
//     Functions to Implement    //
///////////////////////////////////

// These are the functions you should implement
// Feel free to call the functions above or create new helper functions

// copy constructor
BSTree::BSTree(const BSTree& other){
  if(other.root==nullptr){
    this->root=nullptr;
    this->size=0;
  }
  else{
   copy_helper(this->root,other.root);
   this->size=other.size;
  }
}

// move constructor
BSTree::BSTree(BSTree&& other)
{
  if(other.root==nullptr){
    root=nullptr;
    size=0;
  }
  else{
  this->root=other.root;
  this->size=other.size;
  other.root=nullptr;
  other.size=0;
  }
}

//copy assignment
BSTree& BSTree::operator=(const BSTree& other)
{
  if(this != &other){
  make_empty(this->root);
  size=0;
  if(other.root==nullptr){
    this->root=nullptr;
    this->size=0;
  }
  else{
   copy_helper(this->root, other.root);
   this->size=other.size;
   }
  }

  return *this;
}

// move assignment
BSTree& BSTree::operator=(BSTree&& other)
{
  if(this != &other){
    make_empty(root);
    if(other.root==nullptr){
    root=nullptr;
    size=0;
  }
  else{
  this->root=other.root;
  this->size=other.size;
  other.root=nullptr;
  other.size=0;
   }
  }
  return *this;
}

// destructor
BSTree::~BSTree()
{
   make_empty(root);
    // Make sure to call delete on every node of the tree
    // You can use a recursive helper function to do this
}

Node* BSTree::insert(int obj)
{
    root = insert_helper(obj, root, 1);
    /* insert a node into the tree
    first find where the node should go
    then modify pointers to connect your new node */
    return search(obj);
}

Node* BSTree::insert_helper(int num, Node* up, int st){
  if(up == nullptr){
    up = new Node(num);
    up->search_time=st;
    if(size==0){
    root = up;
    }
    size++;
    return up;
  }
  
  else if(num < up->value){
    st++;
    up->left=insert_helper(num, up->left, st);
  }

  else if(num > up->value){
    st++;
    up->right=insert_helper(num, up->right, st);
  }

  return up;

}

Node* BSTree::search(int obj)
{
    /* recursively search down the tree to find the node that contains obj
    if you don't find anything return nullptr */
    return search_helper(obj, root);
}

Node* BSTree::search_helper(int num, Node* up){
  if(up == nullptr){
     return nullptr;
  }
  else if(num<up->value){
    up=search_helper(num,up->left);
  }
  else if(num>up->value){
    up=search_helper(num,up->right);
  }
  return up;
}

void BSTree::update_search_times()
{
    /* do a BFS or DFS of your tree and update the search times of all nodes at once
      The root has a search time of 1, and each child is 1 more than its parent */
      update_helper(1, root);
}

void BSTree::update_helper(int num, Node* up){
   if(up==nullptr){
        return;
      }
      update_helper(num+1 , up->left);
      up->search_time=num;
      update_helper(num+1, up->right);
}

void BSTree::inorder(ostream& out)
{
    /* print your nodes in infix order
    If our tree looks like this:

       4
     2   6
    1 3 5 7

    It should output:
    1[3] 2[2] 3[3] 4[1] 5[3] 6[2] 7[3]
    You can use the << operator to print the nodes in the format shown */
    inorder_helper(out, root);
}

void BSTree::inorder_helper(std::ostream& out, Node* up){
  if(up==nullptr){
    return;
  }
  inorder_helper(out, up->left);
  out << up->value << "[" << up->search_time << "]";
  inorder_helper(out, up->right); 
    
}

void BSTree::print_level_by_level(ostream& out){
    /* Print the tree using a BFS so that each level contains the values for a level of the tree.
    Use X to mark empty positions. 
    
      if our tree looks like this:

       4
     2   6
    1   5 7
           9

    it should output:

    4[1]
    2[2] 6[2]
    1[3] X 5[3] 7[3]
    X X X X X X X 9[4]

    it might be helpful to do this part with the std::queue data structure.
    Hint: the Nth level contains 2^(N-1) nodes (with a value or with an X). Watch out
    for nodes like the left child of 6 above, and print the descendents of an empty
    node as also empty
    You can use the << operator to print nodes in the format shown */
  Node* r = root;
  Node* temp = nullptr;
  queue<Node*> queue;
  Node* PX = nullptr;
  int s=0;
  int level=0;
  int power=0;
  queue.push(r);
  while (!queue.empty()){
    temp=queue.front();
    queue.pop();
    if(temp==nullptr){
      level++;
      out<< "X" ;
      queue.push(PX);
      queue.push(PX);
    }
   if(temp!=nullptr){
      out << temp->value <<"[" << temp->search_time << "] ";
      queue.push(temp->left);
      queue.push(temp->right);
      level++;
      s++;
    }
   if((level==pow(2,power)) && (s==size)){
      out<<endl;
      return;
   }
    if(level==pow(2,power)){
    out<<endl;
    level=0;
    power++;
    }
  }

}

void BSTree::make_empty(Node* erase){
  if(erase == nullptr){
    return;
  }
  if(erase->left != nullptr){
    make_empty(erase->left);
  }
  if(erase->right != nullptr){
    make_empty(erase->right);
  }
  delete erase;
  erase = nullptr;
}

