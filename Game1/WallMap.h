#pragma once
class WallMap : public Map
{
public:
    static WallMap* Create(string name = "WallMap");
private:
    bool* isUp = nullptr;
    int count = 0;
    float* wallSpeed = nullptr;
    list<GameObject*> movePillarList;
private:
    WallMap();
    virtual ~WallMap();
public:
    void	Update() override;
    void    LoadFile(string _file);
};

