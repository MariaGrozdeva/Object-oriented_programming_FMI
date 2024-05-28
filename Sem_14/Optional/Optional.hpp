#pragma once
#include <iostream>

template <typename T>
class Optional
{
private:
	T* data;

	void copyFrom(const Optional<T>& other);
	void free();

public:
	Optional(const T& data);

	Optional();
	Optional(const Optional<T>& other);
	Optional<T>& operator=(const Optional<T>& other);
	~Optional();

	bool has_value() const;
	const T& value() const;
	void setData(const T& data);
	void reset();
};

template <typename T>
Optional<T>::Optional(const T& data)
{
	setData(data);
}

template <typename T>
bool Optional<T>::has_value() const
{
	return data != nullptr;
}
template <typename T>
const T& Optional<T>::value() const
{
	if (!has_value())
	{
		throw std::logic_error("No data");
	}

	return *data;
}
template <typename T>
void Optional<T>::setData(const T& data)
{
	free();
	this->data = new T(data);
}
template <typename T>
void Optional<T>::reset()
{
	free();
	data = nullptr;
}

template <typename T>
Optional<T>::Optional() : data(nullptr)
{}
template <typename T>
Optional<T>::Optional(const Optional<T>& other)
{
	copyFrom(other);
}
template <typename T>
Optional<T>& Optional<T>::operator=(const Optional<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
template <typename T>
Optional<T>::~Optional()
{
	free();
}

template <typename T>
void Optional<T>::copyFrom(const Optional<T>& other)
{
	if (other.has_value())
	{
		data = new T(*other.data);
	}
	else
	{
		data = nullptr;	
	}
}
template <typename T>
void Optional<T>::free()
{
	delete data;
}
