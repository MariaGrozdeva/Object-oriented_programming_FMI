#include <iostream>
#include <cmath>

using std::cin;
using std::cout;

struct Point {
    int x;
    int y;
};

void readPoint(Point& p) {
    cin >> p.x >> p.y;
}

struct Triangle {
    Point p1;
    Point p2;
    Point p3;
};


void readTriangle(Triangle& triangle) {
    readPoint(triangle.p1);
    readPoint(triangle.p2);
    readPoint(triangle.p3);
}

double getDist(const Point& a, const Point& b) {
    const int dx = a.x - b.x;
    const int dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

bool isTriangle(const Triangle& triangle) {
    const double a = getDist(triangle.p1, triangle.p2);
    const double b = getDist(triangle.p2, triangle.p3);
    const double c = getDist(triangle.p1, triangle.p3);

    if (a == 0 || b == 0 || c == 0) {
        return false;
    }

    return a + b > c && a + c > b && b + c > a;
}

double calculateArea(const Triangle& triangle) {
    const int p1p2x = triangle.p2.x - triangle.p1.x;
    const int p1p2y = triangle.p2.y - triangle.p1.y;

    const int p1p3x = triangle.p3.x - triangle.p1.x;
    const int p1p3y = triangle.p3.y - triangle.p1.y;

    return std::abs(p1p2x * p1p3y - p1p3x * p1p2y) * 0.5;
}

void sortTriangles(double* areas, const int number_of_triangles) {
    for (int i = 0; i < number_of_triangles - 1; i++) {
        int minIndex = i;
        for (int j = minIndex + 1; j < number_of_triangles; j++) {
            if (areas[j] < areas[minIndex]) {
                minIndex = j;
            }
        }
        const double temp = areas[i];
        areas[i] = areas[minIndex];
        areas[minIndex] = temp;
    }

}

int main() {
    int number_of_triangles = 0;
    cin >> number_of_triangles;
    if (number_of_triangles <= 0) {
        cout << "Invalid number of triangles!";
        return 0;
    }

    Triangle* triangles = new Triangle[number_of_triangles];
    for (int i = 0; i < number_of_triangles; i++) {
        readTriangle(triangles[i]);
        if (!isTriangle(triangles[i])) {
            cout << "Invalid triangle!";
            delete[] triangles;
            return 0;
        }
    }

    double* areas = new double[number_of_triangles];
    for (int i = 0; i < number_of_triangles; i++) {
        areas[i] = calculateArea(triangles[i]);
    }

    sortTriangles(areas, number_of_triangles);

    for (int i = 0; i < number_of_triangles; i++) {
        cout <<"Area of triangle " << i + 1 << ": " << areas[i] <<"\n";
    }


    delete[] areas;
    delete[] triangles;
    return 0;
}