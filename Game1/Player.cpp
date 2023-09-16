#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	body = Actor::Create();
	body->LoadFile("Player.xml");

	motionDir = 20.0f;
	gravityPower = 40.0f;
	jumpPower = 20.0f;
	moveSpeed = 10.0f;
	jumpmoveSpeed = moveSpeed - 2.0f;
}

Player::~Player()
{
}

void Player::Init(Vector3 pos)
{
	body->SetWorldPos(pos);
}
//State 변경
void Player::Control()
{
	//Run--------------------------------------------------------------------------
	if (state == PlayerState::IDLE) {
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
	//Dash--------------------------------------------------------------------------
	if (diveCool <= 0) {
		if (INPUT->KeyDown('F')) {
			state = PlayerState::DIVE;
			diveCool = 0.8f;
		}
	}
	if (state != PlayerState::DIVE) {
		if (diveCool > 0) diveCool -= DELTA;
		diveTime = 0.3f;
	}
	if (diveTime <= 0) {
		state = PlayerState::IDLE;
	}
	//Jump--------------------------------------------------------------------------
	if (state == PlayerState::JUMP) {
		if (isLand) state = PlayerState::IDLE;
	}
	if (state == PlayerState::IDLE || state == PlayerState::RUN) {
		if (INPUT->KeyDown(VK_SPACE)) {
			body->SetWorldPosY(body->GetWorldPos().y + 1.5f);
			gravity = -jumpPower;
			state = PlayerState::JUMP;
		}
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
			diveTime -= DELTA;
		break;
	}
}

void Player::Motion()
{
	if (body->Find("LhBody")->rotation.y <= -motionDir *ToRadian) motionR = true;
	else if(body->Find("LhBody")->rotation.y >= motionDir * ToRadian)motionR = false;
	if (body->Find("LhBody")->rotation.z <= -motionDir * ToRadian) motionJ = true;
	else if (body->Find("LhBody")->rotation.z >= motionDir * ToRadian)motionJ = false;

	if (state == PlayerState::IDLE) {
		body->Find("LhBody")->rotation = Vector3();
		body->Find("RhBody")->rotation = Vector3();
		motionD = false;
	}
	else if (state == PlayerState::RUN) {
		body->Find("LhBody")->rotation.z = 0;
		body->Find("RhBody")->rotation.z = 0;
		if (motionR) {
			body->Find("LhBody")->rotation.y += 2.5f * DELTA;
		}
		else {
			body->Find("LhBody")->rotation.y -= 2.5f * DELTA;
		}
		if (motionR) {
			body->Find("RhBody")->rotation.y += 2.5f * DELTA;
		}
		else {
			body->Find("RhBody")->rotation.y -= 2.5f * DELTA;
		}
	}
	else if (state == PlayerState::JUMP) {
		body->Find("LhBody")->rotation.y = 0;
		body->Find("RhBody")->rotation.y = 0;
		if (motionJ) {
			body->Find("LhBody")->rotation.z += 5.1f * DELTA;
		}
		else {
			body->Find("LhBody")->rotation.z -= 5.1f * DELTA;
		}
		if (motionJ) {
			body->Find("RhBody")->rotation.z -= 5.1f * DELTA;
		}
		else {
			body->Find("RhBody")->rotation.z += 5.1f * DELTA;
		}
	}
	else if (state == PlayerState::DIVE) {
		if (!motionD) {
			body->Find("LhBody")->rotation = Vector3();
			body->Find("RhBody")->rotation = Vector3();
		}
		motionD = true;
		if (body->Find("LhBody")->rotation.y>=-38.0f*ToRadian) {
			body->Find("LhBody")->rotation.y -= 4.1f * DELTA;
		}
		if (body->Find("RhBody")->rotation.y <= 38.0f * ToRadian) {
			body->Find("RhBody")->rotation.y += 4.1f * DELTA;
		}
	}
}

void Player::Update()
{
	ShowCursor(true);
	
	ImGui::Text("state %d", (int)state);
	ImGui::Text("island %d", isLand);

	//중력 & 떨어지는 움직임(어떤 상황에서도 작용)
	body->MoveWorldPos(-body->GetUp() * gravity * DELTA);
	if (isLand) gravity = 0;
	else gravity += gravityPower * DELTA;

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
	Motion();

	body->Update();
}

void Player::Render()
{
	body->Render();
}


