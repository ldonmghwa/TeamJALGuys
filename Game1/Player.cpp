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
	body->SetWorldPosY(2.0f);
	isLand = false;
	moveSpeed = 5.0f;
	gravity = 0;
	jumpPower = 5.0f;
}

void Player::Control()
{
	//앞뒤좌우 움직임
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

	//점프
	if (INPUT->KeyDown(VK_SPACE)) {
		//y축 위치 1 띄워서 island 변수 false로 만들고
		body->SetWorldPosY(body->GetWorldPos().y + 1.0f);
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
	else gravity += 1.0f * DELTA;

	Control();

	body->Update();
}

void Player::Render()
{
	body->Render();
}


