#include "json/document.h"  // Cocos2d-x内置的rapidjson封装（DOM解析核心）
#include "json/stringbuffer.h" // JSON字符串缓冲区处理
#include "json/writer.h"      // JSON写入器
#include <string>
#include "cocos2d.h"
#include <vector>
#include "./models/CardModel.h" // 自定义卡牌数据模型
#include "json/document.h"     // 二次包含确保编译（非必要）
USING_NS_CC;

/**
 * 从JSON文件读取卡牌数据
 * @return 二维向量：[0]=Playfield卡牌数据，[1]=Stack卡牌数据
 */
std::vector<std::vector<CardInformation>> readJSONFile() {
    // 1. 读取文件内容（使用Cocos2d-x文件工具）
    std::string jsonStr = FileUtils::getInstance()->getStringFromFile("data.json");

    // 2. 初始化返回结构：二维向量容器
    std::vector<std::vector<CardInformation>> res(2);

    // 3. 解析JSON（使用rapidjson DOM模式）
    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str()); // 将字符串解析为DOM树

    // 建议添加的解析错误检查（当前被注释）
    // if (doc.HasParseError()) {
    //     CCLOG("JSON解析错误: %s", doc.GetParseError());
    //     return res;
    // }

    // 4. 临时存储卡牌数据的结构体
    CardInformation tmp;

    // 5. 提取Playfield数组数据 -------------------------
    const rapidjson::Value& playfield = doc["Playfield"]; // 获取Playfield数组引用
    for (rapidjson::SizeType i = 0; i < playfield.Size(); i++) {
        // 5.1 解析卡牌面值（枚举转换）
        tmp._CFTtype = (CardFaceType)(playfield[i]["CardFace"].GetInt());

        // 5.2 解析卡牌花色（枚举转换）
        tmp._CSTtype = (CardSuitType)(playfield[i]["CardSuit"].GetInt());

        // 5.3 解析坐标位置（嵌套对象访问）
        tmp._x = playfield[i]["Position"]["x"].GetFloat();
        tmp._y = playfield[i]["Position"]["y"].GetFloat();

        // 存入结果集第一维
        res[0].push_back(tmp);
    }

    // 6. 提取Stack数组数据 ----------------------------
    const rapidjson::Value& stackfield = doc["Stack"]; // 获取Stack数组引用
    for (rapidjson::SizeType i = 0; i < stackfield.Size(); i++) {
        // 6.1-6.3 同Playfield解析逻辑
        tmp._CFTtype = (CardFaceType)(stackfield[i]["CardFace"].GetInt());
        tmp._CSTtype = (CardSuitType)(stackfield[i]["CardSuit"].GetInt());
        tmp._x = stackfield[i]["Position"]["x"].GetFloat();
        tmp._y = stackfield[i]["Position"]["y"].GetFloat();

        // 存入结果集第二维
        res[1].push_back(tmp);
    }

    return res; // 返回二维数据
}