#pragma once

#include <Geode/Bindings.hpp>

using namespace geode::prelude;

class CrashLayer : public cocos2d::CCLayer {
protected:
    CCLayer* m_menuLayer;

    virtual bool init();
    virtual void keyBackClicked();
    void onBack(cocos2d::CCObject*);
public:
    static CrashLayer* create();
    static cocos2d::CCScene* scene();
};