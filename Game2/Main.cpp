#include "stdafx.h"
#include "Main.h"

Main::Main()
{
	

	//투명 이미지출력
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
void Main::PreRender()
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
	App.SetAppName(L"Game2");
	App.SetInstance(instance);
	//App.InitWidthHeight(1000.0f, 640.0f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}