/*
* This cpp project is to judge which day is it.
* Last revise time : 2017/05/15
*/

#include <sstream>
#include <vector>
#include <string>

using namespace std;

stringstream tt;
const int month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int which_day[7] = { 0, 1, 2, 3, 4, 5, 6 };
extern const int Sun = 0, Mon = 1, Tue = 2, Wed = 3, Thu = 4, Fri = 5, Sat = 6;

struct Date{
	int year, month, day;
};

bool isleap(int year){
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

/* 2017-6-29 */
int judgeday(string this_day){
	tt << this_day;
	char ch;
	Date today;
	tt >> today.year >> ch >> today.month >> ch >> today.day;
	int day_num = 0;
	int index = 0;
	for (int i = 1900; i < today.year; ++i){
		if (isleap(i)) ++index;
	}
	day_num += 365 * (today.year - 1900) + index;
	for (int j = 1; j < today.month; ++j){
		day_num += month_day[j - 1];
	}
	if (isleap(today.year)) ++day_num;
	day_num += today.day;

	tt.clear();
	tt.str("");
	return which_day[day_num % 7];
}