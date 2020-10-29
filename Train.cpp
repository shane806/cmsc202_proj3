//
// Created by Shane Humphrey on 10/13/20.
//

#include "Train.h"
#include <vector>
/*
 Name: Train() - Overloaded Constructor
 Desc - Creates a new train with one car and a size of one. A train
        is a linked list of cars The train is passed a route which is
        a list of stops for the train
 Preconditions - None
 Postconditions - Creates a new train
 */
Train::Train(Route* line){

  m_totalCars = 1;
  m_head = new Car(CAR_CAPACITY, m_totalCars);
  m_route = line;

}
/*
 Name: ~Train() - Destructor
 Desc - Removes each car from the train and deallocates each passenger in each car.
        Resets each of the linked list pointers
 Preconditions - None
 Postconditions - Removes all cars and passengers
 */
Train::~Train(){
  Car *currCar = m_head;
  while (currCar){
    cout << "\ndeallocating Car " << currCar->m_carNumber
         << "\n  deallocating Car " << currCar->m_carNumber
         << "'s passenger(s): " << endl;

    int passCnt = 0;
    for (unsigned int i = 0; i < currCar->m_passengers.size(); i++) {
      delete currCar->m_passengers[i];
      passCnt++;
    }
    cout << "\n    " << passCnt
         << " passenger(s) in Car " << currCar->m_carNumber
         << " deallocated" << endl;

    m_head = currCar->m_next;
    delete currCar;
    currCar = m_head;
  }

}
/*
 Name: AddCar
 Desc - Dynamically allocates a new car and inserts it at the end of the train.
        Increments m_totalCars
 Preconditions - Train must exist
 Postconditions - New car node inserted at end of train
 */
void Train::AddCar(){
  m_totalCars++;

  Car* currCar = m_head;
  while (currCar->m_next)
    currCar = currCar->m_next;

  currCar->m_next = new Car(CAR_CAPACITY, m_totalCars);
}

/*
 Name: RemoveCar(Car*)
 Desc - Removes a car from either the beginning, middle or end of train linked list
 Preconditions - Train exists
 Postconditions - Removes specific car (including passengers)
 UNUSED - 3 Bonus Pts for completing if rest of project is completed
 */
void Train::RemoveCar(Car* removeCar){
  //  Car* toBeRemoved = m_head;
  //
  //  while(toBeRemoved->m_carNumber != removeCar->m_carNumber)
  //    toBeRemoved = toBeRemoved->m_next;

/*
 Name: TrainStatus
 Desc - Displays number of cars, number of passengers, and the route details
 Preconditions - Train is populated
 Postconditions - Displays information at a specific location
 */

void Train::TrainStatus(){
  Car *currCar = m_head;
  cout << "\nNumber of train cars: " << m_totalCars;

  while (currCar){
    int numPassengers = 0;
    cout << "\n\n  Car " << currCar->m_carNumber << ": ";

    for (unsigned int i = 0; i < currCar->m_passengers.size(); i++)
      numPassengers++;
    cout << "Number of passengers: " << numPassengers;
    currCar = currCar->m_next;
  }
  cout << "\n\nRoute details:";
  m_route->PrintRouteDetails();
}

/*
 Name: LoadPassengers(filename)

 Desc - Iterates through an input file and if the name of the "start location"
        matches m_curLocation then creates a new passenger and has them BoardPassenger

 **Note - If you run this twice at any stop, it will load the same people over
          and over again - you do not need to check for this

 Preconditions - Valid input file with first name, last name, age, start location,
                 end location all comma separated with one passenger on each line

 Postconditions - Loads all passengers at this into cars
 */
void Train::LoadPassengers(string passFileName) {

  ifstream passStream(passFileName);

  string line; string tempArr [NUM_PASSENGER_DATATYPES];
  int i = 0; int newPassCnt = 0;
  while (getline(passStream, line, ',')) {

    if (i < (NUM_PASSENGER_DATATYPES - 1))
      tempArr[i] = line;

    i++;
    if (i == (NUM_PASSENGER_DATATYPES - 1)) {

      getline(passStream, line);
      tempArr[i] = line;

      string fullName = tempArr[0] + " "
                        + tempArr[1];
      int age = stoi(tempArr[2]);
      string startLoc = tempArr[3];
      string endLoc = tempArr[4];

      if (m_route->GetCurrentStop()->GetName() == startLoc) {

        Passenger *newPass = new Passenger(fullName, age, startLoc, endLoc);

        BoardPassenger(newPass);

        cout << endl << newPass->GetName()
             << " is boarding (Destination: "
             << newPass->GetFinalDestination() << ")" << endl;

        newPassCnt++;
      }
      i = 0;
    }
  }
  cout << "\nBoarded " << newPassCnt << " passenger(s)";
  passStream.close();
}

/*
 Name: BoardPassenger(Passenger*)
 Desc - Checks to see if the capacity of the train has been met. If so,
        adds a new car and inserts the passenger in the first open car starting at the front.
        Also, displays name and final destination of passenger being loaded.
 Preconditions - Passenger object already allocated and data populated. Train exists
 Postconditions - Adds new passenger to a car from front to back
 */
void Train::BoardPassenger(Passenger* newPass) {
  Car *currCar = m_head;

  while (currCar->IsFull()) {

    if (!currCar->m_next)
      AddCar();

    currCar = currCar->m_next;
  }
  currCar->AddPassenger(newPass);
}

/*
 Name: DisembarkPassenger()
 Desc - For each passenger on the train, checks to see if they are at their final
        destination. If they are, the passenger is removed from the train.

 Note - Deallocate the passenger first then you can use the m_passengers.erase command.
 Do not remove cars that are now unnecessary based on capacity (if you
 added a car to hold 17 passengers and one disembarks, do not remove it)

 Preconditions - Passengers reach their destination
 Postconditions - Passengers are removed from the m_passengers, deallocated, and erased
 */
void Train::DisembarkPassengers() {

  Car* currCar = m_head;
  int passCnt = 0;
  while (currCar)
  {
    for (unsigned int i = 0; i < currCar->m_passengers.size(); i++) {
      if (currCar->m_passengers[i]->GetFinalDestination()
          == m_route->GetCurrentStop()->GetName())
      {
        cout << endl << currCar->m_passengers[i]->GetName()
             << " disembarked the train" << endl;

        delete currCar->m_passengers[i];
        currCar->m_passengers.erase(currCar->m_passengers.begin()+i);
        passCnt++;
      }
    }
    currCar = currCar->m_next;
  }
  cout << endl << passCnt << " passenger(s) disembarked";
}
/*
 Name: TravelToNextStop
 Desc - When chosen from the menu, moves the train to the next stop. If you have
        reached last stop, indicates this.
        When at end, also recommends turning train around.
 Preconditions - Valid train on valid route
 Postconditions - Updates SetCurrentStop to next stop on route
 */
void Train::TravelToNextStop(){

  if (!m_route->GetCurrentStop()->GetNextStop())
    cout << "\nYou've reached the end of the line!\n\n"
         << "Go ahead and choose option 5 to turn the"
         << " train around" << endl;
  else
  {
    m_route->SetCurrentStop(m_route->GetCurrentStop()->GetNextStop());
    cout << "\nArriving at "
         << m_route->GetCurrentStop()->GetName() << endl;
  }
}
/*
 Name: TurnTrainAround()
 Desc - When chosen from the menu at the end of the route, reverses the Route by
        calling ReverseRoute
 Preconditions - Valid train on valid route
 Postconditions - The entire route is reversed and the train starts at the new front
 */
void Train::TurnTrainAround(){

  if (m_route->GetCurrentStop()->GetNextStop())
    cout << "\nYou can only reverse the route at the end of the"
         << " route. \n\nChoose a different option\n";
  else
    m_route->ReverseRoute();
}

/*
   Name: IsTrainFull()
   Desc - Iterates through train to see if total number of passengers is greater
          than maximum capacity
   Preconditions - Valid train on valid route
   Postconditions - Returns true if full else false
*/
bool Train::IsTrainFull() {
  Car* currCar = m_head;
  while (currCar){
    if (!currCar->IsFull())
      return false;
    currCar = currCar->m_next;
  }
  return true;
}

