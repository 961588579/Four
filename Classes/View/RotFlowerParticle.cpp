//
//  RotFlowerParticle.cpp
//  Four
//
//  Created by 王选易 on 14-5-7.
//
//

#include "RotFlowerParticle.h"

bool RotFlowerParticle::init(){
    
    ParticleSnow::init();
    
    this->setTexture(TextureCache::sharedTextureCache()->addImage("star.png"));
    this->setEmissionRate(this->getTotalParticles() / this->getLife());
    this->setPosition(Vec2(320, 1100));
    this->setLife(3);
    this->setLifeVar(1);
    this->setGravity(Vec2::ZERO);
    this->setSpeed(130);
    this->setSpeedVar(30);
    
    // color of particles
    Color4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
    this->setStartColor(startColor);
    
    Color4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
    this->setStartColorVar(startColorVar);
    
    Color4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
    this->setEndColor(endColor);
    
    Color4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};
    this->setEndColorVar(endColorVar);
    
    this->setScale(2.0);
    
    return true;
}
