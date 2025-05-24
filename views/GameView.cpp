#include "GameView.h"
#include "CardView.h"
#include <cocos/ui/UIButton.h>
USING_NS_CC;

Scene* GameView::createScene() {
    return GameView::create(); // 通过CREATE_FUNC生成Scene实例
}


bool GameView::init() {
    if (!Scene::init()) return false;

    // 创建底层紫色区域
    auto purpleLayer = LayerColor::create(
        Color4B(128, 0, 128, 255),  // 紫色RGBA
        1080,
        580
    );
    purpleLayer->setPosition(0, 0); // 左下角对齐
    this->addChild(purpleLayer, -100); // 先添加底层

    // 创建上层棕色区域
    auto brownLayer = LayerColor::create(
        Color4B(139, 69, 19, 255),  // 棕色RGBA
        1080,
        1500
    );
    brownLayer->setPosition(0, purpleLayer->getContentSize().height); // 紧贴紫色层上方
    this->addChild(brownLayer, -100); // 后添加上层

      // 添加卡牌层（zOrder设为2）
    _cardLayer = CardView::create();
    this->addChild(_cardLayer, 2);
    _cardLayer->setButton();
    // 
    brownLayer->setTag(1002);
    purpleLayer->setTag(1003);
    _cardLayer->setTag(1);
    return true;
}