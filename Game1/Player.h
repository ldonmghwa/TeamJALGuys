#pragma once
enum class PlayerState {
	IDLE, RUN, JUMP, CRASH
};
class Player : public Singleton<Player>
{
private:

	PlayerState state = PlayerState::IDLE;
	float moveSpeed = 0;
	float gravity = 0;
	float jumpPower = 0;
public:
	Actor* body;
	bool isLand = 0;
public:
	Player();
	~Player();
	void Init();
	void Control();
	void Motion();
	void Update();
	void Render();
	Actor* GetBody() { return body; }
	Vector3 GetWorldPos() { return body->GetWorldPos(); }
	bool Crash(Actor* object) { return body->Intersect(object); }
	
};

