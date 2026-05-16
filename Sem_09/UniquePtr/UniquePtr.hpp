#pragma once
#include <utility>

template<typename T>
class UniquePtr
{
public:
	explicit UniquePtr(T* ptr = nullptr);
	
	UniquePtr(const UniquePtr&) = delete;
	UniquePtr& operator=(const UniquePtr&) = delete;
	UniquePtr(UniquePtr&& other) noexcept;
	UniquePtr& operator=(UniquePtr&& other) noexcept;
	~UniquePtr() noexcept;

	T& operator*();
	const T& operator*() const;
	T* operator->();
	const T* operator->() const;

	T* get();
	const T* get() const;
	explicit operator bool() const;
	T* release();
	void reset(T* newPtr = nullptr);

private:
	T* ptr;
};

template<typename T>
UniquePtr<T>::UniquePtr(T* ptr) : ptr(ptr)
{}

template<typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& other) noexcept
{
	ptr = other.ptr;
	other.ptr = nullptr;
}

template<typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other) noexcept
{
	if (this != &other)
	{
		delete ptr;
		ptr = other.ptr;
		other.ptr = nullptr;
	}
	return *this;
}

template<typename T>
UniquePtr<T>::~UniquePtr() noexcept
{
	delete ptr;
}

template<typename T>
T& UniquePtr<T>::operator*()
{
	return *ptr;
}

template<typename T>
const T& UniquePtr<T>::operator*() const
{
	return *ptr;
}

template<typename T>
T* UniquePtr<T>::operator->()
{
	return ptr;
}

template<typename T>
const T* UniquePtr<T>::operator->() const
{
	return ptr;
}

template<typename T>
T* UniquePtr<T>::get()
{
	return ptr;
}

template<typename T>
const T* UniquePtr<T>::get() const
{
	return ptr;
}

template<typename T>
UniquePtr<T>::operator bool() const
{
	return ptr != nullptr;
}

template<typename T>
T* UniquePtr<T>::release()
{
	T* tmp = ptr;
	ptr = nullptr;
	return tmp;
}

template<typename T>
void UniquePtr<T>::reset(T* newPtr)
{
	delete ptr;
	ptr = newPtr;
}

template<typename T, typename... Args>
UniquePtr<T> myMakeUnique(Args&&... args)
{
	return UniquePtr<T>(new T(std::forward<Args>(args)...));
}
