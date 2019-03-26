#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>


class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject
{
public:
    Actor(StudentWorld* stw, double startX, double startY, int dir, int depth, int imageID);
    // Actor(int startX, int startY);
    virtual void doSomething() = 0;
    StudentWorld* getWorld();
    bool isAlive(){ return m_isAlive;}
    virtual void setDead() {m_isAlive = false;}
    int getInfectCount() {return m_infectionCount;}
    void incInfect() {m_infectionCount++;}
  //  void clearInfection() {m_infectionCount = 0;}
    bool isInfected();
    void setInfectStatus(bool status) {m_infectionStatus = status;}
    virtual bool blocksMovement() const {return false;}
    virtual bool blocksFlame() const {return false;}
    virtual bool canExit() const {return false;}
    virtual bool triggersOnlyActiveLandmines() const {return false;}
    virtual bool triggersZombieVomit() const {return false;}
    virtual bool threatensCitizens() const {return false;}
    virtual bool triggersCitizens() const {return false;}
    virtual bool threatToPlayer() const {return false;}
    bool escape() {return m_escaped;}
    void activate() {m_isActive=true;}
    bool isActive() {return m_isActive;}
    
private:
    StudentWorld* m_stw;
    bool m_isAlive;
    int m_infectionCount;
    int m_infectionStatus;
    int m_playerScore;
    bool m_escaped;
    bool m_isActive;
    
};
class Agent : public Actor
{
public:
    Agent(StudentWorld* stw, double startX, double startY, const int IID);
    virtual bool blocksMovement() const {return true;}
    virtual bool triggersOnlyActiveLandmines() const {return true;}
    
};
class Zombie : public Agent
{
public:
    Zombie(StudentWorld* stw, double startX, double startY, int movementDist);
    int getPlanDist();
    void setPlanDist(int dist);
    virtual void doSomething() = 0;
    bool isParalyzed() {return m_paralyzed;}
    void setParalyzed(bool value) {m_paralyzed = value;}
    virtual void makePlan() = 0;
    virtual bool threatensCitizens() {return true;}
    virtual void setDead() = 0;
    
private:
    bool m_paralyzed;
    int m_planDistance;
};
class DumbZombie : public Zombie
{
public:
    DumbZombie(StudentWorld* stw, double startX, double startY);
    virtual void doSomething();
    virtual void makePlan();
    virtual void setDead();
};
class SmartZombie : public Zombie
{
public:
    SmartZombie(StudentWorld* stw, double startX, double startY);
    virtual void doSomething();
    virtual void makePlan();
    virtual bool blocksMovement() const {return true;}
    virtual void setDead();
};
class Wall : public Actor
{
public:
    Wall(StudentWorld* stw, double startX, double startY);
    virtual void doSomething();
    virtual bool blocksMovement() const {return true;}
    virtual bool blocksFlame() const {return true;}
};
class ActivatingObject : public Actor
{
public:
    ActivatingObject(StudentWorld* stw, double startX, double startY, int dir, int imageID);
};
class Exit : public ActivatingObject
{
public:
    Exit(StudentWorld* stw, double startX, double startY);
    virtual void doSomething();
    virtual bool blocksFlame() {return true;}
    virtual bool canExit() const {return true;}
    //virtual void activateIfAppropriate(Actor* a);
};
class Pit : public ActivatingObject
{
public:
    Pit(StudentWorld* stw, double startX, double startY);
    virtual bool threatToPlayer() const {return true;}
    virtual void doSomething();
   // virtual void activateIfAppropriate(Actor* a);
};
class Flame : public ActivatingObject
{
public:
    Flame(StudentWorld* stw, double startX, double startY, int dir);
    virtual bool threatToPlayer() const {return true;}
    virtual void doSomething();
   // virtual void activateIfAppropriate(Actor* a);
};
class Vomit : public ActivatingObject
{
public:
    Vomit(StudentWorld* stw, double startX, double startY, int dir);
    virtual void doSomething();
   // virtual void activateIfAppropriate(Actor* a);
};
class Landmine : public ActivatingObject
{
public:
    Landmine(StudentWorld* stw, double startX, double startY);
    virtual void doSomething();
  //  virtual void activateIfAppropriate(Actor* a);
private:
    int m_safetyTicks;
};
class Human : public Agent
{
public:
    Human(StudentWorld* stw, double startX, double startY, const int IID);
    virtual void doSomething();
    virtual bool triggersZombieVomit() const {return true;}
    
};
class Penelope : public Human
{
public:
    Penelope(StudentWorld* stw, double startX, double startY);
    virtual void doSomething();
    int getVaccines() {return m_vaccineCount;}
    int getFlames() {return m_flamethrowerCount;}
    int getMines() {return m_landmineCount;}
    int getLives() {return m_lives;}
    
    void addMines(int amt);
    void addVaccines(int amt);
    void addFlames(int amt);
    
    
private:
    int m_flamethrowerCount;
    int m_landmineCount;
    int m_vaccineCount;
    int m_lives;
};
class Citizen : public Human
{
public:
    Citizen(StudentWorld* stw, double startX, double startY);
    virtual void doSomething();
    virtual void setDead();
private:
    bool m_paralyzed;
    
};
class Goodie : public ActivatingObject
{
public:
    Goodie(StudentWorld* stw, double startX, double startY, const int IID);
    virtual void doSomething();
   // virtual void activateIfAppropriate(Actor* a);
//    virtual void pickUp(Penelope* p) = 0;
};
class VaccineGoodie : public Goodie
{
public:
    VaccineGoodie(StudentWorld* stw, double startX, double startY);
    virtual void doSomething();
};
class GasCanGoodie : public Goodie
{
public:
    GasCanGoodie(StudentWorld* stw, double startX, double startY);
    virtual void doSomething();
};
class LandmineGoodie : public Goodie
{
public:
    LandmineGoodie(StudentWorld* stw, double startX, double startY);
    virtual void doSomething();
};

#endif // ACTOR_H_
