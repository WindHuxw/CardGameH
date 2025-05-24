#include "GameController.h"
#include "./views/CardView.h"
#include <views/GameView.h>
#include <vector>
#include "./models/GameModel.h"
#include "./configs/loader/levelConfigLoader.h"
#include <string>
#include "./configs/loader/LevelConfigLoader.h"
#include "base/CCEventListenerTouch.h"
#include "base/CCEvent.h"
#include "./models/UndoModel.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif





//修改了数据
//static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size designResolutionSize = cocos2d::Size(1080, 2080);


static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

GameController::GameController()
{
}

GameController::~GameController()
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void GameController::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool GameController::applicationDidFinishLaunching() {
    // initialize director
    _director = Director::getInstance();
    auto glview = _director->getOpenGLView();
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("CardGame", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height), 0.5, 1);
#else
        glview = GLViewImpl::create("CardGame");
#endif
        _director->setOpenGLView(glview);
    }
    // turn on display FPS
    _director->setDisplayStats(false);
    // set FPS. the default value is 1.0/60 if you don't call this
    _director->setAnimationInterval(1.0f / 60);
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);
    auto frameSize = glview->getFrameSize();
    if (frameSize.height > mediumResolutionSize.height)
    {
        _director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
    }
    else if (frameSize.height > smallResolutionSize.height)
    {
        _director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
    }
    else
    {
        _director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
    }
    register_all_packages();
    // create a scene. it's an autorelease object
    _scene = GameView::createScene();
    // run
    _director->runWithScene(_scene);
    auto dataRead = readJSONFile();
    _layer = dynamic_cast<CardView*>(_scene->getChildByTag(1));
    getData();
    refresh();
    eventDetectHand();
    eventDetectDesk1();
    eventDetectDesk2();
    return true;
}




void GameController::eventDetectHand()
{
    _listenerHand = EventListenerTouchOneByOne::create();
    _listenerHand->onTouchBegan = [this](Touch* touch, Event* event) {
        if (!this->_beforeHandTop)
        {
            // log("ptrHand  %d", (int)this->_beforeHandTop);
            return false;
        }
        // log("ptrHand  %d", (int)this->_beforeHandTop);
        Point locationInNode = this->_beforeHandTop->convertToNodeSpace(touch->getLocation());
        Size size = this->_beforeHandTop->getContentSize();
        if (Rect(0, 0, size.width, size.height).containsPoint(locationInNode)) {

            ActionData a;
            a._card = _gameInfo.handTop();
            a.area = 0;
            a._isPush = 1;
            _gameInfo.undoSave(a);

            _layer->deleteCard(_gameInfo.handTop()._pointer, 1000, 200);
            if (_beforeHandTop)
            {
                ActionData a;
                Vec2 position = _beforeHandTop->getPosition();
                a._card = _gameInfo.handTop();
                a.area = 0;
                a._isPush = 0;
                a._isMove = 1;
                a._x = position.x;
                a._y = position.y;
                _gameInfo.undoSave(a);
                _layer->moveCard(800, 290, _beforeHandTop);
            }
            _gameInfo.replacementHand();
            this->refresh();
            return true; // 吞噬事件
        }
        return false;
    };
    if (_beforeHandTop)
    {
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listenerHand, _beforeHandTop);
    }

}

void GameController::eventDetectDesk1()
{
    _listenerDesk1 = EventListenerTouchOneByOne::create();
    _listenerDesk1->onTouchBegan = [this](Touch* touch, Event* event) {
        if (!this->_deskTop1)
        {
            return false;
        }
        Point locationInNode = this->_deskTop1->convertToNodeSpace(touch->getLocation());
        Size size = this->_deskTop1->getContentSize();
        if (Rect(0, 0, size.width, size.height).containsPoint(locationInNode)) {
            if ((this->_deskTop1Face - 1 == this->_handFace ||
                this->_deskTop1Face + 1 == this->_handFace)) {
                // 保存删除操作到回滚栈
                ActionData a;
                a._card = _gameInfo.handTop();
                a.area = 1; // 桌面1区域
                a._isPush = 1;
                _gameInfo.undoSave(a);

                _layer->deleteCard(_gameInfo.handTop()._pointer, 1000, 200);
                if (_deskTop1)
                {
                    // 保存移动操作到回滚栈
                    ActionData b;
                    Vec2 position = _deskTop1->getPosition();
                    b._card = _gameInfo.handTop();
                    b.area = 1; // 桌面1区域
                    b._isPush = 0;
                    b._isMove = 1;
                    b._x = position.x;
                    b._y = position.y;
                    _gameInfo.undoSave(b);
                    _layer->moveCard(800, 290, _deskTop1);
                }
                _gameInfo.replacementHand();
                _gameInfo.handPush(_gameInfo.deskTop1());
                _gameInfo.deskPop1();
                this->refresh();
            }
            return true;
        }
        return false;
    };
    if (_deskTop1)
    {
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listenerDesk1, _deskTop1);
    }
}

void GameController::eventDetectDesk2()
{
    _listenerDesk2 = EventListenerTouchOneByOne::create();
    _listenerDesk2->onTouchBegan = [this](Touch* touch, Event* event) {
        if (!this->_deskTop2)
        {
            return false;
        }
        Point locationInNode = this->_deskTop2->convertToNodeSpace(touch->getLocation());
        Size size = this->_deskTop2->getContentSize();
        if (Rect(0, 0, size.width, size.height).containsPoint(locationInNode)) {
            if ((this->_deskTop2Face - 1 == this->_handFace ||
                this->_deskTop2Face + 1 == this->_handFace)) {
                // 保存删除操作到回滚栈
                ActionData a;
                a._card = _gameInfo.handTop();
                a.area = 2; // 桌面2区域
                a._isPush = 1;
                _gameInfo.undoSave(a);
                _layer->deleteCard(_gameInfo.handTop()._pointer, 1000, 200);
                if (_deskTop1)
                {
                    // 保存移动操作到回滚栈
                    ActionData b;
                    Vec2 position = _deskTop2->getPosition();
                    b._card = _gameInfo.handTop();
                    b.area = 2; // 桌面2区域
                    b._isPush = 0;
                    b._isMove = 1;
                    b._x = position.x;
                    b._y = position.y;
                    _gameInfo.undoSave(b);
                    _layer->moveCard(800, 290, _deskTop2);
                }
                _gameInfo.replacementHand();
                _gameInfo.handPush(_gameInfo.deskTop2());
                _gameInfo.deskPop2();
                this->refresh();
            }
            return true;
        }
        return false;
    };
    if (_deskTop2)
    {
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listenerDesk2, _deskTop2);
    }
}

//读取数据
void GameController::getData()
{
    auto dataRead = readJSONFile();
    _layer = dynamic_cast<CardView*>(_scene->getChildByTag(1));
    for (auto data : dataRead[0])
    {
        if (data._x <= 550)
        {
            auto card = _layer->addCard(data._x, data._y + 580, data._CSTtype, data._CFTtype);
            data._pointer = card;
            _gameInfo.deskPush1(data);
        }
        else
        {
            auto card = _layer->addCard(data._x, data._y + 580, data._CSTtype, data._CFTtype);
            data._pointer = card;
            _gameInfo.deskPush2(data);
        }

    }
    { int i = 0;
    for (; i < dataRead[1].size() - 1; i++)
    {

        auto card = _layer->addCard(dataRead[1][i]._x + 200 + 180 * i, dataRead[1][i]._y + 290, dataRead[1][i]._CSTtype, dataRead[1][i]._CFTtype);
        dataRead[1][i]._pointer = card;
        _gameInfo.handPush(dataRead[1][i]);
    }
    auto card = _layer->addCard(800, 290, dataRead[1][i]._CSTtype, dataRead[1][i]._CFTtype);
    dataRead[1][i]._pointer = card;
    _gameInfo.handPush(dataRead[1][i]);
    }
}

void GameController::refresh()
{
    _deskTop1 = _gameInfo.deskTop1()._pointer;
    _deskTop2 = _gameInfo.deskTop2()._pointer;
    _beforeHandTop = _gameInfo.beforeHandTop()._pointer;
    _deskTop1Face = static_cast<int>(_gameInfo.deskTop1()._CFTtype);
    _deskTop2Face = static_cast<int>(_gameInfo.deskTop2()._CFTtype);
    _beforeHandFace = static_cast<int>(_gameInfo.beforeHandTop()._CFTtype);
    _handFace = static_cast<int>(_gameInfo.handTop()._CFTtype);
    if (_gameInfo.judgeWin())
    {
        // 创建并设置Label（一行完成）
        auto winLabel = Label::createWithSystemFont("WIN!", "Arial", 80);
        winLabel->setTextColor(Color4B(255, 215, 0, 255)); // 金色
        winLabel->setPosition(540, 1300); // 屏幕坐标
        _layer->addChild(winLabel);
    };
    eventDetectHand();
    eventDetectDesk1();
    eventDetectDesk2();

}



// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void GameController::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void GameController::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}