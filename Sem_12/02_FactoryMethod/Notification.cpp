#include "Notification.h"
#include "NotificationFactory.hpp"

NotificationCreator::NotificationCreator(const std::string& typeName) : typeName(typeName)
{
	NotificationFactory::getFactory().registerCreator(this);
}

const std::string& NotificationCreator::getTypeName() const
{
	return typeName;
}
