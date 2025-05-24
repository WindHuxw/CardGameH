#pragma once
#include "./models/CardModel.h"
#include "cocos2d.h"
#include "json/document.h"
#include <vector>
#include <string>


std::vector<std::vector<CardInformation>> readJSONFile();
