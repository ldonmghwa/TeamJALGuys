#pragma once
class Map :public Actor
{
public:
    static Map* Create(string name = "Map");
private:
    Map();
    virtual ~Map();
public:
    void	Update() override;

};

