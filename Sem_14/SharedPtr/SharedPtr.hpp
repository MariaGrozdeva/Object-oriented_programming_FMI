#pragma once
#include <stdexcept>

template <typename T>
class SharedPtr
{
private:
	T* data;
	size_t* ptrCount;

	void copyFrom(const SharedPtr<T>& other);
	void free();

public:
	SharedPtr();
	SharedPtr(T* data);

	SharedPtr(const SharedPtr<T>& other);
	SharedPtr<T>& operator=(const SharedPtr<T>& other);
	~SharedPtr();

	const T& operator*() const;
	T& operator*();
	const T* operator->() const;
	T* operator->();
};

template <typename T>
SharedPtr<T>::SharedPtr()
{
	data = nullptr;
	ptrCount = nullptr;
}
template <typename T>
SharedPtr<T>::SharedPtr(T* data)
{
	this->data = data;
	ptrCount = new size_t(1);
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other)
{
	copyFrom(other);
}
template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
template <typename T>
SharedPtr<T>::~SharedPtr()
{
	free();
}

template <typename T>
const T& SharedPtr<T>::operator*() const
{
	if (data == nullptr)
	{
		throw std::logic_error("Pointer not set");
	}
	return *data;
}
template <typename T>
T& SharedPtr<T>::operator*()
{
	if (data == nullptr)
	{
		throw std::logic_error("Pointer not set");
	}
	return *data;
}

template<typename T>
const T* SharedPtr<T>::operator->() const
{
	return data;
}
template<typename T>
T* SharedPtr<T>::operator->()
{
	return data;
}

template <typename T>
void SharedPtr<T>::copyFrom(const SharedPtr<T>& other)
{
	data = other.data;
	ptrCount = other.ptrCount;
	(*ptrCount)++;
}
template <typename T>
void SharedPtr<T>::free()
{
	if (data == nullptr && ptrCount == nullptr)
	{
		return;
	}
	if (*ptrCount == 1)
	{
		delete data, ptrCount;
		data = nullptr;
		ptrCount = nullptr;
	}
	else
	{
		(*ptrCount)--;
	}
}