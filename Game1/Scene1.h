#pragma once
class Scene1 : public Scene
{
private:
	Grid* grid;
	class WallMap* map;
	Actor* wallskin;
	Actor* wall;
	float mapEndingTime;
	bool isTimeStop = false;
	Actor* dron;

public:
	Scene1();
	~Scene1();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void ResizeScreen() override;
};
