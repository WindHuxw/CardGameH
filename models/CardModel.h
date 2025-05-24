#pragma once  // 确保头文件只被编译一次
#include "./views/CardView.h"  // 引入卡牌视图定义
#include <vector>  // 使用STL向量容器
#include <utility> // 包含std::pair工具类
#include "cocos2d.h"  // 引入Cocos2d-x引擎核心头文件

// 卡牌信息结构体定义
typedef struct CardInformation
{
    CardSuitType _CSTtype;  // 卡牌花色类型（枚举值）
    CardFaceType _CFTtype;  // 卡牌数字/面值类型（枚举值）
    Sprite* _pointer;       // 指向Cocos2d-x精灵对象的指针
    float _x;               // 卡牌x坐标
    float _y;               // 卡牌y坐标

}CardInformation;

// 手牌管理类
class HandCard
{
private:
    std::vector<CardInformation> _handCardPairs;  // 使用向量存储手牌数据
public:
    bool handCardPush(CardInformation c);  // 向手牌堆压入一张牌
    bool handCardPop();                    // 从手牌堆弹出一张牌
    CardInformation handTop();             // 获取顶部手牌（当前牌）
    CardInformation beforeHandTop();       // 获取前一张手牌
    int handSize();                        // 获取手牌数量
};

// 桌面牌堆管理类
class DesktopCard
{
private:
    std::vector<CardInformation> _deskCardPairs1;  // 桌面牌堆1存储
    std::vector<CardInformation> _deskCardPairs2;  // 桌面牌堆2存储
public:
    bool deskCardCardPush1(CardInformation c);  // 向牌堆1压入卡牌
    bool deskCardCardPop1();                    // 从牌堆1弹出卡牌
    bool deskCardCardPush2(CardInformation c);  // 向牌堆2压入卡牌
    bool deskCardCardPop2();                    // 从牌堆2弹出卡牌
    CardInformation deskTop1();                 // 获取牌堆1顶部卡牌
    CardInformation deskTop2();                 // 获取牌堆2顶部卡牌
    int deskSize1();                            // 获取牌堆1卡牌数量
    int deskSize2();                            // 获取牌堆2卡牌数量
};