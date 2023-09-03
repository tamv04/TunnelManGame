#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include <string>
#include <vector>
#include "Actor.h"
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

//class Actor; // adding the base class here

class StudentWorld : public GameWorld
{
public:
    bool isThereEarth(int x, int y); // added this here
    bool isAboveEarth(int x, int y); // added this
    bool isThereBoulder(int x, int y,int radius); // added this
    bool CheckRadius(int x1, int y1, int x2, int y2, int radius); // added this
    bool CheckIfActorsAreInRadius(int x, int y, int radius);
    void addBoulderorGoldorBarrel (int num, char actor); // added this here
  //  void updateDisplayText(); // added this here to display stuff
    std::string displayText(int score, int level, int lives, int health, int squirts, int gold, int sonar, int barrels); // added this here
    void addGoodies(); // added this
    void clearBoulder(int x,int y);
    
    void addProtestors()
    {
        int T = max(25, 200 - Level);
        
        int P = min(15, (int)(2 + Level * 1.5));
        
        if(ticks == T && numProtesters <= P)
        {
            actor.push_back(new RegularProtestors(this));
            
            numProtesters ++;
            
            ticks = 0;
        }
        else
        {
            ticks++;
        }
    }
    
    void changeBarrelCount(int i)
    {
        m_barrelsLeft += i;
    } // defining it here
   
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
        
	}
    
    virtual ~StudentWorld(); // added this here for destructor

    void cleanEarth(int x, int y);// earth removal function
    
    virtual void cleanUp(); // destructor

    virtual TunnelMan* Player() // added a getter to get tunnel man 
        {
            return tunnel_man;
        }
    
// make getter for earth
// use this to check if tunnel man and the earth overlaps and then figure out how to delete it. 
    
    
	virtual int init()
	{
        // creating oil field aka earth
        for(int x = 0; x < 64; x++)
        {
            for(int y = 0; y < 60; y++)
            {
                if(x<30||x>33||y<4)
                    theEarth[x][y] = new Earth(this,x,y);
            }
            
        }
        
        tunnel_man = new TunnelMan(this);  // create tunnelman
        actor.push_back (new RegularProtestors(this));
        
        int B = min( (int)getLevel()/2 + 2, 9); // from the specs
        int G = max((int)getLevel()/2, 2);
        int L = min( 2 + (int)getLevel(), 21);
        
        addBoulderorGoldorBarrel(B, 'B'); // sponing stuff rn
        addBoulderorGoldorBarrel(L, 'L'); // sponing stuff rn
        addBoulderorGoldorBarrel(G, 'G'); // sponing stuff rn 
        
        m_barrelsLeft = L; // keepign track of the barrel
        
        return GWSTATUS_CONTINUE_GAME;
	}

	virtual int move()
    {
//         This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
//         Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
//        		decLives();
        vector<Actor*>::iterator it;
        
        for (it = actor.begin(); it!= actor.end(); it++)
        {
            if(it >= actor.end() || (*it) == nullptr )
            {
                break;
            }
                if ((*it)->getIsAlive())
                {
                    (*it)->doSomething();
                }
                if (!tunnel_man->getIsAlive()) {
                    decLives();
                    return GWSTATUS_PLAYER_DIED;
                }
                if (m_barrelsLeft == 0)
                {
                    Level++; // increasing the level
                    return GWSTATUS_FINISHED_LEVEL;
                }
                if (!(*it)->getIsAlive())
                {
                    delete *it;
                    *it = nullptr;
                    it = actor.erase(it);
                }
            
        }
        
        for(int x = 0; x < 64; x++)
        {
            for(int y = 0; y < 60; y++)
            {
                if(x<30||x>33||y<4)
                    if(theEarth[x][y] != nullptr && !theEarth[x][y]-> getIsAlive())
                    {
                        delete theEarth[x][y];
                        theEarth[x][y] = nullptr;
                        
                    }
            }
            
        }
        
        tunnel_man->doSomething();
        
        addProtestors(); // protestors exist now
        
        addGoodies();
        
        string scoreBoard = displayText(Player()->score(), Level , getLives() , Player()-> getHP(), Player()->getWtr(), Player()->getGld(), Player()->getSonar(), m_barrelsLeft);
        
        setGameStatText(scoreBoard);
        
        return GWSTATUS_CONTINUE_GAME;
    }

    vector<Actor*> getActor()
    {
        return actor;
    }

private:
    TunnelMan* tunnel_man; // added this
    vector<Actor*> actor; // added this
    Earth *theEarth[74][70]; // added this
    int m_barrelsLeft;// added this
    int Level = 1;
    int ticks = 0;
    int numProtesters = 1;
};

#endif // STUDENTWORLD_H_
