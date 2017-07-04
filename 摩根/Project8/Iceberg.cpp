/*
 * This cpp is designed for iceberg.
 * It will read the data in "iceberg.txt" and write the result to "iceberg_output.txt"
 * Last revise time : 2017/06/29
 */


#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include "Iceberg.h"
#include <ctime>

using namespace std;

/*
* extern statement
*/

extern int judgeday(string);

/*
* Time range table
*/

vector<string> time_range = { "09:00", "09:30", "10:00", "10:30", "11:00", "11:30", "12:00",
"12:30", "13:00", "13:30", "14:00", "14:30", "15:00", "15:30" };
const int time_len = time_range.size();  //14


/*
* Some maps to save the time range and the Stoke.
*/

map<string, Stoke> stoke_map;
map<string, Stoke> stoke_Mon, stoke_Tue, stoke_Wed, stoke_Thu, stoke_Fri, stoke_Sat, stoke_Sun;
map<string, Stoke> stoke_temp;
vector<map<string, Stoke>*> stoke = { &stoke_map, &stoke_Mon, &stoke_Tue, &stoke_Wed, &stoke_Thu, &stoke_Fri, &stoke_Sat, &stoke_Sun };
double stoke_ratio[8][14]; //map,mon,tue,wed,thu,fri,sat,sun  6*14


/*
*  string judge_range(string)
*	Judge the time range
* ----------------------
*  Usage : tmpTime = judge_range(time);
*/

string judge_range(string time){
	int index = 0;
	for (int i = 0; i < time_len; ++i){
		if (time == time_range[i]) return time_range[i];
		for (int j = 0; j < 5; ++j){
			if (time[j] > time_range[i][j]) {
				index = 1; break;
			}
			else if (time[j] < time_range[i][j]){
				if (index == 1){ return time_range[i - 1]; }
			}
		}
	}
	return time_range[13];
}


/*
* void map_process(map<string, Stoke>)
* update the price and turnover of the stoke in one specify time range
* ------------------------------------
* Usage : map_processing(Stoke)
*/

void map_process(map<string, Stoke> &temp){
	for (int i = 0; i < time_len; ++i){
		temp[time_range[i]].price = (temp[time_range[i]].price * temp[time_range[i]].turnover
			+ stoke_temp[time_range[i]].price * stoke_temp[time_range[i]].turnover)
			/ (temp[time_range[i]].turnover + stoke_temp[time_range[i]].turnover);
		temp[time_range[i]].turnover += stoke_temp[time_range[i]].turnover;
	}
}


/*
* void map_ratio(map<string, Stoke>, int)
* update the ratio of different time range
* ----------------------------------------
* Usage : map_ratio(Stoke, 0);
*/

void map_ratio(map<string, Stoke> &temp, int num){
	int total = 0;
	for (int i = 0; i < time_len; ++i){
		total += temp[time_range[i]].turnover;
	}
	for (int j = 0; j < time_len; ++j){
		stoke_ratio[num][j] = temp[time_range[j]].turnover / total;
	}
}


/*
* void print_iceberg(map<string, Stoke>, int)
* Print the stoke data on the screen 
* ------------------------------------
* Usage : print_iceberg(stoke_map, 0);
*/

void print_iceberg(map<string, Stoke> &stoke, int num){
	vector<string> tmp = { "Total", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
	std::cout << tmp[num] << endl;
	for (int i = 0; i < time_len; ++i){
		if (i == time_len - 1)
			std::cout << time_range[i] << "-16:00" << endl;
		else std::cout << time_range[i] << "-" << time_range[i + 1] << endl;
		std::cout << "Average price: " << stoke[time_range[i]].price << "\t"
			<< "Total_quantity: " << stoke[time_range[i]].turnover << "\t"
			<< stoke_ratio[num][i] << "%" << endl;
	}
	std::cout << endl;
}


/*
 * void iceberg()
 * Read the data from "iceberg.txt" and process
 * Write the result to "iceberg_ouput.txt"
 * ------------------------------------
 * Usage : iceberg()
 * Read : iceberg.txt
 * Write : iceberg_output.txt
 */

void iceberg(){
	/* print the consuming time*/
	clock_t tm_start, tm_end;
	tm_start = float(clock()) * 1000;

	/* open the file */
	string name_in = "iceberg.txt";
	ifstream ist(name_in.c_str());
	if (!ist) throw Wrong1();

	/* Sample order: 2017/5/10 09:00,12.93,420 */
	stringstream ss;
	string order, date, time; //the total order, date, and time 
	double sell_price; //the price of this order
	int sell_number; //the turnover of this order

	/* Initialize the map */
	for (int i = 0; i < time_len; ++i){	
		stoke_map[time_range[i]] = { 0, 0 }; stoke_Mon[time_range[i]] = { 0, 0 };
		stoke_Tue[time_range[i]] = { 0, 0 }; stoke_Wed[time_range[i]] = { 0, 0 };
		stoke_Thu[time_range[i]] = { 0, 0 }; stoke_Fri[time_range[i]] = { 0, 0 };
		stoke_Sat[time_range[i]] = { 0, 0 }; stoke_Sun[time_range[i]] = { 0, 0 };
		stoke_temp[time_range[i]] = { 0, 0 };
	}

	/* temp_sellnum, amount : the stoke number, turnover amount of last order*/
	/* temp_turnover : the stoke number of last time range */
	/* temp_time : the time range the last order belong to */
	/* temp_day : which day is the last day*/
	double temp_sellnum = 0, amount = 0, temp_turnover = 0; 
	string temp_time = "09:00"; //上一行所属的时间段
	int temp_day;

	/* read the data*/
	while (getline(ist, order, '\n')){

		/* while one day finished*/
		if (order[0] == '*'){
			/* empty the data and start a new day*/
			temp_sellnum = 0; amount = 0; temp_turnover = 0;
			temp_time = "09:00";
			switch (temp_day){
			case 1: {map_process(stoke_Mon); break; }
			case 2: {map_process(stoke_Tue); break; }
			case 3: {map_process(stoke_Wed); break; }
			case 4: {map_process(stoke_Thu); break; }
			case 5: {map_process(stoke_Fri); break; }
			case 6: {map_process(stoke_Sat); break; }
			case 0: {map_process(stoke_Sun); break; }
			default: {throw Wrong1(); break; }
			}
			map_process(stoke_map);
			for (int i = 0; i < time_len; ++i){
				stoke_temp[time_range[i]] = { 0, 0 };
			}
			continue;
		}

		/* replace the "," to " " in order to use the sstream */
		order.replace(order.find(','), 1, " ");
		order.replace(order.find(','), 1, " ");
		ss << order;
		ss >> date >> time >> sell_price >> sell_number;

		/* the current time is different from the time range */
		if (judge_range(time) != temp_time){
			amount = 0;
			temp_turnover += stoke_temp[temp_time].turnover; 
		}

		/* update the data */
		amount += (sell_number - temp_sellnum)*sell_price; 
		stoke_temp[judge_range(time)].price = amount / (sell_number - temp_turnover);
		stoke_temp[judge_range(time)].turnover += sell_number - temp_sellnum;

		temp_sellnum = sell_number;
		temp_time = judge_range(time);
		temp_day = judgeday(date);

		/* clean the status and content*/
		ss.clear();  
		ss.str("");  
	}
	
	/* caculate the ratio */
	map_ratio(stoke_map, 0);
	map_ratio(stoke_Mon, 1);
	map_ratio(stoke_Tue, 2);
	map_ratio(stoke_Wed, 3);
	map_ratio(stoke_Thu, 4);
	map_ratio(stoke_Fri, 5);
	map_ratio(stoke_Sat, 6);
	map_ratio(stoke_Sun, 7);

	/* output the result to the txt*/
	/* Sample output: 
	 * 09:00-09:30
	 * Average price: 12.464	Total_quantity: 47640	0.0672274%
	 */
	string name = "icebreg_output.txt";
	ofstream os(name.c_str());
	if (!os) throw Wrong1();

	for (int num = 0; num <= 7; ++num){
		vector<string> tmp = { "Total", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
		os << tmp[num] << endl;
		for (int i = 0; i < time_len; ++i){
			if (i == time_len - 1)
				os << time_range[i] << "-16:00" << endl;
			else os << time_range[i] << "-" << time_range[i + 1] << endl;
			os << "Average price: " << (*stoke[num])[time_range[i]].price << "\t"
				<< "Total_quantity: " << (*stoke[num])[time_range[i]].turnover << "\t"
				<< stoke_ratio[num][i] << "%" << endl;
		}
		os << endl;
	}

	/* close the ostream*/
	os.close();

	/* output the consuming time in this thread*/
	tm_end = float(clock()) * 1000;
	std::cout << "thread icebreg_processing: " << "Consuming time: " << tm_end - tm_start << "us" << endl;
}