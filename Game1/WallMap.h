#pragma once
class WallMap : public Map
{
public:
    static WallMap* Create(string name = "WallMap");

public:
    list<GameObject*> moveObsColliderList;
    list<GameObject*> obsColliderList2;
private:
    bool* isUp;
    int count = 0;
    float* wallSpeed;
private:
    WallMap();
    virtual ~WallMap();
public:
    void	Update() override;
    void    LoadFile(string _file);
};

