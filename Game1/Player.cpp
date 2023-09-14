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
	}
	//Jump
	if (INPUT->KeyDown(VK_SPACE)) {
		state = PlayerState::JUMP;
	}
	//Dash
	if (diveCool <= 0) {
		if (INPUT->KeyDown('F')) {
			state = PlayerState::DIVE;
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
	case PlayerState::DIVE:
		diveTime -= DELTA;
		diveCool = 0.8f;
		if (diveTime > 0) {
			body->MoveWorldPos(body->GetForward() * divePower * DELTA);
		}
		break;
	}
	//점프
	if (INPUT->KeyDown(VK_SPACE)) {
		//y축 위치 1 띄워서 island 변수 false로 만들고
		body->SetWorldPosY(body->GetWorldPos().y + 0.5f);
		//점프파워 음수로 할당
		gravity = -jumpPower;
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
	//중력 & 떨어지는 움직임(어떤 상황에서도 작용)
	body->MoveWorldPos(-body->GetUp() * gravity * DELTA);
	if (isLand) gravity = 0;
	else gravity += 25.0f * DELTA;
	//카메라 고정 풀기
	if (INPUT->KeyDown(VK_F1)) PCamActive = not PCamActive;

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

	if (player->PCamActive) {
		Move();

		// cursor->visible = false;
	}
	else {
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
	}
	oldPosition = body->GetWorldPos();

	
	Control();
	

	body->Update();
}

void Player::Render()
{
	body->Render();
}


