#pragma once
class Obstacle
{
public:
	class Actor* root;

	Obstacle();
	~Obstacle();
	virtual void Init();
	virtual void Release(); //����
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	
};

