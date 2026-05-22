#pragma once
#include "Notification.h"

class SMSNotification : public Notification
{
public:
	SMSNotification(const std::string& phoneNumber, const std::string& message);

	void send() const override;
	Notification* clone() const override;

private:
	std::string phoneNumber;
	std::string message;
};

class SMSCreator : public NotificationCreator
{
public:
	SMSCreator();
	Notification* createNotification(std::istream& is) const override;
};
