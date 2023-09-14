#include "stdafx.h"
#include "Obstacle.h"
#include "Obstacle1.h"

Obstacle1::Obstacle1():Obstacle()
{
	root->LoadFile("fallworld.xml");
}

Obstacle1::~Obstacle1()
{
}

void Obstacle1::Init()
{
}

void Obstacle1::Release()
{
}

void Obstacle1::Update()
{
	Obstacle::Update();

	root->Find("obstacle1")->rotation.y += 0.3 * DELTA;
	root->Find("obchild1")->rotation.y -= 2 * DELTA;
}

void Obstacle1::LateUpdate()
{
	Obstacle::LateUpdate();
}

void Obstacle1::Render()
{
	Obstacle::Render();
}
