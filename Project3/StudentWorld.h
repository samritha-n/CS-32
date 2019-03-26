#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>
#include <list>
#include "Level.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    virtual ~StudentWorld();
    
    bool checkCanMoveTo(double dest_x, double dest_y, Actor* actor);
    bool checkPenelopeOverlap(double x, double y);
    bool checkObjectOverlap(double x, double y, double x2, double y2);
    bool checkBoundaryBoxOverlap(double x1, double y1, double x2, double y2);
 //   bool exitOverlap(double x, double y);
    bool pitOverlap(double x, double y);
    bool citizenOverlap(double x, double y);
    Actor* getPenelope() {return m_penelope;}
    void finishedLevel();
    void citizenEscaped();
    bool locateNearestVomitTrigger(double x, double y, double& otherX, double& otherY, double& distance);
    bool locateNearestCitizenTrigger(double x, double y, double& otherX, double& otherY, double& distance, bool& isThreat);
    bool locateNearestCitizenThreat(double x, double y, double& otherX, double& otherY, double& distance);
    int loadLevelData();
    std::string updateStatus();
    bool citizensLeft() {return m_citizensLeft;}
    void addVomit(double x, double y, int dir);
    void addLandmine(double x, double y);
    void addPit(double x, double y);
    void addSmartZombie(double x, double y);
    void addDumbZombie(double x, double y);
    void addFlame(double x, double y, int dir);
    void addVaccineGoodie(double x, double y);
    void givePenelopeVaccine();
    void pickUpGasCan();
    void pickUpMineGoodie();
    bool isAgentMovementBlockedAt(double x, double y);
    bool isFlameBlockedAt(double x, double y);
    bool isZombieVomitTriggerAt(double x, double y);
    
private:
    Penelope* m_penelope;
    std::list<Actor*> m_charList;
    bool m_finishedLevel;
    int m_citizensLeft;
};

#endif // STUDENTWORLD_H_
