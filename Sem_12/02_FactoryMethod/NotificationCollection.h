#pragma once
#include "Notification.h"

class NotificationCollection
{
public:
	NotificationCollection();
	NotificationCollection(const NotificationCollection& other);
	NotificationCollection& operator=(const NotificationCollection& other);
	~NotificationCollection();

	void add(Notification* notification);
	void sendAll() const;

	Notification* operator[](unsigned index);
	const Notification* operator[](unsigned index) const;

	size_t size() const;

private:
	Notification** notifications;
	size_t count = 0;
	size_t capacity = 8;

	void copyFrom(const NotificationCollection& other);
	void free();
	void resize();
};
