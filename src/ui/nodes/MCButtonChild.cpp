#include "MCButtonChild.h"
#include "MCLabel.h"
#include "../../utils/Utils.h"

using namespace geode::prelude;

CCSprite* generateEdgeSprite(gd::string textureName){

    float scale = CCDirector::sharedDirector()->getContentScaleFactor()/4;

    CCSprite* sprite = CCSprite::create(textureName.c_str(), {49/scale,0,1/scale,5/scale});
    sprite->setAnchorPoint({0,0});

    ccTexParams* params = new ccTexParams{GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
    sprite->getTexture()->setTexParameters(params);

    sprite->setContentSize({sprite->getContentSize().width * scale, sprite->getContentSize().height * scale});

    return sprite;
}

CCSprite* generateSprite(MCButtonChild* parent, gd::string textureName, float width){

    float scale = CCDirector::sharedDirector()->getContentScaleFactor()/4;

    CCSprite* sprite = CCSprite::create(textureName.c_str(), {0,0,width/scale-1.0f/scale,5/scale});

    ccTexParams* params = new ccTexParams{GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
    sprite->getTexture()->setTexParameters(params);
    sprite->setScale(scale);

    parent->removeChildByID("edge"_spr);

    CCSprite* edgeSprite = generateEdgeSprite(textureName);
    edgeSprite->setPositionX(width-1);
    edgeSprite->setZOrder(sprite->getZOrder()+1);
    edgeSprite->setID("edge"_spr);
    edgeSprite->setScale(scale);

    sprite->setContentSize({sprite->getContentSize().width * scale + edgeSprite->getContentSize().width , sprite->getContentSize().height * scale});
    
    parent->edgeTexture = edgeSprite;
    parent->addChild(edgeSprite);

    return sprite;
}

MCButtonChild* MCButtonChild::create(gd::string text, float width, CCObject* target, SEL_MenuHandler selector){

    MCButtonChild* ret = new MCButtonChild();

    CCSprite* buttonSprite = generateSprite(ret, "button.png"_spr, width);
   
    MCLabel* label = MCLabel::create(text, "minecraft.fnt"_spr);
    label->setScale(0.12f);
    label->setZOrder(2);

    if (ret && ret->initWithNormalSprite(buttonSprite, nullptr, nullptr, target, selector)) {
        ret->autorelease();
        ret->scheduleUpdate();
        ret->setScale(3.5);
        ret->addChild(label);
        ret->setAnchorPoint({0,0});
        ret->label = label;
        ret->width = width;
        label->setPosition({ret->getContentSize().width/2, ret->getContentSize().height/2});

        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void MCButtonChild::unselected(){
    
}

void MCButtonChild::doClick(){
    auto engine = FMODAudioEngine::sharedEngine();
    auto system = engine->m_system;

    FMOD::Channel* channel;
    FMOD::Sound* sound;

    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("click.ogg"_spr, false);;
    if(engine->m_sfxVolume > 0) {
        system->createSound(fullPath.c_str(), FMOD_DEFAULT, nullptr, &sound);
        system->playSound(sound, nullptr, false, &channel);
        channel->setVolume(engine->m_sfxVolume);
    }

    geode::Loader::get()->queueInMainThread([this]() { //delay it by a frame because for some reason it crashes the touch dispatcher otherwise ???
        if(m_pListener && m_pfnSelector){
            (m_pListener->*m_pfnSelector)(this);
        }
    });
}

void MCButtonChild::selected(){
    #ifndef GEODE_IS_ANDROID
    doClick();
    #endif
}

void MCButtonChild::activate(){
    #ifdef GEODE_IS_ANDROID
    doClick();
    #endif
}

