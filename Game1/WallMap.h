#pragma once
class WallMap : public Map
{
public:
    static WallMap* Create(string name = "WallMap");

public:
    vector<GameObject*>   pillarUnderList;
    vector<GameObject*>   pillarList;
    vector<GameObject*>   glitingBoardList;
    vector<GameObject*>   upDownBoardList;
    vector<GameObject*>   leftRightBoardList;
private:
    bool* isPillarUnderUp;
    bool* isUpDownBoardUp;
    bool                  isGlitingBoardChange = false;
    int                   count = 0;
    float* pillarUnderSpeed;
    float* upDownBoardSpeed;
    float                 glitingBoardActiveTime;
    vector<GameObject*>   glitingBoardList1;
    vector<GameObject*>   glitingBoardList2;
    vector<GameObject*>   upDownBoardList1;
    vector<GameObject*>   upDownBoardList2;
private:
    WallMap();
    virtual ~WallMap();
public:
    void	Update() override;
    void    LoadFile(string _file);
};

