#pragma once
class Obstacle3 : public Obstacle
{
private:
	class Obstacle3Sphere* ball[2];
	float fireTime;
	
public:
	Obstacle3();
	~Obstacle3();
	Obstacle3(Vector3 pos);
	virtual void Init();
	virtual void Release(); //«ÿ¡¶
	virtual void Update()override;
	virtual void LateUpdate()override;
	virtual void Render()override;
	

};

