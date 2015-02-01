#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
   
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //load block
    auto winsize = Director::getInstance()->getWinSize();
    this->blockWidth = winsize.width*0.2;
    this->p_firstBlock = Vec2(winsize.width/2-blockWidth*2,winsize.height/2+blockWidth);
    
    for (int i = 0; i<6; i++) {
        for (int j = 0; j<6; j++) {
            auto block = Block::create();
            block->setHang(i);
            block->setLie(j);
            block->setBlank(true);
            blocks.pushBack(block);
        }
    }
    
    for (int i = 1; i<5; i++) {
        for (int j = 1; j<5; j++) {
            
            int index = rand()%4;
            blocks.at(i*6+j)->setIndex(index);
//            blocks.at(i*6+j)->setHang(i);
//            blocks.at(i*6+j)->setLie(j);
            blocks.at(i*6+j)->setBlank(false);
            blocks.at(i*6+j)->setTextureRect(Rect(2, 2, blockWidth-4, blockWidth-4));
            blocks.at(i*6+j)->setContentSize(Size(blockWidth,blockWidth));
            blocks.at(i*6+j)->setColor(getColorWithIndex(index));
            blocks.at(i*6+j)->setAnchorPoint(Vec2(0,0));
            blocks.at(i*6+j)->setPosition(p_firstBlock.x+(j-1)*blockWidth,p_firstBlock.y-(i-1)*blockWidth);
            blocks.at(i*6+j)->setTag(i*6+j);
            addChild(blocks.at(i*6+j));

        }
    }
    
    //listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* t,Event* e){
        
        for (auto it = blocks.begin(); it != blocks.end(); it++) {
            auto block = *it;
            if (block->getBoundingBox().containsPoint(t->getLocation())) {
                //log("----tag : %d-----hang : %d----lie : %d",block->getTag(),block->getHang(),block->getLie());
                
                if (this->touch == true) {
                    
                    this->findAll(block);
                    this->printvector(this->targets);
                    
                    this->origins.clear();
                    this->firstBlockTag = block->getTag();
                    touch = !touch;
                    
                }else{
                    
                    for (auto i = targets.begin(); i != targets.end(); i++) {
                        auto b = *i;
                        if ((block->getIndex() == b->getIndex())
                            &&(block->getHang() == b->getHang())
                            &&(block->getLie() == b->getLie())) {
                            
                            
                            auto fb = (Block*)this->getChildByTag(this->firstBlockTag);
                            block->setBlank(true);
                            fb->setBlank(true);
                            
                            block->setColor(Color3B::BLACK);
                            fb->setColor(Color3B::BLACK);
                            
                        }
                        
                    }
                    
                    this->targets.clear();
                    touch = !touch;
                }
            }
        }
        
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    //exit
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

    auto closeItem = static_cast<ui::Button*>(rootNode->getChildByName("Button_1"));
    closeItem->addTouchEventListener(CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    return true;
}

//find target blocks with    up down left right
void HelloWorld::findOnce(Block *block)
{
    int hang = 0;
    int lie  = 0;
    
    //up
    hang = block->getHang()-1;
    lie = block->getLie();
    while (hang >= 0) {
        Block* temp = blocks.at(6*hang+lie);
        if (temp->getBlank() == false) {
            targets.pushBack(temp);
            hang = hang - 100;
        }else{
            origins.pushBack(temp);
        }
        hang = hang - 1;
    }
    
    //down
    hang = block->getHang()+1;
    lie = block->getLie();
    while (hang <= 5) {
        Block* temp = blocks.at(6*hang+lie);
        if (temp->getBlank() == false) {
            targets.pushBack(temp);
            hang = hang + 100;
        }else{
            origins.pushBack(temp);
        }
        hang = hang + 1;
    }
    
    //left
    hang = block->getHang();
    lie = block->getLie()-1;
    while (lie >= 0) {
        Block* temp = blocks.at(6*hang+lie);
        if (temp->getBlank() == false) {
            targets.pushBack(temp);
            lie = lie - 100;
        }else{
            origins.pushBack(temp);
        }
        lie = lie - 1;
    }
    
    //right
    hang = block->getHang();
    lie = block->getLie()+1;
    while (lie <= 5) {
        Block* temp = blocks.at(6*hang+lie);
        if (temp->getBlank() == false) {
            targets.pushBack(temp);
            lie = lie + 100;
        }else{
            origins.pushBack(temp);
        }
        lie = lie + 1;
    }
    
    
}


//find all target Blocks
void HelloWorld::findAll(Block *block){
    origins.pushBack(block);
    for (int i = 0; i < 3; i++) {
        if (origins.size() != 0) {
            
            //temp
            Vector<Block*> t;
            for (int i = 0; i < origins.size(); i++) {
                t.pushBack(origins.at(i));
            }
            
            origins.clear();
            
            //add to target
            for (int i = 0; i < t.size(); i++) {
                findOnce(t.at(i));
            }
            
            t.clear();
        }
    }
}


//index to color
Color3B HelloWorld::getColorWithIndex(int index){
    if (index == 1) {
        return Color3B::WHITE;
    } else if(index == 2){
        return Color3B::RED;
    } else if(index == 3){
        return Color3B::BLUE;
    } else{
        return Color3B::YELLOW;
    }
}


//print
void HelloWorld::printvector(Vector<Block *> bs){
    for (auto i = bs.begin(); i != bs.end() ; i++) {
        auto t = *i;
        log("++----tag : %d-----hang : %d----lie : %d",t->getTag(),t->getHang(),t->getLie());
    }
}

//exit button
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
