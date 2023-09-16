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
    bool* isLeftRightBoardGo;
    bool                  isGlitingBoardChange = false;
    float* pillarUnderSpeed;
    float* upDownBoardSpeed;
    float* leftRightBoardSpeed;
    float                 glitingBoardActiveTime;
    float                 backUpGlitingBoardActiveTime;
    vector<GameObject*>   glitingBoardList1;
    vector<GameObject*>   glitingBoardList2;
    vector<GameObject*>   upDownBoardList1;
    vector<GameObject*>   upDownBoardList2;
private:
    WallMap();
    virtual ~WallMap();
public:
    void Update() override;
    void LoadFile(string _file);
    void LateUpdate();
};