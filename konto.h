#include <iostream>
#include <string>
#pragma once

using namespace std;

class Account
{
private:
	string account_name; // nazwa konta
	string account_number; // numer konta

	bool locked = false; // czy zablokowany
	int pin; // numer PIN

	int total; // stan konta
	int limit_card; // limit wyp³at z karty
	int limit_day_transfer; // limit dzienny przelewów
public:
	string getAccountInfo();
	string getAccountNumber();

	int getPin();
	int getLimitCard();
	int getLimitDayTransfer();
	void setLimitCard(int new_limit_card);
	void setLimitDayTransfer(int new_limit_day_transfer);
	void setLock();
	bool getLock();
	void AddMoney(int money);
	void RemoveMoney(int money);
	Account(string account_name, string account_number, int total, int pin, int limit_card, int limit_day_transfer);
};

