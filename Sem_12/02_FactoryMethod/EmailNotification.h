#pragma once
#include "Notification.h"

class EmailNotification : public Notification
{
public:
	EmailNotification(const std::string& recipient, const std::string& subject);

	void send() const override;
	Notification* clone() const override;

private:
	std::string recipient;
	std::string subject;
};

class EmailCreator : public NotificationCreator
{
public:
	EmailCreator();
	Notification* createNotification(std::istream& is) const override;
};
