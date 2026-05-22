#pragma once
#include "Notification.h"

class PushNotification : public Notification
{
public:
	PushNotification(const std::string& deviceToken, const std::string& title);

	void send() const override;
	Notification* clone() const override;

private:
	std::string deviceToken;
	std::string title;
};

class PushCreator : public NotificationCreator
{
public:
	PushCreator();
	Notification* createNotification(std::istream& is) const override;
};
