#pragma once

class Main : public Scene
{
private:

	Camera* cam1;
	Grid* grid;
	WallMap* map;
	Actor* pillar1Ob;
	Actor* pillar1Root;
	vector<GameObject*> vMapOb;
	//UI* ui;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};