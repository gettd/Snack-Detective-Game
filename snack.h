#ifndef SNACK_H
#define SNACK_H

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Snack {
private:
  string name;
  string brand;
  int quantity;
  double price;
  Snack *left;
  Snack *right;
  vector<Snack *> snackVector;

public:
  Snack(string n = "snack", string b = "brand", int q = 1, double p = 0);
  void display();
  void addSnack(Snack *&root, const string &n, const string &b, int q,
                double p);
  void displayStackForm();
  Snack *searchSnackByName(Snack *root, const string &name);
  void editSnack(const string &name, string newBrand, int newQuantity,
                 double newPrice);
  void deleteSnack(Snack *&root, const string &name);
  Snack *findMin(Snack *root);
  ~Snack();
  string getName() const { return name; }
  string getBrand() const { return brand; }
  int getQuantity() const { return quantity; }
  double getPrice() const { return price; }
};

Snack::Snack(string n, string b, int q, double p) {
  name = n;
  brand = b;
  quantity = q;
  price = p;
  left = nullptr;
  right = nullptr;
}

void Snack::display() {
  cout << "Name     : " << name << endl;
  cout << "Brand    : " << brand << endl;
  cout << "Quantity : " << quantity << endl;
  cout << "Price    : " << price << endl;
}
void Snack::addSnack(Snack *&root, const string &n, const string &b, int q,
                     double p) {
  Snack *newSnack = new Snack(n, b, q, p);
  if (root == nullptr) {
    root = newSnack;
  } else if (newSnack->name < root->name) {
    addSnack(root->left, n, b, q, p);
  } else {
    addSnack(root->right, n, b, q, p);
  }
}

Snack *Snack::searchSnackByName(Snack *root, const string &name) {
  if (root == nullptr || root->name == name) {
    return root;
  }
  if (name < root->name) {
    return searchSnackByName(root->left, name);
  }
  return searchSnackByName(root->right, name);
}

void Snack::editSnack(const string &name, string newBrand, int newQuantity,
                      double newPrice) {
  Snack *snackToEdit = searchSnackByName(this, name);
  if (snackToEdit) {
    snackToEdit->brand = newBrand;
    snackToEdit->quantity = newQuantity;
    snackToEdit->price = newPrice;
  } else {
    cout << "Snack not found in inventory. Cannot edit.\n";
  }
}

void Snack::deleteSnack(Snack *&root, const string &name) {
  if (root == nullptr) {
    return;
  }
  if (name < root->name) {
    deleteSnack(root->left, name);
  } else if (name > root->name) {
    deleteSnack(root->right, name);
  } else {
    if (root->left == nullptr) {
      Snack *temp = root->right;
      delete root;
      root = temp;
    } else if (root->right == nullptr) {
      Snack *temp = root->left;
      delete root;
      root = temp;
    } else {
      Snack *successor = findMin(root->right);
      root->name = successor->name;
      root->brand = successor->brand;
      root->quantity = successor->quantity;
      root->price = successor->price;
      deleteSnack(root->right, successor->name);
    }
  }
}

Snack *Snack::findMin(Snack *root) {
  if (root == nullptr) {
    return nullptr;
  }
  while (root->left) {
    root = root->left;
  }
  return root;
}

void Snack::displayStackForm() {
 stack<Snack*> tempStack;
    Snack* current = this;
    while (current != nullptr || !tempStack.empty()) {
        while (current != nullptr) {
            tempStack.push(current);
            current = current->left;
        }
        current = tempStack.top();
        tempStack.pop();
        current->display();
        cout << endl;
        current = current->right; 
    }
}

Snack::~Snack() {}

#endif // SNACK_H
