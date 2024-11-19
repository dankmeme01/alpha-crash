#include "MCButton.h"
#include "MCButtonChild.h"

MCButton* MCButton::create(gd::string text, float width, CCObject* target, SEL_MenuHandler selector){

    auto ret = new MCButton();

    if (ret && ret->init()) {
        MCButtonChild* child = MCButtonChild::create(text, width, target, selector);
        ret->child = child;
        ret->setContentSize(child->getScaledContentSize());
        ret->addChild(child);
        ret->ignoreAnchorPointForPosition(false);
        ret->autorelease();
        ret->scheduleUpdate();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

void MCButton::addSprite(CCSprite* sprite){
    sprite->setZOrder(5);
    this->child->addChild(sprite);
}

CCSize MCButton::getContentSize(){
    return this->child->getContentSize();
}