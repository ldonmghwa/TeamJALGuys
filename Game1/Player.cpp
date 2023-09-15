#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	body = Actor::Create();
	body->LoadFile("Player.xml");

}

Player::~Player()
{
}

void Player::Init()
{
	body->SetWorldPosY(5.0f);
	moveSpeed = 10.0f;
	jumpmoveSpeed = moveSpeed - 3.0f;
	gravity = 0;
}
//State 변경
void Player::Control()
{
	//Run
	if (state != PlayerState::DIVE) {
		if (INPUT->KeyPress('W')) {
			state = PlayerState::RUN;
		}
		if (INPUT->KeyPress('A')) {
			state = PlayerState::RUN;
		}
		if (INPUT->KeyPress('S')) {
			state = PlayerState::RUN;
		}
		if (INPUT->KeyPress('D')) {
			state = PlayerState::RUN;
		}
		if (diveCool > 0) diveCool -= DELTA;
		diveTime = 0.3f;
	}
	//Dash
	if (diveCool <= 0) {
		if (INPUT->KeyDown('F')) {
			state = PlayerState::DIVE;
			diveCool = 0.8f;
		}
	}
	if (INPUT->KeyUp('W')) {
		state = PlayerState::IDLE;
	}
	if (INPUT->KeyUp('A')) {
		state = PlayerState::IDLE;
	}
	if (INPUT->KeyUp('S')) {
		state = PlayerState::IDLE;
	}
	if (INPUT->KeyUp('D')) {
		state = PlayerState::IDLE;
	}
	if (diveTime <= 0) {
		state = PlayerState::IDLE;
	}
}
//State에 따른 실제 움직임
void Player::Move()
{
	switch (state) {
		case PlayerState::IDLE:
			diveTime = 0.3f;
		break;
		case PlayerState::RUN:
			if (INPUT->KeyPress('W')) {
				body->MoveWorldPos(body->GetForward() * moveSpeed * DELTA);
			}
			if (INPUT->KeyPress('A')) {
				body->MoveWorldPos(-body->GetRight() * moveSpeed * DELTA);
			}
			if (INPUT->KeyPress('S')) {
				body->MoveWorldPos(-body->GetForward() * moveSpeed * DELTA);
			}
			if (INPUT->KeyPress('D')) {
				body->MoveWorldPos(body->GetRight() * moveSpeed * DELTA);
			}
		break;
		case PlayerState::JUMP:
			if (INPUT->KeyPress('W')) {
				body->MoveWorldPos(body->GetForward() * jumpmoveSpeed * DELTA);
			}
			if (INPUT->KeyPress('A')) {
				body->MoveWorldPos(-body->GetRight() * jumpmoveSpeed * DELTA);
			}
			if (INPUT->KeyPress('S')) {
				body->MoveWorldPos(-body->GetForward() * jumpmoveSpeed * DELTA);
			}
			if (INPUT->KeyPress('D')) {
				body->MoveWorldPos(body->GetRight() * jumpmoveSpeed * DELTA);
			}
		break;
		case PlayerState::DIVE:
			if (diveTime >= 0) {
				body->MoveWorldPos(body->GetForward() * divePower * DELTA);
			}
			else {
				state = PlayerState::IDLE;
			}
			diveTime -= DELTA;
		break;
	}

	//점프
	if (isLand) {
		if (INPUT->KeyDown(VK_SPACE)) {
			body->SetWorldPosY(body->GetWorldPos().y + 0.5f);
			gravity = -jumpPower;
		}
	}

	
}

void Player::Motion()
{
	if (state == PlayerState::IDLE) {

	}
	else if (state == PlayerState::RUN) {

	}
	else if (state == PlayerState::JUMP) {

	}
	else if (state == PlayerState::CRASH) {

	}
}

void Player::Update()
{
	ShowCursor(true);

	//중력 & 떨어지는 움직임(어떤 상황에서도 작용)
	body->MoveWorldPos(-body->GetUp() * gravity * DELTA);
	if (isLand) gravity = 0;
	else gravity += 25.0f * DELTA;

	//카메라 고정 풀기
	if (INPUT->KeyDown(VK_F10)) PCamActive = not PCamActive;

	if (PCamActive) {
		POINT ptMouse;
		ptMouse.x = App.GetHalfWidth();
		ptMouse.y = App.GetHalfHeight();
		Vector3 Rot;
		Rot.x = (INPUT->position.y - ptMouse.y) * 0.001f;
		Rot.y = (INPUT->position.x - ptMouse.x) * 0.001f;
		player->body->rotation.y += Rot.y;
		Camera::main->rotation.x += Rot.x;
		ClientToScreen(App.GetHandle(), &ptMouse);
		SetCursorPos(ptMouse.x, ptMouse.y);

		Move();
	}
	else {
		gravity = 0;

		if (INPUT->KeyPress('W')) {
			body->MoveWorldPos(body->GetForward() * 50 * DELTA);
		}
		if (INPUT->KeyPress('A')) {
			body->MoveWorldPos(-body->GetRight() * 50 * DELTA);
		}
		if (INPUT->KeyPress('S')) {
			body->MoveWorldPos(-body->GetForward() * 50 * DELTA);
		}
		if (INPUT->KeyPress('D')) {
			body->MoveWorldPos(body->GetRight() * 50 * DELTA);
		}
		if (INPUT->KeyPress('Q')) {
			body->MoveWorldPos(-body->GetUp() * 50 * DELTA);
		}
		if (INPUT->KeyPress('E')) {
			body->MoveWorldPos(body->GetUp() * 50 * DELTA);
		}
		if (INPUT->KeyPress(VK_RBUTTON))
		{
			Vector3 Rot;
			Rot.x = INPUT->movePosition.y * 0.001f;
			Rot.y = INPUT->movePosition.x * 0.001f;
			body->Find("PCam")->rotation += Rot;
		}
	}
	oldPosition = body->GetWorldPos();

	Control();

	body->Update();
}

void Player::Render()
{
	body->Render();
}


