#ifndef TRAIN_H
#define	TRAIN_H

#include "TrainRunner.h"
#include "BinaryHeap.h"
#include "StackLi.h"


class Station3
{
  public:
    bool pick;
    bool drop;
    short pcount;
    short dcount;
    StackLi<short> carsOBID;
    StackLi<short> carspick;
    Station3(): pick(false), drop(false), pcount(0), dcount(0){}

}; // for the list created that keeps track

class Station2 
{
public:
  bool known;
  unsigned short distance;
  short prev;
  Station2():known(false),distance(-1),prev(-1){}
  //Station():adjCount(0){}
}; //for the dijkstra's table

class HeapNode
{
  public:
 	short id;
 	short dist;

}; //class HeapNode


class Train
{
public:

  short stationNum, carNum;
  int total; //total sitance travelled
  short previous; //stores where the train last was
  short current; //where the train is now
  short currStation;
  short delivered; // used for the while loop - counts the delivered cars
  short carCount; // number of carsOnBoard

  Station2 *dtable; //dijkstra's table
  Station *stationsar;
  BinaryHeap<HeapNode> heap;
  StackLi <short> stack;
  StackLi <short> resetStack;
  Station3 list[20000];
  
  Train(Station *stations, int numStations, int numCars);
  void dijkstra(Operation *operations, Car *cars);
  void fillList(Car *cars);
  void stackReset();
  void run(Car *cars, Operation *operations, int *numOperations);
}; // class train 

#endif	// TRAIN_H

