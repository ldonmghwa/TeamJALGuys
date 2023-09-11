#pragma once
class WallMap : public Map
{
public:
    static WallMap* Create(string name = "WallMap");
private:
    bool* isUp;
    int count = 0;
    float* wallSpeed;
    list<GameObject*> movePillarList;
private:
    WallMap();
    virtual ~WallMap();
public:
    void	Update() override;
    void    LoadFile(string _file);
};

