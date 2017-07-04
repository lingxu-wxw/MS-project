#ifndef ICEBERG_H_
#define ICEBERG_H_

/*
 * This head project is designed for iceberg.
 * Last revise time : 2017/06/29
 */

#include <string>
#include <map>
#include <vector>
using namespace std;

/*
 * Error processing
 */

class Wrong1{};


/*
 * A struct to save the price and turnover
 * ---------------------------------------
 * 2017/5/10 09:00,12.93,420  price = 12.93  turnover = 420  timerange: 9:00-9:30
 */

struct Stoke{
	double price; //the average price of this time range
	double turnover; //the total turnover of this time range 
};


/* 
 * Statement of some function
 */

string judge_range(string);

void map_process(map<string, Stoke>&);

void map_ratio(map<string, Stoke>&, int);

void print_iceberg(map<string, Stoke>&, int);

void iceberg();


#endif