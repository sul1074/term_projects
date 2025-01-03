#pragma once
#include "GameObject.h"
#include "Canvas.h"
#include <math.h>
#include <algorithm>

#define PI 3.14159265

class RegularPolygon : public GameObject
{
	int sides;
	int radius;
	float rotatingRad;
	bool isSelected;
	bool isBlinking;
	vector<Vector2> points;

public:
	RegularPolygon(int n, const Vector2& pos) : sides(n), radius(rand() % 30 + 1), rotatingRad(0.001f), isSelected(false), isBlinking(false), GameObject("", pos, Dimension{ 0,0 }, true)
	{
		if (n < 2) {
			Debug::Log("You should submit the number that greater than 2");
			exit(1);
		}

		updatePolygon();
	}

	// getter & setter
	Vector2 getCenterPoint() const { return getPosition(); }
	void setCenterPoint(const Vector2& pos) { getPosition() = pos; }

	bool getIsSelected() const { return isSelected; }
	void setIsSelected(bool selected = true) { isSelected = selected; }

	void startBlinking() { isBlinking = true; }
	void stopBlinking() {
		isBlinking = false;
		setVisible(true); 
	}

	int getNumsOfSides() const { return sides; }
	void adjustNumsOfSides(const int n) {
		if (n < 0 && sides == 2) return;
		if (isBlinking == true) stopBlinking();

		sides += n;
		updatePolygon();
	}

	int getRadius() const { return radius; }
	void adjustRadius(const int length) {
		if (length < 0 && radius == 1) return;
		else if (length > 0 && radius == 30) return;
		if (isBlinking == true) stopBlinking();

		radius += length;
		updatePolygon();
	}

	void resetRotatingSpeed() { rotatingRad = 0.001f; }


	void update(InputManager& input) override;

	void draw() override
	{
		if (isBlinking) setVisible(!(isVisible()));

		if (isVisible())
		{
			for (int i = 0; i < sides; i++)
			{
				if (i + 1 < sides)
					canvas.drawLine('#', points[i] + getPosition(), points[i + 1] + getPosition());
			}
			canvas.drawLine('#', points[sides - 1] + getPosition(), points[0] + getPosition());
		}
	}
		
	// update vertex position of the polygon depending on the number of sides, and diameter
	void updatePolygon()
	{
		points.clear();

		for (int i = 0; i < sides; i++)
		{
			double rad = 2.0 * i * PI / sides;
			points.push_back(Vector2{ cos(rad) * radius, sin(rad) * radius});
		}
	}

	// rotate the polygon
	void rotatePolygon()
	{
		if (isBlinking == true) stopBlinking();

		for_each(points.begin(), points.end(), [=](auto& point) {
			float newX = point.x * cos(rotatingRad) + point.y * sin(rotatingRad);
			float newY = -1 * point.x * sin(rotatingRad) + point.y * cos(rotatingRad);
			point = Vector2{ newX, newY };
			});
		rotatingRad += 0.001f;
	}

	// relevant to adjusting the number of sides of the polygon
	RegularPolygon& operator++() { adjustNumsOfSides(1); return *this; }
	RegularPolygon& operator--(int unused) { adjustNumsOfSides(-1); return *this; }

	// relevant to move
	void moveLeft() { 
		if (isBlinking == true) stopBlinking(); 
		setPosition(getPosition() + Vector2{ -1, 0 }); 
	}
	void moveRight() {
		if (isBlinking == true) stopBlinking(); 
		setPosition(getPosition() + Vector2{ 1, 0 }); 
	}
	void moveDown() { 
		if (isBlinking == true) stopBlinking(); 
		setPosition(getPosition() + Vector2{ 0, 1 });
	}
    void moveUp() { 
		if (isBlinking == true) stopBlinking(); 
		setPosition(getPosition() + Vector2{ 0, -1 }); 
	}

	~RegularPolygon()
	{
		points.clear();
	}
};

