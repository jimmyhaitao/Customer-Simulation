#include "Cashier.h"
#include "Customers.h"
#include <iostream>

/**
 * Constructor
 */
void Cashiers::set_cashiers(int idx) {
	this -> idx = idx;
}

void Cashiers::push_queue(Customers res) {
	this -> last_customer = res;
	this -> myQueue.push(res);
}
void Cashiers::servicing() {
	if(this -> is_empty()) {
		return;
	}
	if(this -> get_type() == 'T' && this -> get_resting() == false) {
		resting = true;
	} else {
		myQueue.front().check_out();
		resting = false;
		if(myQueue.front().get_num_items() == 0) {
			myQueue.pop();
			if(is_empty()) {
				last_customer = Customers();
			}
		}
	}
}




