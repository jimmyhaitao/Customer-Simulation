#ifndef CASHIER_LINE_H
#define CASHIER_LINE_H
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <iterator> 
#include <map> 
#include "Customers.h"
#include "Cashier.h"

using namespace std;

/**
* Cashiers_line class
* It stores a queue of Cashiers
* It also map the arrival time for Customers
*/
class Cashiers_line{
  private:
    vector<Cashiers> my_cashiers_line;
    map<int, vector<Customers> > my_map;
  public:
    Cashiers_line() { }
    Cashiers_line(int number_of_cashiers);
    //get. Declared in the header file
    vector<Cashiers> get_my_cashiers_line() {
      return my_cashiers_line;
    }
    void servicing_all();
    map<int, vector<Customers> > get_map() {
      	return this -> my_map;
    }
    void set_map(map<int, vector<Customers> > temp);
    void serving_customers(vector<Customers>& list);
    bool finished();
};

#endif
