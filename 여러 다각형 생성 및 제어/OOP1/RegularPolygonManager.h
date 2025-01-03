#pragma once

#include <vector>
#include "RegularPolygon.h"
#include "Selector.h"

class RegularPolygonManager : public GameObject
{
	int n;
	Selector* selector;
	vector<RegularPolygon*> polygons;

public:
	RegularPolygonManager(int n) : n(n), GameObject("", Vector2{ 0, 0 }, Dimension{ 0, 0 }, false)
	{
		selector = new Selector();
		for (int i = 0; i < n; i++)
			addPolygon(new RegularPolygon(rand() % 5 + 2, Vector2{ rand() % 30 + i*5, rand() % 40 + i*5 }));
	}

	void addPolygon(RegularPolygon* polygon) { polygons.push_back(polygon); }

	void update(InputManager& input) override
	{
		for_each(polygons.begin(), polygons.end(), [&](auto* polygon) {
			if (polygon->getIsSelected() == false) return;
			polygon->update(input);
			});

		selectPolygon(input);
	}

	void selectPolygon(InputManager& input);

	void draw() override;

	~RegularPolygonManager()
	{
		delete selector;
		for (auto it = polygons.begin(); it != polygons.end(); it++)
			delete* it;
		polygons.clear();
	}
};

