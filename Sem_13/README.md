# Колекция от обекти в полиморфна йерархия

Можем да реализираме хетерогенна колекция (от различни типове  **с общ базов клас**) чрез масив от указатели. Указателите трябва да са от типа на базовия клас.
```c++
struct Dog
{
	virtual void printBreed() const = 0;
	virtual ~Dog() {}
};

struct GoldenRetriever : Dog
{
	virtual void printBreed() const override
	{
		std::cout << "My breed is Golden Retriever!" << std::endl;
	}
};
struct Huskita : Dog
{
	virtual void printBreed() const override
	{
		std::cout << "My breed is Huskita!" << std::endl;
	}
};
struct Poodle : Dog
{
	virtual void printBreed() const override
	{
		std::cout << "My breed is Poodle!" << std::endl;
	}
};

class DogsCollection
{
private:
	Dog** dogs;

	size_t capacity;
	size_t count;

	void copyFrom(const DogsCollection& other);
	void free();

public:
	DogsCollection();
	DogsCollection(const DogsCollection&);
	DogsCollection& operator=(const DogsCollection&);
	~DogsCollection();

	void addGoldenRetriever();
	void addHuskita();
	void addPoodle();
};

void DogsCollection::addGoldenRetriever()
{
	dogs[count++] = new GoldenRetriever();
}
void DogsCollection::addHuskita()
{
	dogs[count++] = new Huskita();
}
void DogsCollection::addPoodle()
{
	dogs[count++] = new Poodle();
}
```

## Триене

Понеже имаме виртуален деструктор в базовия клас, не се интересуваме какви са обектите, които трием от колекцията.
```c++
void DogsCollection::free()
{
	for (size_t i = 0; i < count; i++)
		delete dogs[i];
	delete[] dogs;
}
```

## Копиране

Искаме да реализираме копиране на колекцията. Това трябва да стане без да нарушаваме абстракцията - искаме обеките да се копират без да се налага да преглеждаме типовете им. Затова дефинираме виртуална функция clone, която ще връща копие на обекта. Тази функция я разписваме във всеки от наследниците.
```c++
struct Dog
{
	// ...
	virtual ~Dog() {}
	virtual Dog* clone() const = 0;
};

struct GoldenRetriever : Dog
{
	// ...
	virtual Dog* clone() const override
	{
		return new GoldenRetriever(*this);
	}
};
struct Huskita : Dog
{
	// ...
	virtual Dog* clone() const override
	{
		return new Huskita(*this);
	}
};
struct Poodle : Dog
{
	// ...
	virtual Dog* clone() const override
	{
		return new Poodle(*this);
	}
};

void DogsCollection::copyFrom(const DogsCollection& other)
{
	capacity = other.capacity;
	count = other.count;

	dogs = new Dog * [capacity];
	for (size_t i = 0; i < count; i++)
		dogs[i] = other.dogs[i]->clone();
}

```
