#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>
using namespace std;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld; // added this here because were using a pointer to referal back to it

class Actor: public GraphObject // base class
{
    //StudentWorld* m_world; // to referal back to the student world class because this is getting used in the game world
   bool alive_checker = true; // using this to check if my tunnel man is alive
    
public:
    StudentWorld* m_world = m_world; // added it
    virtual ~Actor() // destructor for actor
    {
        
    }
    // constructor
    Actor(StudentWorld* world, int imageID, int startX, int startY, Direction startDirection, float size, unsigned int depth): GraphObject(imageID, startX, startY, startDirection, size, depth), m_world(world) {}
    
    virtual void doSomething() = 0; // pure virtual functions

    virtual void annoy(int damage) = 0; // pure virtual functions
    
    virtual void Move(int ch) = 0; // pure virtual functions
    
    virtual StudentWorld* getWorld()
        {
            return m_world;
        }
    
    virtual void die() {
        alive_checker = false;
    }

    virtual void live() {
        alive_checker = true;
    }

    virtual bool getIsAlive() // using this to check if the tunnelman is still alive
    {
        return alive_checker;
    }

private:
  
   // StudentWorld* m_world; // to referal back to the student world class because this is getting used in the game world
  //  bool alive_checker = true; // using this to check if my tunnel man is alive
    
};


class TunnelMan : public Actor
{
    int hit_pts, water, sonar, nuggets; // the stuff the spec told me to add

public:
    int getWtr(); // added
    int getSonar(); // added
    int getGld(); // added
    int getHP()
    {
        return hit_pts;
    } // added
    int score() // this keeps track of score
    {
        return m_score;
    }

    void score(int i) // setter
    {
        m_score += i;
    }
    
    
    virtual ~TunnelMan() // destructor
    {
        
    }
    
    // making the constructor here through the instructions
    TunnelMan(StudentWorld* world, int imageID = TID_PLAYER, int startX = 30, int startY = 60, float size = 1.0, unsigned int depth = 0) : Actor(world, imageID, startX, startY, right, size, depth), hit_pts(10), water(5), sonar(1), nuggets(0) {setVisible(true);
        live(); // added this
    }

    virtual void doSomething();

    virtual void annoy(int damage);
    
    virtual void Move(int ch); // added this here 
    
    void getting_hit_pts(int damage)
    {
        hit_pts -= damage; // getting damaged by reducing its hit points
        //  -= operator to subtract the value of damage from the hit_pts variable,
    }
    
    void changeSonar(int j)
    {
        sonar += j;
    }
    
    void changeWater(int k)
    {
        water += k;
    }
    
    void changeGold(int h)
    {
        nuggets += h;
    }
    
private:
    int m_score=0;

};

class Earth : public Actor
{
    
public:
    // making the constructor here
    Earth(StudentWorld* world, int startX, int startY, int imageID = TID_EARTH, Direction startDirection = right, float size = .25, unsigned int depth = 3): Actor(world, imageID, startX, startY, startDirection, size, depth) {setVisible(true);}
    
    virtual ~Earth() // destructors
    {
        
    }
    
    virtual void doSomething();

    virtual void annoy(int damage){}
    
    virtual void Move(int ch){}

};

class Boulder : public Actor
{
public:
    Boulder(StudentWorld* world,int startX, int startY, int imageID = TID_BOULDER, float size = 1.0, int depth = 1): Actor(world, imageID, startX, startY, down , size, depth) {setVisible(true);}
        
    virtual void doSomething();
    
    virtual void annoy(int damage){}
    
    virtual void Move(int ch){}
    
    
    virtual ~Boulder();
private:
    bool isStable = true;
    bool isFalling = false;
    int m_ticks = 0;

};

class Squirt : public Actor {
public:
    Squirt(StudentWorld* world, int startX, int startY, Direction dir) :Actor(world, TID_WATER_SPURT, startX, startY, dir, 1.0, 1),m_travel(0) {setVisible(true);}
    
    virtual void doSomething();
    
 //   bool annoyProtesters();
    // added these here
    virtual void annoy(int damage){}
    
    virtual void Move(int ch){}
    
private:
    int m_travel;
};


class Pickupable :public Actor {
public:
    // added this but maybe look into it
    Pickupable(StudentWorld* world, int imageID, int startX, int startY, float size = 1.0 , int depth = 2) :Actor(world, imageID, startX, startY, right , size, depth) {setVisible(true);}
  
    virtual void doSomething() = 0;
    
    void disappearIn(int ticks){}
    
    virtual void annoy(int damage){}
    
    virtual void Move(int ch){}
    
private:
    int m_tick;
};


class Barrel : public Pickupable {
public:
    Barrel(StudentWorld* world, int startX, int startY, int imageID = TID_BARREL) : Pickupable (world, imageID, startX, startY){setVisible(false);}
    
    virtual void doSomething();
    
    virtual void annoy(int damage){}
    
    virtual void Move(int ch){}
};

class Gold :public Pickupable
{
public:
    // added this into it
    Gold(StudentWorld* world, int startX, int startY, int imageID = TID_GOLD) : Pickupable (world, imageID, startX, startY){setVisible(false);}
    
    
    virtual void doSomething();
    
    virtual ~Gold(){}
    
private:
    bool isDropped;
};

class Goodie : public Pickupable
{
public:
    Goodie(StudentWorld* world, int imageID, int startX, int startY)  : Pickupable (world, imageID, startX, startY){setVisible(true);}
    
    virtual void doSomething();
    
//    virtual void annoy(int damage){}
//    
//    virtual void Move(int ch){}
    
};


class Oil : public Actor
{
public:
    Oil(int x, int y, StudentWorld* ptr) ;
    
    virtual void doSomething();
    
    virtual void annoy(int damage){}
    
    virtual void Move(int ch){}
    
    virtual ~Oil();
private:
    //int state;
    
};


class Sonar :public Goodie {
public:
    virtual void annoy(int damage){}
    
    virtual void Move(int ch){}
    
    virtual void doSomething();
    
    Sonar(StudentWorld* world, int startX, int startY,int imageID = TID_SONAR, float size = 1.0, int depth = 2 ): Goodie (world, imageID, startX, startY){setVisible(true);}

};

class WaterPool: public Goodie {
public:
    virtual void annoy(int damage){}
    
    virtual void Move(int ch){}
    
    virtual void doSomething();
    
    WaterPool(StudentWorld* world, int startX, int startY, int imageID = TID_WATER_POOL, float size = 1.0, int depth = 2): Goodie (world, imageID, startX, startY){setVisible(true);}

};

class Water : public Actor
{
public:
    Water(int x, int y, StudentWorld* ptr);
    virtual void doSomething() {
        return;
    }
    virtual ~Water();
};



class RegularProtestors : public Actor
{
public:
    RegularProtestors(StudentWorld* world, int imageID = TID_PROTESTER, float size = 1.0 , int depth = 0, int hP = 5) : Actor(world, imageID, 60, 60, left , size, depth) {setVisible(true);}
    
    virtual void doSomething();
    
    
    virtual void annoy(int damage){}

    virtual void Move(int ch){}
    
    
private:
    int numSquaresToMoveInCurrentDirection;
    int ticks = 0;
    bool resting = false;
    bool leaving = false;
    

};
