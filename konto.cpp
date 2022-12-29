#include "konto.h"
#include <string>

using namespace std;

// Przedstawienie danych u¿ytkownika
string Account::getAccountInfo()
{
	string info = "Imiê i nazwisko w³aœciciela konta: " + account_name +"\nNumer konta: " + account_number + "\nStan konta: " + to_string(total) + "\nLimit wyp³at z karty: " + to_string(limit_card) + "\nLimit dzienny dla przelewów: " + to_string(limit_day_transfer);
	return info;
}

// Wybranie numeru konta
string Account::getAccountNumber()
{
	return account_number;
}

// Wybranie numeru PIN
int Account::getPin()
{
	return pin;
}

// Wybranie limitu wyp³at z karty
int Account::getLimitCard()
{
	return limit_card;
}

// Wybranie dziennego limitu dla przelewów
int Account::getLimitDayTransfer()
{
	return limit_day_transfer;
}

// Ustawienie nowego limitu karty konta
void Account::setLimitCard(int new_limit_card)
{
	limit_card = new_limit_card;
}

// Ustawienie nowego dziennego limitu dla przelewów
void Account::setLimitDayTransfer(int new_limit_day_transfer)
{
	limit_day_transfer = new_limit_day_transfer;
}

// Zablokowanie karty
void Account::setLock()
{
	locked = true;
}

// Wybranie statusu blokady karty
bool Account::getLock()
{
	return locked;
}

// Dodanie pieniêdzy do konta
void Account::AddMoney(int money)
{
	total=total+money;
}

// Zwolnienie pieniêdzy z konta
void Account::RemoveMoney(int money)
{
	total=total-money;
}

Account::Account(string account_name, string account_number, int total, int pin, int limit_card, int limit_day_transfer)
{
	this->account_name = account_name;
	this->account_number = account_number;
	this->total = total;
	this->pin = pin;
	this->limit_card = limit_card;
	this->limit_day_transfer = limit_day_transfer;
}
