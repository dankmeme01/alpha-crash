#include "CrashLayer.h"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

CrashLayer* CrashLayer::create() {
    auto ret = new CrashLayer();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool CrashLayer::init() {
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    setKeypadEnabled(true);
    return true;
}

void CrashLayer::keyBackClicked() {
    CCDirector::sharedDirector()->popScene();
}

void CrashLayer::onBack(CCObject* object) {
    keyBackClicked();
}

CCScene* CrashLayer::scene() {
    auto layer = CrashLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
}
