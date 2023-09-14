#include "stdafx.h"
#include "Obstacle.h"
#include "Obstacle2.h"

Obstacle2::Obstacle2() :Obstacle()
{
	root->LoadFile("obstacleWindmill.xml");
}

Obstacle2::~Obstacle2()
{
}

void Obstacle2::Init()
{
}

void Obstacle2::Release()
{
}

void Obstacle2::Update()
{
	Obstacle::Update();
	root->Find("obstacle1Root")->rotation.z += DELTA;
	root->Find("obstacle1poll1")->SetWorldPos(root->Find("obstacle1Root")->GetWorldPos());
}

void Obstacle2::LateUpdate()
{
	Obstacle::LateUpdate();
}

void Obstacle2::Render()
{
	Obstacle::Render();
}
