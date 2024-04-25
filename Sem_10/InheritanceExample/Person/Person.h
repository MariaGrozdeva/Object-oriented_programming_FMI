#pragma once
class Person
{
public:
	Person();
	Person(const char*, unsigned);
	Person(const Person&);
	Person(Person&&) noexcept;
	Person& operator=(const Person&);
	Person& operator=(Person&&) noexcept;
	~Person();

	const char* getName()const;
	unsigned getAge()const;

private:
	void setName(const char*);

private:
	char* name;
	unsigned age;
};