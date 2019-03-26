#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//Actor
Actor::Actor(StudentWorld* stw, double startX, double startY, int dir, int depth, int imageID)
: GraphObject(imageID, startX, startY, dir, depth), m_stw(stw), m_isAlive(true),m_infectionStatus(false),m_infectionCount(0),m_isActive(false)
{}
StudentWorld* Actor::getWorld()
{
    return m_stw;
}
bool Actor::isInfected()
{
    if(m_infectionCount >= 500)
        m_infectionStatus = true;
    return m_infectionStatus;
}
//Agent
Agent::Agent(StudentWorld* stw, double startX, double startY, const int IID)
:Actor(stw,startX,startY,right, 0,IID)
{}

//Human
Human::Human(StudentWorld* stw, double startX, double startY, const int IID)
:Agent(stw,startX,startY,IID)
{}
void Human::doSomething()
{
    if(!isAlive())
        return;
    //CHECK INFECTION?
}
//Citizen
Citizen::Citizen(StudentWorld* stw, double startX, double startY)
: Human(stw,startX,startY,IID_CITIZEN),m_paralyzed(false)
{}
void Citizen::doSomething()
{
    Human::doSomething();
    if(m_paralyzed)
    {
        m_paralyzed=false;
        return;
    }
    else
        m_paralyzed = true;
    
    if(getInfectCount() == 500)
    {
        setDead();
        getWorld()->increaseScore(-1000);
        getWorld()->playSound(SOUND_ZOMBIE_BORN);
        if (randInt(1,10) <= 7)
        {
            getWorld()->addDumbZombie(getX(), getY());
        }
        else
        {
            getWorld()->addSmartZombie(getX(), getY());
        }
            
        return;
    }
    //Determine distance to nearest Penelope and move towards
    double otherX;
    double otherY;
    bool isZombie = false;
    double dist = -1;

    
    getWorld()->locateNearestCitizenTrigger(getX(), getY(),otherX, otherY, dist, isZombie);
    //Nearest is Penelope
    if(!isZombie && dist <= (80*80))
    {
        double pX = getWorld()->getPenelope()->getX();
        double pY = getWorld()->getPenelope()->getY();
        
        //Same Row
        if(pY == getY())
        {
            if(pX > getX() && getWorld()->checkCanMoveTo(getX()+2, getY(), this))
            {
                setDirection(right);
                moveTo(getX()+2,getY());
                return;
            }
            else if (pX < getX() && getWorld()->checkCanMoveTo(getX()-2, getY(), this))
            {
                setDirection(left);
                moveTo(getX()-2,getY());
                return;
            }
            else
                return;
        }
        //Same Column
        if(pX == getX())
        {
            if(pY > getY() && getWorld()->checkCanMoveTo(getX(), getY()+2, this))
            {
                setDirection(up);
                moveTo(getX(),getY()+2);
                return;
            }
            else if (pX < getX() && getWorld()->checkCanMoveTo(getX(), getY()-2, this))
            {
                setDirection(down);
                moveTo(getX(),getY()-2);
                return;
            }
            else
                return;
        }
        //not same row or col
        else
        {
            int horizontal = -1;
            int vertical= -1;
            int chosenDir;
            int alternateDir;
            if(pX > getX()) //If penelope is to the right
            {
                horizontal = right;
            }
            if(pX < getX())
            {
                horizontal = left;
            }
            if(pY > getY()) //if penelope is North
            {
                vertical = up;
            }
            if (pY < getY())
            {
                vertical = down;
            }
            
            //Chosen Dir = vertical
            if(randInt(1,2) == 1)
            {
                chosenDir = vertical;
                alternateDir = horizontal;
            }
            else
            {
                chosenDir = horizontal;
                alternateDir = vertical;
            }
            
            if(chosenDir == up)
            {
                if(!getWorld()->isAgentMovementBlockedAt(getX(), getY()+2))
                {
                    setDirection(up);
                    moveTo(getX(),getY()+2);
                    return;
                }
            }
            if(chosenDir == down)
            {
                if(!getWorld()->isAgentMovementBlockedAt(getX(), getY()+2))
                {
                    setDirection(down);
                    moveTo(getX(),getY()-2);
                    return;
                }

            }
            if(chosenDir == left)
            {
                if(!getWorld()->isAgentMovementBlockedAt(getX(), getY()+2))
                {
                    setDirection(left);
                    moveTo(getX()-2,getY());
                    return;
                }
            }
            if(chosenDir == right)
            {
                if(!getWorld()->isAgentMovementBlockedAt(getX(), getY()+2))
                {
                    setDirection(right);
                    moveTo(getX()+2,getY());
                    return;
                }
            }
            
            //Check Alternate
            if(alternateDir == up)
            {
                if(!getWorld()->isAgentMovementBlockedAt(getX(), getY()+2))
                {
                    setDirection(up);
                    moveTo(getX(),getY()+2);
                    return;
                }
            }
            if(alternateDir == down)
            {
                if(!getWorld()->isAgentMovementBlockedAt(getX(), getY()+2))
                {
                    setDirection(down);
                    moveTo(getX(),getY()-2);
                    return;
                }
                
            }
            if(alternateDir == left)
            {
                if(!getWorld()->isAgentMovementBlockedAt(getX(), getY()+2))
                {
                    setDirection(left);
                    moveTo(getX()-2,getY());
                    return;
                }
            }
            if(alternateDir == right)
            {
                if(!getWorld()->isAgentMovementBlockedAt(getX(), getY()+2))
                {
                    setDirection(right);
                    moveTo(getX()+2,getY());
                    return;
                }
            }
        }
        
    }
    //Zombie is closer
    if(isZombie && dist <= (80*80))
    {
        int chosenDir = -5;
        int curr_dist = dist;
        //Check Directions:
        //up
        if(!getWorld()->isAgentMovementBlockedAt(getX(), getY()+2))
        {
            double new_dist;
            double xTemp,yTemp;
            getWorld()->locateNearestCitizenThreat(getX(), getY()+2, xTemp, yTemp, new_dist);
            if(new_dist > curr_dist)
            {
                chosenDir = up;
                curr_dist = new_dist;
            }
        }
        //down
        if(!getWorld()->isAgentMovementBlockedAt(getX(), getY()-2))
        {
            double new_dist;
            double xTemp,yTemp;
            getWorld()->locateNearestCitizenThreat(getX(), getY()-2, xTemp, yTemp, new_dist);
            if(new_dist > curr_dist)
            {
                chosenDir = down;
                curr_dist = new_dist;
            }
        }
        //left
        if(!getWorld()->isAgentMovementBlockedAt(getX() -2 , getY()))
        {
            double new_dist;
            double xTemp,yTemp;
            getWorld()->locateNearestCitizenThreat(getX()-2, getY(), xTemp, yTemp, new_dist);
            if(new_dist > curr_dist)
            {
                chosenDir = left;
                curr_dist = new_dist;
            }
        }
        //right
        if(!getWorld()->isAgentMovementBlockedAt(getX()+2, getY()))
        {
            double new_dist;
            double xTemp,yTemp;
            getWorld()->locateNearestCitizenThreat(getX()+2, getY(), xTemp, yTemp, new_dist);
            if(new_dist > curr_dist)
            {
                chosenDir = right;
                curr_dist = new_dist;
            }
        }
        //Move to Direction if its closer
        if(curr_dist == dist)
            return;
        setDirection(chosenDir);
        switch(chosenDir)
        {
            case up:
                moveTo(getX(),getY()+2);
            case down:
                moveTo(getX(),getY()-2);
            case left:
                moveTo(getX()-2,getY());
            case right:
                moveTo(getX()+2,getY());
        }
    }
    
}
void Citizen::setDead()
{
    Actor::setDead();
    getWorld()->playSound(SOUND_CITIZEN_DIE);
    getWorld()->increaseScore(-1000);
}
//Penelope
Penelope::Penelope(StudentWorld* stw, double startX, double startY)
: Human(stw,startX,startY, IID_PLAYER), m_flamethrowerCount(0), m_landmineCount(0), m_vaccineCount(0), m_lives(3)
{}
void Penelope::doSomething()
{
    Human::doSomething();
    //Check Key Pressed
    if(isInfected())
    {
        if(getInfectCount() == 500)
        {
            setDead();
            getWorld()->playSound(SOUND_PLAYER_DIE);
        }
        else
            incInfect();
    }
    int key;
    getWorld()->getKey(key);
    switch(key)
    {
        case KEY_PRESS_UP: //UP
        {
            setDirection(up);
            bool checkObj = getWorld()->checkCanMoveTo(getX(), getY()+4, this);
            if(!checkObj)
                moveTo(getX(), getY()+4);
            break;
        }
        case KEY_PRESS_DOWN: //DOWN
        {
            setDirection(down);
            bool checkObj = getWorld()->checkCanMoveTo(getX(), getY()-4, this);
            if(!checkObj)
                moveTo(getX(),getY()-4);
            break;
        }
        case KEY_PRESS_LEFT: //LEFT
        {
            setDirection(left);
            bool checkObj = getWorld()->checkCanMoveTo(getX()-4, getY(), this);
            if(!checkObj)
                moveTo(getX()-4, getY());
            break;
        }
        case KEY_PRESS_RIGHT: //RIGHT
        {
            setDirection(right);
            bool checkObj = getWorld()->checkCanMoveTo(getX()+4, getY(), this);
            if(!checkObj)
                moveTo(getX()+4,getY());
            break;
        }
        case KEY_PRESS_SPACE: //FLAME THROWER
        {
            if(m_flamethrowerCount >= 1)
            {
                m_flamethrowerCount--;
                getWorld()->playSound(SOUND_PLAYER_FIRE);
                int px = getX();
                int py = getY();
                int posX = 0;
                int posY = 0;
                for(int i=0; i<3; i++){
                    switch(getDirection())
                    {
                        case 90: //UP
                        {
                            posX = px;
                            posY = py+i*SPRITE_HEIGHT;
                            break;
                        }
                        case 270: //DOWN
                        {
                            posX = px;
                            posY = py-i*SPRITE_HEIGHT;
                            break;
                        }
                        case 180: //LEFT
                        {
                            posX = px-i*SPRITE_WIDTH;
                            posY = py;
                            break;
                        }
                        case 0: //RIGHT
                        {
                            posX = px + i*SPRITE_WIDTH;
                            posY = py;
                            break;
                        }
                    }
                    //CHECK BOUNDARY AND ADD
                    if(getWorld()->isFlameBlockedAt(posX, posY))
                        break;
                    else
                        getWorld()->addFlame(posX,posY,getDirection());
                    
                }
            }
            break;
        }
        case KEY_PRESS_TAB: //LANDMINES
        {
            if(m_landmineCount > 0)
            {
                //ADD LANDMINE
                m_landmineCount--;
                getWorld()->addLandmine(getX()-SPRITE_WIDTH,getY());
            }
            break;
        }
        case KEY_PRESS_ENTER:
        {
            if(m_vaccineCount > 0){
                setInfectStatus(false);
                m_vaccineCount--;
            }
            
            break;
        }
            
    }
}
void Penelope::addMines(int amt)
{
    m_landmineCount += amt;
}
void Penelope::addFlames(int amt)
{
    m_flamethrowerCount += amt;
}
void Penelope::addVaccines(int amt)
{
    m_vaccineCount += amt;
}
//Wall
Wall::Wall(StudentWorld* stw, double startX, double startY)
: Actor(stw,startX,startY,right, 0,IID_WALL)
{}
void Wall::doSomething()
{}

//Zombie
Zombie::Zombie(StudentWorld* stw, double startX, double startY, int movementDist)
:Agent(stw,startX,startY,IID_ZOMBIE), m_planDistance(0),m_paralyzed(false)
{}
int Zombie::getPlanDist()
{
    return m_planDistance;
}
void Zombie::setPlanDist(int dist)
{
    m_planDistance = dist;
}



//Dumb Zombie
DumbZombie::DumbZombie(StudentWorld* stw, double startX, double startY)
:Zombie(stw,startX,startY,0)
{}
void DumbZombie::doSomething()
{
    if(!isAlive())
        return;
    if(isParalyzed())
    {
        setParalyzed(false);
        return;
    }
    setParalyzed(true);
    
    int px = getX();
    int py = getY();
    int posX, posY = 0;
    
    switch(getDirection())
    {
        case up:
        {
            posX = px;
            posY = py+SPRITE_HEIGHT;
            break;
        }
        case down:
        {
            posX = px;
            posY = py-SPRITE_HEIGHT;
            break;
        }
        case left:
        {
            posX = px-SPRITE_WIDTH;
            posY = py;
            break;
        }
        case right:
        {
            posX = px + SPRITE_WIDTH;
            posY = py;
            break;
        }
    }
    double otherX, otherY, dist;
    getWorld()->locateNearestVomitTrigger(posX, posY, otherX, otherY, dist);
    
    if(dist <= 100)
    {
        if(randInt(1,3) == 1)
        {
            getWorld()->addVomit(posX, posY, right);
            getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
            return;
        }
    }
    if(getPlanDist() == 0){
        setPlanDist(randInt(3,10));
        makePlan();
    }
    
    
    
}
void DumbZombie::makePlan()
{
    double newX = 0;
    double newY = 0;
    switch(randInt(1,4))
    {
        case 1:
            setDirection(down);
            newX = getX();
            newY = getY()-1;
            break;
        case 2:
            setDirection(up);
            newX = getX();
            newY = getY()+1;
            break;
        case 3:
            setDirection(left);
            newX = getX()-1;
            newY = getY();
            break;
        case 4:
            setDirection(right);
            newX = getX();
            newY = getY()+1;
            break;
    }
    if(!getWorld()->isAgentMovementBlockedAt(newX, newY))
    {
        moveTo(newX,newY);
        setPlanDist(getPlanDist()-1);
    }
    else
        setPlanDist(0);
}
void DumbZombie::setDead()
{
    Actor::setDead();
    getWorld()->playSound(SOUND_ZOMBIE_DIE);
    getWorld()->increaseScore(1000);
    
    if(randInt(1,10) == 1)
    {
        getWorld()->addVaccineGoodie(getX(), getY());
    }
}

//Smart Zombie
SmartZombie::SmartZombie(StudentWorld* stw, double startX, double startY)
:Zombie(stw,startX,startY,0)
{}

void SmartZombie::doSomething()
{
    if(!isAlive())
        return;
    if(isParalyzed())
    {
        setParalyzed(false);
        return;
    }
    setParalyzed(true);
    
    int px = getX();
    int py = getY();
    int posX, posY = 0;
    
    switch(getDirection())
    {
        case up:
        {
            posX = px;
            posY = py+SPRITE_HEIGHT;
            break;
        }
        case down:
        {
            posX = px;
            posY = py-SPRITE_HEIGHT;
            break;
        }
        case left:
        {
            posX = px-SPRITE_WIDTH;
            posY = py;
            break;
        }
        case right:
        {
            posX = px + SPRITE_WIDTH;
            posY = py;
            break;
        }
    }
    double otherX, otherY, dist;
    getWorld()->locateNearestVomitTrigger(posX, posY, otherX, otherY, dist);
    
    if(dist <= 100)
    {
        if(randInt(1,3) == 1)
        {
            getWorld()->addVomit(posX, posY, right);
            getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
            return;
        }
    }
    if(getPlanDist() == 0){
        setPlanDist(randInt(3,10));
        makePlan();
    }
    
}
void SmartZombie::makePlan()
{
    setPlanDist(randInt(3,10));
    double nearX;
    double nearY;
    double dist;
    getWorld()->locateNearestVomitTrigger(getX(), getY(), nearX, nearY, dist);
    if(dist > (80*80))
    {
        switch(randInt(1,4))
        {
            case 1:
                setDirection(up);
                break;
            case 2:
                setDirection(down);
                break;
            case 3:
                setDirection(right);
                break;
            case 4:
                setDirection(left);
                break;
        }
    }
    else
    {
        int vertical;
        int horizontal;
        if(getY() < nearY)
            vertical = up;
        else
            vertical = down;
        if(getX() > nearX)
            horizontal = left;
        else
            horizontal = right;
        //If same col
        if(getY() == nearY)
        {
            setDirection(horizontal);
        }
        //Same row
        else if(getX() == nearX)
        {
            setDirection(vertical);
        }
        else
        {
            switch(randInt(1,2))
            {
                case 1:
                    setDirection(horizontal);
                    break;
                case 2:
                    setDirection(vertical);
                    break;
            }
        }
    }
    double dest_x = getX();
    double dest_y = getY();
    switch(getDirection())
    {
        case up:
            dest_y = getY() + 1;
            break;
        case down:
            dest_y = getY() - 1;
            break;
        case left:
            dest_x = getX() - 1;
            break;
        case right:
            dest_x = getX() + 1;
            break;
    }
    if(!getWorld()->isAgentMovementBlockedAt(dest_x, dest_y))
    {
        moveTo(dest_x,dest_y);
        setPlanDist(getPlanDist()-1);
    }
    else
        setPlanDist(0);
        
    
}
void SmartZombie::setDead()
{
    Actor::setDead();
    getWorld()->playSound(SOUND_ZOMBIE_DIE);
    getWorld()->increaseScore(2000);
}


//Activating Object
ActivatingObject::ActivatingObject(StudentWorld* stw, double startX, double startY, int dir, const int IID)
: Actor(stw,startX,startY,dir,1, IID)
{}

//Flame
Flame::Flame(StudentWorld* stw, double startX, double startY, int dir)
: ActivatingObject(stw,startX,startY,dir,IID_FLAME)
{}
void Flame::doSomething()
{}

//Exit
Exit::Exit(StudentWorld* stw, double startX, double startY)
:ActivatingObject(stw,startX,startY,right,IID_EXIT)
{}
void Exit::doSomething()
{
    if(getWorld()->citizenOverlap(getX(), getY()))
    {
        getWorld()->citizenEscaped();

    }
    if(getWorld()->checkPenelopeOverlap(getX(), getY()) && getWorld()->citizensLeft() == 0)
    {
        getWorld()->finishedLevel();
    }
}

//Pit
Pit::Pit(StudentWorld* stw, double startX, double startY)
:ActivatingObject(stw,startX,startY,right,IID_PIT)
{}
void Pit::doSomething()
{
    if(getWorld()->checkPenelopeOverlap(getX(), getY()))
    {
        getWorld()->getPenelope()->setDead();
    }
}

//Vomit
Vomit::Vomit(StudentWorld* stw, double startX, double startY, int dir)
: ActivatingObject(stw,startX,startY,dir,IID_VOMIT)
{}
void Vomit::doSomething()
{}

//Landmine
Landmine::Landmine(StudentWorld* stw, double startX, double startY)
: ActivatingObject(stw,startX,startY,right,IID_LANDMINE)
{
    m_safetyTicks = 30;
}
void Landmine::doSomething()
{
    if(!isAlive())
        return;
    if(!isActive())
    {
        if(m_safetyTicks == 0)
        {
            activate();
            return;
        }
        else
            m_safetyTicks--;
    }
    if(!getWorld()->isFlameBlockedAt(getX(), getY()) && isActive())
    {
        setDead();
        getWorld()->playSound(SOUND_LANDMINE_EXPLODE);
        ///INTRODUCE FLAME AT
        //(X,Y)
        getWorld()->addFlame(getX(),getY(),right);
        //8 adjacent locations
        getWorld()->addFlame(getX()-SPRITE_WIDTH,getY()+SPRITE_HEIGHT, right);
        getWorld()->addFlame(getX(),getY()+SPRITE_HEIGHT,right);
        getWorld()->addFlame(getX()+SPRITE_WIDTH,getY()+SPRITE_HEIGHT,right);
        getWorld()->addFlame(getX()-SPRITE_WIDTH,getY(),right);
        getWorld()->addFlame(getX()+SPRITE_WIDTH,getY(),right);
        getWorld()->addFlame(getX()-SPRITE_WIDTH,getY()-SPRITE_HEIGHT,right);
        getWorld()->addFlame(getX(),getY()-SPRITE_HEIGHT,right);
        getWorld()->addFlame(getX()+SPRITE_WIDTH,getY()-SPRITE_HEIGHT,right);
        
        //ADD PIT
        getWorld()->addPit(getX(),getY());
        
    }
    
}

//Goodie
Goodie::Goodie(StudentWorld* stw, double startX, double startY, const int IID)
: ActivatingObject(stw,startX,startY,right, IID)
{}
void Goodie::doSomething()
{
    if(!isAlive())
        return;
    //Penelope Picked up Goodie
    if(getWorld()->checkPenelopeOverlap(getX(), getY()))
    {
        getWorld()->increaseScore(50);
        setDead();
        getWorld()->playSound(SOUND_GOT_GOODIE);
    }
    
    //Overlapped with Flame
    if(!getWorld()->isFlameBlockedAt(getX(), getY()))
        setDead();
}

VaccineGoodie::VaccineGoodie(StudentWorld* stw, double startX, double startY)
: Goodie(stw,startX,startY,IID_VACCINE_GOODIE)
{}
void VaccineGoodie::doSomething()
{
    Goodie::doSomething();
    if(getWorld()->checkPenelopeOverlap(getX(), getY()))
        getWorld()->givePenelopeVaccine();
}

GasCanGoodie::GasCanGoodie(StudentWorld* stw, double startX, double startY)
: Goodie(stw,startX,startY,IID_GAS_CAN_GOODIE)
{}
void GasCanGoodie::doSomething()
{
    Goodie::doSomething();
    if(getWorld()->checkPenelopeOverlap(getX(), getY()))
        getWorld()->pickUpGasCan();
}

LandmineGoodie::LandmineGoodie(StudentWorld* stw, double startX, double startY)
: Goodie(stw,startX,startY,IID_LANDMINE_GOODIE)
{}
void LandmineGoodie::doSomething()
{
    Goodie::doSomething();
    if(getWorld()->checkPenelopeOverlap(getX(), getY()))
        getWorld()->pickUpMineGoodie();
}

