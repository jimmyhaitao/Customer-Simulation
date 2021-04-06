#ifndef CASHIER_H
#define CASHIER_H
#include <iostream>
#include <queue>
#include "Customers.h"
#include "Customers.cpp"

using namespace std;

/**
* Cashiers class
* It stores a single Cashiers's information
*/
class Cashiers{
  private:
    queue<Customers> myQueue;
    Customers last_customer;
    int idx;
    char type;
    bool resting;
  public:
    Cashiers(int idx, char type) {
      this -> idx = idx;
      this -> type = type;
    }
    //get. Declared in the header file
    queue<Customers> get_myQueue() {
      return myQueue;
    }
    Customers get_last_customer() {
      return this -> last_customer;
    }
    int get_queue_size() {
      return this -> myQueue.size();
    }
    bool is_empty() {
      return this -> myQueue.empty();
    }
    bool get_resting() {
      return this -> resting;
    }
    char get_type() {
      return this -> type;
    }
    int get_idx() {
      return idx;
    }
    //set. Should be in the cpp file
    void set_cashiers(int idx);
    void push_queue(Customers res);
    void servicing();
    void serving_customers(vector<Cashiers> my_cashiers_line);
};

#endif
