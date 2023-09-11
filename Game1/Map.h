#pragma once
class Map :public Actor
{
protected:
    static Map* Create(string name = "Map");
protected:
    int obstacleNum;
    list<GameObject*> obstacleList;
protected:
    Map();
    virtual ~Map();
public:
    void	Update();
    void    LoadFile(string _file);
    void    AddObstacle(string _file);
};

