#pragma once

class Main : public Scene
{
private:

	Camera* cam1;
	Grid* grid;
	WallMap* map;
	Actor* obstacle1;
	Actor* obstacle2;
	Actor* obstacle1Root;
	//UI* ui;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
