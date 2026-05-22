#include "NotificationFactory.hpp"
#include "NotificationCollection.h"
#include "EmailNotification.h"
#include "SMSNotification.h"
#include "PushNotification.h"
#include <fstream>

int main()
{
	std::ifstream ifs("notifications.txt");
	if (!ifs.is_open())
	{
		return -1;
	}

	size_t count;
	ifs >> count;

	NotificationCollection coll;

	for (size_t i = 0; i < count; i++)
	{
		Notification* n = NotificationFactory::getFactory().createNotification(ifs);
		if (n)
		{
			coll.add(n);
		}
		else
		{
			std::cout << "Unknown notification type, skipping." << std::endl;
		}
	}

	ifs.close();

	coll.sendAll();
}
