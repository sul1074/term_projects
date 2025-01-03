#include "Selector.h"
#include "InputManager.h"
#include "Canvas.h"

void Selector::drag(InputManager& input)
{
	if (input.getMouseButtonDown(0)) { setPosition(input.getMousePosition()); }

	canvas.drawRectangle(getPosition(), input.getMousePosition(), true);
	changeDimension((input.getMousePosition() - getPosition()));
}