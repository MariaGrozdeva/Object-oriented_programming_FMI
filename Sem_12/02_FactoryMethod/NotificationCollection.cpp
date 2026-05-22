#include "NotificationCollection.h"
#include <stdexcept>

void NotificationCollection::add(Notification* notification)
{
	if (!notification)
	{
		return;
	}
	if (count == capacity)
	{
		resize();
	}
	notifications[count++] = notification;
}

void NotificationCollection::sendAll() const
{
	for (size_t i = 0; i < count; i++)
	{
		notifications[i]->send();
	}
}

Notification* NotificationCollection::operator[](unsigned index)
{
	if (index >= count)
	{
		throw std::out_of_range("Index is out of range!");
	}
	return notifications[index];
}

const Notification* NotificationCollection::operator[](unsigned index) const
{
	if (index >= count)
	{
		throw std::out_of_range("Index is out of range!");
	}
	return notifications[index];
}

size_t NotificationCollection::size() const
{
	return count;
}

NotificationCollection::NotificationCollection()
{
	notifications = new Notification*[capacity]{nullptr};
}

NotificationCollection::NotificationCollection(const NotificationCollection& other)
{
	copyFrom(other);
}

NotificationCollection& NotificationCollection::operator=(const NotificationCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

NotificationCollection::~NotificationCollection()
{
	free();
}

void NotificationCollection::copyFrom(const NotificationCollection& other)
{
	count = other.count;
	capacity = other.capacity;

	notifications = new Notification*[capacity];
	for (size_t i = 0; i < count; i++)
	{
		notifications[i] = other.notifications[i]->clone();
	}
}

void NotificationCollection::free()
{
	for (size_t i = 0; i < count; i++)
	{
		delete notifications[i];
	}
	delete[] notifications;
}

void NotificationCollection::resize()
{
	Notification** resized = new Notification*[capacity *= 2];

	for (size_t i = 0; i < count; i++)
	{
		resized[i] = notifications[i];
	}

	delete[] notifications;
	notifications = resized;
}
