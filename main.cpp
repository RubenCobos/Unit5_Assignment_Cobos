// A  Restaurant Project Struct style Dr_T Dr. Tyson McMillan 10-2-2019

//#include <iostream>
//#include<string>
#include "Input_Validation.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

/*struct MenuItem
{
  string name;
  double itemCost;
  string desc;
  char addLetter;
  char removeLetter;
  int count;
};*/

class MenuItem // Object Definition
{
private:
  string name;
  double itemCost;
  string desc;
  char addLetter;
  char removeLetter;
  int count;

public:
  MenuItem();

  void Set_Name(string n) { name = n; }
  void Set_Cost(double c) { itemCost = c; }
  void Set_Desc(string d) { desc = d; }
  void Set_Add(char a) { addLetter = a; }
  void Set_Remove(char r) { removeLetter = r; }
  void Set_Count(int c) { count = count + c; }
  void Reset_Count() { count = 0; }

  string Get_Name() const { return name; }
  double Get_Cost() const { return itemCost; }
  string Get_Desc() const { return desc; }
  char Get_Add() const { return addLetter; }
  char Get_Remove() const { return removeLetter; }
  int Get_Count() const { return count; }

  ~MenuItem() { ; }
};

MenuItem::MenuItem() // Constructor
{
  name = "";
  itemCost = 0.0;
  desc = "";
  addLetter = '\0';
  removeLetter = '\0';
  count = 0;
}

// function definitions
void populateMenu(vector<MenuItem> &entireMenu) {
  // put some default values in our Menu
  const int numItems = 7;
  MenuItem Item1;
  MenuItem Item2;
  MenuItem Item3;
  MenuItem Item4;
  MenuItem Item5;
  MenuItem Item6;
  MenuItem Item7;

  entireMenu.push_back(Item1); // add to the end of list the Item1
  entireMenu.push_back(Item2); // add to the end of list the Item2
  entireMenu.push_back(Item3); // add to the end of list the Item3
  entireMenu.push_back(Item4); // add to the end of list the Item4
  entireMenu.push_back(Item5); // add to the end of list the Item5
  entireMenu.push_back(Item6); // add to the end of list the Item6
  entireMenu.push_back(Item7); // add to the end of list the Item7

  vector<string> defaultMenuNames = {"Item 1", "Item 2", "Item 3", "Item 4",
                                     "Item 5", "Item 6", "Item 7"};
  vector<char> defaultAddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  vector<char> defaultRemoveLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

  for (int i = 0; i < numItems; i++) {
    // add each item to the default list efficiently
    entireMenu[i].Set_Name(defaultMenuNames[i]);
    entireMenu[i].Set_Add(defaultAddLetters[i]);
    entireMenu[i].Set_Remove(defaultRemoveLetters[i]);
    entireMenu[i].Set_Cost(3.00 + i); // set a random starter cost for each item
    entireMenu[i].Set_Count(0);       // initialze all counts to 0
    entireMenu[i].Set_Desc("delicious"); // set all default desc to "delicous"
  }
}

void showMenu(vector<MenuItem> &m) {
  cout << fixed << setprecision(2); // set doubles to 2 decimal places
  cout << "DrT's Effcient Menu" << endl;
  cout << "ADD  \tNAME \t COST \tREMOVE\tCOUNT\tDESC" << endl;
  for (int i = 0; i < m.size(); i++) {
    cout << m[i].Get_Add() << ")" << setw(10) << m[i].Get_Name() << setw(5)
         << "$" << m[i].Get_Cost() << setw(5) << "(" << m[i].Get_Remove() << ")"
         << setw(7) << m[i].Get_Count() << setw(13) << m[i].Get_Desc() << endl;
  }
}

void printReceipt(vector<MenuItem> &m, double sub, double tax, double tip,
                  double total) {
  ofstream receipt;
  stringstream numconv;
  string receiptNum;
  string filename;
  static int num = 0;

  ++num;
  numconv << num;
  numconv >> receiptNum;
  filename = "receipt" + receiptNum + ".txt";

  receipt.open(filename, ofstream::out);

  cout << fixed << setprecision(2);
  receipt << fixed << setprecision(2);

  // To screen
  cout << "\nDr T's Diner\n";
  cout << "------------\n";

  for (int i = 0; i < m.size(); i++) {
    if (m[i].Get_Count() > 0) {
      cout << m[i].Get_Name() << '\t' << "Qty. " << m[i].Get_Count() << '\t'
           << m[i].Get_Cost() * m[i].Get_Count() << endl;
    }
  }

  cout << "Subtotal: $" << sub << endl;
  cout << "Tax: $" << tax << endl;
  cout << "Tip: $" << tip << endl;
  cout << "Total: $" << total << endl;
  cout << "------------\n\n";

  // To file
  receipt << "\nDr T's Diner\n";
  receipt << "------------\n";

  for (int i = 0; i < m.size(); i++) {
    if (m[i].Get_Count() > 0) {
      receipt << m[i].Get_Name() << '\t' << "Qty. " << m[i].Get_Count() << '\t'
              << m[i].Get_Cost() * m[i].Get_Count() << endl;
    }
  }

  receipt << "Subtotal: $" << sub << endl;
  receipt << "Tax: $" << tax << endl;
  receipt << "Tip: $" << tip << endl;
  receipt << "Total: $" << total << endl;
  receipt << "------------\n\n";

  receipt.close();
}

void acceptOrder(vector<MenuItem> &m) {
  char option = '\0';  // the user-selected menu item
  char yorn = '\0';    // yes or no for tip option
  char payment = '\0'; // cash or card? (1 = cash, 2 = card)
  double cash = 0.0;   // payment amount
  double subtotal = 0.0;
  double tip = 0.0;              // tip amount
  double tax = 0.0;              // sales tax amount
  double total = 0.0;            // total sale
  const double taxRate = 0.0825; // Texas sales tax rate

  cout << fixed << setprecision(2);

  while (option != 'x' && option != 'X') {
    // reset item count to 0 when starting a new order
    for (int i = 0; i < m.size(); i++) {
      m[i].Reset_Count();
    }

    do // start new order
    {
      cout << "\nNEW CUSTOMER ORDER\n";
      cout << "Please choose an item ('O' to place order, 'X' to exit "
              "program): ";
      option = Validate_Character(option);

      for (int i = 0; i < m.size(); i++) {
        if (option == m[i].Get_Add()) {
          cout << "\nMenu Item " << m[i].Get_Add() << " selected.";
          m[i].Set_Count(1);          // increment the count by 1
          cout << "\033[2J\033[1;1H"; // clear screen
          cout << "\n1 UP on " << m[i].Get_Name() << endl;
          subtotal +=
              m[i].Get_Cost(); // increment the subtotal by the cost of the item
          showMenu(m);         // show the updated menu
          cout << "\nSubtotal: $" << subtotal << endl;
        } else if (option == m[i].Get_Remove()) {
          cout << "\nRemove Item " << m[i].Get_Remove() << " selected.";
          if (m[i].Get_Count() > 0) // subtract if and only if the count is > 0
          {
            m[i].Set_Count(-1);         // decrement the count by 1
            cout << "\033[2J\033[1;1H"; // clear screen
            cout << "\n1 DOWN on " << m[i].Get_Name() << endl;
            subtotal -= m[i].Get_Cost(); // decrement the subtotal by the cost
                                         // of the item
            showMenu(m); // show the updated menu
            cout << "\nSubtotal: $" << subtotal << endl;
          } else // the the user why you blocked item removal
          {

            cout << "\nItem count must be > 0 to remove: " << m[i].Get_Name()
                 << endl;
          }
        } else if (option != m[i].Get_Add() && option != m[i].Get_Remove() &&
                   option != 'x' && option != 'X' && option != 'o' &&
                   option != 'O') // test for all of my valid inputs
        {
          if (i == 0) {
            cout << "\nInvalid input (" << option << "). Please try again."
                 << endl;
          }
        }
      }
    } while (option != 'o' && option != 'O' && option != 'x' && option != 'X');

    // exit outer loop
    if (option == 'x' || option == 'X') {
      break;
    }

    cout << "\nThank you for placing your order." << endl;

    // Tax
    tax = subtotal * taxRate;

    // Tipping
    cout << "Would you like to tip (y or n)? 20% recommended: ";
    yorn = Validate_Character(yorn);
    if (yorn == 'y' || yorn == 'Y') {
      cout << "Enter tip amount: ";
      tip = Validate_Rational(tip);
      total = subtotal + tax + tip;
    } else if (yorn == 'n' || yorn == 'N') {
      total = subtotal + tax;
    } else {
      cout << "\nInvalid input (" << yorn << "). Please try again." << endl;
    }

    // Payment
    cout << "Total due: $" << total << endl;
    cout << "Payment method? (1 = cash, 2 = card): ";
    payment = Validate_Character(payment);
    if (payment == '1') {
      do {
        cout << "Enter cash amount: ";
        cash = Validate_Rational(cash);
        if (cash >= total) {
          cout << "Change due: $" << cash - total << endl;
          total = 0.0;
        }
        if (cash < total) {
          total = total - cash;
          cout << "Total due: $" << total << endl;
        }
      } while (total > 0.0);
    } else if (payment == '2') {
      cout << "Processing payment... Approved.\n";
    } else {
      cout << "\nInvalid input (" << payment << "). Please try again." << endl;
    }

    total = subtotal + tax + tip; // recalculate total for receipt

    // Receipt
    printReceipt(m, subtotal, tax, tip, total);
  }
}

int main() {
  vector<MenuItem> wholeMenu;
  populateMenu(wholeMenu); // put some default values in the menu
  showMenu(wholeMenu);     // print the current data of the menu on screen
  acceptOrder(wholeMenu);

  return 0;
}