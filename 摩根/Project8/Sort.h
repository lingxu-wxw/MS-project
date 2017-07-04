#pragma once

#ifndef SORT_H_
#define SORT_H_

/*
* This head project is designed for sort.
* Last revise time : 2017/06/29
*/

#include <string>
#include <vector>

using namespace std;

/*
* Error processing
*/

class Wrong2{};


/*
 * A struct to save the data of an order
 * Sample order : 1,Buy,GOOG,923,1000000
 * ---------------------------------------
 * sell - bid - false
 * buy - ask - true
 */

struct Order{
	/* for the sample order: 
	  side = true , symbol = "GOOG" , price = 923 , quantity = 1000000*/
	bool side; 
	string symbol;
	double price;
	int quantity;

	/* total_quantity : the quantity that has been met
	  average price : the average price of the met quantity
	  lest quantity : the quantity that has not been met
	  split : the stoke number put in the different exchanges*/
	int total_quantity;
	double average_price;
	int left_quantity;
	int split_NYSE;
	int split_NASDAQ;
	int split_IEX;

	/* Initialize */
	Order() :total_quantity(0), average_price(0), left_quantity(0), split_NYSE(0), split_NASDAQ(0), split_IEX(0) {}
};

/* object of struct Order*/
extern Order order_1, order_2, order_3, order_4, order_5;


/*
* A struct to save the data of an exchange
* Sample quote : NYSE,Bid,GOOG,1300,923.17
* ---------------------------------------
* It will be saved in struct NYSE
* GOOG_Bid_quantity = 1300  GOOG_Bid_price = 923.17
*/

struct NYSE{
	int GOOG_Bid_quantity; double GOOG_Bid_price;  int GOOG_Ask_quantity; double GOOG_Ask_price;
	int AAPL_Bid_quantity; double AAPL_Bid_price;  int AAPL_Ask_quantity; double AAPL_Ask_price;
	string name = "NYSE";
	NYSE(){}
};
struct NASDAQ{
	int GOOG_Bid_quantity; double GOOG_Bid_price;  int GOOG_Ask_quantity; double GOOG_Ask_price;
	int AAPL_Bid_quantity; double AAPL_Bid_price;  int AAPL_Ask_quantity; double AAPL_Ask_price;
	string name = "NASDAQ";
	NASDAQ(){}
};
struct IEX{
	int GOOG_Bid_quantity; double GOOG_Bid_price;  int GOOG_Ask_quantity; double GOOG_Ask_price;
	int AAPL_Bid_quantity; double AAPL_Bid_price;  int AAPL_Ask_quantity; double AAPL_Ask_price;
	string name = "IEX";
	IEX(){}
};

/* object of struct NYSE, NASDAQ, IEX*/
extern NYSE exchange_NYSE;
extern NASDAQ exchange_NASDAQ;
extern IEX exchange_IEX;


/*
* A struct to save the current level-1 book of different symbol 
* Sample quote : NYSE,Bid,GOOG,1300,923.17
* ---------------------------------------
* If this quote can met none of the order, it will be saved in the book 
* The book will be updated when a new quote needs to save
* e.g. The sample quote will be saved in struct GOOG
* NYSE_Bid_size = 1300  NYSE_Bid_price = 923.17
*/

struct GOOG{
	int NYSE_Bid_size = 0; double NYSE_Bid_price = 0;  int NYSE_Ask_size = 0; double NYSE_Ask_price = 0;
	int NASDAQ_Bid_size = 0; double NASDAQ_Bid_price = 0;  int NASDAQ_Ask_size = 0; double NASDAQ_Ask_price = 0;
	int IEX_Bid_size = 0; double IEX_Bid_price = 0;  int IEX_Ask_size = 0; double IEX_Ask_price = 0;
	string name = "GOOG";
	GOOG(){}
};
struct AAPL{
	int NYSE_Bid_size = 0; double NYSE_Bid_price = 0;  int NYSE_Ask_size = 0; double NYSE_Ask_price = 0;
	int NASDAQ_Bid_size = 0; double NASDAQ_Bid_price = 0;  int NASDAQ_Ask_size = 0; double NASDAQ_Ask_price = 0;
	int IEX_Bid_size = 0; double IEX_Bid_price = 0;  int IEX_Ask_size = 0; double IEX_Ask_price = 0;
	string name = "AAPL";
	AAPL(){}
};

/* object of struct GOOG, AAPL*/
extern GOOG book_google;
extern AAPL book_apple;


/*
 * Statement of some function
 */

template<class T>
void printOrder(T&, int, ofstream&);

void updateOrder(Order&, int, double);

template<class T>
void printExchange(T, ofstream&);

template<class T>
void updateExchange(T&, string, bool, double, int);

template<class T>
void printBook(T&, ofstream&, ofstream&);

void updateBook(string, string, bool, int, double);

void add_new_order();

static bool isfinish = false;

void sorts();


#endif