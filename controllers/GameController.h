#ifndef _APP_DELEGATE_H_  // 防止头文件重复包含
#define _APP_DELEGATE_H_

#include "cocos2d.h"          // Cocos2d-x引擎核心头文件
#include "./models/GameModel.h" // 游戏数据模型头文件
USING_NS_CC;                  // 使用Cocos2d-x命名空间

/**
 * @brief Cocos2d-x应用委托类（游戏主控制器）
 *
 * 私有继承Application，隐藏部分Director接口
 * 职责：
 * 1. 管理游戏生命周期
 * 2. 处理全局触摸事件
 * 3. 协调模型与视图交互
 */
class GameController : private cocos2d::Application
{
private:
    // 触摸事件监听器
    EventListenerTouchOneByOne* _listenerHand;  // 手牌区域监听
    EventListenerTouchOneByOne* _listenerDesk1; // 桌面1区监听
    EventListenerTouchOneByOne* _listenerDesk2; // 桌面2区监听

    // Cocos2d-x核心组件
    Director* _director;  // 导演实例
    Scene* _scene;        // 主场景
    CardView* _layer;     // 卡牌视图层

    // 游戏数据模型
    GameInformation _gameInfo;  // 核心游戏状态

    // 当前卡牌状态缓存
    Sprite* _deskTop1;      // 桌面1顶部卡牌精灵
    Sprite* _deskTop2;      // 桌面2顶部卡牌精灵
    Sprite* _beforeHandTop; // 前一张手牌精灵
    int _deskTop1Face;      // 桌面1顶部牌面值
    int _deskTop2Face;      // 桌面2顶部牌面值
    int _beforeHandFace;    // 前一张手牌面值
    int _handFace;          // 当前手牌面值

public:
    // 生命周期管理
    GameController();  // 构造函数
    virtual ~GameController();  // 析构函数

    // 游戏数据初始化
    void getData();  // 从配置文件加载初始数据

    // 视图更新
    void refresh();  // 刷新游戏状态到视图

    // 事件监听设置
    void eventDetectHand();  // 手牌触摸检测
    void eventDetectDesk1(); // 桌面1区触摸检测
    void eventDetectDesk2(); // 桌面2区触摸检测

    // 继承自Application的接口
    virtual void initGLContextAttrs();  // 初始化OpenGL上下文属性
    virtual bool applicationDidFinishLaunching();  // 应用启动完成回调
    virtual void applicationDidEnterBackground();  // 应用进入后台回调
    virtual void applicationWillEnterForeground(); // 应用返回前台回调
};

#endif // _APP_DELEGATE_H_