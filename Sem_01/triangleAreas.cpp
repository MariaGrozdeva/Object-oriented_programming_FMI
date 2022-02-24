#include <iostream>

struct Point
{
	int x;
	int y;
};
void readPoint(Point& p)
{
	std::cin >> p.x >> p.y;
}
void printPoint(const Point& p)
{
	std::cout << "x: " << p.x << ", y: " << p.y;
}

struct Triangle
{
	Point p1;
	Point p2;
	Point p3;
};
void readTriangle(Triangle& t)
{
	readPoint(t.p1);
	readPoint(t.p2);
	readPoint(t.p3);
}
void printTriangle(const Triangle& t)
{
	printPoint(t.p1);
	std::cout << std::endl;
	printPoint(t.p2);
	std::cout << std::endl;
	printPoint(t.p3);
	std::cout << std::endl;
}

double getDist(const Point& p1, const Point& p2)
{
	int dx = p1.x - p2.x;
	int dy = p1.y - p2.y;

	return sqrt(dx * dx + dy * dy);
}
double getArea(const Triangle& t)
{
	double sideA = getDist(t.p1, t.p2);
	double sideB = getDist(t.p2, t.p3);
	double sideC = getDist(t.p3, t.p1);

	double halfPer = (sideA + sideB + sideC) / 2;
	return sqrt(halfPer * (halfPer - sideA) * (halfPer - sideB) * (halfPer - sideC));
}

double* getAreas(const Triangle* arr, unsigned int n)
{
	double* areas = new double[n];

	for (size_t i = 0; i < n; i++)
		areas[i] = getArea(arr[i]);

	return areas;
}

int main()
{
	unsigned int n;
	std::cout << "Enter number of triangles:" << std::endl;
	std::cin >> n;

	Triangle* triangles = new Triangle[n];
	for (size_t i = 0; i < n; i++)
	{
		std::cout << "Enter triangle:" << std::endl;
		readTriangle(triangles[i]);
	}
	std::cout << std::endl;

	double* areas = getAreas(triangles, n);
	for (size_t i = 0; i < n; i++)
		std::cout << "Area of triangle " << i << ": " << areas[i] << std::endl;

	delete[] triangles, areas;
}