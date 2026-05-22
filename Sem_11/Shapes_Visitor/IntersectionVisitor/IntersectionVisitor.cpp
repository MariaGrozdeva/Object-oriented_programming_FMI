#include "IntersectionVisitor.h"

// ── CircleIntersectionVisitor ────────────────────────────────────────────────

CircleIntersectionVisitor::CircleIntersectionVisitor(const Circle* circle)
	: self(circle) {}

void CircleIntersectionVisitor::visitCircle(const Circle* other)
{
	std::cout << "Formula for circle with circle" << std::endl;
}

void CircleIntersectionVisitor::visitTriangle(const Triangle* other)
{
	std::cout << "Formula for circle with triangle" << std::endl;
}

void CircleIntersectionVisitor::visitRectangle(const Rectangle* other)
{
	std::cout << "Formula for circle with rectangle" << std::endl;
}

// ── TriangleIntersectionVisitor ──────────────────────────────────────────────

TriangleIntersectionVisitor::TriangleIntersectionVisitor(const Triangle* triangle)
	: self(triangle) {}

void TriangleIntersectionVisitor::visitCircle(const Circle* other)
{
	std::cout << "Formula for triangle with circle" << std::endl;
}

void TriangleIntersectionVisitor::visitTriangle(const Triangle* other)
{
	std::cout << "Formula for triangle with triangle" << std::endl;
}

void TriangleIntersectionVisitor::visitRectangle(const Rectangle* other)
{
	std::cout << "Formula for triangle with rectangle" << std::endl;
}

// ── RectangleIntersectionVisitor ─────────────────────────────────────────────

RectangleIntersectionVisitor::RectangleIntersectionVisitor(const Rectangle* rectangle)
	: self(rectangle) {}

void RectangleIntersectionVisitor::visitCircle(const Circle* other)
{
	std::cout << "Formula for rectangle with circle" << std::endl;
}

void RectangleIntersectionVisitor::visitTriangle(const Triangle* other)
{
	std::cout << "Formula for rectangle with triangle" << std::endl;
}

void RectangleIntersectionVisitor::visitRectangle(const Rectangle* other)
{
	std::cout << "Formula for rectangle with rectangle" << std::endl;
}
