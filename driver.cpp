//
// Created by Shane Humphrey on 10/13/20.
//
#include "Route.h"
#include "Train.h"

int main(){
  const string routeFile = "proj3_routes.txt";
  const string passFile = "proj3_passengers.csv";
  Route* link = new Route();
  link->LoadRoute(routeFile);
  link->PrintRouteDetails();
  Train* rail = new Train(link);
  rail->LoadPassengers(passFile);

  delete link;
  delete rail;
  return 0;

}