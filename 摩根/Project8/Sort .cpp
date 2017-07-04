/*
* This cpp is designed for sort.
* It will read the data in "order.txt" and "quote.txt"
* Homework 2 : The result of aggressive take will be written in "Aggressive_order1.txt" and so on...
* Homework 3 : The result of passive take 
	The result of book will be written in "Passive_AAPL_Ask.txt" and so on... 
	The result of exchange will be written in "Exchange_IEX.txt" and so on...
	The result of split will be written in "Aggressive_order1.txt" and so on...
*--------------------------------------
* Last revise time : 2017/06/29
*/

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include "Sort.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

/* object of struct Order*/
Order order_1, order_2, order_3, order_4, order_5;
vector<Order*> order = { &order_1, &order_2, &order_3, &order_4, &order_5 };

/* object of struct NYSE, NASDAQ, IEX*/
NYSE exchange_NYSE;
NASDAQ exchange_NASDAQ;
IEX exchange_IEX;

/* object of struct GOOG, AAPL*/
GOOG book_google;
AAPL book_apple;


/*
* void printOrder(T&, int , ofstream&)
* Write the result of order to the txt
* ------------------------------------
* Usage : printOrder(order_1,1, ost_agre1);
* sell - bid - false, buy - ask - true
*/

template<class T>
void printOrder(T &order, int num, ofstream& ost){
	/*
	 *	This is for homework 2, the result of aggressive take 
	 */
	ost << "\n" << "Order " << num << endl
		<< "Total_quantity: " << order.total_quantity << endl
		<< "Average_price: " << order.average_price << endl;

	/*
	*	This is for homework 3, the result of split
	*/
	if (order.total_quantity == order.quantity){
		ost << "Done!" << endl;
		ost << "\n" << "Do not need to split!" << endl;
	}
	else{
		/*
		* rate1 - NYSE  rate2 - NASDAQ  rate3 - IEX
		*/
		order.left_quantity = order.quantity - order.total_quantity;
		double rate1, rate2, rate3;

		if (order.symbol == "AAPL" && order.side == false){
			int book_size = book_apple.NYSE_Bid_size + book_apple.NASDAQ_Bid_size + book_apple.IEX_Bid_size;
			rate1 = double(book_apple.NYSE_Bid_size) / book_size;
			rate2 = double(book_apple.NASDAQ_Bid_size) / book_size;
			rate3 = double(book_apple.IEX_Bid_size) / book_size;
		}
		else if (order.symbol == "AAPL" && order.side == true){
			int book_size = book_apple.NYSE_Ask_size + book_apple.NASDAQ_Ask_size + book_apple.IEX_Ask_size;
			rate1 = double(book_apple.NYSE_Ask_size) / book_size;
			rate2 = double(book_apple.NASDAQ_Ask_size) / book_size;
			rate3 = double(book_apple.IEX_Ask_size) / book_size;
		}
		if (order.symbol == "GOOG" && order.side == false){
			int book_size = book_google.NYSE_Bid_size + book_google.NASDAQ_Bid_size + book_google.IEX_Bid_size;
			rate1 = double(book_google.NYSE_Bid_size) / book_size;
			rate2 = double(book_google.NASDAQ_Bid_size) / book_size;
			rate3 = double(book_google.IEX_Bid_size) / book_size;
		}
		else if (order.symbol == "GOOG" && order.side == true){
			int book_size = book_google.NYSE_Ask_size + book_google.NASDAQ_Ask_size + book_google.IEX_Ask_size;
			rate1 = double(book_google.NYSE_Ask_size) / book_size;
			rate2 = double(book_google.NASDAQ_Ask_size) / book_size;
			rate3 = double(book_google.IEX_Ask_size) / book_size;
		}
		order.split_NYSE = order.left_quantity * rate1;
		order.split_NASDAQ = order.left_quantity * rate2;
		order.split_IEX = order.left_quantity * rate3;
		ost << "\nSplit:\n" << "NYSE: " << order.split_NYSE << endl
			<< "NASDAQ: " << order.split_NASDAQ << endl
			<< "IEX: " << order.split_IEX << endl;
	}
}


/*
* void updateOrder(Order&, int, double)
* Update the order 
* ------------------------------------
* Usage : updateOrder((*order[i]),size,price);
*/

void updateOrder(Order &order, int size, double price){
	order.average_price = double(order.total_quantity*order.average_price + size*price) / (order.total_quantity + size);
	order.total_quantity += size;
}


/*
* void printExchange(T, ofstream&)
* Write the result of exchange to the txt
* ------------------------------------
* Usage : printExchange(exchange_NYSE, ost_ex_NYSE);
*/

template<class T>
void printExchange(T exchange, ofstream& ost){
	ost << "\n" << exchange.name << endl
		<< "GOOG_Bid: " << setw(8) << exchange.GOOG_Bid_price << "  " << exchange.GOOG_Bid_quantity << endl
		<< "GOOG_Ask: " << setw(8) << exchange.GOOG_Ask_price << "  " << exchange.GOOG_Ask_quantity << endl
		<< "AAPL_Bid: " << setw(8) << exchange.AAPL_Bid_price << "  " << exchange.AAPL_Bid_quantity << endl
		<< "AAPL_Ask: " << setw(8) << exchange.AAPL_Ask_price << "  " << exchange.AAPL_Ask_quantity << endl;
}


/*
* void updateExchange(T&, string, bool, double, int)
* Update the exchange
* ------------------------------------
* Usage : updateExchange(exchange_NYSE, symbol, side, price, size);
*/

template<class T>
void updateExchange(T &temp, string symbol, bool side, double price, int size){
	if (symbol == "GOOG" && side == false){
		temp.GOOG_Bid_price = (temp.GOOG_Bid_price*temp.GOOG_Bid_quantity + price*size) / (temp.GOOG_Bid_quantity + size);
		temp.GOOG_Bid_quantity += size;
	}
	else if (symbol == "GOOG" && side == true){
		temp.GOOG_Ask_price = (temp.GOOG_Ask_price*temp.GOOG_Ask_quantity + price*size) / (temp.GOOG_Ask_quantity + size);
		temp.GOOG_Ask_quantity += size;
	}
	else if (symbol == "AAPL" && side == false){
		temp.AAPL_Bid_price = (temp.AAPL_Bid_price*temp.AAPL_Bid_quantity + price*size) / (temp.AAPL_Bid_quantity + size);
		temp.AAPL_Bid_quantity += size;
	}
	else if (symbol == "AAPL" && side == true){
		temp.AAPL_Ask_price = (temp.AAPL_Ask_price*temp.AAPL_Ask_quantity + price*size) / (temp.AAPL_Ask_quantity + size);
		temp.AAPL_Ask_quantity += size;
	}
}


/*
* void printBook(T &, ofstream &, ofstream &)
* Write the result of book to the txt
* ------------------------------------
* Usage : printBook(book_apple, ost_pass_A_B, ost_pass_A_A);
*/

template<class T>
void printBook(T &book, ofstream &ost_Bid, ofstream &ost_Ask){
	ost_Bid << " " << setw(4) << book.NYSE_Bid_size << "@" << setw(6) << book.NYSE_Bid_price << "   "
		<< setw(4) << book.NASDAQ_Bid_size << "@" << setw(6) << book.NASDAQ_Bid_price << "   "
		<< setw(4) << book.IEX_Bid_size << "@" << setw(6) << book.IEX_Bid_price << "   \n";
	ost_Ask << " " << setw(4) << book.NYSE_Ask_size << "@" << setw(6) << book.NYSE_Ask_price << "¡¡ "
		<< setw(4) << book.NASDAQ_Ask_size << "@" << setw(6) << book.NASDAQ_Ask_price << "  "
		<< setw(4) << book.IEX_Ask_size << "@" << setw(6) << book.IEX_Ask_price << "  \n";
}


/*
* void updateBook(string, string, bool, int, double)
* Update the book
* ------------------------------------
* Usage : updateBook(symbol, exchange, side, size, price);
* sell - bid - false, buy - ask - true
*/

void updateBook(string symbol, string exchange, bool side, int size, double price){
	if (symbol == "GOOG"){
		if (exchange == "NYSE" && side == false) { book_google.NYSE_Bid_size = size; book_google.NYSE_Bid_price = price; }
		else if (exchange == "NYSE" && side == true) { book_google.NYSE_Ask_size = size; book_google.NYSE_Ask_price = price; }
		else if (exchange == "NASDAQ" && side == false) { book_google.NASDAQ_Bid_size = size; book_google.NASDAQ_Bid_price = price; }
		else if (exchange == "NASDAQ" && side == true) { book_google.NASDAQ_Ask_size = size; book_google.NASDAQ_Ask_price = price; }
		else if (exchange == "IEX" && side == false) { book_google.IEX_Bid_size = size; book_google.IEX_Bid_price = price; }
		else if (exchange == "IEX" && side == true) { book_google.IEX_Ask_size = size; book_google.IEX_Ask_price = price; }
		else return;
	}
	else if (symbol == "AAPL"){
		if (exchange == "NYSE" && side == false) { book_apple.NYSE_Bid_size = size; book_apple.NYSE_Bid_price = price; }
		else if (exchange == "NYSE" && side == true) { book_apple.NYSE_Ask_size = size; book_apple.NYSE_Ask_price = price; }
		else if (exchange == "NASDAQ" && side == false) { book_apple.NASDAQ_Bid_size = size; book_apple.NASDAQ_Bid_price = price; }
		else if (exchange == "NASDAQ" && side == true) { book_apple.NASDAQ_Ask_size = size; book_apple.NASDAQ_Ask_price = price; }
		else if (exchange == "IEX" && side == false) { book_apple.IEX_Bid_size = size; book_apple.IEX_Bid_price = price; }
		else if (exchange == "IEX" && side == true) { book_apple.IEX_Ask_size = size; book_apple.IEX_Ask_price = price; }
		else return;
	}
}


/*
* void add_new_order()
* Using the thread to add new order.
* ------------------------------------
* Still need tp improve.
*/

Order tmp_order;
void add_new_order(){
	clock_t tm_start, tm_end;
	tm_start = float(clock()) * 1000;

	srand(time(NULL));
	double a = rand() / double(RAND_MAX + 1);
	double t = rand() / double(RAND_MAX + 1);
	double s = rand() / double(RAND_MAX + 1);
	double u = rand() / double(RAND_MAX + 1);
	std::cout << t << endl << s << endl << u << endl;
	if (t < 0.5) tmp_order.side = true;
	else tmp_order.side = false;
	if (s < 0.5){
		tmp_order.symbol = "GOOG";
		if (tmp_order.side == true) tmp_order.price = 920 + 15 * u;
		else tmp_order.price = 910 + 15 * u;
	}
	else {
		tmp_order.symbol = "AAPL";
		if (tmp_order.side == true) tmp_order.price = 145 + 15 * u;
		else tmp_order.price = 140 + 15 * u;
	}
	tmp_order.quantity = 1000000;
	order.push_back(&tmp_order);

	tm_end = float(clock()) * 1000;
	std::cout << "thread add_order: " << "Consuming time: " << tm_end - tm_start << "us" << endl;
}


/*
* void updateBook(string, string, bool, int, double)
* Update the book
* ------------------------------------
* Usage : updateBook(symbol, exchange, side, size, price);
* sell - bid - false, buy - ask - true
*/

void sorts(){
	/* print the consuming time*/
	clock_t tm_start, tm_end;
	tm_start = float(clock()) * 1000;

	/* open the input file */
	string name_1 = "Orders.txt", name_2 = "Quotes.txt";
	ifstream ist_order(name_1.c_str()), ist_quote(name_2.c_str());
	if (!ist_order || !ist_quote) throw Wrong2();
	stringstream tt;

	/* open the output file */
	string file_agre1 = "Aggressive_order1.txt", file_agre2 = "Aggressive_order2.txt", file_agre3 = "Aggressive_order3.txt", file_agre4 = "Aggressive_order4.txt", file_agre5 = "Aggressive_order5.txt";
	string file_ex1 = "Exchange_IEX.txt", file_ex2 = "Exchange_NASDAQ.txt", file_ex3 = "Exchange_NYSE.txt";
	string file_pass1 = "Passive_AAPL_Ask.txt", file_pass2 = "Passive_AAPL_Bid.txt", file_pass3 = "Passive_GOOG_Ask.txt", file_pass4 = "Passive_GOOG_Bid.txt";

	ofstream ost_agre1(file_agre1.c_str()), ost_agre2(file_agre2.c_str()), ost_agre3(file_agre3.c_str()), ost_agre4(file_agre4.c_str()), ost_agre5(file_agre5.c_str());
	ofstream ost_ex_IEX(file_ex1.c_str()), ost_ex_NASDAQ(file_ex2.c_str()), ost_ex_NYSE(file_ex3.c_str());
	ofstream ost_pass_A_A(file_pass1.c_str()), ost_pass_A_B(file_pass2.c_str()), ost_pass_G_A(file_pass3.c_str()), ost_pass_G_B(file_pass4.c_str());

	/* write the title */
	ost_pass_A_A << "    NYSE        NASDAQ         IEX     \n";
	ost_pass_A_B << "    NYSE        NASDAQ         IEX     \n";
	ost_pass_G_A << "    NYSE        NASDAQ         IEX     \n";
	ost_pass_G_B << "    NYSE        NASDAQ         IEX     \n";

	/* read the "order.txt"*/
	/* Struct order: 
	  bool side;  string symbol; double price; int quantity; 
	  Sample order: 1,Buy,GOOG,923,1000000
	*/
	int index = 0; 
	string tmp_order = "", s;
	int n;

	while (index < 5){
		getline(ist_order, tmp_order, '\n');
		tmp_order.replace(tmp_order.find(','), 1, " ");
		tmp_order.replace(tmp_order.find(','), 1, " ");
		tmp_order.replace(tmp_order.find(','), 1, " ");
		tmp_order.replace(tmp_order.find(','), 1, " ");

		tt << tmp_order;
		tt >> n >> s >> (*order[index]).symbol >> (*order[index]).price >> (*order[index]).quantity;
		if (s == "Sell") (*order[index]).side = false;
		else if (s == "Buy") (*order[index]).side = true;

		/* clean the status and content*/
		tt.clear();
		tt.str("");
		++index;
	}

	/* read the "order.txt"*/
	/* quote: exchange,side,symbol,size,price
	 * Sample quote: NYSE,Bid,GOOG,1300,923.17
	 * sell - bid - false, buy - ask - true
	 */
	string tmp_quote, copy_quote;
	string exchange, symbol, m; 
	bool side;
	int size;
	double price;
	index = 1;
	bool getlatency = false;

	/* the latency */
	clock_t t_start, t_end;
	string tmpName = "latency.txt";
	ofstream latency(tmpName.c_str());
	bool hastofive; 

	while (getline(ist_quote, tmp_quote, '\n')){
		copy_quote = tmp_quote;
		tmp_quote.replace(tmp_quote.find(','), 1, " ");
		tmp_quote.replace(tmp_quote.find(','), 1, " ");
		tmp_quote.replace(tmp_quote.find(','), 1, " ");
		tmp_quote.replace(tmp_quote.find(','), 1, " ");
		tt << tmp_quote;
		tt >> exchange >> m >> symbol >> size >> price;
		if (m == "Bid") side = false;
		else if (m == "Ask") side = true;

		hastofive = false;

		/* processing the quote */
		/* traverse all the order to see if any one can take the quote aggressively.
			If not, update the book. 
		*/
		for (int i = 0; i < order.size(); ++i){  
			/* need to get the latency */
			if (order.size()>5) getlatency = true;

			/* If the order can be taken aggressively*/
			if (side == (*order[i]).side && symbol == (*order[i]).symbol){ 

				/* If the order is already full*/
				if ((*order[i]).total_quantity >= (*order[i]).quantity){
					continue;
				}

				/* If the order is not full now*/
				if ((*order[i]).total_quantity + size <= (*order[i]).quantity){ 

					/* If the quote meets the requirement of one order, then take it aggressively*/
					if ((side == true && price <= (*order[i]).price) || (side == false && price >= (*order[i]).price)){
						
						/* update the order */
						updateOrder((*order[i]), size, price);
						switch (i){
						case 0:ost_agre1 << copy_quote << "\n"; break;
						case 1:ost_agre2 << copy_quote << "\n"; break;
						case 2:ost_agre3 << copy_quote << "\n"; break;
						case 3:ost_agre4 << copy_quote << "\n"; break;
						case 4:ost_agre5 << copy_quote << "\n"; break;
						default: break;
						}
						
						/* update the exchange */
						if (exchange == "NYSE"){
							updateExchange(exchange_NYSE, symbol, side, price, size);
							ost_ex_NYSE << copy_quote << "\n";
						}
						if (exchange == "IEX") {
							updateExchange(exchange_IEX, symbol, side, price, size);
							ost_ex_IEX << copy_quote << "\n";
						}
						if (exchange == "NASDAQ"){
							updateExchange(exchange_NASDAQ, symbol, side, price, size);
							ost_ex_NASDAQ << copy_quote << "\n";
						}
						size = 0;
						break;
					}
				}

				/* If the order is not full, but will be full after taking this quote*/
				else{ 

					/* If the quote meets the requirement of one order, then take part of it aggressively to make the order full*/
					if ((side == true && price <= (*order[i]).price) || (side == false && price >= (*order[i]).price)){
						int rest_quantity = (*order[i]).quantity - (*order[i]).total_quantity;

						/* update the order*/
						updateOrder((*order[i]), rest_quantity, price);

						/* update the exchange */
						if (exchange == "NYSE") updateExchange(exchange_NYSE, symbol, side, price, rest_quantity);
						if (exchange == "IEX") updateExchange(exchange_IEX, symbol, side, price, rest_quantity);
						if (exchange == "NASDAQ") updateExchange(exchange_NASDAQ, symbol, side, price, rest_quantity);

						/* This quote still has some size */
						size = size - rest_quantity;
					}
				}
			}
		}

		/* If the quote hasn't been taken or has been taken part, then update the book*/
		if (size != 0) updateBook(symbol, exchange, side, size, price);

		/* print the current book to the txt*/
		printBook(book_apple, ost_pass_A_B, ost_pass_A_A);
		printBook(book_google, ost_pass_G_B, ost_pass_G_A);

		/* clean the status and content*/
		tt.clear();
		tt.str("");
		++index;
	}

	/* print the exchange data to the txt*/
	printExchange(exchange_NYSE, ost_ex_NYSE);
	printExchange(exchange_IEX, ost_ex_IEX);
	printExchange(exchange_NASDAQ, ost_ex_NASDAQ);

	/* print the order data to the txt*/
	printOrder(order_1, 1, ost_agre1);
	printOrder(order_2, 2, ost_agre2);
	printOrder(order_3, 3, ost_agre3);
	printOrder(order_4, 4, ost_agre4);
	printOrder(order_5, 5, ost_agre5);

	/* close the ofstream*/
	ost_agre1.close(); ost_agre2.close(); ost_agre3.close(); ost_agre4.close(); ost_agre5.close();
	ost_ex_IEX.close(); ost_ex_NASDAQ.close(); ost_ex_NYSE.close();
	ost_pass_A_A.close(); ost_pass_A_B.close(); ost_pass_G_A.close(); ost_pass_G_B.close();

	/* print the consuming time of this thread*/
	isfinish = true;
	tm_end = float(clock()) * 1000;
	std::cout << "thread sort_processing: " << "Consuming time: " << tm_end - tm_start << "us" << endl;
}