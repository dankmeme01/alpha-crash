#include "MCLabel.h"
#include "../../utils/Utils.h"
#include <cstdlib>
#include <iostream>

MCLabel* MCLabel::create(std::string text, std::string font){
    MCLabel *ret = new MCLabel();

    if (ret && ret->init(text, font)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}


bool MCLabel::init(std::string text, std::string font){
    CCLabelBMFont::initWithString(text.c_str(), font.c_str());
    return true;
}
