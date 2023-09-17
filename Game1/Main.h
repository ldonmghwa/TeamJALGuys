#pragma once

class Main : public Scene
{
private:
	Scene* SCIntro;
	Scene* SC1;
	Scene* SC2;
	Scene* SC3;
	
	
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
