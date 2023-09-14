#pragma once
class SceneIntro : public Scene
{
private:


public:
	SceneIntro();
	~SceneIntro();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void ResizeScreen() override;
};
