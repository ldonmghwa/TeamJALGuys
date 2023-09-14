#pragma once
class GameManager : public Singleton<GameManager>
{
public:
	list<class Obstacle*> obstacleList;

	virtual ~GameManager();
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void ResizeScreen();
};

