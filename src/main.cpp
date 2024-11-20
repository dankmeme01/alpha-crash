#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CCLabelBMFont.hpp>

using namespace geode::prelude;

class MCLabel : public CCLabelBMFont {
public:
    static MCLabel* create(std::string text, std::string font) {
        MCLabel *ret = new MCLabel();
        if (ret->init(text, font)) {
            return static_cast<MCLabel*>(ret->autorelease());
        } else {
            delete ret;
            return nullptr;
        }
    }

    bool init(std::string text, std::string font) {
        return CCLabelBMFont::initWithString(text.c_str(), font.c_str());
    }
};


class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

		FMODAudioEngine::sharedEngine()->playEffect("click.ogg"_spr);
		MCLabel* label2 = MCLabel::create("Singleplayer", "minecraft.fnt"_spr);

        return true;
    }
};
