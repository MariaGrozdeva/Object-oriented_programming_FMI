#include "Circle/Circle.h"
#include "Triangle/Triangle.h"
#include "Rectangle/Rectangle.h"
#include "IntersectionVisitor/IntersectionVisitor.h"

// Creates the correct visitor for 'a' then lets 'b' accept it.
// Dispatch 1: which concrete type is 'a'? (resolved by a->accept)
// Dispatch 2: which concrete type is 'b'? (resolved by b->accept inside visitor)

class IntersectionDispatcher : public ShapeVisitor
{
public:
	IntersectionDispatcher(const Shape* other) : other(other) {}

	void visitCircle(const Circle* a) override
	{
		CircleIntersectionVisitor v(a);
		other->accept(&v);
	}
	void visitTriangle(const Triangle* a) override
	{
		TriangleIntersectionVisitor v(a);
		other->accept(&v);
	}
	void visitRectangle(const Rectangle* a) override
	{
		RectangleIntersectionVisitor v(a);
		other->accept(&v);
	}

private:
	const Shape* other;
};

void intersectsWith(const Shape* a, const Shape* b)
{
	IntersectionDispatcher dispatcher(b);
	a->accept(&dispatcher);
}

void printIfShapesIntersect(const Shape* const* shapes, size_t shapesCount)
{
	for (size_t i = 0; i < shapesCount - 1; i++)
	{
		intersectsWith(shapes[i], shapes[i + 1]);
	}
}

void freeCollection(Shape** shapes, size_t shapesCount)
{
	for (size_t i = 0; i < shapesCount; i++)
	{
		delete shapes[i];
	}
	delete[] shapes;
}

int main()
{
	Shape** arr = new Shape * [4];

	arr[0] = new Circle(3, 3, 4);
	arr[1] = new Circle(1, 4, 5);
	arr[2] = new Triangle(-2, -3, 1, -3, 1, 0);
	arr[3] = new Rectangle(3, 4, 6, 8);

	std::cout << "Intersection of shapes:" << std::endl;
	printIfShapesIntersect(arr, 4);

	freeCollection(arr, 4);
}
