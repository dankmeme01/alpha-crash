#include "ExtrasLayer.h"
#include "../../utils/Utils.h"
#include "../nodes/MCLabel.h"
#include "../nodes/MCButton.h"
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

ExtrasLayer* ExtrasLayer::create() {
    auto ret = new ExtrasLayer();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool ExtrasLayer::init() {

    return true;
}

void ExtrasLayer::onNewgrounds(CCObject* object){
}

void ExtrasLayer::keyBackClicked() {
    CCDirector::sharedDirector()->popScene();
}

void ExtrasLayer::onBack(CCObject* object) {
    keyBackClicked();
}

CCScene* ExtrasLayer::scene() {
    auto layer = ExtrasLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
}
