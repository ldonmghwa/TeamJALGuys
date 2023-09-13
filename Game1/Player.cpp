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

void Player::Control()
{
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
	if (INPUT->KeyDown(VK_SPACE)) {
		state = PlayerState::JUMP;
	}
	if (INPUT->KeyPress('F')) {
		state = PlayerState::DIVE;
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

}

void Player::Move()
{
	if (INPUT->KeyDown(VK_F1)) PCamActive = not PCamActive;

	//�յ��¿� ������
	switch (state) {
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
	}
	//����
	if (INPUT->KeyDown(VK_SPACE)) {
		//y�� ��ġ 1 ����� island ���� false�� �����
		body->SetWorldPosY(body->GetWorldPos().y + 0.1f);
		//�����Ŀ� ������ �Ҵ�
		gravity = -jumpPower;
	}
	//���̺�
	if (INPUT->KeyDown('F')) {
		body->MoveWorldPos(body->GetForward() * divePower * DELTA);
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
	//�߷� & �������� ������(� ��Ȳ������ �ۿ�)
	body->MoveWorldPos(-body->GetUp() * gravity * DELTA);
	if (isLand) gravity = 0;
	else gravity += 25.0f * DELTA;

	oldPosition = body->GetWorldPos();

	Control();
	Move();


	body->Update();
}

void Player::Render()
{
	body->Render();
}


