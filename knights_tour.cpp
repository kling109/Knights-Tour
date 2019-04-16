/*
Name: Trevor Kling
ID: 002270716
Email: kling109@mail.chapman.edu
Course: CPSC 406 Algorithm Analysis
Last Date Modified: 11 April 2019
Project: Knight's Tour Implementations
*/

#include <iostream>
#include <chrono>
#include "knights_tour.h"

using namespace std;

/*

*/
KnightTour::KnightTour(int x, int y, int n)
{
  this->boardSize = n;
  vector<int>* start = new vector<int>();
  start->push_back(x-1);
  start->push_back(y-1);
  this->paths = new GenericTree<vector<int>*>(start);
 }

KnightTour::~KnightTour()
{
 paths->~GenericTree();
}

/*

*/
bool KnightTour::contains(vector<Node<vector<int>*>*>* source, vector<int>* elem)
{
  if (source == NULL || elem == NULL || elem->size() < 2)
  {
    cout << "Source for conainment or element does not exist." << endl;
    return false;
  }
  for (int i = 0; i < source->size(); ++i)
  {
    if (source->at(i)->getData() == NULL || source->at(i)->getData()->size() < 2)
    {
      cout << "The source vector was not completely filled." << endl;
      return false;
    }
    if (source->at(i)->getData()->at(0) == elem->at(0) && source->at(i)->getData()->at(1) == elem->at(1))
    {
      return true;
    }
  }
  return false;
}

/*

*/
void KnightTour::addChildren(Node<vector<int>*>* currLoc)
{
  if (currLoc->getData()->size() < 2)
  {
    cout << "The given node does not contain the necessary data." << endl;
    return;
  }
  int x = currLoc->getData()->at(0);
  int y = currLoc->getData()->at(1);
  vector<Node<vector<int>*>*>* visited = this->paths->trace(currLoc);
  if (x+2 < this->boardSize)
  {
    if (y+1 < this->boardSize)
    {
      vector<int>* newSquare = new vector<int>();
      newSquare->push_back(x+2);
      newSquare->push_back(y+1);
      if (!contains(visited, newSquare))
      {
        this->paths->insert(newSquare, currLoc);
      }
    }
    if (y-1 >= 0)
    {
      vector<int>* newSquare = new vector<int>();
      newSquare->push_back(x+2);
      newSquare->push_back(y-1);
      if (!contains(visited, newSquare))
      {
        this->paths->insert(newSquare, currLoc);
      }
    }
  }
  if (x-2 >= 0)
  {
    if (y+1 < this->boardSize)
    {
      vector<int>* newSquare = new vector<int>();
      newSquare->push_back(x-2);
      newSquare->push_back(y+1);
      if (!contains(visited, newSquare))
      {
        this->paths->insert(newSquare, currLoc);
      }
    }
    if (y-1 >= 0)
    {
      vector<int>* newSquare = new vector<int>();
      newSquare->push_back(x-2);
      newSquare->push_back(y-1);
      if (!contains(visited, newSquare))
      {
        this->paths->insert(newSquare, currLoc);
      }
    }
  }
  if (x+1 < this->boardSize)
  {
    if (y+2 < this->boardSize)
    {
      vector<int>* newSquare = new vector<int>();
      newSquare->push_back(x+1);
      newSquare->push_back(y+2);
      if (!contains(visited, newSquare))
      {
        this->paths->insert(newSquare, currLoc);
      }
    }
    if (y-2 >= 0)
    {
      vector<int>* newSquare = new vector<int>();
      newSquare->push_back(x+1);
      newSquare->push_back(y-2);
      if (!contains(visited, newSquare))
      {
        this->paths->insert(newSquare, currLoc);
      }
    }
  }
  if (x-1 >= 0)
  {
    if (y+2 < this->boardSize)
    {
      vector<int>* newSquare = new vector<int>();
      newSquare->push_back(x-1);
      newSquare->push_back(y+2);
      if (!contains(visited, newSquare))
      {
        this->paths->insert(newSquare, currLoc);
      }
    }
    if (y-2 >= 0)
    {
      vector<int>* newSquare = new vector<int>();
      newSquare->push_back(x-1);
      newSquare->push_back(y-2);
      if (!contains(visited, newSquare))
      {
        this->paths->insert(newSquare, currLoc);
      }
    }
  }
}

/*

*/
Node<vector<int>*>* KnightTour::bruteSearch(Node<vector<int>*>* currLoc, int currDepth)
{
  if (currLoc == NULL)
  {
    cout << "No node was given." << endl;
    return NULL;
  }
  int newDepth = currDepth + 1;
  addChildren(currLoc);
  if (newDepth == this->depth)
  {
    return currLoc;
  }
  else if (currLoc->getChildren()->size() == 0)
  {
    return NULL;
  }
  else
  {
    for (int i = 0; i < currLoc->getChildren()->size(); ++i)
    {
      Node<vector<int>*>* point = bruteSearch(currLoc->getChildren()->at(i), newDepth);
      if (point != NULL)
      {
        return point;
      }
    }
    return NULL;
  }
}

/*

*/
void KnightTour::runBrute()
{
  this->depth = this->boardSize * this->boardSize;
  Node<vector<int>*>* pathFound = bruteSearch(this->paths->getRoot(), 0);
  if (pathFound == NULL)
  {
    cout << "There is no way to cover the full board from that starting position." << endl;
  }
  else
  {
    cout << "A way to traverse the board was found!" << endl;
    cout << "Take the following path (board positions are indicated as [x,y] where x,y are between 1 and n): " << endl;
    vector<Node<vector<int>*>*>* moves = this->paths->trace(pathFound);
    cout << "The knight begins at [" << moves->at((moves->size()-1))->getData()->at(0)+1 << ", " << moves->at((moves->size()-1))->getData()->at(1)+1 << "]" << endl;
    for (int i = 0; i < moves->size()-1; ++i)
    {
      cout << "Move knight to [" << moves->at((moves->size()-2) - i)->getData()->at(0)+1 << ", " << moves->at((moves->size()-2) - i)->getData()->at(1)+1 << "]" << endl;
    }
  }
}

/*

*/
Node<vector<int>*>* KnightTour::heurSearch(Node<vector<int>*>* currLoc, int currDepth)
{
  if (currLoc == NULL)
  {
    cout << "No node was given." << endl;
    return NULL;
  }
  int newDepth = currDepth + 1;
  if (newDepth == this->depth)
  {
    return currLoc;
  }
  else if (currLoc->getChildren()->size() == 0)
  {
    return NULL;
  }
  else
  {
    vector<Node<vector<int>*>*>* children = currLoc->getChildren();
    for (int i = 0; i < children->size(); ++i)
    {
      addChildren(children->at(i));
    }
    for (int i = 0; i < children->size()-1; ++i)
    {
      for (int j = 0; j < children->size() - i - 1; ++j)
      {
        if (children->at(j)->getChildren()->size() > children->at(j+1)->getChildren()->size())
        {
          Node<vector<int>*>* temp = children->at(j);
          children->at(j) = children->at(j+1);
          children->at(j+1) = temp;
        }
      }
    }
    for (int i = 0; i < currLoc->getChildren()->size(); ++i)
    {
      Node<vector<int>*>* point = heurSearch(currLoc->getChildren()->at(i), newDepth);
      if (point != NULL)
      {
        return point;
      }
    }
    return NULL;
  }
}

/*

*/
void KnightTour::runHeur()
{
  this->depth = this->boardSize * this->boardSize;
  addChildren(this->paths->getRoot());
  Node<vector<int>*>* pathFound = heurSearch(this->paths->getRoot(), 0);
  if (pathFound == NULL)
  {
    cout << "There is no way to cover the full board from that starting position." << endl;
  }
  else
  {
    cout << "A way to traverse the board was found!" << endl;
    cout << "Take the following path (board positions are indicated as [x,y] where x,y are between 1 and n): " << endl;
    vector<Node<vector<int>*>*>* moves = this->paths->trace(pathFound);
    cout << "The knight begins at [" << moves->at((moves->size()-1))->getData()->at(0)+1 << ", " << moves->at((moves->size()-1))->getData()->at(1)+1 << "]" << endl;
    for (int i = 0; i < moves->size()-1; ++i)
    {
      cout << "Move knight to [" << moves->at((moves->size()-2) - i)->getData()->at(0)+1 << ", " << moves->at((moves->size()-2) - i)->getData()->at(1)+1 << "]" << endl;
    }
  }
}

/*

*/
int main()
{
  chrono::time_point<std::chrono::high_resolution_clock> start1 = chrono::high_resolution_clock::now();
  KnightTour* testBrute = new KnightTour(3, 3, 6);
  testBrute->runBrute();
  testBrute->~KnightTour();
  chrono::time_point<std::chrono::high_resolution_clock> finish1 = chrono::high_resolution_clock::now();
  chrono::duration<double> elapsed1 = finish1 - start1;
  chrono::time_point<std::chrono::high_resolution_clock> start2 = chrono::high_resolution_clock::now();
  KnightTour* testHeur = new KnightTour(3, 3, 6);
  testHeur->runHeur();
  testHeur->~KnightTour();
  chrono::time_point<std::chrono::high_resolution_clock> finish2 = chrono::high_resolution_clock::now();
  chrono::duration<double> elapsed2 = finish2 - start2;
  cout << "Brute Run Time: " << elapsed1.count() << endl;
  cout << "Heuristic Run Time: " << elapsed2.count() << endl;
  return 0;
}
