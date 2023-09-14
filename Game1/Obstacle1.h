#pragma once
class Obstacle1: public Obstacle
{
public:
	Obstacle1();
	~Obstacle1();
	virtual void Init();
	virtual void Release(); //«ÿ¡¶
	virtual void Update()override;
	virtual void LateUpdate();
	virtual void Render()override;

};

