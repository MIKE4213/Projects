#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>

struct Node
{
  int value;
  Node* left;
  Node* right;
  int search_time; //see the problem description

  // Node constructor
  Node(int val = 0, Node* l = nullptr, Node* r = nullptr)
    : value(val), left(l), right(r), search_time(0) {}
};

struct BSTree
{
public:
  BSTree();
  BSTree(const BSTree& other);
  // move constructor
  BSTree(BSTree&& other);
  // copy assignment
  BSTree& operator=(const BSTree& other);
  // move assignment
  BSTree& operator=(BSTree&& other);
  ~BSTree();

  inline const Node* get_root() const { return root; }
  inline const int get_size() const { return size; }
  Node* insert(int obj);
  Node* search(int obj);
  void update_search_times();
  float get_average_search_time();
  void inorder(std::ostream& out);
  void print_level_by_level(std::ostream& out);

private:
  int size;
  Node* root;

  int get_total_search_time(Node* node);
  // you can add recursive helper functions to help you
  // this is one is implemented for you:
  void copy_helper(Node*& newNode, const Node* sourceNode);
  void make_empty(Node*);
  Node* insert_helper(int num, Node* up, int st);
  Node* search_helper(int num, Node* up);
  void inorder_helper(std::ostream& out, Node* up);
  void update_helper(int num, Node* up);
};

// print a node
std::ostream& operator<<(std::ostream& out, Node& node);

// print a BSTree
std::ostream& operator<<(std::ostream& out, BSTree& tree);

// read in a tree from a file
std::istream& operator>>(std::istream& in, BSTree& tree);


#endif
