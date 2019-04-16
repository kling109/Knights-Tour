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
#include "tree.h"

class KnightTour
{
  /*

  */
  private:
    GenericTree<std::vector<int>*>* paths;
    int depth;
    int boardSize;
    bool contains(std::vector<Node<std::vector<int>*>*>* source, std::vector<int>* elem);
    Node<std::vector<int>*>* bruteSearch(Node<std::vector<int>*>* currLoc, int currDepth);
    Node<std::vector<int>*>* heurSearch(Node<std::vector<int>*>* currLoc, int currDepth);
    void addChildren(Node<std::vector<int>*>* currentLoc);
    void addSortedChildren(Node<std::vector<int>*>* currentLoc);
  public:
    KnightTour(int x, int y, int n);
    ~KnightTour();
    void runBrute();
    void runHeur();
};
