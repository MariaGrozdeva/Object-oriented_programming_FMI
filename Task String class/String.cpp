
#include <iostream>
#include <cstring>
#include <algorithm>		// std::reverse in operator*=
#include <fstream>
#include "String.h"

const size_t MAX_SIZE = 256;


String::String() : size(0), capacity(0) {
	str = new char[capacity + 1];
	*str = '\0';
}
String::String(const String& other) {
	size = other.size;
	capacity = other.capacity;
	str = new char[capacity + 1];
	strcpy(str, other.str);
}
String::String(const char* other_str) : size(0), capacity(0), str(nullptr) {
	if (!other_str) 
		throw ("Trying to read from nullptr!");
	
	capacity = strlen(other_str);
	size = capacity;
	str = new char[capacity + 1];
	strcpy(str, other_str);
}
String::~String() {
	delete[] str;
}

String& String::operator=(const String& other) {
	if (this != &other) {
		if (other.size > capacity) {
			delete[] str;
			capacity = other.size;
			str = new char[capacity + 1];
		}
		
		strcpy(str, other.str);
		size = other.size;
	}

	return *this;
}
String& String::operator+=(char ch) {
	if (ch != '\0') {
		if (size >= capacity)	// If the string is full, resize it.
			resize(1);

		str[size] = ch;
		str[size + 1] = '\0';
		++size;
	}
	
	return *this;
}
String& String::operator+=(const char* other_str) {
	size_t size_of_other = strlen(other_str);
	if (capacity < size + size_of_other)
		resize(size + size_of_other - capacity);
	
	strcpy(str + size, other_str);
	size += size_of_other;

	return *this;
}
String& String::operator+=(const String& other) {
	if (capacity < size + other.size)
		resize(other.size - capacity);
	
	strcpy(str + size, other.str);
	size += other.size;
	return *this;
}
// If 'k > 0' concatenates to itself 'k' times.
// If 'k < 0' reverses 'str' and then concats. 'abs(k)' times.
String& String::operator*=(int k) {
	if (k == 0) {
		*str = '\0';
		size = 0;
		return *this;
	}

	if (k < 0) {
		std::reverse(str, str + size);	// <algorithm>
		k *= -1;
	}

	size_t newSize = size * k;
	if (capacity < newSize)
		resize(newSize - capacity);
	// Copy the string 'k' times.
	for (int i = 1; i < k; ++i) {
		strcpy(str + (i * size) + 1, str + ((i - 1) * size) + 1);
		str[i * size] = str[0];
	}
	size = newSize;

	return *this;
}
String& String::operator/=(const String& other) {
	/*
		Оператор /= , който по подаден стринг, връща като резултат всички символи,
		които се съдържат в текущия стринг, но не са част от подадения.

		Има поне два начина да се направи това:
			1) Да се премахнат всички елементи в текущия низ, които се съдържат в подадения.
			2) Да се премахнат всички елементи в текущия низ, които се съдържат в подадения и да сепремахнат повторенията.

		Направил съм го по 1) начин и не съм махал повторенията в текущия низ.
	*/
	size_t common_char_count = 0;
	for (size_t i = 0; str[i]; ++i) {
		if (strchr(other.str, str[i])) {
			removeAt(i);		// Remove common characters.
			--i;
		}
		else
			++common_char_count;
	}
	size = common_char_count;

	return *this;
}
char String::operator[](size_t index) const {
	if (index <= size)
		return str[index];
	else
		throw std::out_of_range("Reading from invalid index!");
}

std::istream& operator>>(std::istream& istream, String& str1) {
	char buff[MAX_SIZE];
	istream.getline(buff, MAX_SIZE);
	str1 *= 0;		// Does not resize 'str1',
	str1 += buff;	// 'str1' is resized only if needed.

	return istream;
}
std::ifstream& operator>>(std::ifstream& ifile, String& str1) {
	if (!ifile.good())
		ifile.clear();

	size_t read_from = ifile.tellg();
	ifile.seekg(0, std::ios::end);
	// 'char_count' is greater than or equat to the number of chars in the txt file
	// because some chars in the file take up 2 bytes.
	size_t char_count = ifile.tellg();
	char_count -= read_from;
	ifile.seekg(read_from, std::ios::beg);

	if (str1.capacity < char_count) {
		delete[] str1.str;
		str1.str = new char[char_count + 1];
		str1.capacity = char_count;
	}
	size_t i = 0;
	while (ifile) {
		ifile.get(str1.str[i]);
		++i;
	}
	if (ifile.eof())
		ifile.clear();
	str1.str[i - 1] = '\0';
	str1.size = i;

	return ifile;
}
std::ostream& operator<<(std::ostream& outStream, const String& string) {
	if (outStream.good()) {
		outStream << string.getCString();
	}
	// Maybe if the stream is not good should throw an exception.
	return outStream;
}
String operator+(const String& str1, const String& str2) {
	String result(str1);
	result += str2;

	return result;
}
String operator*(const String& str1, int k) {
	String result(str1);
	result *= k;
	return result;
}
String operator/(const String& str1, const String& str2) {
	String result(str1);
	result /= str2;
	return result;
}
bool operator==(const String& str1, const String& str2) {
	return !(strcmp(str1.getCString(), str2.getCString()));
}
bool operator!=(const String& str1, const String& str2) {
	return strcmp(str1.getCString(), str2.getCString());
}

void String::resize(size_t add_capacity) {
	if (add_capacity == 0)
		return;

	capacity += add_capacity;
	char* new_str = new char[capacity + 1];
	strcpy(new_str, str);
	delete[] str;
	str = new_str;
}
void String::insertAt(char ch, size_t index) {
	if (ch != '\0' && index <= size) {
		if (size >= capacity)	// If the string is full, resize it.
			resize(1);

		// Shifts the characters by one to the right.
		for (size_t i = size + 1; i > index; --i)
			str[i] = str[i - 1];

		str[index] = ch;
		++size;
	}
	else
		throw "Invalid index or trying to insert terminating zero in middle of string!";
}
void String::removeAt(size_t index) {
	if (index < size) {
		str[index] = '\0';
		strcpy(str + index, str + index + 1);	// Shift by one character to the left.
		--size;
	}
	else
		throw std::out_of_range("Invalid index!");
}
void String::freeUnused() {
	capacity = size;
	char* new_str = new char[capacity + 1];
	strcpy(new_str, str);
	delete[] str;
	str = new_str;
}

const char* String::getCString() const { return str; }
size_t String::getSize() const { return size; }
size_t String::getCapacity() const { return capacity; }