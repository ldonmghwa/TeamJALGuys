#pragma once
class Obstacle2 : public Obstacle
{
private:
	float CollisionTime;
	bool isGoFoward;
	bool isGoBack;
public:

	
	Obstacle2();
	~Obstacle2();
	Obstacle2(Vector3 pos);
	virtual void Init();
	virtual void Release(); //«ÿ¡¶
	virtual void Update()override;
	virtual void LateUpdate()override;
	virtual void Render()override;
	
};

