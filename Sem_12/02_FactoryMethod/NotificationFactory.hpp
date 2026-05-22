#pragma once
#include "Notification.h"
#include <cassert>
#include <limits>

class NotificationFactory
{
public:
	static NotificationFactory& getFactory()
	{
		static NotificationFactory factory;
		return factory;
	}

	void registerCreator(const NotificationCreator* creator)
	{
		assert(count < MAX_CREATORS_COUNT);
		creators[count++] = creator;
	}

	Notification* createNotification(std::istream& is)
	{
		std::string type;
		is >> type;

		const NotificationCreator* creator = getCreator(type);
		if (creator)
		{
			return creator->createNotification(is);
		}
		else
		{
			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return nullptr;
		}
	}

private:
	static constexpr size_t MAX_CREATORS_COUNT = 10;
	const NotificationCreator* creators[MAX_CREATORS_COUNT];
	size_t count;

	const NotificationCreator* getCreator(const std::string& type) const
	{
		for (size_t i = 0; i < count; i++)
		{
			if (creators[i]->getTypeName() == type)
			{
				return creators[i];
			}
		}
		return nullptr;
	}

	NotificationFactory() : count(0) {}
	~NotificationFactory() = default;
	NotificationFactory(const NotificationFactory&) = delete;
	NotificationFactory& operator=(const NotificationFactory&) = delete;
};
