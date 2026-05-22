#include "PushNotification.h"

PushNotification::PushNotification(const std::string& deviceToken, const std::string& title)
	: deviceToken(deviceToken), title(title)
{}

void PushNotification::send() const
{
	std::cout << "Sending push to device " << deviceToken << " | Title: " << title << std::endl;
}

Notification* PushNotification::clone() const
{
	return new PushNotification(*this);
}

PushCreator::PushCreator() : NotificationCreator("push")
{}

Notification* PushCreator::createNotification(std::istream& is) const
{
	std::string deviceToken, title;
	is >> deviceToken >> title;
	return new PushNotification(deviceToken, title);
}

static PushCreator __;
