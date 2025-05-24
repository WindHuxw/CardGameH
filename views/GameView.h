#pragma once  // 防止头文件重复包含

#include "cocos2d.h"  // Cocos2d-x引擎核心头文件
#include <string>    // 字符串处理
#include <vector>    // 向量容器
#include "CardView.h" // 卡牌视图头文件

/**
 * 游戏主场景类（继承自Cocos2d-x的Scene）
 *
 * 职责：
 * 1. 作为游戏根容器管理所有视图层
 * 2. 初始化卡牌操作层（CardView）
 * 3. 提供场景创建快捷方式
 */
class GameView : public cocos2d::Scene {

private:
    CardView* _cardLayer;  // 卡牌操作层指针（核心游戏视图）

public:
    /**
     * 静态场景创建方法（Cocos2d-x标准模式）
     * @return 创建好的场景对象指针（已自动释放）
     */
    static cocos2d::Scene* createScene();

    /**
     * 重写Scene初始化方法
     * @return 是否初始化成功
     */
    virtual bool init() override;

    // Cocos2d-x宏，自动生成create()方法
    CREATE_FUNC(GameView);
};