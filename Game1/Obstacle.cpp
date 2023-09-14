#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle()
{
	root = Actor::Create();
}

Obstacle::~Obstacle()
{
}

void Obstacle::Init()
{
}

void Obstacle::Release()
{
}

void Obstacle::Update()
{
	root->Update();
}

void Obstacle::LateUpdate()
{
	
}

void Obstacle::Render()
{
	root->Render();
}
