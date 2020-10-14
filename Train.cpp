//
// Created by Shane Humphrey on 10/13/20.
//

#include "Train.h"
/*
 Name: Train() - Overloaded Constructor

 Desc - Creates a new train with one car and a size of one. A train is a linked list of cars
        The train is passed a route which is a list of stops for the train

 Preconditions - None

 Postconditions - Creates a new train
 */
Train::Train(Route* line){

  m_head = new Car();
  m_route = line;
  m_totalCars = 1;
}

/*
 Name: ~Train() - Destructor

 Desc - Removes each car from the train and deallocates each passenger in each car.
        Resets each of the linked list pointers

 Preconditions - None

 Postconditions - Removes all cars and passengers
 */
Train::~Train(){
  Car* curr = m_head;
  while (curr){
    m_head = m_head->m_next;
    delete curr;
    curr = m_head;
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

}

/*
 Name: RemoveCar(Car*)

 Desc - Removes a car from either the beginning, middle or end of train linked list

 Preconditions - Train exists

 Postconditions - Removes specific car (including passengers)

 UNUSED - 3 Bonus Pts for completing if rest of project is completed
 */
void Train::RemoveCar(Car*){

}

/*
 Name: TrainStatus

 Desc - Displays number of cars, number of passengers, and the route details

 Preconditions - Train is populated

 Postconditions - Displays information at a specific location
 */
void Train::TrainStatus(){

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
void Train::LoadPassengers(string passName) {

  ifstream humanStream(passName);

  string lineZ;
  string tempArr [NUM_PASSENGER_DATATYPES];
  int i=0;
  while(getline(humanStream,lineZ,',')) {// ="Nathenael,Dereb,21,Falls Road,Penn Station"
    if (i<4)
      tempArr[i] = lineZ;
//    cout << tempArr[i];
    i++;
    if (i == 4) {
      getline(humanStream, lineZ);
      tempArr[i] = lineZ;
      i = 0;
      string fullName = tempArr[0] + " "
                        + tempArr[1];
      int age = stoi(tempArr[2]);
      string startLoc = tempArr[3];
      string endLoc = tempArr[4];
//      cout << "\nname: " << fullName
//           << "\nage: " << age
//           << "\nstart loc: " << startLoc
//           << "\nend loc: " << endLoc;

      if (m_route->GetCurrentStop()->GetName() == startLoc)
        Passenger newPass = Passenger(fullName, age, startLoc,endLoc);
    }
  }
}

/*
 Name: BoardPassenger(Passenger*)

 Desc - Checks to see if the capacity of the train has been met. If so,
        adds a new car and inserts the passenger in the first open car starting at the front.
        Also, displays name and final destination of passenger being loaded.

 Preconditions - Passenger object already allocated and data populated. Train exists

 Postconditions - Adds new passenger to a car from front to back
 */
  void Train::BoardPassenger(Passenger*){

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
  void Train::DisembarkPassengers(){

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

  }

/*
 Name: TurnTrainAround()

 Desc - When chosen from the menu at the end of the route, reverses the Route by
        calling ReverseRoute

 Preconditions - Valid train on valid route

 Postconditions - The entire route is reversed and the train starts at the new front
 */
  void Train::TurnTrainAround(){

  }

/*
   Name: IsTrainFull()

   Desc - Iterates through train to see if total number of passengers is greater
          than maximum capacity

   Preconditions - Valid train on valid route

   Postconditions - Returns true if full else false
*/
  bool Train::IsTrainFull(){
    return true;
  }
