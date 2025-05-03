//Andre Bieller
#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class ItemData { //Item class. Holds the key for the item, as well as it's name in a string
    public: 
        int key;
        string item;

        ItemData(int k, string s) : key(k), item(s) {

        }
    
};

class Inventory { //Inventory class. Hashed data array.
    private:
        vector<ItemData*> inventoryList; //Array of hashed data
        int inventorySize; //Array size
        ItemData* nonItem; 

    public:
        Inventory(int size) : inventorySize(size) { //Constructor. Resizes array, sets all new cells to null
            inventoryList.resize(inventorySize);
            
            for(int i = 0; i < inventorySize; i++) {
                inventoryList[i] = NULL;
            }

            nonItem = new ItemData(-1, " ");
        }

        void displayInventory() { //Display the array, skipping empty cells
            cout << "Current warehouse inventory: \n";
            for(int i = 0; i < inventorySize; i++) {
                if(inventoryList[i] != NULL) {
                    cout << inventoryList[i]->item << ": " << inventoryList[i]->key << " \n";
                }
            }
        }

        int firstHash(int hashKey) { //Hashing the key for initial placement
            return hashKey % inventorySize;
        }

        int secondHash(int hashKey) { //Hashing the key to determine step amount if initial spot is taken
            return 5 - (hashKey % 5);
        }

        void insert(int keyInsert, ItemData* newItem) { //Insert a new item into the array.
            int hashedKey = firstHash(keyInsert); //Get hashed key
            int stepSize = secondHash(keyInsert); //Get step amount

            while(inventoryList[hashedKey] != NULL && inventoryList[hashedKey]->key != -1) { //While the found spot is not null or nonItem, step forward
                hashedKey += stepSize;
                hashedKey %= inventorySize;
            }

            inventoryList[hashedKey] = newItem; //Otherwise, add new item
        }

        ItemData* remove(int removeKey) { //Remove an item from the array
            int hashedKey = firstHash(removeKey); //Get hashed key
            int stepSize = secondHash(removeKey); //get step amount

            while(inventoryList[hashedKey] != NULL) { //while the found spot is not null
                if(inventoryList[hashedKey]->key == removeKey){ //Check to see if hashed key matches the key to find
                    ItemData* temp = inventoryList[hashedKey]; //If so, return the found item and set the cell to NULL
                    inventoryList[hashedKey] = NULL;
                    return temp;
                }

                hashedKey += stepSize; //Otherwise, step forward
                hashedKey %= inventorySize;
            }
        }

        int generateKey() { //Genrate a random key based on system time, for almost guaranteed different keys every time
            srand((time(0)));
            int randKey = rand() % 5001;
            return randKey;
        }

        ItemData* find(int findKey) { //Find a key. 
            int hashedKey = firstHash(findKey);
            int stepSize = secondHash(findKey);

            while(inventoryList[hashedKey] != NULL) {
                if(inventoryList[hashedKey]->key == findKey) {
                    return inventoryList[hashedKey];
                }

                hashedKey += stepSize;
                hashedKey %= inventorySize;
            }
            return NULL;
        }
};

void userInput(Inventory* inv) { //Asks the user for a number input to contiue
    cout << "Welcome. What would you like to do? Press the corresponding number: \n"; 
    cout << "1. View inventory\n2. Remove item from manifest\n3. Add item to manifest\n4. End Program\n";
    int numInput;
    cin >> numInput;
    string itemAdded;

    switch (numInput) {
        case 1: //If 1,  display the array
            inv->displayInventory();
            userInput(inv);
            break;

        case 2: //If 2, ask for a number input, calling remove() based on the input
            cout << "Please input the key number of the item you wish to remove:\n ";
            int removeInput;
            cin >> removeInput;
            inv->remove(removeInput);
            inv->displayInventory();
            userInput(inv);
            break;

        case 3: //If 3, add an item bases on user's string input
            ItemData* userItem;
            cout << "Please enter the name of the furniture you are adding to inventory (No spaces): \n";
            
            cin >> itemAdded;
            userItem = new ItemData(inv->generateKey(), itemAdded);
            inv->insert(userItem->key,  userItem);
            inv->displayInventory();
            userInput(inv);
            break;

        case 4: //End program
            cout << "Goodbye!";
            break;

    }
}

void initializeProgram() {
    Inventory furnitureWareHouse(300); //Create initial array
    userInput(&furnitureWareHouse); //Call user input
}