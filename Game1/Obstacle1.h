#pragma once
class Obstacle1: public Obstacle
{
private:
	float HitTime;
	bool  isGoCircle;
public:
	Obstacle1();
	~Obstacle1();
	
	virtual void Init();
	virtual void Release(); //����
	virtual void Update()override;
	virtual void LateUpdate();
	virtual void Render()override;

};

