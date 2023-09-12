#pragma once
class WallMap : public Map
{
public:
    static WallMap* Create(string name = "WallMap");

public:
    list<GameObject*> moveObsColliderList;
    list<GameObject*> obsColliderList2;
    list<GameObject*> boardColliderList;
private:
    bool* isUp;
    bool isBoardChange = false;
    int count = 0;
    float* wallSpeed;
    float boardActiveTime;
    list<GameObject*> boardList1;
    list<GameObject*> boardList2;
private:
    WallMap();
    virtual ~WallMap();
public:
    void	Update() override;
    void    LoadFile(string _file);
};

