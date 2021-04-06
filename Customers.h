#ifndef CUSTOMERS_H
#define CUSTOMERS_H
#include <iostream>
using namespace std;

/**
* Customer class
* It stores customer's information
*/
class Customers{
  private:
    char type;
    int time_arrived;
    int num_items;

  public:
    Customers(char type, int time_arrived, int num_items);
    Customers() {}
    //get. Declared in the header file
    char get_type() {
      return type;
    }
    int get_time_arrived() {
      return time_arrived;
    }
    int get_num_items() {
      return num_items;
    }

    //set. Should be in the cpp file
    void check_out();
    void set_customers(char type, int time_arrived, int num_items);
    void set_type(char type);
    void set_time_arrived(int time_arrived);
    void set_num_items(int num_items);
};

#endif
