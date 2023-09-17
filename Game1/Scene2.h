#pragma once
class Scene2 : public Scene
{
private:
	Grid*  grid;
	Actor* obstacle;
	Actor* ground;
	Actor* temp;
	Actor* wallskin;
	Actor* wall;
	bool   isCheck1;
	bool   isCheck2;
public:
	Scene2();
	~Scene2();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void ResizeScreen() override;
};
