#include "MCButton.h"
#include "MCButtonChild.h"

MCButton* MCButton::create(gd::string text, float width, CCObject* target, SEL_MenuHandler selector){

    MCButton* ret = new MCButton();

    MCButtonChild* child = MCButtonChild::create(text, width, target, selector);
    if (ret && ret->init()) {
        ret->child = child;
        ret->setContentSize(child->getScaledContentSize());
        ret->addChild(child);
        ret->ignoreAnchorPointForPosition(false);
        ret->autorelease();
        ret->scheduleUpdate();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void MCButton::addSprite(CCSprite* sprite){
    sprite->setZOrder(5);
    this->child->addChild(sprite);
}

CCSize MCButton::getContentSize(){
    return this->child->getContentSize();
}