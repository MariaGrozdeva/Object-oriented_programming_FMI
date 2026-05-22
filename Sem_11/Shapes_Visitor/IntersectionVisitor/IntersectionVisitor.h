#pragma once
#include "../ShapeVisitor/ShapeVisitor.h"
#include "../Circle/Circle.h"
#include "../Triangle/Triangle.h"
#include "../Rectangle/Rectangle.h"

// One visitor per "left" shape type.
// When constructed, it holds a pointer to the left shape.
// When accept() calls visitX(), we know both types.

class CircleIntersectionVisitor : public ShapeVisitor
{
public:
	CircleIntersectionVisitor(const Circle* circle);

	void visitCircle(const Circle* other) override;
	void visitTriangle(const Triangle* other) override;
	void visitRectangle(const Rectangle* other) override;

private:
	const Circle* self;
};

class TriangleIntersectionVisitor : public ShapeVisitor
{
public:
	TriangleIntersectionVisitor(const Triangle* triangle);

	void visitCircle(const Circle* other) override;
	void visitTriangle(const Triangle* other) override;
	void visitRectangle(const Rectangle* other) override;

private:
	const Triangle* self;
};

class RectangleIntersectionVisitor : public ShapeVisitor
{
public:
	RectangleIntersectionVisitor(const Rectangle* rectangle);

	void visitCircle(const Circle* other) override;
	void visitTriangle(const Triangle* other) override;
	void visitRectangle(const Rectangle* other) override;

private:
	const Rectangle* self;
};
