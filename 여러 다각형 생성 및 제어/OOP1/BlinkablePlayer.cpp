#include "BlinkablePlayer.h"
#include "InputManager.h"

void BlinkablePlayer::update(InputManager& input)
{
	if (input.getKey(VK_LEFT)) move(Vector2(-1, 0));
	if (input.getKey(VK_RIGHT)) move(Vector2(1, 0));
	if (input.getKey(VK_UP)) move(Vector2(0, -1));
	if (input.getKey(VK_DOWN)) move(Vector2(0, 1));
}
