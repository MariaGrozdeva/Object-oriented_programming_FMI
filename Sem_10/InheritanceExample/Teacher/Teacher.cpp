#include "Teacher.h"
#pragma warning (disable : 4996)

unsigned int roundToPowerOfTwo(unsigned int value) {
	value--;
	value |= value >> 1;
	value |= value >> 2;
	value |= value >> 1;
	value |= value >> 4;
	value |= value >> 16;
	value++;
	return value;
}
void Teacher::free()
{
	for (int i = 0; i < subjectsCount; i++) {
		delete[]subjects[i];
	}
	delete[]subjects;
	subjects = nullptr;
}
void Teacher::copyFrom(const Teacher& other) {
	subjectsCount = other.subjectsCount;
	subjects = new char* [capacity];
	for (int i = 0; i < subjectsCount; i++) {
		subjects[i] = new char[strlen(other.subjects[i]) + 1];
		strcpy(subjects[i], other.subjects[i]);
	}
}
void Teacher::moveFrom(Teacher&& other) {
	subjects = other.subjects;
	other.subjects = nullptr;
	subjectsCount = other.subjectsCount;
	capacity = other.capacity;
	other.subjectsCount = other.capacity = 0;
}

Teacher::Teacher(const char* name, unsigned int age, const char* const* subjects, unsigned int subjectsCount) :Person(name, age) {
	this->subjectsCount = subjectsCount;

	this->capacity = roundToPowerOfTwo(subjectsCount);

	this->subjects = new char* [capacity];
	for (int i = 0; i < subjectsCount; i++) {
		this->subjects[i] = new char[strlen(subjects[i]) + 1];
		strcpy(this->subjects[i], subjects[i]);
	}
	}

Teacher::Teacher(const Teacher& other):Person(other) {
	copyFrom(other);
	}
Teacher::Teacher(Teacher&& other) noexcept :Person(other){
	moveFrom(std::move(other));
}

Teacher& Teacher::operator=(const Teacher& other) {
	if (this != &other) {
		Person::operator=(other);

		free();
		copyFrom(other);
	}
	return *this;
	}
Teacher& Teacher::operator=(Teacher&& other) noexcept {
	if (this != &other) {
		Person::operator=(other);

		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Teacher::~Teacher() {
	free();
	}

void Teacher::resize(unsigned int newCapacity) {
	char** newSubjects = new char* [newCapacity] {nullptr};
	for (int i = 0; i < capacity; i++) {
		newSubjects[i] = subjects[i];
	}

	delete[]subjects;
	subjects = newSubjects;
	capacity = newCapacity;
}

unsigned int Teacher::getFirstFreeIndex() const{
	for (int i = 0; i < capacity; i++){
		if (!subjects[i]){
			return i;
		}
	}
	return -1;
}
void Teacher::removeAt(unsigned index) {
	if (index >= subjectsCount) {
		//throw
	}
	delete subjects[index];
	subjects[index] = nullptr;
	subjectsCount--;
}
void Teacher::popBack()
{
	if (size() == 0)
	{
		return;
	}

	delete subjects[subjectsCount - 1];
	subjectsCount--;

	// shrink if count is much smaller than capacity
}

size_t Teacher::size() const {
	return subjectsCount;
}

bool Teacher::contains(unsigned int index) const{
	return index <= subjectsCount && subjects[index];
}

void Teacher::setAtIndex(const char* obj, unsigned int index) {
	if (subjectsCount >= capacity){
		resize(capacity * 2);
	}
	if (subjects[index]){
		//throw std::invalid_argument("An object at this index already exists");
	}
	subjects[index] = new char[strlen(obj) + 1];
	subjectsCount++;
}

const char* Teacher::operator[](unsigned index) const{
	if (index >= subjectsCount || !subjects[index])
	{
		//throw std::out_of_range("Invalid index!");
	}
	return subjects[index];
}
