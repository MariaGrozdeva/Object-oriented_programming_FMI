#include "EmailNotification.h"

EmailNotification::EmailNotification(const std::string& recipient, const std::string& subject)
	: recipient(recipient), subject(subject)
{}

void EmailNotification::send() const
{
	std::cout << "Sending email to " << recipient << " | Subject: " << subject << std::endl;
}

Notification* EmailNotification::clone() const
{
	return new EmailNotification(*this);
}

EmailCreator::EmailCreator() : NotificationCreator("email")
{}

Notification* EmailCreator::createNotification(std::istream& is) const
{
	std::string recipient, subject;
	is >> recipient >> subject;
	return new EmailNotification(recipient, subject);
}

static EmailCreator __;
