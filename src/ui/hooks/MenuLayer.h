#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
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
		MCButton* editButton = MCButton::create("Online Levels", 49.1f, this, menu_selector(MenuLayer::onCreator));
		MCButton* modsButton = MCButton::create("Mods", 24.0f, this, menu_selector(MyMenuLayer::onMods));
		MCButton* skinButton = MCButton::create("Skins", 24.0f, this, menu_selector(MenuLayer::onGarage));

		MCButton* optionsButton = MCButton::create("Options...", 24.0f, this, menu_selector(MyMenuLayer::onOptions));
		MCButton* quitButton = MCButton::create("Quit Game", 24.0f, this, menu_selector(MenuLayer::onQuit));

		MCButton* profileButton = MCButton::create("", 5.0f, this, menu_selector(MyMenuLayer::onMyProfile));
		MCButton* extrasButton = MCButton::create("", 5.0f, this, menu_selector(MyMenuLayer::onExtras));

		CCSprite* profileSprite = Utils::createPixelSprite("teleport_to_player.png"_spr);
		profileSprite->setZOrder(1);
		profileSprite->setPosition({profileButton->getContentSize().width/2, profileButton->getContentSize().height/2});
		profileButton->addSprite(profileSprite);

		CCSprite* extrasSprite = Utils::createPixelSprite("search.png"_spr);
		extrasSprite->setZOrder(1);
		extrasSprite->setPosition({extrasButton->getContentSize().width/2, extrasButton->getContentSize().height/2});
		extrasButton->addSprite(extrasSprite);


		menu->addChild(playButton);
		playButton->setID("play-button"_spr);
		menu->addChild(editButton);
		editButton->setID("edit-button"_spr);
		menu->addChild(modsButton);
		modsButton->setID("mods-button"_spr);
		menu->addChild(skinButton);
		skinButton->setID("skin-button"_spr);
		menu->addChild(optionsButton);
		optionsButton->setID("options-button"_spr);
		menu->addChild(quitButton);
		quitButton->setID("quit-button"_spr);
		menu->addChild(profileButton);
		profileButton->setID("profile-button"_spr);
		menu->addChild(extrasButton);
		extrasButton->setID("extras-button"_spr);

		menu->ignoreAnchorPointForPosition(false);

		this->addChild(menu);
		menu->setID("minecraft-menu"_spr);

		auto titleSprite = "minecraft-title.png"_spr;
		if (Utils::isMinceraft()) {
			titleSprite = "minceraft-title.png"_spr;
		}

		CCSprite* title = Utils::createPixelSprite(titleSprite);
		title->setScale(title->getScale()*0.9);
		

		CCSprite* subTitle = Utils::createPixelSprite("edition.png"_spr);
		subTitle->setScale(subTitle->getScale()/scale*0.9);

		subTitle->setPosition({title->getContentSize().width/2, title->getContentSize().height/2 - 11.5f/scale});

		this->addChild(title);
		title->setID("minecraft-title"_spr);

		title->addChild(subTitle);
		subTitle->setID("minecraft-subtitle"_spr);
		
		this->scheduleUpdate();

		setPositions(winSize);

		CCScheduler::get()->scheduleSelector(schedule_selector(MyMenuLayer::myUpdate), this, 0.0, false);

		return true;
	}

	void onMods(CCObject* sender) {
		geode::openModsList();
	}

	void onMyProfile(CCObject* sender) {

		ProfilePage* page = ProfilePage::create(GJAccountManager::sharedState()->m_accountID, true);
		page->show();
	}

	void onExtras(CCObject* sender) {
		CCScene* scene = ExtrasLayer::scene();
		auto transition = CCTransitionFade::create(0.0f, scene);
		CCDirector::sharedDirector()->pushScene(transition);
	}

	void myUpdate(float dt){

		auto winSize = CCDirector::sharedDirector()->getWinSize();

		float ratio = winSize.width / winSize.height;
		float lastRatio = this->m_fields->lastSize.width / this->m_fields->lastSize.height;

		if(ratio != lastRatio){
			setPositions(winSize);
		}

		this->m_fields->lastSize = winSize;
	}

	void setPositions(CCSize winSize){

		CCNode* menu = this->getChildByID("minecraft-menu"_spr);;

		MCButton* playButton = typeinfo_cast<MCButton*>(menu->getChildByID("play-button"_spr));
		MCButton* editButton = typeinfo_cast<MCButton*>(menu->getChildByID("edit-button"_spr));
		MCButton* modsButton = typeinfo_cast<MCButton*>(menu->getChildByID("mods-button"_spr));
		MCButton* skinButton = typeinfo_cast<MCButton*>(menu->getChildByID("skin-button"_spr));
		MCButton* optionsButton = typeinfo_cast<MCButton*>(menu->getChildByID("options-button"_spr));
		MCButton* quitButton = typeinfo_cast<MCButton*>(menu->getChildByID("quit-button"_spr));
		MCButton* profileButton = typeinfo_cast<MCButton*>(menu->getChildByID("profile-button"_spr));
		MCButton* extrasButton = typeinfo_cast<MCButton*>(menu->getChildByID("extras-button"_spr));

		CCSprite* title = typeinfo_cast<CCSprite*>(this->getChildByID("minecraft-title"_spr));

		playButton->setPosition({winSize.width/2, winSize.height/2+45});
		editButton->setPosition({winSize.width/2, winSize.height/2+23});
		modsButton->setPosition({winSize.width/2 - 44, winSize.height/2+1});
		skinButton->setPosition({winSize.width/2 + 44, winSize.height/2+1});
		optionsButton->setPosition({winSize.width/2 - 44, winSize.height/2-28});
		quitButton->setPosition({winSize.width/2 + 44, winSize.height/2-28});
		profileButton->setPosition({winSize.width/2.0f - 98.5f, winSize.height/2-28});
		extrasButton->setPosition({winSize.width/2.0f + 98.5f, winSize.height/2-28});

		title->setPosition({winSize.width/2.0f, winSize.height-55});
	}
};
