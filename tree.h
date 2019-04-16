/*
Name: Trevor Kling
ID: 002270716
Email: kling109@mail.chapman.edu
Course: CPSC 406 Algorithm Analysis
Last Date Modified: 11 April 2019
Project: Knight's Tour Implementations
*/

#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class Node
{
  /*

  */
  private:
    T data;
    Node* parent;
    vector<Node*>* children;
  public:
    Node(T newData);
    ~Node();
    T getData();
    void setParent(Node* par);
    Node* getParent();
    void addChild(Node* child);
    vector<Node*>* getChildren();
};

template <typename T>
class GenericTree
{
  /*

  */
  private:
    Node<T>* root;
    Node<T>* searchHelper(Node<T>* toSearch, T toFind);
    void printHelper(Node<T>* toSearch);
  public:
    GenericTree(T rootKey);
    ~GenericTree();
    Node<T>* getRoot();
    void insert(T key, Node<T>* location);
    Node<T>* search(T key);
    vector<Node<T>*>* trace(Node<T>* endNode);
    void remove(T key);
    void printTree();
};

/*

*/
template<typename T>
Node<T>::Node(T newData)
{
  this->data = newData;
  this->parent = NULL;
  this->children = new vector<Node<T>*>();
}

/*

*/
template<typename T>
Node<T>::~Node()
{
  this->parent = NULL;
  this->children = NULL;
}

/*

*/
template<typename T>
T Node<T>::getData()
{
  return this->data;
}

/*

*/
template<typename T>
void Node<T>::setParent(Node<T>* par)
{
  this->parent = par;
}

/*

*/
template<typename T>
Node<T>* Node<T>::getParent()
{
  return this->parent;
}

/*

*/
template<typename T>
void Node<T>::addChild(Node<T>* child)
{
  child->parent = this;
  this->children->push_back(child);
}

/*

*/
template<typename T>
vector<Node<T>*>* Node<T>::getChildren()
{
  return this->children;
}

/*

*/
template<typename T>
GenericTree<T>::GenericTree(T rootKey)
{
  this->root = new Node<T>(rootKey);
}

/*

*/
template<typename T>
GenericTree<T>::~GenericTree()
{
  this->root->~Node();
}

/*

*/
template<typename T>
Node<T>* GenericTree<T>::getRoot()
{
  return this->root;
}

/*

*/
template<typename T>
void GenericTree<T>::insert(T key, Node<T>* location)
{
  Node<T>* newNode = new Node<T>(key);
  location->addChild(newNode);
}

/*

*/
template<typename T>
Node<T>* GenericTree<T>::searchHelper(Node<T>* toSearch, T toFind)
{
  if (toSearch->getData() == toFind)
  {
    return toSearch;
  }
  if (toSearch->getChildren()->size() == 0)
  {
    return NULL;
  }
  for (int i = 0; i < toSearch->getChildren()->size(); ++i)
  {
    Node<T>* foundNode = searchHelper(toSearch->getChildren()->at(i), toFind);
    if (foundNode != NULL)
    {
      return foundNode;
    }
  }
}

/*

*/
template<typename T>
Node<T>* GenericTree<T>::search(T key)
{
  return searchHelper(this->root, key);
}

/*

*/
template<typename T>
vector<Node<T>*>* GenericTree<T>::trace(Node<T>* endNode)
{
  Node<T>* currNode= endNode;
  vector<Node<T>*>* path = new vector<Node<T>*>();
  while (currNode != this->root)
  {
    path->push_back(currNode);
    currNode = currNode->getParent();
  }
  path->push_back(currNode);
  return path;
}

/*

*/
template<typename T>
void GenericTree<T>::remove(T key)
{
  Node<T>* toRemove = search(key);
  Node<T>* par = toRemove->getParent();
  vector<Node<T>*>* childs = toRemove->getChildren();
  for (int i = 0; i < childs->size(); ++i)
  {
    Node<T>* currChild = childs->at(i);
    currChild->setParent(par);
    par->addChild(currChild);
    childs->at(i) = NULL;
  }
  vector<Node<T>*>* parChild = par->getChildren();
  for (int i = 0; i < parChild->size(); ++i)
  {
    if (parChild->at(i) == toRemove)
    {
      parChild->erase(parChild->begin() + i);
    }
  }
  toRemove->~Node();
}

/*

*/
template<typename T>
void GenericTree<T>::printHelper(Node<T>* toSearch)
{
  cout << "Node Data: " << toSearch->getData() << endl;
  cout << "Node Parent Data: " << toSearch->getParent()->getData() << endl;
  cout << "Number of Children: " << toSearch->getChildren()->size() << endl;
  cout << "----" << endl;
  for (int i = 0; i < toSearch->getChildren()->size(); ++i)
  {
    printHelper(toSearch->getChildren()->at(i));
  }
}

/*

*/
template<typename T>
void GenericTree<T>::printTree()
{
  cout << "Node Data: " << this->root->getData() << endl;
  cout << "Node Parent Data: N/A for root"<< endl;
  cout << "Number of Children: " << this->root->getChildren()->size() << endl;
  cout << "----" << endl;
  for (int i = 0; i < this->root->getChildren()->size(); ++i)
  {
    printHelper(this->root->getChildren()->at(i));
  }
}
