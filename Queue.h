//
//  Queue.h
//  Assignment2
//
//  Created by Tristan Wuster on 3/13/21.
//

#ifndef Queue_h
#define Queue_h

using namespace std;
class Event{
public:
    int customerID;
    int arrivalTime;
    int duration;
    bool arrival;

    Event(int arrivalTime, int duration, int customerID, bool arrival);
    friend bool operator < (const Event &event1, const Event &event2);

};

class Customer{
public:
    Customer(Event event) : customerID(event.customerID), duration(event
    .duration), arrivaltime(event.arrivalTime) {}

    int customerID;
    int arrivaltime;
    int duration;
};


void Simulation();

void processArival();

void processDeparture();

void processDeparture();



void processArival();

void Simulation();

#endif /* Queue_h */
