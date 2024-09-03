#pragma once
class Person
{
public:
	Person() = default;
	Person(const char* name, unsigned age);
	Person(const Person& other);
	Person& operator=(const Person& other);
	Person(Person&& other) noexcept;
	Person& operator=(Person&& other) noexcept;
	~Person();

	const char* getName() const;
	unsigned getAge() const;

	void setName(const char* newName);
	void setAge(unsigned newAge);

	void print() const;

private:
	char* name;
	unsigned age;

	void copyFrom(const Person& other);
	void moveFrom(Person&& other);
	void free();
};

