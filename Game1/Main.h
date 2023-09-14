#pragma once

class Main : public Scene
{
private:
	Scene* SCIntro;
	Scene* SC1;
	Scene* SC2;
	/*Camera* cam1;
	Grid* grid;
	WallMap* map;
	Actor* obstacle;*/
	
	/*Actor* pillar1Ob;
	Actor* pillar1Root;*/
	
	
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
