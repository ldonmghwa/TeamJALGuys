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
	float jumpmoveSpeed = 0;
	float gravityPower = 0;
	float diveTime = 0.3f;
	float diveCool = 0;
	float jumpPower = 0;
	const float divePower = 30.0f;
	float playerTime = 0;
	int second1 = 0;
	int second10 = 0;

	bool gameStart = 0;
	bool isJump = 0;
	bool motionR = 0;
	bool motionJ = 0;
	bool motionD = 0;
	float motionDir = 0;
public:
	UI* Second1;
	UI* Second10;
	Actor* body;
	float gravity = 0;

	bool isLand = 0;
	bool PCamActive = 1;
public:
	Player();
	~Player();
	void Init(Vector3 pos);
	void Control();
	void Move();
	void Motion();
	void Update();
	void LateUpdate();
	void Render();
	Actor* GetBody() { return body; }
	Vector3 GetWorldPos() { return body->GetWorldPos(); }
	bool Crash(Actor* object) { return body->Intersect(object); }
};

