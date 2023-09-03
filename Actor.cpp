#include "Actor.h"
#include "StudentWorld.h"

#include "GameConstants.h"
#include <string>
using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

void TunnelMan::annoy(int damage)
{
    getting_hit_pts(damage);
    if (hit_pts <= 0)
    {
        die();
        getWorld()->playSound(SOUND_PLAYER_GIVE_UP);
    }
    
}

void TunnelMan::Move(int ch)
{
    bool same_direction = false;

    switch(ch)
    {
        case KEY_PRESS_LEFT:
            if (getDirection() != left)
            {
                setDirection(left); // Set direction if not already the same
            } else
            same_direction = true; // If it is the same mark true
            if(getX() > 0 && !getWorld()->isThereBoulder(getX()-3,getY(),1))
            {
                moveTo(getX()-1, getY());
            };
            
            break;
            
        case KEY_PRESS_RIGHT:
            if (getDirection() != right)
            {
                setDirection(right);
            }
            else
            same_direction = true;
            if(getX() < 60 && !getWorld()->isThereBoulder(getX()+3,getY(),1))
            {
                moveTo(getX()+1, getY());
                
            };
            
            break;
            
        case KEY_PRESS_UP:
            if (getDirection() != up)
            {
             setDirection(up);
            }
            else
            same_direction = true;
            if(getY() < 60 && !getWorld()->isThereBoulder(getX(),getY()+3,1))
            {
                moveTo(getX(), getY()+1);
                
            }
            
            break;
            
        case KEY_PRESS_DOWN:
            if (getDirection() != down)
            {
                setDirection(down);
            }
            else
            same_direction = true;
            if(getY() > 0 && !getWorld()->isThereBoulder(getX(),getY()-3,1) )
            {
                moveTo(getX(), getY()-1);
                
            }
            
            break;
       
        case KEY_PRESS_ESCAPE:
            die();
            return;
            
        case 'z':
               
        case 'Z':            //use sonar kit
                    
        if (sonar > 0)
        {
            sonar--;
           vector<Actor*>::iterator it;
            it = getWorld()->getActor().begin();
            while (it != getWorld()->getActor().end())
            {
                if (it >= getWorld()->getActor().end() || (*it) == nullptr )
                {
                    if (getWorld()->CheckRadius(getX(),getY(), (*it)->getX(),(*it)->getY() ,12))
                        (*it)-> setVisible(true);
                }
                it++;
            }
            getWorld()->playSound(SOUND_SONAR);
            
        }
            break;
        case KEY_PRESS_SPACE:
            if(water > 0)
            {
                changeWater(-1);
                getWorld()->getActor().push_back(new Squirt(getWorld(), getX() + 3 , getY() , getDirection()));
            }
            break;
    }
}

void TunnelMan:: doSomething()
{
int ch;
    bool alive_checker = getIsAlive();
    if(alive_checker == false)
    {
        setVisible(false);
        return;
    }
    else
    {
        for(int r = 0 ; r< 64; r++)
        {
            for (int c = 0; c < 60; c++)
            {
                if(r == getX() && c == getY())
                {
                    m_world -> cleanEarth(getX(), getY());
                    break;
                }
            }
        }
    }
    getWorld() -> getKey(ch);
    Move(ch);
}

// can probs delete this
void Earth :: doSomething()
{
    if(getWorld()->Player()->getX() == getX() && getWorld() -> Player() -> getY() == getY())
    {
        
    }
}


// this is for boulder to declare the functions
void Boulder::doSomething()
{
    if (!getIsAlive()) return;
    
    if(getWorld()->isAboveEarth(getX(),getY()-1))
    {
        m_ticks =0;
        
        isStable = true;
        isFalling = false;
    }
    
    if (isStable)
    {
        if(getWorld()->isAboveEarth(getX(),getY() -1))
            return;
        else isStable = false;
        
    }
    if(m_ticks == 30)
    {
        isFalling = true;
        getWorld()->playSound(SOUND_FALLING_ROCK);
    }
    
    m_ticks++;
        if (isFalling)
        {
            if (getWorld()->isAboveEarth(getX(), getY()-1)|| getWorld()->isThereBoulder(getX(), getY()-4, 0) || getY()==0)
                die();
            else moveTo(getX(), getY() - 1);
            
           if((getWorld()-> CheckRadius(getX(),getY() , getWorld()->Player()->getX(), getWorld() -> Player() -> getY() ,3)))
              
               getWorld()->Player()->annoy(100);
        }
}



Boulder::~Boulder()
{

}

void Gold::doSomething()
{
    if (!getIsAlive()) return;
    if(!isVisible() && getWorld()->CheckRadius(getX(),getY() , getWorld()->Player()->getX(), getWorld() -> Player() -> getY() ,4))
    {
        setVisible(true);
        return;
    }
    
    if(!isDropped && getWorld()->CheckRadius(getX(),getY(), getWorld()->Player()->getX(), getWorld() -> Player() -> getY() ,3))
    {
        die();
        getWorld() -> playSound(SOUND_GOT_GOODIE);
        getWorld()-> Player() -> score(10);
        getWorld()->Player()-> changeGold(1); // increasing the gold count here
        return;
    }
}

// barrels do something here
void Barrel::doSomething() {
    if (!getIsAlive()) return;
    
    if (!isVisible() && getWorld()->CheckRadius(getX(),getY() , getWorld()->Player()->getX(), getWorld() -> Player() -> getY() ,4))
    {
        setVisible(true);
        return;
    }
    if (getWorld()->CheckRadius(getX(),getY(), getWorld()->Player()->getX(), getWorld() -> Player() -> getY() ,3))
    {
        die();
        getWorld()->playSound(SOUND_FOUND_OIL);
        getWorld()-> Player() -> score(1000);
        getWorld()->changeBarrelCount(-1);
        return;
    }
    
}

// added the goodies do something
void Goodie::doSomething()
{
    if (!getIsAlive()) return;
    if (getWorld()->CheckRadius(getX(),getY(), getWorld()->Player()->getX(), getWorld() -> Player() -> getY() ,3))
     {
        die();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()-> Player() -> score(1000);
        return;
    }
    disappearIn(std::max(100, 300 - 10 * (int)getWorld()->getLevel()));
}

void Sonar::doSomething()
{
    if (!getIsAlive()) return;
    if (getWorld()->CheckRadius(getX(),getY(), getWorld()->Player()->getX(), getWorld() -> Player() -> getY() ,3))
    {
        die();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()-> Player() -> score(75);
        getWorld() ->Player() ->changeSonar(1);
    }
    
}

void WaterPool::doSomething()
{
    if (!getIsAlive())
        return;
    if (getWorld()->CheckRadius(getX(),getY(), getWorld()->Player()->getX(), getWorld() -> Player() -> getY() ,3))
    {
        die();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()-> Player() -> score(100);
        getWorld() ->Player() ->changeWater(5);
    }
    
}


void RegularProtestors :: doSomething()

{
    if (!getIsAlive())
        return;
    if (resting == true)
    {
            ticks++;
            return;
    }
}


void Squirt::doSomething()
{
    cerr << "test" << endl;
    if (!getIsAlive())
        return;
    if(m_travel == 4)
    {
        die();
        return;
    }
    m_travel++;
    cerr << m_travel << endl;
    switch (getDirection()) {
        case left:
            if (getWorld()->isThereEarth(getX() - 1, getY()) || getWorld()->isThereBoulder(getX() - 1, getY(),1)) {
                die(); return;
            }
            else   moveTo(getX() - 1, getY());
            break;
        case right:
            if (getWorld()->isThereEarth(getX() + 1, getY()) || getWorld()->isThereBoulder(getX() + 1, getY(),1)) {
                die(); return;
            }
            else   moveTo(getX() + 1, getY());
            break;
        case up:
            if (getWorld()->isThereEarth(getX(), getY() + 1 || getWorld()->isThereBoulder(getX(), getY() + 1,1))) {
                die(); return;
            }
            else moveTo(getX(), getY() + 1);
            break;
        case down:
            if (getWorld()->isThereEarth(getX(), getY() - 1 || getWorld()->isThereBoulder(getX(), getY() - 1,1))) {
                die(); return;
            }
            else moveTo(getX(), getY() - 1);
            break;
        case none : return;
    }
}




// defining short functions here
int TunnelMan::getWtr()
{
    return water;
}

int TunnelMan::getSonar()
{
    return sonar;
}

int TunnelMan::getGld()
{
    return nuggets;
}



//Gold::~Gold()
//{
//    
//}
