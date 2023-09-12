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
	//�յ��¿� ������
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

	//����
	if (INPUT->KeyDown(VK_SPACE)) {
		//y�� ��ġ 1 ����� island ���� false�� �����
		body->SetWorldPosY(body->GetWorldPos().y + 1.0f);
		//�����Ŀ� ������ �Ҵ�
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
	

	//�߷� & �������� ������(� ��Ȳ������ �ۿ�)
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


