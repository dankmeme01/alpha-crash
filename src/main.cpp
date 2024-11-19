#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "CrashLayer.h"

using namespace geode::prelude;

#include <Geode/modify/CCDirector.hpp>
#include <Geode/modify/CCMenuItemSpriteExtra.hpp>

class $modify(MyCCMenuItemSpriteExtra, CCMenuItemSpriteExtra){

    struct Fields {
        cocos2d::SEL_MenuHandler m_buttonCallback;
        CCObject* m_buttonTarget;
        bool m_isMCButton = false;
    };

    bool init(cocos2d::CCNode* p0, cocos2d::CCNode* p1, cocos2d::CCObject* p2, cocos2d::SEL_MenuHandler p3){
        m_fields->m_buttonCallback = p3;
        m_fields->m_buttonTarget = p2;
        return CCMenuItemSpriteExtra::init(p0, p1, p2, p3);
    }

    void selected(){
        CCMenuItemSpriteExtra::selected();
    }

    void unselected(){
        CCMenuItemSpriteExtra::unselected();
    }

    void activate(){
        CCMenuItemSpriteExtra::activate();
    }
};

class $modify(MyCCDirector, CCDirector){

	bool replaceScene(CCScene *pScene){
		return CCDirector::replaceScene(pScene);
	}
};

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
			this,
			menu_selector(MyMenuLayer::onMyButton)
		);

		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(myButton);

		myButton->setID("my-button"_spr);

		menu->updateLayout();

		return true;
	}

	void onMyButton(CCObject*) {
		CCScene* scene = CrashLayer::scene();
		auto transition = CCTransitionFade::create(0.0f, scene);
		CCDirector::sharedDirector()->pushScene(transition);
	}
};