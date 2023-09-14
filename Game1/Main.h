#pragma once

class Main : public Scene
{
private:
	Grid* grid;
	WallMap* map;
	Actor* obstacle;
	UI* ui;
	UI* mouse;
	UI* cursor;
	
	/*Actor* pillar1Ob;
	Actor* pillar1Root;*/
	
	
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
