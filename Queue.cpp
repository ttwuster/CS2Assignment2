#include <iostream>
#include <fstream>
#include <queue>
#include "Queue.h"
using namespace  std;
bool operator < (const Event &event1, const Event &event2) {
    return event1.arrivalTime > event2.arrivalTime;
}

Event::Event(int arrTime, int dur, int custID, bool arrival) : arrivalTime
(arrTime), duration(dur), customerID(custID), arrival(arrival) {}

void Simulation();

void processArival(Event event, priority_queue<Event> &pQueue, queue<Customer>
        &queue, bool &tellerAvailable, int currentTime);

void processDeparture(Event event, priority_queue<Event> &pQueue,
                      queue<Customer> &queue,  bool &Available, int currentTime );

void processDeparture(Event event, priority_queue<Event> &pQueue,
                      queue<Customer> &queue, bool &tellerAvailable, int
                      currentTime) {

    pQueue.pop();
    if(!queue.empty()){
        Customer customer(queue.front());
        queue.pop();
        int departureTime = currentTime + event.duration;
        Event newDeparture(departureTime, 0, customer.customerID, false);
        pQueue.push(newDeparture);
        
        
        cout << "Customer " << customer.customerID << " Finishes " << endl;
        customer.customerID++;
        tellerAvailable = true;
    }
}

void processArival(Event event, priority_queue<Event> &pQueue,
        queue<Customer> &queue, bool &tellerOpen, int currentTime) {

    pQueue.pop();

    Customer customer(event);

    if(queue.empty() && tellerOpen){
        int departureTime = currentTime + event.duration;
        Event newDeparture(departureTime, 0, customer.customerID, false );
        pQueue.push(newDeparture);
    if(event.duration == 10)
    {
        cout << "Customer  " << customer.customerID << " Arrives \n" << " starts being served (cash)" << endl;
        tellerOpen = true;
    }
 if(event.duration == 30)
{
    cout << "Customer   " << customer.customerID << " Arrives \n" << " starts being served (check)" << endl;
    tellerOpen = true;
}
    
    else{
        queue.push(customer);
    }
}
}

void Simulation(){
    bool tellerAvailable;
    cout << "DMV Simulation" << endl;
    queue<Customer> DMVQueue;
    priority_queue<Event> eventListPQueue;
    tellerAvailable = true;

    ifstream inFile;
    string filename = "/Users/tristanwuster/CS2/Assignment2/Assignment2/LINE.txt";
    inFile.open(filename);
    if(inFile.is_open()){

        int ArrivalTime;
        int WaitTime;
        int CustomerNUM = 0;
        while( inFile >> ArrivalTime && inFile >> WaitTime){
            CustomerNUM ++;
            Event arrival(ArrivalTime, WaitTime, CustomerNUM, true);
            eventListPQueue.push(arrival);
        }

        while(!eventListPQueue.empty()){

            Event newEvent = eventListPQueue.top();

            int currentTime = newEvent.arrivalTime;
            if(newEvent.arrival){
                processArival(newEvent, eventListPQueue, DMVQueue,
                        tellerAvailable, currentTime);
            }
            else{
                processDeparture(newEvent, eventListPQueue, DMVQueue,
                        tellerAvailable, currentTime);
            }
        }
    }else{
        cout << "File didn't open properly" << endl;
    }

    inFile.close();

}
