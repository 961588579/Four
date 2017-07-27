//
//  Model.cpp
//  Four
//
//  Created by 王选易 on 14-4-21.
//
//

#include "Model.h"

#include <algorithm>

Model* Model::addTransition(const string& from, const string& event, const string& to){
    map<string, string>& form_transitions = transitions[from];
    form_transitions[event] = to;
    return this;
}

void Model::onAsyncMessage(Node* node, void* msg){
    async = false;
    __String *message = (__String *)msg;
    this->onMessage(message->getCString());
    message->release();
}

bool Model::checkMessage(const string &msg){
    return transitions[currentState].find(msg) != transitions[currentState].end();
}

void Model::onMessage(const string& msg){
    CCLOG("%s", msg.c_str());
    if (checkMessage(msg) && !async) {
        this->currentState = this->transitions[this->currentState][msg];
        CCLOG("transfer to State : %s", this->currentState.c_str());
        __NotificationCenter::getInstance()->postNotification(msg.c_str());
    }
}

void Model::onMessage(const string &msg, Ref* o){
    CCLOG("%s", msg.c_str());
    if (checkMessage(msg) && !async) {
        this->currentState = this->transitions[this->currentState][msg];
        CCLOG("transfer to State : %s", this->currentState.c_str());
        __NotificationCenter::getInstance()->postNotification(msg.c_str(), o);
    }
}

void Model::waitAction(Node* node, FiniteTimeAction* action, const string& msg){
    using namespace cocos2d;
    async = true;
    __String* cc_msg = __String::create(msg);
    cc_msg->retain();
    FiniteTimeAction* action2 = __CCCallFuncND::create(this, CC_CALLFUNCND_SELECTOR(Model::onAsyncMessage), (void *) cc_msg);
    Sequence* sequence = Sequence::createWithTwoActions(action, action2);
    node->runAction(sequence);
}

const char* Model::getState(){
    return this->currentState.c_str();
}
