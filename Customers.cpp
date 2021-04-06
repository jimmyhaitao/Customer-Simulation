#include "Customers.h"
#include <iostream>

/**
 * Constructor
 */
Customers::Customers(char type, int time_arrived, int num_items) {
	set_customers(type, time_arrived, num_items);
}

void Customers::set_customers(char type, int time_arrived, int num_items) {
	type = type;
    time_arrived = time_arrived;
    num_items = num_items;
}

void Customers::check_out() {
	this -> set_num_items(this -> num_items - 1);
}

void Customers::set_type(char type) {
	this -> type = type;
}

void Customers::set_time_arrived(int time_arrived) {
	this -> time_arrived = time_arrived;
}

void Customers::set_num_items(int num_items) {
	this -> num_items = num_items;
}



