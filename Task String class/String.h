#pragma once
#pragma warning (disable : 4996)


class String {
private:
	char* str;
	size_t size, capacity;

public:

	String();
	String(const String&);
	String(const char*);
	~String();

	String& operator=(const String&);	
	String& operator+=(char ch);			// Concatenates the string with the given character.
	String& operator+=(const char*);		// Concats c-string.
	String& operator+=(const String&);		// Concatenates string.
	String& operator*=(int k);				// Concat. to itself 'k' times.
	String& operator/=(const String&);
	char operator[](size_t) const;			// Returns the character in position 'index'. 

	friend std::ifstream& operator>>(std::ifstream&, String&);

	void resize(size_t);				// Increases the capacity by given amount.
	void insertAt(char, size_t);		// Returns false if the character or the index are invalid.
	void removeAt(size_t);				// Returns false if 'index' is invalid.
	void freeUnused();					// Frees the unused capacity.

	const char* getCString() const;
	size_t getSize() const;
	size_t getCapacity() const;
};

std::istream& operator>>(std::istream&, String&);
std::ifstream& operator>>(std::ifstream&, String&);
std::ostream& operator<<(std::ostream&, const String&);
String operator+(const String&, const String&);
String operator*(const String&, int);
String operator/(const String&, const String&);
bool operator==(const String&, const String&);
bool operator!=(const String&, const String&);