#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_penelope = nullptr;
    m_finishedLevel = false;
    m_citizensLeft = 0;
}
StudentWorld::~StudentWorld()
{
    cleanUp();
}
string StudentWorld::updateStatus()
{
    int lives = getLives();
    int vaccines = m_penelope->getVaccines();
    int mines = m_penelope->getMines();
    int flames = m_penelope->getFlames();
    int level = getLevel();
    int score = getScore();
    int infec = m_penelope->getInfectCount();
    
    ostringstream oss;
    oss.setf(ios::fixed);
    oss.precision(2);
    oss << "Score: " << score << "  ";
    oss << "Level: " << level << "  ";
    oss << "Lives: " << lives << "  ";
    oss << "Vaccines: " << vaccines << "  ";
    oss << "Flames: " << flames << "  ";
    oss << "Mines: " << mines << "  ";
    oss << "Infected: " << infec << "  ";
    string s = oss.str();
    
    return s;
}
int StudentWorld::init()
{
    m_citizensLeft = 0;
    m_penelope = nullptr;
    m_finishedLevel = false;
    
    if(loadLevelData() == 1)
        return GWSTATUS_LEVEL_ERROR;
    
    //Activate objects that can be
    list<Actor*>::iterator it = m_charList.begin();
    for(it = m_charList.begin(); it != m_charList.end(); it++)
    {
        (*it)->activate();
    }
    
    
    return GWSTATUS_CONTINUE_GAME;
}
int StudentWorld::move()
{
    // Give each actor a chance to do something, including Penelope

    list<Actor*>::iterator it = m_charList.begin();
    for(it = m_charList.begin(); it != m_charList.end(); it++)
    {
        if((*it)->isAlive())
            (*it)->doSomething();
        if(!m_penelope->isAlive()){
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        //if penelope completed current level
        if(m_finishedLevel)
        {
            //m_finishedLevel = false;
            return GWSTATUS_FINISHED_LEVEL;
        }

        
        
    }
    // Remove newly-dead actors after each tick
    list<Actor*>::iterator it2 = m_charList.begin();
    for(it = m_charList.begin(); it != m_charList.end(); it++)
    {
        if(!((*it2)->isAlive()))
        {
            (*it2)->setDead(); //hasDied FIX
           list<Actor*>::iterator temp = it2;
           delete *temp;
           m_charList.erase(temp);
        }
    }
    // Update the game status line
    setGameStatText(updateStatus());
    
    // the player hasn’t completed the current level and hasn’t died, so
    // continue playing the current level
    return GWSTATUS_CONTINUE_GAME;
}
int StudentWorld::loadLevelData()
{
    Level lev(assetPath());
    //Get level file
    ostringstream oss;
    oss.setf(ios::fixed);
    oss.precision(2);
    
    oss << "level";
    if(getLevel() < 10)
        oss << "0";
    oss << getLevel() << ".txt";
    
    string levelFile = oss.str();
    
    Level::LoadResult result = lev.loadLevel(levelFile);
    if (result == Level::load_fail_file_not_found)
        cerr << "Cannot find " << levelFile << " data file" << endl;
    else if (result == Level::load_fail_bad_format)
        cerr << "Your level was improperly formatted" << endl;
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        for(int r=0; r<LEVEL_HEIGHT; r++){
            for(int c=0; c<LEVEL_WIDTH; c++){
                Level::MazeEntry ge = lev.getContentsOf(r,c);
               switch(ge)
                {
                    case Level::player:
                        m_penelope = new Penelope(this, r*SPRITE_WIDTH, c*SPRITE_HEIGHT);
                        m_charList.push_back(m_penelope);
                        break;
                    case Level::citizen:
                        m_charList.push_back(new Citizen(this,r*SPRITE_WIDTH, c*SPRITE_HEIGHT));
                        m_citizensLeft++;
                        break;
                    case Level::smart_zombie:
                        m_charList.push_back(new SmartZombie(this,r*SPRITE_WIDTH, c*SPRITE_HEIGHT));
                        break;
                    case Level::dumb_zombie:
                        m_charList.push_back(new DumbZombie(this,r*SPRITE_WIDTH, c*SPRITE_HEIGHT));
                        break;
                    case Level::wall:
                        m_charList.push_back(new Wall(this,r*SPRITE_WIDTH, c*SPRITE_HEIGHT));
                        break;
                    case Level::exit:
                        m_charList.push_back(new Exit(this,r*SPRITE_WIDTH, c*SPRITE_HEIGHT));
                        break;
                    case Level::pit:
                        m_charList.push_back(new Pit(this,r*SPRITE_WIDTH, c*SPRITE_HEIGHT));
                        break;
                    case Level::vaccine_goodie:
                        m_charList.push_back(new VaccineGoodie(this,r*SPRITE_WIDTH, c*SPRITE_HEIGHT));
                        break;
                    case Level::gas_can_goodie:
                        m_charList.push_back(new GasCanGoodie(this,r*SPRITE_WIDTH, c*SPRITE_HEIGHT));
                        break;
                    case Level::landmine_goodie:
                        m_charList.push_back(new LandmineGoodie(this,r*SPRITE_WIDTH, c*SPRITE_HEIGHT));
                        break;
                    default:
                        break;
                }
                
            }
        }
        
    }
    else
        return 1;
    
    return 0;
}
void StudentWorld::cleanUp()
{
    list<Actor*>::iterator it = m_charList.begin();
    for(it = m_charList.begin(); it != m_charList.end(); it++)
    {
        delete(*it);
        it = m_charList.erase(it);
    }
    m_penelope = nullptr;
}
bool StudentWorld::checkBoundaryBoxOverlap(double x1, double y1, double x2, double y2)
{
    //Left and Right X
    double P_LX = x1;
    double P_RX = x1+ SPRITE_WIDTH-1;
    
    //Top and Bottom Y
    double P_TY = y1;
    double P_BY = y1 + SPRITE_HEIGHT-1;
    
    
    double leftX = x2;
    double leftY = y2;
    double rightX = x2 + SPRITE_WIDTH-1;
    double rightY = y2 + SPRITE_HEIGHT-1;
    
    
    if( (P_LX >= leftX && P_LX <= rightX) && (P_TY >= leftY && P_TY <= rightY) )
        return true;
    if( (P_RX >= leftX && P_RX <= rightX) && (P_TY >= leftY && P_TY <= rightY) )
        return true;
    if( (P_LX >= leftX && P_LX <= rightX) && (P_BY >= leftY && P_BY <= rightY) )
        return true;
    if( (P_RX >= leftX && P_RX <= rightX) && (P_BY >= leftY && P_BY <= rightY) )
        return true;
    
    return false;
}
bool StudentWorld::checkCanMoveTo(double dest_x, double dest_y, Actor* actor)
{
    list<Actor*>::iterator it;
    for(it = m_charList.begin(); it != m_charList.end(); it++)
    {
        if(*it != actor && (*it)->blocksMovement())
        {
            if(checkBoundaryBoxOverlap(dest_x, dest_y, (*it)->getX(), (*it)->getY()))
                return true;
        }
    }
    return false;
}
bool StudentWorld::checkObjectOverlap(double x, double y, double x2, double y2)
{
    double a_xc = x + SPRITE_WIDTH/2.0;
    double a_yc = x + SPRITE_HEIGHT/2.0;
    
    //x-center and y-center passed in
    double x_c = x2 + SPRITE_WIDTH / 2.0;
    double y_c = y2 + SPRITE_HEIGHT/2.0;
    
    //Change in X and Y
    double deltaX = x_c - a_xc;
    double deltaY = y_c - a_yc;
    
    //Distance Formula
    double distance = (deltaX*deltaX) + (deltaY*deltaY);
    
    if(distance <= 100.0)
    {
        return true;
    }
    return false;
}
bool StudentWorld::checkPenelopeOverlap(double x, double y)
{
    ///Penelope x-center and y-center
    double p_xc = m_penelope->getX() + SPRITE_WIDTH/2.0;
    double p_yc = m_penelope->getY() + SPRITE_HEIGHT/2.0;
    
    //x-center and y-center passed in
    double x_c = x + SPRITE_WIDTH / 2.0;
    double y_c = y + SPRITE_HEIGHT/2.0;
    
    //Change in X and Y
    double deltaX = p_xc - x_c;
    double deltaY = p_yc - y_c;
    
    //Distance Formula
    double distance = (deltaX*deltaX) + (deltaY*deltaY);
    
    if(distance <= 100)
    {
        return true;
    }

  return false;
}
bool StudentWorld::isFlameBlockedAt(double x, double y)
{
    list<Actor*>::iterator it;
    for(it = m_charList.begin(); it != m_charList.end(); it++)
    {
        if((*it)->blocksFlame())
        {
            if(checkObjectOverlap(x, y, (*it)->getX(), (*it)->getY()))
            {
                return true;
            }
        }
    }
    return false;
}
bool StudentWorld::pitOverlap(double x, double y)
{
    list<Actor*>::iterator it;
    for(it = m_charList.begin(); it != m_charList.end(); it++)
    {
        if((*it)->threatToPlayer())
        {
            if(checkObjectOverlap(x, y, (*it)->getX(), (*it)->getY()))
            {
                return true;
            }
        }
    }
    return false;
}
bool StudentWorld::citizenOverlap(double x, double y)
{
    if(m_citizensLeft == 0)
        return false;
    list<Actor*>::iterator it;
    for(it = m_charList.begin(); it != m_charList.end(); it++)
    {
        if((*it)->triggersZombieVomit() && (*it) != m_penelope)
        {
            if(checkObjectOverlap(x, y, (*it)->getX(), (*it)->getY()))
            {
                return true;
            }
        }
    }
    return false;
}
bool StudentWorld::locateNearestCitizenThreat(double x, double y, double& otherX, double& otherY, double &distance)
{
    if(m_citizensLeft == 0)
        return false;
    int minDist = -1;
    int tempDist = -1;
    list<Actor*>::iterator it;
    for(it = m_charList.begin(); it != m_charList.end(); it++)
    {
        if((*it)->triggersCitizens())
        {
            double x2 = (*it)->getX();
            double y2 = (*it)->getY();
            
            double deltaX = x2 - x;
            double deltaY = y2 - y;
            
            tempDist = (deltaX*deltaX) + (deltaY*deltaY);
            if(tempDist < minDist)
            {
                minDist = tempDist;
                otherX = x2;
                otherY = y2;
            }
            
            
        }
    }
    distance = minDist;
    return true;
}
bool StudentWorld::locateNearestVomitTrigger(double x, double y, double &otherX, double &otherY, double &distance)
{
    if(m_citizensLeft == 0 || !(m_penelope->isAlive()))
        return false;
    int minDist = -1;
    int tempDist = -1;
    list<Actor*>::iterator it;
    for(it = m_charList.begin(); it != m_charList.end(); it++)
    {
        if((*it)->triggersZombieVomit())
        {
            double x2 = (*it)->getX();
            double y2 = (*it)->getY();
            
            double deltaX = x2 - x;
            double deltaY = y2 - y;
            
            tempDist = (deltaX*deltaX) + (deltaY*deltaY);
            if(tempDist < minDist)
            {
                minDist = tempDist;
                otherX = x2;
                otherY = y2;
            }
            
            
        }
    }
    distance = minDist;
    return true;
}
bool StudentWorld::locateNearestCitizenTrigger(double x, double y, double &otherX, double &otherY, double &distance, bool &isThreat)
{
    Actor* temp = nullptr;
    if(m_citizensLeft == 0)
        return false;
    int minDist = -1;
    int tempDist = -1;
    list<Actor*>::iterator it;
    for(it = m_charList.begin(); it != m_charList.end(); it++)
    {
        if((*it)->triggersCitizens() || (*it)==m_penelope)
        {
            double x2 = (*it)->getX();
            double y2 = (*it)->getY();
            
            double deltaX = x2 - x;
            double deltaY = y2 - y;
            
            tempDist = (deltaX*deltaX) + (deltaY*deltaY);
            if(tempDist < minDist)
            {
                minDist = tempDist;
                otherX = x2;
                otherY = y2;
                temp = (*it);
            }
        }
    }
    if(minDist != -1 && temp != nullptr)
    {
        if(temp->triggersCitizens())
            isThreat=true;
        else
            isThreat=false;
        distance = minDist;
        return true;
    }
    return false;
}
bool StudentWorld::isAgentMovementBlockedAt(double x, double y)
{
    list<Actor*>::iterator it;
    for(it = m_charList.begin(); it != m_charList.end(); it++)
    {
        if((*it)->getX() == x && (*it)->getY() == y)
        {
            if((*it)->blocksMovement())
                return true;
        }
    }
    return false;
}

void StudentWorld::addSmartZombie(double x, double y)
{
    m_charList.push_back(new SmartZombie(this,x,y));
}
void StudentWorld::addDumbZombie(double x, double y)
{
    m_charList.push_back(new DumbZombie(this,x,y));
}
void StudentWorld::addFlame(double x, double y, int dir)
{
    m_charList.push_back(new Flame(this,x,y,dir));
}
void StudentWorld::addLandmine(double x, double y)
{
    m_charList.push_back(new Landmine(this,x,y));
}
void StudentWorld::addVomit(double x, double y, int dir)
{
    m_charList.push_back(new Vomit(this,x,y,dir));
}
void StudentWorld::addPit(double x, double y)
{
    m_charList.push_back(new Pit(this,x,y));
}
void StudentWorld::givePenelopeVaccine()
{
    m_penelope->addVaccines(1);
}
void StudentWorld::pickUpGasCan()
{
    m_penelope->addFlames(5);
}
void StudentWorld::finishedLevel()
{
    m_finishedLevel = true;
}
void StudentWorld::pickUpMineGoodie()
{
    m_penelope->addMines(2);
}
void StudentWorld::addVaccineGoodie(double x, double y)
{
    m_charList.push_back(new VaccineGoodie(this, x,y));
}
void StudentWorld::citizenEscaped()
{
    m_citizensLeft--;
}
