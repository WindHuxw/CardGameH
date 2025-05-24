// CardView.h
#ifndef CARDVIEW_H
#define CARDVIEW_H

#include "cocos2d.h"  // Cocos2d-x引擎核心头文件
#include "./configs/models/CardResConfig.h"  // 卡牌资源配置文件
#include "ui/CocosGUI.h"  // Cocos2d-x UI组件

USING_NS_CC;  // 使用Cocos2d-x命名空间

// 卡牌花色枚举类型（扑克牌四种花色）
enum CardSuitType
{
    CST_NONE = -1,       // 无效花色
    CST_CLUBS,          // 梅花（三叶草）
    CST_DIAMONDS,       // 方块（钻石）
    CST_HEARTS,         // 红桃（心形）
    CST_SPADES,         // 黑桃（剑形）
    CST_NUM_CARD_SUIT_TYPES  // 花色类型总数（用于边界检查）
};

// 卡牌面值枚举类型（A-K）
enum CardFaceType
{
    CFT_NONE = -1,      // 无效面值
    CFT_ACE,            // A
    CFT_TWO,            // 2
    CFT_THREE,          // 3
    CFT_FOUR,           // 4
    CFT_FIVE,           // 5
    CFT_SIX,            // 6
    CFT_SEVEN,          // 7
    CFT_EIGHT,          // 8
    CFT_NINE,           // 9
    CFT_TEN,            // 10
    CFT_JACK,           // J
    CFT_QUEEN,          // Q
    CFT_KING,           // K
    CFT_NUM_CARD_FACE_TYPES  // 面值类型总数（用于边界检查）
};

// 卡牌视图类（继承自Cocos2d-x的Layer）
class CardView : public cocos2d::Layer {
public:
    ui::Button* _backButton;  // 返回按钮指针（用于界面导航）

public:
    // Cocos2d-x宏定义，自动生成create()函数
    CREATE_FUNC(CardView);

    // 初始化返回按钮
    void setButton();

    /**
     * 创建并添加卡牌精灵到场景
     * @param x 横坐标位置
     * @param y 纵坐标位置
     * @param cst 卡牌花色（CardSuitType枚举）
     * @param cft 卡牌面值（CardFaceType枚举）
     * @return 创建的精灵指针
     */
    Sprite* addCard(float x, float y, CardSuitType cst, CardFaceType cft);

    /**
     * 移动卡牌动画
     * @param x 目标位置x坐标
     * @param y 目标位置y坐标
     * @param card 要移动的卡牌精灵指针
     * @return 是否移动成功
     */
    bool moveCard(float x, float y, Sprite* card);

    /**
     * 删除卡牌（带动画效果）
     * @param card 要删除的卡牌精灵
     * @param targetX 动画终点x坐标
     * @param targetY 动画终点y坐标
     * @return 是否删除成功
     */
    bool deleteCard(Sprite* card, float targetX, float targetY);

    // 重写Layer的初始化方法
    virtual bool init() override;
};

#endif // CARDVIEW_H