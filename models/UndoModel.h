#pragma once  // 确保头文件只被编译一次
#include <stack>      // 使用STL栈容器
#include <functional> // 函数对象支持
#include "./views/CardView.h"  // 卡牌视图定义
#include <models/CardModel.h>  // 卡牌数据模型

/*
 还没完成回滚功能！！！！！！！！！！！！！
*/


// 动作数据结构体（记录游戏操作）
typedef struct ActionData
{
    bool _isPush = 0;  // 标记是否为压栈操作（1=压入，0=弹出）
    bool _isMove = 0;   // 标记是否为移动操作
    int _x;            // 操作发生时卡牌的x坐标
    int _y;            // 操作发生时卡牌的y坐标
    int area;          // 操作区域标识（0=手牌区，1=桌面1区，2=桌面2区）
    CardInformation _card; // 关联的卡牌完整数据
};

// 撤销功能模型类（基于命令模式实现）
class UndoModel {
private:
    std::stack<ActionData> _undoStack;  // 使用栈结构存储操作记录（LIFO）

public:
    // 压入操作记录到撤销栈
    bool stackPush(ActionData a);

    // 从撤销栈弹出顶部操作（不返回数据）
    bool stackPop();

    // 检查撤销栈是否为空
    bool isEmpty();

    // 执行撤销操作并返回动作数据（会弹出栈顶元素）
    ActionData undo();
};