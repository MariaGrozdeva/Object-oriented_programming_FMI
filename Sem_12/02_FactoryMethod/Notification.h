#pragma once
#include <iostream>
#include <string>

class Notification
{
public:
	virtual void send() const = 0;
	virtual Notification* clone() const = 0;
	virtual ~Notification() = default;
};

class NotificationCreator
{
public:
	NotificationCreator(const std::string& typeName);
	virtual ~NotificationCreator() = default;

	const std::string& getTypeName() const;

	virtual Notification* createNotification(std::istream& is) const = 0;

private:
	std::string typeName;
};
