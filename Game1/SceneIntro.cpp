#include "stdafx.h"
#include "SceneIntro.h"

SceneIntro::SceneIntro()
{
	title = UI::Create();
	title->LoadFile("Title.xml");

	SOUND->AddSound("titlebgm.mp3","titlebgm");
	SOUND->AddSound("selectMove.mp3", "move");
}

SceneIntro::~SceneIntro()
{
}

void SceneIntro::Init()
{
	SOUND->SetVolume("titlebgm", 0.6f);
	SOUND->Play("titlebgm");
}

void SceneIntro::Release()
{
}

void SceneIntro::Update()
{
	title->RenderHierarchy();

	ShowCursor(true);
	

	switch (select) {
	case 0:
		title->Find("Start")->scale.x = 0.22f;
		title->Find("Start")->scale.y = 0.12f;
		title->Find("Cont")->scale.x = 0.2f;
		title->Find("Cont")->scale.y = 0.1f;
		title->Find("Quit")->scale.x = 0.2f;
		title->Find("Quit")->scale.y = 0.1f;
		if (INPUT->KeyDown(VK_RETURN)) {
			SOUND->Stop("titlebgm");
			SCENE->ChangeScene("SC1");
		}
		break;
	case 1:
		title->Find("Cont")->scale.x = 0.22f;
		title->Find("Cont")->scale.y = 0.12f;
		title->Find("Start")->scale.x = 0.2f;
		title->Find("Start")->scale.y = 0.1f;
		title->Find("Quit")->scale.x = 0.2f;
		title->Find("Quit")->scale.y = 0.1f;
		if (INPUT->KeyDown(VK_RETURN)) {
			title->Find("ContUi")->visible = not title->Find("ContUi")->visible;
		}
		break;
	case 2:
		title->Find("Quit")->scale.x = 0.22f;
		title->Find("Quit")->scale.y = 0.12f;
		title->Find("Start")->scale.x = 0.2f;
		title->Find("Start")->scale.y = 0.1f;
		title->Find("Cont")->scale.x = 0.2f;
		title->Find("Cont")->scale.y = 0.1f;
		if (INPUT->KeyDown(VK_RETURN)) {
			exit(0);
		}
		break;
	}

	if (select < 2) {
		if (INPUT->KeyDown(VK_DOWN)) {
			SOUND->Stop("move");
			SOUND->Play("move");
			select++;
		}
	}
	if (select > 0) {
		if (INPUT->KeyDown(VK_UP)) {
			SOUND->Stop("move");
			SOUND->Play("move");
			select--;
		}
	}


	title->Update();
	Camera::main->Update();
}

void SceneIntro::LateUpdate()
{
}

void SceneIntro::Render()
{
	Camera::main->Set();
	title->Render();
}

void SceneIntro::PreRender()
{
}

void SceneIntro::ResizeScreen()
{
	Camera::main->viewport.x = 0.0f;
	Camera::main->viewport.y = 0.0f;
	Camera::main->viewport.width = App.GetWidth();
	Camera::main->viewport.height = App.GetHeight();
	
	Camera::main->width = App.GetWidth();
	Camera::main->height = App.GetHeight();
}
