#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CCObject.hpp>
#include <Geode/modify/CCString.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include "../../utils/Utils.h"
#include "../nodes/MCLabel.h"
#include "../nodes/MCButton.h"
#include "../layers/ExtrasLayer.h"

using namespace geode::prelude;


class $modify(MyMenuLayer, MenuLayer) {

	struct Fields {
		CCSize lastSize;
	};

	static void onModify(auto& self) {
        (void) self.setHookPriority("MenuLayer::init", -1000);
    }

	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		auto winSize = CCDirector::sharedDirector()->getWinSize();

		FMODAudioEngine::sharedEngine()->playEffect("click.ogg"_spr);

		CCMenu* menu = CCMenu::create();

		MCButton* playButton = MCButton::create("Singleplayer", 49.1f, this, menu_selector(MenuLayer::onPlay));

		menu->addChild(playButton);
		playButton->setID("play-button"_spr);

		menu->ignoreAnchorPointForPosition(false);

		this->addChild(menu);
		menu->setID("minecraft-menu"_spr);

		setPositions(winSize);

		return true;
	}

	void onPlay(CCObject* s)  {
		MenuLayer::onPlay(s);

		CCNode* menu = this->getChildByID("minecraft-menu"_spr);;
		MCButton* playButton = typeinfo_cast<MCButton*>(menu->getChildByID("play-button"_spr));
	}

	void setPositions(CCSize winSize){
		CCNode* menu = this->getChildByID("minecraft-menu"_spr);;
		MCButton* playButton = typeinfo_cast<MCButton*>(menu->getChildByID("play-button"_spr));
		playButton->setPosition({winSize.width/2, winSize.height/2+45});
	}
};
