#include "Cashier.h"
#include "Cashier.cpp"
#include "Customers.h"
#include "Cashier_line.h"
#include <iostream>
// #include <cmath>
// #include <climits>
// #include <unordered_map>
// #include <iterator> 
// #include <map>
// #include <algorithm>
/**
 * Constructor
 */
Cashiers_line::Cashiers_line(int number_of_cashiers) {
	for(int i = 1; i <= number_of_cashiers; i++) {
		if(i == number_of_cashiers) { //trainee
			Cashiers temp(i, 'T');
			this -> my_cashiers_line.push_back(temp);
			break;
		}
		Cashiers temp(i, 'R');
		this -> my_cashiers_line.push_back(temp);
	}
}

void Cashiers_line::set_map(map<int, vector<Customers> > temp) {
	this -> my_map = temp;
}

void Cashiers_line::servicing_all() {
	for(unsigned i = 0; i < my_cashiers_line.size(); i++) {
		my_cashiers_line[i].servicing();
	}
}

void Cashiers_line::serving_customers(vector<Customers>& list) {
	// cout << "list size = " << my_customer_list.size() << endl;
		// Customers res = my_customer_list[i];
		// cout << "my customer " << res.get_type() << " time "<< res.get_time_arrived() << " num items "<< res.get_num_items() << " in service " << res.get_in_service() << endl; 
	for(unsigned i = 0; i < list.size(); i++) {
		// cout << "list size = " << list.size() << endl;
		int res = 0;
		if(list[i].get_type() == 'A') { // type A
			int curMin = my_cashiers_line[res].get_queue_size();
			for(unsigned j = 0; j < my_cashiers_line.size(); j++) {
				int temp = my_cashiers_line[j].get_queue_size();
				if(temp < curMin) { //update
					res = j;
					curMin = temp;
				} else if(temp == curMin && my_cashiers_line[j].get_idx() < my_cashiers_line[res].get_idx()){
					res = j;
				}
			}
			// Cashiers shorest;
			// shorest = get_shorest_line(my_cashiers_line);
			// my_cashiers_line[0].push_queue(this);
			// cout << " type A queue size = " << my_cashiers_line[0].get_myQueue().size() << endl;
		} 
		if(list[i].get_type() == 'B') { //type B
			// int last;
			int curMin2 = my_cashiers_line[res].get_last_customer().get_num_items();
			for(unsigned k = 0; k < my_cashiers_line.size(); k++) {
				if(my_cashiers_line[k].is_empty()) { //update
					res = k;
					break;
				} else if(my_cashiers_line[k].get_last_customer().get_num_items() < curMin2){
					curMin2 = my_cashiers_line[k].get_last_customer().get_num_items();
					res = k;
				}
			}
			// int last = get_fewest_last_line(my_cashiers_line);
			// my_cashiers_line[last].push_queue(this);
			// cout << " type B queue size = " << my_cashiers_line[last].get_myQueue().size() << endl;
		}
		my_cashiers_line[res].push_queue(list[i]);
		// cout << "my queue size = " << my_cashiers_line[res].get_queue_size() << endl;
	}
	// my_cashiers_line[0].push_queue(list[0]);
}

/**
 * check if the simulation is finished or not
 * return true if it is
 * return false if it is still in operation
 */
bool Cashiers_line::finished() {
	for(unsigned i = 0; i < my_cashiers_line.size(); i++) {
		if(!my_cashiers_line[i].is_empty()) {
			return false;
		}
	}
	return true;
}

// int main() {
// 	cout << "hello world. My cashier_line" << endl;
// 	return 0;
// }


