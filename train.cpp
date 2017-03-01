// Author: Raja and Patty

#include "TrainRunner.h"
#include "train.h"

#include <iostream>
#include <cstring> 

using namespace std; 

Train::Train(Station *stations, int numStations, int numCars) 
{
  stationsar = new Station[numStations];
  stationNum = numStations;
  carNum = numCars;
  total = 0;
  current = 0;
  currStation = 0;
  previous = 0;
  delivered = 0;
  carCount = 0;
  memcpy(stationsar, stations, numStations * (sizeof(*stations)));

  BinaryHeap<HeapNode> heap((1001)); // trying

  dtable = new Station2[numStations];
  
} // Train()


void Train::run(Car *cars, Operation *operations, int *numOperations)
{

 //filling hash table of stations
  fillList(cars);
  int popped, cpopped;
  Operation obj;
  //dijkstra(operations, cars);
  while(delivered < carNum)
  {
     dijkstra(operations, cars);
     while(!stack.isEmpty())
     {
       popped = stack.topAndPop();
       short i = 0;
       obj.operation = 'M';
       while(stationsar[current].adjacent[i] != popped) 
       {
          i++;
       
       }
       total += stationsar[current].distances[i];
       obj.time = total;
       obj.ID = popped;
       operations[*numOperations] = obj;
       (*numOperations)++;
       current = popped;
       previous = current;
     } //end of moving around

    if(list[popped].drop==true)
    {
      while(!(list[popped].carsOBID.isEmpty()) && list[popped].dcount != 0)
      {
        cpopped = list[popped].carsOBID.topAndPop();
        list[popped].dcount--;
        obj.operation = 'D';
        obj.ID = cpopped;
        obj.time = total;
        operations[*numOperations] = obj;
        (*numOperations)++;
        carCount--;
        delivered++;
        
        
      } // end of while loop - everything has been delivered
     if(list[popped].dcount == 0)
       list[popped].drop = false;
    } //dropping off first

   if(list[popped].pick == true && carCount < 40)
   {
     //Operation obj2 = Operation(total, 'M', );
     while(!(list[popped].carspick.isEmpty()) &&  list[popped].pcount != 0)
     {
       cpopped = list[popped].carspick.topAndPop();
       list[cars[cpopped].destination].carsOBID.push(cpopped);
       list[popped].pcount--;
       obj.operation = 'P';
       obj.ID = cpopped;
       obj.time = total;
       operations[*numOperations] = obj;
       (*numOperations)++;
       carCount++;
     } // end of while loop - everything is picked up

    if(list[popped].pcount ==0)
      list[popped].pick = false;

   }
    //all counts are managed before repeating the loop
    stackReset();
  }

} // run()

void Train::dijkstra(Operation *operations, Car *cars)
{
  
  dtable[current].prev = previous;
  dtable[current].known = true;
  dtable[current].distance = 0; //total;*/
  
  HeapNode obj;

  bool flag = false;
  resetStack.push(current);
  while(flag == false)
  {
    for(int i = 0; i < stationsar[currStation].adjCount; i++)
    {
      //goes in only if the distance in the dtable is greater than the sum of distances
      if(dtable[stationsar[currStation].adjacent[i]].known == false && dtable[stationsar[currStation].adjacent[i]].distance > dtable[currStation].distance + stationsar[currStation].distances[i])
      { 
       
        //testing
        dtable[stationsar[currStation].adjacent[i]].distance = dtable[currStation].distance + stationsar[currStation].distances[i];
        dtable[stationsar[currStation].adjacent[i]].prev = previous; 
        obj.id = stationsar[currStation].adjacent[i];
        obj.dist = dtable[stationsar[currStation].adjacent[i]].distance;
        resetStack.push(obj.id);
        heap.insert(obj);
        if((carCount < 40) && (list[stationsar[currStation].adjacent[i]].pick == true) || 
         (!list[stationsar[currStation].adjacent[i]].carsOBID.isEmpty())) 
         {
                 flag = true;
               
       }
       if(carCount >= 40 && !list[stationsar[currStation].adjacent[i]].carsOBID.isEmpty())
       {
          flag = true;
       }
     } 
          //if adjacent stations are interested station

  } //end of for loop
                                                                            
  
 
   if(flag == true) //can stop because there is pick up and drop off
    {
       while(!heap.isEmpty())              
       {
          if(!list[heap.findMin().id].carsOBID.isEmpty())
          {
             currStation = heap.findMin().id;
             heap.deleteMin();
               break;
          }
          else if(carCount < 40 && list[heap.findMin().id].pick == true)// && pickflag == true)
            {
               currStation = heap.findMin().id;
               heap.deleteMin();
                 break;
            }
          else
          {
            heap.deleteMin();   
          }
        } // end of while loop when falg is true

   } // if flag is true = relevant

   else //keep doing dij
   {
     currStation = heap.findMin().id;
     dtable[currStation].known = true;
      previous = currStation;
  
      heap.deleteMin();
   
  }

  } //end of while loop ------------------------------>>>>


  for(short k = currStation; k != current; k = dtable[k].prev)
  {
      stack.push(k);
  }
 
  heap.makeEmpty();

} //dijkstra()


void Train::fillList(Car *cars)
{
  for(short i = 0; i < carNum; i++)
  {
    list[cars[i].origin].pick = true;
    list[cars[i].origin].carspick.push(i);
    list[cars[i].origin].pcount++;
    list[cars[i].destination].drop = true;
    list[cars[i].destination].dcount ++;
  }

} //fillList

void Train::stackReset()
{

  int popped;
  while(!(resetStack.isEmpty()))
  {
    popped = resetStack.topAndPop();
    dtable[popped].known = false;
    dtable[popped].distance = -1;
    dtable[popped].prev = -1;
  } //end of while loop

} //stackReset()


