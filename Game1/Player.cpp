#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	body = Actor::Create();
	body->LoadFile("Player.xml");

	Second1 = UI::Create();
	Second1->LoadFile("Second1.xml");
	Second1->name = "Second1";

	Second10 = UI::Create();
	Second10->LoadFile("Second10.xml");
	Second10->name = "Second10";
	

	motionDir = 20.0f;
	gravityPower = 40.0f;
	jumpPower = 20.0f;
	moveSpeed = 10.0f;
	jumpmoveSpeed = moveSpeed - 2.0f;

	SOUND->AddSound("jump.mp3", "jump");
	SOUND->AddSound("dash.mp3", "dash");
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
		SOUND->Stop("dash");
		SOUND->Play("jump");
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
		SOUND->Stop("jump");
		SOUND->Play("dash");
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
	cout << second1 << endl;
	cout << second1 << endl;
	ShowCursor(false);
	
	/*ImGui::Text("second1 %d", second1);
	ImGui::Text("second10 %d", second10);
	ImGui::Text("time %f", playerTime);*/

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
		ShowCursor(true);
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
	
	playerTime += DELTA;

	second1 = (int)playerTime % 10;
	second10 = (int)playerTime / 10;

	

	Control();
	Motion();
	body->Update();
	Second1->Update();
	Second10->Update();
}

void Player::LateUpdate()
{
	/*if (second10 < 1) Second10->texture->LoadFile("0.jpg");
	else if (second10 < 2) Second10->texture->LoadFile("1.jpg");
	else if (second10 < 3) Second10->texture->LoadFile("2.jpg");
	else if (second10 < 4) Second10->texture->LoadFile("3.jpg");
	else if (second10 < 5) Second10->texture->LoadFile("4.jpg");

	if (second1 < 1) Second1->texture->LoadFile("0.jpg");
	else if (second1 < 2) Second1->texture->LoadFile("1.jpg");
	else if (second1 < 3) Second1->texture->LoadFile("2.jpg");
	else if (second1 < 4) Second1->texture->LoadFile("3.jpg");
	else if (second1 < 5) Second1->texture->LoadFile("4.jpg");*/

}

void Player::Render()
{
	body->Render();
	//Second1->Render();
	//Second10->Render();
}


