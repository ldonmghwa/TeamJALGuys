#pragma once
enum class PlayerState {
	IDLE, RUN, JUMP, DIVE, CRASH
};
class Player : public Singleton<Player>
{
private:
	PlayerState state = PlayerState::IDLE;
	Vector3 oldPosition = Vector3();

	float moveSpeed = 0;
	float gravity = 0;
	float diveTime = 0.3f;
	float diveCool = 0;
	const float jumpPower = 15.0f;
	const float divePower = 30.0f;

public:
	Actor* body;

	bool isLand = 0;
	bool PCamActive = 1;
public:
	Player();
	~Player();
	void Init();
	void Control();
	void Move();
	void Motion();
	void Update();
	void Render();
	Actor* GetBody() { return body; }
	Vector3 GetWorldPos() { return body->GetWorldPos(); }
	bool Crash(Actor* object) { return body->Intersect(object); }
};

