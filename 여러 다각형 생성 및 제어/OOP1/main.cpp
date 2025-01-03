#include <iostream>
#include <cstdlib> // include rand()
#include <Windows.h>
#include <conio.h>
#include "GameObject.h"
#include "Utils.h"
#include "InputManager.h"

using namespace std;

/*
* RegularPolygonManager 생성자는 생성할 폴리곤의 갯수를 인자로 받으며, 전달받은 인자의 값에 해당하는 개수만큼 RegularPolygon을 생성합니다.
* 따라서 각각의 생성된 RegularPolygon들은 RegularPolygonManager에 의해 관리됩니다.
* RegularPolygonManager는 Selector 객체를 가지며, Selector를 통해 드래그의 범위를 화면에 나타내고, 범위 내에 RegularPolygon이 있는지 확인하고 선택되게 합니다.
* RegularPolygonManager에서 RegularPolygon의 상태가 선택된 것이 아니라면 업데이트하지 않도록 함으로써, 선택된 RegularPolygon들에 대해서만 폴리곤 변경 기능을 제공하도록 하였습니다.
*/

int main()
{
	GameObject::Initialize();
    InputManager input;
	bool exit_flag = false;

	while (exit_flag == false)
	{
		GameObject::ClearFrame();
		input.readEveryFrame();

		GameObject::ProcessInput(exit_flag, input);

		GameObject::ExamineCollision();

		GameObject::UpdateAll(input);
		
		GameObject::DrawAll();

		GameObject::RenderFrame();
	}

    GameObject::Deinitialize();

	return 0;
}

