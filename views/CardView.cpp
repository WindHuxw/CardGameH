// CardView.cpp
#include "CardView.h"
#include "./configs/models/CardResConfig.h"
USING_NS_CC;
//// 声明外部变量（不分配内存）
//extern const std::vector<std::string>  kCardSuitTypePaths;
//extern const std::vector<std::string> kBigBlackPaths;
//extern const std::vector<std::string> kSmallBlackPaths;
//extern const std::vector<std::string> kBigRedPaths;
//extern const std::vector<std::string> kSmallRedPaths;

//添加卡片
Sprite* CardView::addCard(float x, float y, CardSuitType cst, CardFaceType cft) {
    // 1. 创建4个精灵

    Sprite* whiteRect = nullptr;
    Sprite* baseSprite = nullptr;
    Sprite* overlaySprite = nullptr;
    Sprite* smallBlack = nullptr;

    if (cst == CST_CLUBS || cst == CST_SPADES)
    {
        whiteRect = Sprite::create();
        baseSprite = Sprite::create(kBigBlackPaths[cft]);
        overlaySprite = Sprite::create(kCardSuitTypePaths[cst]);
        smallBlack = Sprite::create(kSmallBlackPaths[cft]);
    }
    else
    {
        whiteRect = Sprite::create();
        baseSprite = Sprite::create(kBigRedPaths[cft]);
        overlaySprite = Sprite::create(kCardSuitTypePaths[cst]);
        smallBlack = Sprite::create(kSmallRedPaths[cft]);
    }
 
    whiteRect->setTextureRect(Rect(0, 0,
        baseSprite->getContentSize().width * 1.5f,
        baseSprite->getContentSize().height * 1.5f
    ));
    whiteRect->setColor(Color3B::WHITE);
    whiteRect->setPosition(Vec2(x, y)); // 左下角坐标为(x,y)
    this->addChild(whiteRect, -100);    // 强制设为最底层

    baseSprite->setPosition(Vec2(
        whiteRect->getContentSize().width * 0.5f,  // 水平居中
        whiteRect->getContentSize().height * 0.5f-40  // 垂直居中
    ));
    whiteRect->addChild(baseSprite);    // 绑定到whiteRect

    overlaySprite->setPosition(Vec2(100, 225));  // 相对于baseSprite的偏移
    baseSprite->addChild(overlaySprite, 1);     // 层级较高

    smallBlack->setPosition(Vec2(0, 225));      // 相对于baseSprite的偏移
    baseSprite->addChild(smallBlack, 1);        // 与club.png同层级

    return whiteRect;
}


bool CardView::moveCard(float x, float y, Sprite* card)
{
    // 绝对坐标移动（从当前位置移动到 (200, 200)）
    auto moveTo = MoveTo::create(1.0f, Vec2(x, y));
    card->runAction(moveTo);
    return true;
}

bool CardView::deleteCard(Sprite* card, float targetX, float targetY)
{
    if (!card || !card->getParent()) {
        CCLOG("Error: Invalid card or card has no parent!");
        return false;
    }

    // 1. 停止卡片当前所有动作
    card->stopAllActions();

    // 2. 创建移动动画（1秒内移动到目标位置）
    auto moveTo = MoveTo::create(0.5f, Vec2(targetX, targetY));

    // 3. 创建删除回调（动画完成后执行）
    auto removeSelf = CallFunc::create([card]() {
        card->removeFromParentAndCleanup(true); // 彻底删除节点
        });

    // 4. 组合动作序列
    auto sequence = Sequence::create(moveTo, removeSelf, nullptr);

    // 5. 运行动画
    card->runAction(sequence);

    return true;
}

void CardView::setButton()
{
    // 创建按钮（初始尺寸150x60）
    _backButton = ui::Button::create();
    _backButton->setPosition(Vec2(1000, 290));
    _backButton->setContentSize(Size(70, 305));
    _backButton->setScale9Enabled(true);
    _backButton->setName("backButton"); // 设置名称便于查找


    // 创建文字标签
    auto label = Label::createWithTTF("R\ne\nt\nu\nr\nn", "fonts/Marker Felt.ttf", 50);
    label->setPosition(_backButton->getPosition() + Vec2(0, 0));

    //// 添加点击事件（测试用：点击后放大按钮）
  /*  _backButton->addClickEventListener([=](Ref* sender) {
        });*/

    // 添加到场景
    this->addChild(_backButton, 10);
    this->addChild(label, 10);
}
bool CardView::init() {
    if (!Layer::init()) return false;
  /*  auto ca = addCard(100, 100, CST_DIAMONDS, CFT_SIX);
    moveCard(100,600, ca);*/
    return true;
}

