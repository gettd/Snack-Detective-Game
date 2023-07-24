#include "snack.h"
#include <cstdlib> // Include the cstdlib library for std::system
#include <cstring>
#include <iostream>
using namespace std;

// Clear screen def for windows and mac/linux
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

int main() {
  // Array to store snacks
  const int MAX_SNACKS = 10;
  Snack *snacks[MAX_SNACKS];
  int snackCount = 0;

  // Default snacks for inventory
  /*snacks[snackCount++] = new Snack("Potato Chips", "Lays", 10, 20);
  snacks[snackCount++] = new Snack("Chocolate Bar", "Hershey's", 5, 15);
  snacks[snackCount++] = new Snack("Chicken", "KFC", 10, 30);*/

  // Display the current inventory
  (void)std::system(CLEAR_SCREEN);
  cout << "=========================" << endl;
  cout << "Current Inventory:\n";
  for (int i = 0; i < snackCount; i++) {
    snacks[i]->display();
    cout << "\n";
  }
  cout << "=========================" << endl;
  // Add more snacks
  string n, b;
  int q;
  double p;
  char ans;
  do {
    cout << "Add more snack(s) ? (Y/N): ";
    cin >> ans;
    cout << "\n";
    if (ans != 'Y') {
      break;
    }
    if (snackCount >= MAX_SNACKS) {
      cout << "=========================" << endl;
      cout << "Inventory is full!!" << endl;
      cout << "=========================" << endl;
      break;
    } else {
      cout << "Snack Name: ";
      cin >> n;
      cout << "Brand: ";
      cin >> b;
      cout << "How many: ";
      cin >> q;
      cout << "Price: ";
      cin >> p;
      snacks[snackCount++] = new Snack(n, b, q, p);
      cout << endl;
    }
  } while (1);

  // Construct the binary search tree from the snacks array
  Snack *root = nullptr;
  for (int i = 0; i < snackCount; i++) {
    snacks[0]->addSnack(root, snacks[i]->getName(), snacks[i]->getBrand(),
                        snacks[i]->getQuantity(), snacks[i]->getPrice());
  }

  // Display the current inventory in stack form
  (void)std::system(CLEAR_SCREEN);

  // Display a menu to the user and let them choose between options
  char option;
  do {
    cout << "\nWhat do you want to do?\n";
    cout << "1. Display Inventory in Stack Form\n";
    cout << "2. Search Snack by Name using BST\n";
    cout << "3. Exit\n";
    cout << "Option: ";
    cin >> option;

    switch (option) {
    case '1':
      cout << "===============================" << endl;
      cout << "Current Inventory in Stack Form :\n";
      root->displayStackForm();
      cout << "===============================" << endl;
      break;
    case '2': {
      string searchQuery;
      cout << "Enter the snack name to search: ";
      cin.ignore(); // Ignore the previous newline character in the input buffer
      getline(cin, searchQuery);

      Snack *result = snacks[0]->searchSnackByName(root, searchQuery);
      if (result) {
        cout << "Snack found:\n";
        result->display();
        // edit or delete
        char action;
        bool shouldExit = false;
        string newBrand;
        int newQuantity;
        double newPrice;
        do {
          cout << "\n  Choose your action:\n";
          cout << "  1. Edit the snack information\n";
          cout << "  2. Delete the snack from your inventory\n";
          cout << "  3. Go back\n";
          cout << "  Action: ";
          cin >> action;
          switch (action) {
          case '1':
            cout << "Enter the new brand for the snack: ";
            cin.ignore();
            getline(cin, newBrand);
            cout << "Enter the new quantity for the snack: ";
            cin >> newQuantity;
            cout << "Enter the new price for the snack: ";
            cin >> newPrice;
            // Call the editSnack function to update the snack's information
            result->editSnack(searchQuery, newBrand, newQuantity, newPrice);

            cout << "\nSNACK " << searchQuery
                 << " INFORMATION UPDATED SUCCESSFULLY!\n\n";
            cout << "=========================" << endl;
            cout << "Updated Inventory\n";
            root->displayStackForm();
            cout << "=========================" << endl;

            shouldExit = true; // Set the flag to exit the loop
            break;
          case '2':
            result->deleteSnack(root, searchQuery);
            (void)std::system(CLEAR_SCREEN);
            cout << "\nDELETED SNACK " << searchQuery << " SUCCESSFULLY\n\n";
            cout << "=========================" << endl;
            cout << "Updated Inventory\n";
            root->displayStackForm();
            cout << "=========================" << endl;
            shouldExit = true;
            break;
          case '3':
            cout << "Exiting...\n";
            shouldExit = true;
            break;
          default:
            cout << "Invalid action. Please try again.\n";
            break;
          }
        } while (!shouldExit);
        break;
      } else {
        cout << "Snack not found in inventory.\n";
      }
      break;
    }
    case '3':
      cout << "Exiting program\n";
      break;
    default:
      cout << "Invalid option. Please try again.\n";
      break;
    }
    // Pause after each option to give the user time to read the output
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
    // Clear the console after the user presses Enter
    (void)std::system(CLEAR_SCREEN);

  } while (option != '3');

  // Clean up dynamically allocated memory
  for (int i = 0; i < snackCount; i++) {
    delete snacks[i];
  }

  return 0;
}
