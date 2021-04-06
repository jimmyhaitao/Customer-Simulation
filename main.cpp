#include "Cashier.h"
#include "Cashier_line.h"
#include "Cashier_line.cpp"
#include "Customers.h"
#include <iostream>
#include <queue>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <climits>

using namespace std;
  /**
  * Main simulator class
  * private myQueue: read from the input, it should be a list of customers
  * private my_cashiers_line: read from the input, it should be a list of cashiers lining up
  * output: the total time for all the customers to finish checking out
  * timing: normal cashiers take 1 minute, training(the last one) takes 2 minutes
  * @author Jimmy Liao
  * @date Oct 20, 2019
  */
class Simulator {
  private: 
    int time;
    queue<Customers> myQueue;
    Cashiers_line my_cashiers_line;
  public:
    /**
    * default constructor
    */
    Simulator() {}
    /**
    * constructor initialize the cashiers line
    */
    Simulator(Cashiers_line my_cashiers_line) {
      this -> my_cashiers_line = my_cashiers_line;
    }
    Simulator(vector<string> input) {
      this -> my_cashiers_line = read_file(input);
      // cout << "constructor " << my_cashiers_line.get_my_cashiers_line().size() << "  " << my_cashiers_line.get_map().size() << endl;
      this -> time = time_helper(my_cashiers_line);
    }
    /**
    * get function for my_cashiers_line
    */
    Cashiers_line get_Cashiers_line() {
      return this -> my_cashiers_line;
    }
    /**
    * get function for myQueue
    */
    queue<Customers> get_my_queue() {
      return this -> myQueue;
    }
    int get_time() {
      return this -> time;
    }

    Cashiers_line read_file(vector<string> input) {
      // cout << input[0] << input[1] << input[2] << endl;
      if(is_number(input[0])) { //a single integer (number of registers)
        int num = std::stoi(input[0]);
        Cashiers_line cashiers_line(num);
        map<int, vector<Customers> > cur_map;
        for(unsigned i = 1; i < input.size(); i++) {
          Customers cur = build_customer(input[i]);
          myQueue.push(cur);
          // cout << "my customer " << cur.get_type() << " time "<< cur.get_time_arrived() << " num items "<< cur.get_num_items() << endl; 
          int idx = input[i][1] - '0'; //current time
          // map<int, vector<Customers>> cur_map = cashiers_line.get_map();
          cur_map[idx].push_back(cur);
          // cout << "map size = " << cur_map.size() << endl;
          // cout << "current time = " << idx << endl;
          // int idx = input[i][1] - '0';          
          vector<Customers> list = cur_map[input[i][1] - '0'];
          if(list.size() == 0) {
            list.push_back(cur);
            cur_map[idx] = list;
          } else {
              list.push_back(cur);
          }
        }
        cashiers_line.set_map(cur_map);
        return cashiers_line;
      } else {
        cout << "Error in the number of registers" << endl;
        exit(-1);
      }
    }
    /**
    * put all the customers that arrvie at the same time into a vector
    */
    void same_time_customers(vector<Customers> list, int time) {
      while(this -> get_my_queue().empty() && this -> get_my_queue().front().get_time_arrived() == time) {
        Customers cur = this -> get_my_queue().front();
        this -> get_my_queue().pop();
        list.push_back(cur);
        // cout << "list size = " << list.size() << " queue size = " << this -> get_my_queue().size() << endl;
      }
    }

    bool is_number(string s) {
      for(unsigned i = 0; i < s.size(); i++) {
        if(!isdigit(s[i])) {
          return false;
        }
      }
      return true;
    }

    Customers build_customer(string input) {
      // Customers(char type, int time_arrived, int num_items, bool in_service);
      if(input.size() != 3) {
        cout << "Error in input of customers" << endl;
        exit(-1);
      }
      if(input[0] == 'A' || input[0] == 'B') {
        // cout << input[0] << input[1] << input[2] << endl;
        Customers res(input[0], input[1] - '0', input[2] - '0');
        res.set_type(input[0]);
        res.set_time_arrived(input[1] - '0');
        res.set_num_items(input[2] - '0');
        // cout << "my customer " << res.get_type() << " time "<< res.get_time_arrived() << " num items "<< res.get_num_items() << " in service " << res.get_in_service() << endl; 
        return res;   
      } else {
        cout << "Customer Type not valid" << endl;
        exit(-1);
      }
    }
    /**
     * Compare
     * True if A has priority over B
     * False otherwise
     * 
     * If two or more customers arrive at the same time, those with fewer items choose registers
     * before those with more, and if they have the same number of items then type A's choose before
     * type B's.
     */
    struct compare {
      bool operator()(Customers A, Customers B) {
        if(A.get_num_items() < B.get_num_items()) {
          return true;
        } else if(A.get_num_items() > B.get_num_items()) {
          return false;
        } else { //have the same number of items
          if(A.get_type() == 'A' && B.get_type() == 'B') {
            return true;
          }
          if(A.get_type() == 'B' && B.get_type() == 'A') {
            return false;
          }
          if(A.get_type() == 'A' && B.get_type() == 'A') { 
            return true;
          }
          if(A.get_type() == 'B' && B.get_type() == 'B') {
            return true;
          }
        }
      return false;
    } 
  };

    int time_helper(Cashiers_line my_cashiers_line) {
      int time = 1;
      // int last_customer = 0;
      // if(my_cashiers_line.get_map().size() != 0) {
      //   last_customer = (--my_cashiers_line.get_map().end()) -> first;
      // }
      // cout << "last_cusotmer = " << last_customer << endl;
      while(time == 1 || my_cashiers_line.finished() == false) {
        vector<Customers>list = my_cashiers_line.get_map()[time];
        // cout << "current time = " << time << " list size = " << list.size() << endl;
        // same_time_customers(list, time); //Customer 
        if(!list.empty()) {
          sort(list.begin(), list.end(), compare());
          // cout << "first = " << list[0].get_num_items() << "second = " << list[1].get_num_items() << endl;
          my_cashiers_line.serving_customers(list);
        }
        // cout << "length of the line 1 = " << my_cashiers_line.get_my_cashiers_line()[0].get_queue_size() << my_cashiers_line.get_my_cashiers_line()[0].get_type() << endl;
        // cout << "length of the line 2 = " << my_cashiers_line.get_my_cashiers_line()[1].get_queue_size() << my_cashiers_line.get_my_cashiers_line()[1].get_type() << endl;
        my_cashiers_line.servicing_all();
        time ++;
      } //end of while
      return time;
    }
};

  int main(int agrc, char** argv) {
    ifstream file;
    file.open(argv[1]);
    string line;
    vector<string>input;
    while (getline(file, line)) {
      line.erase(remove(line.begin(), line.end(), ' '), line.end());
      input.push_back(line);
    }
    Simulator my_simulator(input);
    int total_time = my_simulator.get_time();
    cout << "Finished at: t = " << total_time << " minutes" << endl;
    return 0;
  }
