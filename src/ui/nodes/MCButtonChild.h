#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class MCButtonChild : public CCMenuItemSprite
{
public:
    CCSprite* edgeTexture;
    static MCButtonChild* create(gd::string text, float width, CCObject* target, SEL_MenuHandler selector);
    void selected();
    void unselected();
    void activate();
    void doClick();
private:
    bool isHovering = false;
    bool isInvisible = false;
    bool fadeStarted = false;
    float width = 50;
    CCLabelBMFont* label;
};