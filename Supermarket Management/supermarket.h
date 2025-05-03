//Andre Bieller
#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Customer {  //Customer class. Holds number of items
        
    public:
        int items;
        Customer(int i) : items(i) { // Constructor

        }

        int getItems() {
            return items;
        }
};

class Cashier { //Cashier class. Manages customer queue, checking for empty lines, and time simulation
    private:
        vector<Customer*> customerQueue;
        string name;
        int front;
        int rear;
        int nCustomers;
        int emptyChecks;
        int currentTime;
    public:
        Cashier* nextCashier;
        Cashier(string n) : name(n), front(0), rear(-1), nCustomers(0), emptyChecks(0), currentTime(0) { //Constructor
            customerQueue.resize(20);
        }

        void newCustomer(Customer* c) { //Adds a cusomter into the queue
            if (rear == customerQueue.size() - 1) {
                rear = -1;
            }

            customerQueue[rear++] = c;
            nCustomers++;

            cout << "A new customer has arrived, and gone to " << name << "'s register with " << c->items << " items. There is now a queue of " << nCustomers << ".\n";
        }

        Customer* finishCusomter() { //Removes the finished cusomer from the queue
            Customer* temp = customerQueue[front++];
            if (front == customerQueue.size()) {
                front = 0;
            }

            nCustomers--;
            return temp;
        }

        Customer* nextCustomer() { //Returns the current customer
            return customerQueue[front];
        }

        int size() { //Returns the number of customers
            return nCustomers;
        }

        int getEmpty() { //Returns the number of checks that the chashier's queue has been found empty
            return emptyChecks;
        }

        void addEmpty() { //Adds one to emptyChecks
            emptyChecks++;
        }

        string getName() { // Returns the cashier's designation
            return name;
        }

        void resetEmpty() { //Resets emptyChecks back to zero
            emptyChecks = 0;
        }

        void passTime() { //Passes time by removing items from customer's item numbers. 10 per thirty seconds
            nextCustomer()->items = nextCustomer()->items - 10;
        }

       
        
        
};

class Store { //Store class. Handles opening and closing of registers.
    private:
        Cashier* first;
        int numCashiers; //NUmber of cashiers that have been opened, for unique naming
    public:
        Store() : numCashiers(0), first(NULL){ //Constructor

        }

        void openRegister() { //Open a new register
            string newName = "Cashier " + to_string(numCashiers); //Get name from number of already opened registers
            Cashier* newCashier = new Cashier(newName); //Create a new Cashier
            Cashier* previous = NULL;
            Cashier* current = first;

            cout << "Opening "  << newCashier->getName() << "'s register.\n";

            while (current != NULL) { //While the current cashier is not null, cycle to the next
                previous = current;
                current = current->nextCashier;
            }

            if (previous == NULL) { //If previous is still null, then new cashier must be the first
                first = newCashier;
            }
            else { //Else, add new cashier and link it to previous
                newCashier->nextCashier = previous->nextCashier;
                previous->nextCashier = newCashier;
            }

            numCashiers++;
        }

        Cashier* closeRegister(Cashier* toClose) { //Closing a register
            Cashier* previous = NULL;
            Cashier* current = first;

            while (current != toClose) { //While the current register is does not match the one to close, cycle forward
                previous = current;
                current = current->nextCashier;
            }

            previous->nextCashier = current->nextCashier;  //Replace links
            cout << "Closing " << toClose->getName() << "'s register.\n";
            return current; //Forget the Cashier
        }

        void addCusomter() { //Add a customer
            Cashier* current = first;
            Cashier* smallest = first;
            int randomItems = rand() % 31; //Select a random number of items, up to 30
           
            if (randomItems < 1) { //If items end up being zero, add one.
                randomItems++;
            }
            
            Customer* addedCustomer = new Customer(randomItems); //Create a new customer

            if (current->size() >= 6) { //If the current cashier's queue is 6 or more, open another register
                Cashier* current = first;
                int cashierCount = 0; //Count for number of currently open regusters

                while (current != NULL) { //Find a null link
                    cashierCount++;
                    current = current->nextCashier;
                }

                if (cashierCount < 9) { //If less then nine cashiers are open, proceed with opening
                openRegister();
                }
                else {
                    cout << "There are already 9 registers open.\n"; //Else, continue
                }
            }

            current = first;
            Cashier* pNext = first->nextCashier; //Next cashier, for simplicity

            while (pNext != NULL) { //While the next cashier isn't null, cycle through and find the smallest queue
                if (current->size() > pNext->size()) {
                    smallest = pNext;
                    pNext = pNext->nextCashier;
                    current = pNext;
                }
                else {
                    pNext = pNext->nextCashier;
                    current = pNext;
                }
            }

            smallest->newCustomer(addedCustomer); //Add customer to the smalles queue
            
        }

        void serveCustomers() { //Logic for removing items and finishing customers
            Cashier* current = first;
            
            while (current != NULL) { //While cashier isn't null
                if (current->size() != 0) { //If the cashier's queue isn't empty
                    if (current->nextCustomer()->items <= 0) { //And the current customer has no more items
                        
                        cout << current->getName() << " has finished their current customer. Moving on...\n"; //Delete customer and move on.
                        current->finishCusomter();
                        current = current->nextCashier;
                    }
                    else { //Else, if the customer does have items, get the amount of time in seconds needed to finishe that customer (Three seconds per item) and reset the  empty checks.
                        cout << current->getName() << "'s current customer has " << current->nextCustomer()->getItems() * 3 << " seconds left on their checkout time.\n";
                        current->resetEmpty();
                        current->passTime();
                        current = current->nextCashier;
                    }
                }
                else if (current->size() == 0 && current != first){ //Else, if the queue is empty, and more than one register is open, add one to the empty checks. 
                    current->addEmpty();
                    if(current->getEmpty() == 3) { //If empty checks equal three, close the register
                        closeRegister(current);
                    }
                    current = current->nextCashier;
                }
                else { //Else if only one register is open and the queue is empty, pass. 
                    cout << "No customers. Waiting...\n";
                    current = current->nextCashier;
                }
            }
            string blank; 
            cout << "Press enter to advance time by 30 seconds...\n"; //Pass 30 simulated seconds, removing items from customers. 
            getline(cin, blank);
            addCusomter(); //Add two customers
            addCusomter();
            serveCustomers(); //Serve customers
        }

};

void initializeProgram() {
    Store simulatedStore; //Create initial object, and run initial funcitons. The rest loops. 
    simulatedStore.openRegister();
    simulatedStore.serveCustomers();
}