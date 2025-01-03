#include "RegularPolygonManager.h"
#include "InputManager.h"
#include "Canvas.h"

void RegularPolygonManager::selectPolygon(InputManager& input)
{
	if (input.getMouseButton(0))
	{
		selector->drag(input);

		for_each(polygons.begin(), polygons.end(), [=](auto* polygon) {
			if (selector->isInside(polygon->getPosition())) polygon->startBlinking();
			else polygon->stopBlinking();
			});
	}

	if (input.getMouseButtonUp(0))
	{
		// initialize select status of polygons
		for_each(polygons.begin(), polygons.end(), [](auto* polygon) {
			polygon->setIsSelected(false);
		});
		
		// determine which polygons are selected
		for_each(polygons.begin(), polygons.end(), [=](auto* polygon) {
			if (selector->isInside(polygon->getPosition())) { polygon->setIsSelected(); }
		});
	}
}

void RegularPolygonManager::draw()
{
	for_each(polygons.begin(), polygons.end(), [](auto* polygon) {
		polygon->draw();
	});
}
