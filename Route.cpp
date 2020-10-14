//
// Created by Shane Humphrey on 10/13/20.
//

#include <string>
#include <fstream>
#include <iostream>
#include "Stop.cpp"
#include "Route.h"
using namespace std;

//Routes are the route a train would take from stop to stop
//In this case, it is a linked lists that is made up of stops (nodes)

/*
   Name: Route() - Default Constructor
   Desc - Creates a new empty route
   Preconditions - None
   Postconditions - Sets everything to either nullptr or 0
*/
Route::Route(){
  m_head = nullptr;
  m_tail = nullptr;
  m_currentStop = nullptr;
  m_totalStops = 0;
}

/*
   Name: ~Route - Destructor
   Desc - Removes all of the stops from the route
   Preconditions - Route must have nodes
   Postconditions - Route will be empty and m_head and m_tail and m_currentStop
                    will be nullptr and m_totalStops will be 0
*/
Route::~Route(){
  Stop* curr = m_head;
  while(m_head!=nullptr){

    m_head = m_head->GetNextStop();
    delete curr;
    curr = m_head;
  }
}

/*
   Name: LoadRoute(string)
   Desc - Reads the route file and calls AddStop once per line. Increments m_totalStops.
   Preconditions - Route allocated and file available
   Postconditions - Populates route with stops. Sets m_currentStop to m_head when load completed.
*/
void Route::LoadRoute(string routeFile) {
  ifstream routeStream (routeFile);

  string line1; int i; int j;
  while (getline(routeStream, line1)) {
    string stopName; string stopNum;

    for(i = 0; line1[i] != ','; i++)
      stopName += line1[i];

    for(j = i+1; j<line1.length(); j++)
      stopNum+=line1[j];

//    cout << "\nName: " << stopName
//         << "\nNumber: " << stoi(stopNum);
    AddStop(stopName, stoi(stopNum));
    m_totalStops++;
  }
  routeStream.close();
  m_currentStop = m_head;
}

/*
   Name: AddStop(string, int)
   Desc - Allocates new stop and inserts in end of route
   Preconditions - Route allocated and data for stop available
   Postconditions - New stop inserted in end of route
*/
void Route::AddStop(string stopName, int stopNum) {
  Stop* newStop = new Stop(stopName, stopNum);

  newStop->SetNextStop(newStop);
  if (m_head == nullptr)
    m_head = newStop;
  else{
    m_tail->SetNextStop(newStop);
  }
  m_tail = newStop;
}
/*
   Name: PrintRouteDetails()
   Desc - Prints information about the next stop on the route
   Preconditions - Route allocated and data for next stop available
   Postconditions - Outputs data only
*/
void Route::PrintRouteDetails(){
  cout << "\nCurrent stop: "
       << GetCurrentStop()->GetName() << endl;

  cout << "\nNext stop: "
       << GetCurrentStop()->GetNextStop()->GetName() << endl;

//  Stop* nextStop = m_currentStop->GetNextStop();
//  cout << nextStop->GetName() << endl;
//  cout << nextStop->GetNumber() << endl;
}

/*
   Name: GetCurrentStop
   Desc - Returns the m_currentStop
   Preconditions - m_currentStop has been assigned
   Postconditions - Returns the pointer
*/
Stop* Route::GetCurrentStop(){
  return m_currentStop;
}

/*
   Name: SetCurrentStop
   Desc - Updates m_currentStop
   Preconditions - m_currentStop is available
   Postconditions - Updates m_currentStop as the train moves
*/
void Route::SetCurrentStop(Stop* currStop){
  m_currentStop = currStop;
}

/*
   Name: ReverseRoute
   Desc - At the end of a route, the route can be reversed (as in the train turns around)
   Recommendations - Code this function last (dead last)
   Preconditions - Route has been completed
   Postconditions - Replaces old route with new reversed route.
*/
void Route::ReverseRoute(){

}