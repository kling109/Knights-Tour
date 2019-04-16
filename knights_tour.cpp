/*
Name: Trevor Kling
ID: 002270716
Email: kling109@mail.chapman.edu
Course: CPSC 406 Algorithm Analysis
Last Date Modified: 11 April 2019
Project: Knight's Tour Implementations
*/

#include <iostream>
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
 for (int i = 0; i < source->size(); ++i)
 {
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
void KnightTour::addSortedChildren(Node<vector<int>*>* currLoc)
{
  int x = currLoc->getData()->at(0);
  int y = currLoc->getData()->at(1);
  vector<Node<vector<int>*>*>* visited = this->paths->trace(currLoc);
  vector<vector<int>*>* toAdd = new vector<vector<int>*>();
  if (x+2 < this->boardSize)
  {
    if (y+1 < this->boardSize)
    {
      vector<int>* newSquare = new vector<int>();
      newSquare->push_back(x+2);
      newSquare->push_back(y+1);
      if (!contains(visited, newSquare))
      {
        toAdd->push_back(newSquare);
      }
    }
    if (y-1 >= 0)
    {
      vector<int>* newSquare = new vector<int>();
      newSquare->push_back(x+2);
      newSquare->push_back(y-1);
      if (!contains(visited, newSquare))
      {
        toAdd->push_back(newSquare);
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
        toAdd->push_back(newSquare);
      }
    }
    if (y-1 >= 0)
    {
      vector<int>* newSquare = new vector<int>();
      newSquare->push_back(x-2);
      newSquare->push_back(y-1);
      if (!contains(visited, newSquare))
      {
        toAdd->push_back(newSquare);
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
        toAdd->push_back(newSquare);
      }
    }
    if (y-2 >= 0)
    {
      vector<int>* newSquare = new vector<int>();
      newSquare->push_back(x+1);
      newSquare->push_back(y-2);
      if (!contains(visited, newSquare))
      {
        toAdd->push_back(newSquare);
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
        toAdd->push_back(newSquare);
      }
    }
    if (y-2 >= 0)
    {
      vector<int>* newSquare = new vector<int>();
      newSquare->push_back(x-1);
      newSquare->push_back(y-2);
      if (!contains(visited, newSquare))
      {
        toAdd->push_back(newSquare);
      }
    }
  }
  for (int i = 0; i < toAdd->size(); ++i)
  {
    int count = 0;
    int currx = toAdd->at(i)->at(0);
    int curry = toAdd->at(i)->at(1);
    if (x+2 < this->boardSize)
    {
      if (y+1 < this->boardSize)
      {
        vector<int>* testpos = new vector<int>();
        testpos->push_back(x+2);
        testpos->push_back(y+1);
        if (!contains(visited, testpos))
        {
          ++count;
        }
      }
      if (y-1 >= 0)
      {
        vector<int>* testpos = new vector<int>();
        testpos->push_back(x+2);
        testpos->push_back(y-1);
        if (!contains(visited, testpos))
        {
          ++count;
        }      }
    }
    if (x-2 >= 0)
    {
      if (y+1 < this->boardSize)
      {
        vector<int>* testpos = new vector<int>();
        testpos->push_back(x-2);
        testpos->push_back(y+1);
        if (!contains(visited, testpos))
        {
          ++count;
        }
      }
      if (y-1 >= 0)
      {
        vector<int>* testpos = new vector<int>();
        testpos->push_back(x-2);
        testpos->push_back(y-1);
        if (!contains(visited, testpos))
        {
          ++count;
        }
      }
    }
    if (x+1 < this->boardSize)
    {
      if (y+2 < this->boardSize)
      {
        vector<int>* testpos = new vector<int>();
        testpos->push_back(x+1);
        testpos->push_back(y+2);
        if (!contains(visited, testpos))
        {
          ++count;
        }
      }
      if (y-2 >= 0)
      {
        vector<int>* testpos = new vector<int>();
        testpos->push_back(x+1);
        testpos->push_back(y-2);
        if (!contains(visited, testpos))
        {
          ++count;
        }
      }
    }
    if (x-1 >= 0)
    {
      if (y+2 < this->boardSize)
      {
        vector<int>* testpos = new vector<int>();
        testpos->push_back(x-1);
        testpos->push_back(y+2);
        if (!contains(visited, testpos))
        {
          ++count;
        }
      }
      if (y-2 >= 0)
      {
        vector<int>* testpos = new vector<int>();
        testpos->push_back(x-1);
        testpos->push_back(y-2);
        if (!contains(visited, testpos))
        {
          ++count;
        }
      }
    }
    toAdd->at(i)->push_back(count);
  }
  if (toAdd->size() != 0)
  {
    for (int i = 0; i < toAdd->size()-1; ++i)
    {
      for (int j = 0; j < toAdd->size() - i - 1; ++j)
      {
        if (toAdd->at(j)->at(2) > toAdd->at(j+1)->at(2))
        {
          vector<int>* temp = toAdd->at(j);
          toAdd->at(j) = toAdd->at(j+1);
          toAdd->at(j+1) = temp;
        }
      }
    }
    for (int i = 0; i < toAdd->size(); ++i)
    {
      toAdd->at(i)->pop_back();
      this->paths->insert(toAdd->at(i), currLoc);
    }
  }
}

/*

*/
Node<vector<int>*>* KnightTour::heurSearch(Node<vector<int>*>* currLoc, int currDepth)
{
  int newDepth = currDepth + 1;
  addSortedChildren(currLoc);
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
  KnightTour* testBrute = new KnightTour(1, 1, 5);
  testBrute->runBrute();
  testBrute->~KnightTour();
  KnightTour* testHeur = new KnightTour(1, 1, 5);
  testHeur->runHeur();
  testHeur->~KnightTour();
  return 0;
}
