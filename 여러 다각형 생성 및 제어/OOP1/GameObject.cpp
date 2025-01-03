#include <cstdlib> // include rand()
#include <Windows.h>
#include <algorithm>
#include <conio.h>
#include "GameObject.h"
#include "Canvas.h"
#include "Cards.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BlinkablePlayer.h"
#include "InputManager.h"
#include "RegularPolygon.h"
#include "RegularPolygonManager.h"

#ifdef POLYGON
Canvas GameObject::canvas(80, 7*7);
#elif DEMO_MATCH3
Canvas GameObject::canvas(5*9, 7*7);
#else
Canvas GameObject::canvas(80, 20);
#endif

vector<GameObject*> GameObject::objs;
vector<GameObject*> GameObject::pendingObjs;

void GameObject::draw() { if (alive == true) canvas.draw(shape, position, dimension, visible); }

void GameObject::Initialize()
{
	objs.clear();

	auto dim = canvas.getDimension();
#ifdef POLYGON
	GameObject::Add(new RegularPolygonManager(5));

#elif DEMO_MATCH3
	GameObject::Add(new Cards(9, 7, { 5,7 }));
#else
	for (int i = 0; i < 5; i++)
	{
		switch (rand() % 2)
		{
		case 0:
			GameObject::Add(new BlinkablePlayer("########  ##########    ##    ", Position{ rand() % dim.x, rand() % dim.y }, Dimension{ 6, 5 }, true));
			break;
		case 1:
			GameObject::Add(new Enemy("\xb2\xb2\xb2\xb2\xb2   \xb2\xb2\xb2\xb2\xb2   \xb2\xb2\xb2\xb2", Position{ rand() % dim.x, rand() % dim.y }, Dimension{ 4, 5 }, true));
			break;
		}
	}
#endif

}

void GameObject::Add(GameObject* obj)
{
	pendingObjs.push_back(obj);
}

void GameObject::Remove(GameObject* obj)
{
	if (obj == nullptr) return;
	objs.erase(find(objs.begin(), objs.end(), obj));
	delete obj;
}

void GameObject::ClearFrame()
{
	canvas.clear();
}

void GameObject::ProcessInput(bool& exit_flag, InputManager& input)
{
#ifdef POLYGON


#elif DEMO_MATCH3

	if (input.getKey('I')) {
		/*
		for (auto obj : objs)
		{
			auto pos = obj->getPosition();
			Debug::Log("[%s (%2df, %ddf) %d %d] ", obj->getShape(), (int)pos.x, (int)pos.y, obj->isVisible(), obj->isAlive());
		}

		for_each(objs.begin(), objs.end(),
			[](auto obj) {
				auto pos = obj->getPosition();
				Debug::Log("[%s (%2df, %ddf) %d %d] ", obj->getShape(), (int)pos.x, (int)pos.y, obj->isVisible(), obj->isAlive());
			}
		);

		for (auto it = objs.begin(); it != objs.end(); it++)
		{
			auto obj = *it;
			auto pos = obj->getPosition();
			Debug::Log("[%s (%2df, %ddf) %d %d] ", obj->getShape(), (int)pos.x, (int)pos.y, obj->isVisible(), obj->isAlive());
		}
		*/

		for (int i = 0; i < objs.size(); i++)
		{
			auto obj = objs[i];
			auto pos = objs[i]->getPosition();

			Debug::Log("[%2d: %s (%2df, %ddf) %d %d] ", i, objs[i]->getShape(), (int)pos.x, (int)pos.y, objs[i]->isVisible(), objs[i]->isAlive());
		}
		

		Bullet::printNumberOfCreatedBullets();
	}
	if (input.getKeyDown(VK_SPACE)) {
		auto canvasDim = canvas.getDimension();

		// pick any player closer to a randomized position.
		auto randPos = Vector2{ (float)(rand() % (canvasDim.x - 5)), (float)(rand() % (canvasDim.y - 2)) };	
	}
	if (input.getKeyDown('Q')) {
		exit_flag = true;
	}

#else
	BlinkablePlayer* player = nullptr;

	if (input.getKey('I')) { // press 'i'
		for_each(objs.begin(), objs.end(),
			[](auto obj) {
				auto pos = obj->getPosition();
				Debug::Log("[%s (%2df, %ddf) %d %d] ", obj->getShape(), (int)pos.x, (int)pos.y, obj->isVisible(), obj->isAlive());
			}
		);
		Bullet::printNumberOfCreatedBullets();
	}
	else if (input.getKeyDown(VK_SPACE)) {
		auto canvasDim = canvas.getDimension();

		// pick any player closer to a randomized position.
		auto randPos = Vector2{ (float)(rand() % (canvasDim.x - 5)), (float)(rand() % (canvasDim.y - 2)) };
		for (auto obj : objs)
		{
			BlinkablePlayer* source = dynamic_cast<BlinkablePlayer*>(obj);
			if (source == nullptr) continue;
			if (source->isVisible() == false) continue;
			if (player == nullptr) {
				player = source;
				continue;
			}
			// player is not null, that is it is assumed to find any player during array traversal.
			if ((source->getPosition()).distance(randPos) < (player->getPosition()).distance(randPos))
				player = source;
		}
		if (player != nullptr) { // if found
			Enemy* enemy = nullptr;
			auto found = find_if(objs.begin(), objs.end(), [](auto obj) { return dynamic_cast<Enemy*>(obj) != nullptr; });
			if (found != objs.end()) enemy = static_cast<Enemy*>(*found);
			auto targetPos = Vector2{ (float)(rand() % canvasDim.x), (float)(rand() % canvasDim.y) };
			if (enemy) targetPos = enemy->getPosition();

			bullet = new Bullet("O", targetPos, { 1,1 }, 1.0f);
			GameObject::Add(bullet);
			bullet->fire(player, targetPos);

			player->setBlinkingPeriod(30);
		}
	}
	else if (input.getKeyDown('Q')) { // 'q'
		exit_flag = true;
	}
	if (input.getMouseButtonDown(0)) {
		auto mousePos = input.getMousePosition();
	}
	if (input.getMouseButton(0)) {
		auto mousePos = input.getMousePosition();
	}
	if (input.getMouseButtonUp(0)) {
		auto mousePos = input.getMousePosition();
	}

#endif



}

void GameObject::UpdateAll(InputManager& input)
{
	for_each(objs.begin(), objs.end(), [&](auto obj) { obj->update(input);  });
	RemoveDeadObjects();
	
	for (auto pending : pendingObjs) objs.push_back(pending);
	pendingObjs.clear();
}

void GameObject::DrawAll()
{
	for_each(objs.cbegin(), objs.cend(), [](auto obj) { obj->draw(); });
}

void GameObject::RenderFrame()
{
	canvas.render();
	Sleep(10);
}

void GameObject::ExamineCollision()
{
	for (auto it = objs.begin(); it != objs.end(); it++)
	{
		auto obj_i = *it;
		if (obj_i->isAlive() == false) continue;
		ICollidable* c_i = dynamic_cast<ICollidable*>(obj_i);
		if (c_i == nullptr) continue;
		for (auto jt = it + 1; jt != objs.end() && obj_i->isAlive() == true; jt++)
		{
			auto obj_j = *jt;
			if (obj_j->isAlive() == false) continue;
			ICollidable* c_j = dynamic_cast<ICollidable*>(obj_j);
			if (c_j == nullptr) continue;
			if (obj_i->isColliding(obj_j) == false)  continue;
			c_j->onCollision(obj_i);
			c_i->onCollision(obj_j);
		}
	}
	RemoveDeadObjects();
}

void GameObject::RemoveDeadObjects()
{
	auto firstToRemove = stable_partition(objs.begin(), objs.end(),
		[](auto obj) { return obj->isAlive(); }
	);
	for (auto it = firstToRemove; it != objs.end(); it++) 
		delete *it;
	objs.erase(firstToRemove, objs.end());
}

void GameObject::Deinitialize()
{
	for (auto it = objs.begin(); it != objs.end(); it++)
		delete *it;
	objs.clear();
}