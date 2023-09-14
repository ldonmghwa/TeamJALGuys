#pragma once
class Obstacle2 : public Obstacle
{
public:
	Obstacle2();
	~Obstacle2();
	virtual void Init();
	virtual void Release(); //«ÿ¡¶
	virtual void Update()override;
	virtual void LateUpdate()override;
	virtual void Render()override;

};

