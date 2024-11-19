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

        float scale = CCDirector::sharedDirector()->getContentScaleFactor()/4;

		Utils::getNodeSafe(this, "main-menu")->setVisible(false);
		Utils::getNodeSafe(this, "profile-menu")->setVisible(false);
		Utils::getNodeSafe(this, "player-username")->setVisible(false);
		Utils::getNodeSafe(this, "social-media-menu")->setVisible(false);
		Utils::getNodeSafe(this, "close-menu")->setVisible(false);
		Utils::getNodeSafe(this, "bottom-menu")->setVisible(false);
		Utils::getNodeSafe(this, "more-games-menu")->setVisible(false);
		Utils::getNodeSafe(this, "main-menu-bg")->setVisible(false);
		Utils::getNodeSafe(this, "main-menu-bg")->setScale(0);
		Utils::getNodeSafe(this, "right-side-menu")->setVisible(false);
		Utils::getNodeSafe(this, "main-title")->setVisible(false);

		CCMenu* menu = CCMenu::create();

		MCButton* playButton = MCButton::create("Singleplayer", 49.1f, this, menu_selector(MenuLayer::onPlay));

		menu->addChild(playButton);
		playButton->setID("play-button"_spr);

		menu->ignoreAnchorPointForPosition(false);

		this->addChild(menu);
		menu->setID("minecraft-menu"_spr);

		setPositions(winSize);

		this->schedule(schedule_selector(MyMenuLayer::updateStuff), 0.1f);

		return true;
	}

	void updateStuff(float) {
	}

	void onPlay(CCObject* s)  {

		MenuLayer::onPlay(s);

		CCNode* menu = this->getChildByID("minecraft-menu"_spr);;
		MCButton* playButton = typeinfo_cast<MCButton*>(menu->getChildByID("play-button"_spr));

		log::debug("rc = {}, rcc = {}", playButton->retainCount(), playButton->child->retainCount());
	}

	void setPositions(CCSize winSize){
		CCNode* menu = this->getChildByID("minecraft-menu"_spr);;
		MCButton* playButton = typeinfo_cast<MCButton*>(menu->getChildByID("play-button"_spr));
		playButton->setPosition({winSize.width/2, winSize.height/2+45});
	}
};
