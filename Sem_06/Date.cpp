#include "Date.h"

const int Date::YEAR_OF_CHANGE{ 1916 };
const int Date::YEAR_OF_CHANGE_REMOVE_DAYS_COUNT{ 13 };
const Date::Months Date::YEAR_OF_CHANGE_REMOVE_DAYS_WHICH_MONTH{ APRIL };


//PUBLIC---------------------------------------------------------------------------------------------

Date::Date(const int y, const int m, const int d) {
	year = y;
	month = convertNumberToMonth(m);
	day = d;
	makeDateValid();
}

int Date::getYear() const  { return year; }
int Date::getMonth() const { return month; }
int Date::getDay() const   { return day; }

void Date::setYear(const int y) {
	year = y;
	makeDateValid();
}
void Date::setMonth(const int m) {
	month = convertNumberToMonth(m);
	makeDateValid();
}
void Date::setDay(const int d) {
	day = d;
	makeDateValid();
}

bool Date::areDatesEqual(const Date& date) const{
	if (year == date.getYear() && month == date.getMonth() && day == date.getDay())
		return true;
	else
		return false;
}

int Date::dayOfTheWeek() const {
	int dayCount = howManyDaysFromBeginning();

	// 1/1/1 is a Saturday
	return (dayCount + 4) % 7 + 1;
}

Date Date::whatsTheNextDate() const {
	Date nextDate = *this;

	++nextDate.day;

	// If the previous date is 1916/03/31
	if (nextDate.year == YEAR_OF_CHANGE && nextDate.day > highestValidDayNumberInAMonth(MARCH) && nextDate.month == MARCH) {
		nextDate.month = YEAR_OF_CHANGE_REMOVE_DAYS_WHICH_MONTH;
		nextDate.day = YEAR_OF_CHANGE_REMOVE_DAYS_COUNT + 1;
		return nextDate;
	}


	if (nextDate.day > highestValidDayNumberInAMonth(nextDate.month)) {
		nextDate.month = convertNumberToMonth(nextDate.month + 1);
		nextDate.day = 1;
		
		if (nextDate.month == JANUARY)
			++nextDate.year;
	}

	return nextDate;
}

void Date::print() const {
	std::cout << std::endl << "year/month/day\n"
		<< year << "/" << month << "/" << day << std::endl;
}

//PRIVATE--------------------------------------------------------------------------------------------

bool Date::isLeapYear() const {
	// Years before 'YEAR_OF_CHANGE'
	if (year <= YEAR_OF_CHANGE) {
		if (year % 4 == 0)
			return true;
		else
			return false;
	}

	// Years after 'YEAR_OF_CHANGE'
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return true;
	else
		return false;
}

bool Date::makeDateValid() {
	bool isValid = true;

	// Validate days
	if (day < 1 || highestValidDayNumberInAMonth(month) < day) {
		day = 1;			// тук малко радикално го слагам да е първи ден при всички положения. Сигурно по-културно може да се измисли.
		isValid = false;
	}

	// Account for 1-13/april/1916
	if (year == YEAR_OF_CHANGE && month == YEAR_OF_CHANGE_REMOVE_DAYS_WHICH_MONTH && day <= YEAR_OF_CHANGE_REMOVE_DAYS_COUNT) {
		day = YEAR_OF_CHANGE_REMOVE_DAYS_COUNT + 1;
		isValid = false;
	}

	return isValid;
}

Date::Months Date::convertNumberToMonth(const int num) const {
	switch (num) {
	case JANUARY:	return JANUARY;
	case FEBRUARY:	return FEBRUARY;
	case MARCH:		return MARCH;
	case APRIL:		return APRIL;
	case MAY:		return MAY;
	case JUNE:		return JUNE;
	case JULY:		return JULY;
	case AUGUST:	return AUGUST;
	case SEPTEMBER: return SEPTEMBER;
	case OCTOBER:	return OCTOBER;
	case NOVEMBER:	return NOVEMBER;
	case DECEMBER:	return DECEMBER;
	default:
		return JANUARY;		// if 'num' is not 1-12, set to january
	}
}

int Date::highestValidDayNumberInAMonth(const Date::Months& monthToCheck) const {
	switch (monthToCheck) {
	case JANUARY:	return 31;
	case MARCH:		return 31;
	case MAY:		return 31;
	case JULY:		return 31;
	case AUGUST:	return 31;
	case OCTOBER:	return 31;
	case DECEMBER:	return 31;

	case APRIL:		return 30;
	case JUNE:		return 30;
	case SEPTEMBER: return 30;
	case NOVEMBER:	return 30;

	case FEBRUARY:
		if (isLeapYear())
			return 29;
		else
			return 28;
	}
}

int Date::howManyDaysFromBeginning() const {
	int dayCount = 0;
	int finY = year - 1;	// completely finished years

	// Count the days in the completely finished years
	if (finY < YEAR_OF_CHANGE)
		dayCount = finY * 365 + finY / 4;
	else {
		dayCount = finY * 365 + finY / 4 - finY / 100 + finY / 400 + YEAR_OF_CHANGE / 100 - YEAR_OF_CHANGE / 400 - YEAR_OF_CHANGE_REMOVE_DAYS_COUNT;
		/*
			dayCount  = finY * 365									// days without accounting for leap years
			dayCount += finY / 4 - finY / 100 + finY / 400			// there is a leap year every year divisible by four except for years which are both divisible by 100 and not divisible by 400 (this rule is true after year 1916)
			dayCount += YEAR_OF_CHANGE / 100 - YEAR_OF_CHANGE / 400 // from year 1 to 1916 leap year was every year divisible by four. Add the missing leap days excluded from the above statement
			dayCount -= YEAR_OF_CHANGE_REMOVE_DAYS_COUNT			// 1-13/april/1916 do not exist. Remove them
		*/
	}
		
	// Count the days in the ramaining months
	if (year == YEAR_OF_CHANGE && month >= YEAR_OF_CHANGE_REMOVE_DAYS_WHICH_MONTH)
		dayCount -= YEAR_OF_CHANGE_REMOVE_DAYS_COUNT;

	for (int i = JANUARY; i < month; ++i)
		dayCount += highestValidDayNumberInAMonth(convertNumberToMonth(i));		// тука май стана малко тромаво
	
	dayCount += day;

	return dayCount;
}
