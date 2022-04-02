#pragma once
#include <iostream>

// Works according to the Bulgarian calendar from year 1 to the end of eternity :)
// Websites I used: https://www.timeanddate.com/calendar/custom.html?year=1916&country=73&cdt=1&typ=0&display=3&df=1
//					https://scienceworld.wolfram.com/astronomy/LeapYear.html#:~:text=The%20complete%20list%20of%20leap,2040%2C%202044%2C%20and%202048.

/*
	Специфики на календара:
		- от 1 до 1916 година високосни години са тези, които се делят на 4.
		- след 1916 високосни години са тези, които се делят на 4, с изключение на тези, които се делят на 100, но не се делят на 400.
			Пр. 2100, 2200, 2300, 2500 НЕ СА високосни.
				2000, 2400, 2800, 3200 СА високосни.
		- датите от 1 до 13 април 1916г. не съществуват (30 март, 31 март, 14 април, 15 април).
		- 1/1/1 е събота :)
*/



class Date
{
private:
	enum Months {
		BEG = 0,
		JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER,
		END
	};

private:
	int year;
	Months month;
	int day;
	static const int YEAR_OF_CHANGE;							// Пропускат се 13 дни. Сменя се начинът на определяне на високосни години
	static const int YEAR_OF_CHANGE_REMOVE_DAYS_COUNT;			// 1-13/april/1916 these days are missing from the calendar (13 days are skiped)
	static const Months YEAR_OF_CHANGE_REMOVE_DAYS_WHICH_MONTH;	// april/1916

public:
	Date(const int y, const int m, const int d);
	
	int getYear() const;
	int getMonth() const;
	int getDay() const;

	void setYear(const int y);
	void setMonth(const int m);
	void setDay(const int d);

	bool areDatesEqual(const Date& date) const;
	int dayOfTheWeek() const;						// Returns [1, 7]. 1-Monday, 2-Tuesday, ... , 7-Sunday
	Date whatsTheNextDate() const;

	void print() const;

private:
	bool isLeapYear() const;
	bool makeDateValid();											// If the date is invalid, corrects it to default and returns false. If valid, does not change it and returns true.
	Months convertNumberToMonth(const int num) const;
	int highestValidDayNumberInAMonth(const Date::Months&) const;	// Тази ф-я не се казва 'numberOfDaysInMonth', защото април/1916 не е имал 30 дни, а само 17 (това е единствената дата, за която ф-ята не връща правилния брой на дните от месеца)
	int howManyDaysFromBeginning() const;							// Returns the number of days since 1/1/1
};

