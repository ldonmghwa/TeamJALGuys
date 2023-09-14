#pragma once
class Obstacle
{
public:
	class Actor* root;

	Obstacle();
	~Obstacle();
	virtual void Init();
	virtual void Release(); //«ÿ¡¶
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	
};

