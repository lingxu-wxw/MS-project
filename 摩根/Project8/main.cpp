/*
* This is the main cpp.
*--------------------------------------
* Last revise time : 2017/06/29
*/

#include <iostream>
#include "Sort.h"
#include "Iceberg.h"
#include <thread>
#include <windows.h>

using namespace std;

extern void add_command();

int main(){
	try{
		thread sort_processing(sorts);
		sort_processing.join();

		thread iceberg_processing(iceberg);
		iceberg_processing.join();
		
		cout << endl;

		add_command();

		/*clock_t tm_start, tm_end;
		tm_start = float(clock()) * 1000;
		tm_end = float(clock()) * 1000;
		cout << "Consuming time: " << tm_end - tm_start << "us" << endl;*/

		//²âÊÔ
		/*string s = judge_range("09:06:00");
		string t = judge_range("17:00:00");
		cout << s <<" "<< t << endl;*/
		/*cout << judgeday("2016-6-13") << endl;*/

		std::system("pause");
		return 0;
	}
	catch (Wrong1){
		cerr << "Error!" << endl;
		std::system("pause");
		return 1;
	}
	catch (Wrong2){
		cerr << "Error!" << endl;
		std::system("pause");
		return 2;
	}
}