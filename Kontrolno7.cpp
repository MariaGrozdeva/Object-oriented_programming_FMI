#include <iostream>

class Time
{
public:
	Time();
	Time(size_t h, size_t m, size_t s);
	~Time();
	int compare()const;
	Time getToMidnight() const;
	bool isDinnerTime() const;
	bool isPartyTime()const;
	void print(bool is12hoursClock) const;

private:
	size_t hours;
	size_t minutes;
	size_t seconds;

};

Time::Time()
{
	hours = 0;
	minutes = 0;
	seconds = 0;
}
Time::Time(size_t h, size_t m, size_t s)
{
	if (s > 59)
		m += s / 60;
	if (m > 59)
		h += m / 60;

	hours = h % 24;

	minutes = m % 60;

	seconds = s % 60;
}
Time::~Time()
{
}
int Time::compare()const
{
	size_t h, m, s;
	std::cin >> h >> m >> s;


	if (this->hours > h)
	{
		return 1;
	}
	else if (this->hours < h)
	{
		return -1;
	}
	else if (this->minutes > m)
	{
		return 1;
	}
	else if (this->minutes < m)
	{
		return -1;
	}
	else if (this->seconds > s)
	{
		return 1;
	}
	else if (this->seconds < s)
	{
		return -1;
	}
	else
		return 0;
}
/*Time Time::getToMidnight()const
{
//idk how to do it
	Time p(23-hours,59-minutes,59-seconds);
	

	return p;
}*/

bool Time::isDinnerTime()const
{
	if (hours > 20 && hours < 22)
	{
		return 1;
	}
	else if (hours == 20 && minutes > 30)
	{
		return 1;
	}

	return 0;
	
}
bool Time::isPartyTime()const
{
	if (hours == 23)
	{
		return 1;
	}
	else if (hours < 6)
	{
		return 1;
	}

	return 0;
}

void Time::print(bool is12hoursClock) const
{
	if (is12hoursClock)
	{
		if (hours > 12)
		{
			std::cout << hours - 12 << ":" << minutes << ":" << seconds << "PM" << '\n';
		}
		else if (hours == 12)
		{
			std::cout << hours << ":" << minutes << ":" << seconds << "PM" << '\n';
		}
		else if (hours < 12)
		{
			std::cout << hours << ":" << minutes << ":" << seconds << '\n';
		}
	}
	else
	{
		std::cout << hours << ":" << minutes << ":" << seconds<<'\n';
	}
}

int main()
{
	Time t(20, 20, 59);

	t.print(0);
	//t.getToMidnight();
}