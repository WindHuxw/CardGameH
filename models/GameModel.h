#ifndef GAMEMODEL_H  // 防止头文件重复包含
#define GAMEMODEL_H

#include "CardModel.h"    // 卡牌数据模型头文件
#include <vector>        // 标准向量容器
#include <utility>       // 包含 std::pair 工具类
#include "UndoModel.h"   // 撤销功能模型头文件

// 前向声明（避免循环依赖）
class UndoModel;

// 游戏核心数据模型类
class GameInformation
{
private:
    bool win = false;          // 游戏胜利标志（默认false）
    HandCard _handCard;        // 手牌管理模块
    DesktopCard _desktopCard;  // 桌面牌堆管理模块
    UndoModel _undoModel;      // 撤销功能模块

public:
    /* 基础卡牌操作接口 */
    bool handPush(CardInformation c);  // 向手牌堆压入一张牌
    bool handPop();                   // 从手牌堆弹出一张牌
    bool deskPush1(CardInformation c); // 向桌面牌堆1压入卡牌
    bool deskPop1();                   // 从桌面牌堆1弹出卡牌
    bool deskPush2(CardInformation c); // 向桌面牌堆2压入卡牌
    bool deskPop2();                   // 从桌面牌堆2弹出卡牌

    /* 特殊游戏逻辑 */
    bool replacementHand();           // 常规手牌替换逻辑
    bool replacementHandByDesk1();     // 使用牌堆1替换手牌
    bool replacementHandByDesk2();     // 使用牌堆2替换手牌

    /* 撤销功能 */
    bool undoSave(ActionData a);      // 保存操作记录到撤销栈
    ActionData undoGame();             // 执行撤销操作并返回动作数据

    /* 状态查询接口 */
    CardInformation handTop();        // 获取当前手牌顶部卡牌
    CardInformation beforeHandTop();  // 获取前一张手牌（用于动画效果）
    CardInformation deskTop1();       // 获取牌堆1顶部卡牌
    CardInformation deskTop2();       // 获取牌堆2顶部卡牌
    bool judgeWin();                  // 执行胜利条件判断（更新win标志）
    bool isWin();                     // 获取当前胜利状态（只读）

};
#endif // GAMEMODEL_H