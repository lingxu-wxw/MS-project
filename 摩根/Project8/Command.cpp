/*
* This is the command cpp.
*--------------------------------------
* Last revise time : 2017/06/29
*/

#include <iostream>
#include "Sort.h"
#include "Iceberg.h"
#include <ctime>

using namespace std;

extern int judgeday(string);
extern map<string, Stoke> stoke_Mon, stoke_Tue, stoke_Wed, stoke_Thu, stoke_Fri, stoke_Sat, stoke_Sun, stoke_map;
extern double stoke_ratio[8][14]; //map,mon,tue,wed,thu,fri,sat,sun  6*14

void usingIceberg();

/*
 * Print the command on the screen and let the user choose 
 */

void add_command(){
	std::cout << "0 - Quit.\n"
		<< "1 - Display the status of order 1.\n"
		<< "2 - Display the status of order 2.\n"
		<< "3 - Display the status of order 3.\n"
		<< "4 - Display the status of order 4.\n"
		<< "5 - Display the status of order 5.\n"
		<< "6 - Display the level-1 book of AAPL_Ask.\n"
		<< "7 - Display the level-1 book of AAPL_Bid.\n"
		<< "8 - Display the level-1 book of GOOG_Ask.\n"
		<< "9 - Display the level-1 book of GOOG_Bid.\n"
		<< "10 - Display the history turnover data.\n"
		<< "11 - Display the history turnover data of Monday.\n"
		<< "12 - Display the history turnover data of Tuesday.\n"
		<< "13 - Display the history turnover data of Wednesday.\n"
		<< "14 - Display the history turnover data of Thursday.\n"
		<< "15 - Display the history turnover data of Friday.\n"
		<< "16 - Display the history turnover data of Saturday.\n"
		<< "17 - Display the history turnover data of Sunday.\n"
		<< "18 - Give a great amount of stokes and split it by using Iceberg;\n\n";

	int index = -1;

	while (index != 0){
		std::cout << "Command ";
		cin >> index;
		switch (index){
		case 0: std::cout << "Quit.\n\n"; goto END; break;
		case 1: std::cout << "Order 1 takes " << order_1.total_quantity << " stoke at an average price of " << order_1.average_price << ". \n"
			<< "This order is done and does not need to split!\n\n";
			break;
		case 2: std::cout << "Order 2 takes " << order_2.total_quantity << " stoke at an average price of " << order_2.average_price << ". \n"
			<< "This order will split " << order_2.split_NYSE << " stoke to NYSE, " << order_2.split_NASDAQ << " stoke to NASDAQ and " << order_2.split_IEX << " stoke to IEX\n\n";
			break;
		case 3: std::cout << "Order 3 takes " << order_3.total_quantity << " stoke at an average price of " << order_3.average_price << ". \n"
			<< "This order is done and does not need to split!\n\n";
			break;
		case 4: std::cout << "Order 4 takes " << order_4.total_quantity << " stoke at an average price of " << order_4.average_price << ". \n"
			<< "This order will split " << order_4.split_NYSE << " stoke to NYSE, " << order_4.split_NASDAQ << " stoke to NASDAQ and " << order_4.split_IEX << " stoke to IEX\n\n";
			break;
		case 5: std::cout << "Order 5 takes " << order_5.total_quantity << " stoke at an average price of " << order_5.average_price << ". \n"
			<< "This order will split " << order_5.split_NYSE << " stoke to NYSE, " << order_5.split_NASDAQ << " stoke to NASDAQ and " << order_5.split_IEX << " stoke to IEX\n\n";
			break;
		case 6: std::cout << "The level-1 book of AAPL_Ask:\n"
			<< "NYSE: " << book_apple.NYSE_Ask_size << "@" << book_apple.NYSE_Ask_price << "   "
			<< "NASDAQ: " << book_apple.NASDAQ_Ask_size << "@" << book_apple.NASDAQ_Ask_price << "   "
			<< "IEX: " << book_apple.IEX_Ask_size << "@" << book_apple.IEX_Ask_price << "  \n\n";
			break;
		case 7: std::cout << "The level-1 book of AAPL_Bid:\n"
			<< "NYSE: " << book_apple.NYSE_Bid_size << "@" << book_apple.NYSE_Bid_price << "    "
			<< "NASDAQ: " << book_apple.NASDAQ_Bid_size << "@" << book_apple.NASDAQ_Bid_price << "    "
			<< "IEX: " << book_apple.IEX_Bid_size << "@" << book_apple.IEX_Bid_price << "   \n\n";
			break;
		case 8: std::cout << "The level-1 book of GOOG_Ask:\n"
			<< "NYSE: " << book_google.NYSE_Ask_size << "@" << book_google.NYSE_Ask_price << "   "
			<< "NASDAQ: " << book_google.NASDAQ_Ask_size << "@" << book_google.NASDAQ_Ask_price << "   "
			<< "IEX: " << book_google.IEX_Ask_size << "@" << book_google.IEX_Ask_price << "  \n\n";
			break;
		case 9: std::cout << "The level-1 book of GOOG_Bid:\n"
			<< "NYSE: " << book_google.NYSE_Bid_size << "@" << book_google.NYSE_Bid_price << "    "
			<< "NASDAQ: " << book_google.NASDAQ_Bid_size << "@" << book_google.NASDAQ_Bid_price << "    "
			<< "IEX: " << book_google.IEX_Bid_size << "@" << book_google.IEX_Bid_price << "   \n\n";
			break;
		case 10: std::cout << "The history turnover data is displayed.\n";
			print_iceberg(stoke_map, 0);
			break;
		case 11: std::cout << "The history turnover data of Monday is displayed.\n";
			print_iceberg(stoke_Mon, 1);
			break;
		case 12: std::cout << "The history turnover data of Tuesday is displayed.\n";
			print_iceberg(stoke_Tue, 2);
			break;
		case 13: std::cout << "The history turnover data of Wednesday is displayed.\n";
			print_iceberg(stoke_Wed, 3);
			break;
		case 14: std::cout << "The history turnover data of Thursday is displayed.\n";
			print_iceberg(stoke_Thu, 4);
			break;
		case 15: std::cout << "The history turnover data of Friday is displayed.\n";
			print_iceberg(stoke_Fri, 5);
			break;
		case 16: std::cout << "The history turnover data of Saturday is displayed.\n";
			print_iceberg(stoke_Sat, 6);
			break;
		case 17: std::cout << "The history turnover data of Sunday is displayed.\n";
			print_iceberg(stoke_Sun, 7);
			break;
		case 18:
			usingIceberg();
			break;
		default:
			std::cout << "Please enter the command between 0 to 15.\n";
			break;
		}
	}
END:;
}

void usingIceberg(){

}