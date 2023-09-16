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
    bool*                 isPillarUnderUp;
    bool*                 isUpDownBoardUp;
    bool*                 isLeftRightBoardGo;
    bool                  isGlitingBoardChange = false;
    bool                  isUpDownBoardLanding = false;
    bool                  isUpDownBoardUpP = false;
    float*                pillarUnderSpeed;
    float*                upDownBoardSpeed;
    float                upDownBoardSpeedP;
    float*                leftRightBoardSpeed;
    float*                glitingBoardActiveTime;
    float*                backUpGlitingBoardActiveTime;
    float                 landingYPos;
    float                 playerScaleY;
    

    vector<GameObject*>   glitingBoardList1;
    vector<GameObject*>   glitingBoardList2;
    vector<GameObject*>   upDownBoardList1;
    vector<GameObject*>   upDownBoardList2;

    Vector3               playerLandPos;
    GameObject*           ground0;
    GameObject*           ground1;
    GameObject*           ground2;
    GameObject*           ground3;
    GameObject*           goal;
    GameObject*           landingBoard;
private:
    WallMap();
    virtual ~WallMap();
public:
    void Init();
    void Update() override;
    void LoadFile(string _file);
    void LateUpdate();
};