#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Block.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(HelloWorld);
    
private:
    Vec2 p_firstBlock;
    float blockWidth;
    Vector<Block*> blocks;
    Vector<Block*> targets;
    Vector<Block*> origins;
    bool touch = true;
    int firstBlockTag;
    
public:
    Color3B getColorWithIndex(int index);
    void findAll(Block *block);
    void findOnce(Block *block);
    void printvector(Vector<Block*> bs);
};

#endif // __HELLOWORLD_SCENE_H__
