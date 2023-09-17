#pragma once
class Obstacle3Sphere : public Actor
{
private:
    Vector3 dir;
    float   power = 0.0f;
    bool    isFire = false;
    bool    isHit = false;
    float   fireTime;
    float   disappearTime;
    float   collisionTime;
  
private:
    Obstacle3Sphere();
    virtual ~Obstacle3Sphere();
public:
    static Obstacle3Sphere* Create();
    void	Update() override;
    void    LateUpdate();
    void	Render() override;
    bool    Fire(Vector3 pos, Vector3 dir, float power);
    bool    GetIsFire() { return isFire; }
};

