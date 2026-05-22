#include "SMSNotification.h"

SMSNotification::SMSNotification(const std::string& phoneNumber, const std::string& message)
	: phoneNumber(phoneNumber), message(message)
{}

void SMSNotification::send() const
{
	std::cout << "Sending SMS to " << phoneNumber << " | Message: " << message << std::endl;
}

Notification* SMSNotification::clone() const
{
	return new SMSNotification(*this);
}

SMSCreator::SMSCreator() : NotificationCreator("sms")
{}

Notification* SMSCreator::createNotification(std::istream& is) const
{
	std::string phoneNumber, message;
	is >> phoneNumber >> message;
	return new SMSNotification(phoneNumber, message);
}

static SMSCreator __;
