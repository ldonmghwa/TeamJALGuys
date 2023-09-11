#include "stdafx.h"
#include "Main.h"

Main::Main()
{
	

}

Main::~Main()
{
}

void Main::Init()
{
}

void Main::Release()
{
   
}

void Main::Update()
{
	
}

void Main::LateUpdate()
{
}

void Main::Render()
{
	
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    App.SetAppName(L"MapTool");
    App.SetInstance(instance);
	App.InitWidthHeight(1600.f,900.0f);
    App.background = Color(0.3, 0.3, 0.3);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}