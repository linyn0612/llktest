//
//  Block.h
//  llktest
//
//  Created by 林跃南 on 15/1/31.
//
//

#ifndef __llktest__Block__
#define __llktest__Block__

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;

class Block :public Sprite{
public:
    
    virtual bool init();
    CREATE_FUNC(Block);
    
    CC_SYNTHESIZE(int, _hang, Hang);
    CC_SYNTHESIZE(int, _lie, Lie);
    CC_SYNTHESIZE(bool, _blank, Blank);
    CC_SYNTHESIZE(int, _index, Index);
    //CC_SYNTHESIZE(Color3B, _color, BlockColor);
    
};

#endif /* defined(__llktest__Block__) */
