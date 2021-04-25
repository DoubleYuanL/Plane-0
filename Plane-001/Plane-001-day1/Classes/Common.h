#ifndef __COMMON_H__
#define __COMMON_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <iostream>
#include <string>

using namespace std;
#include "external/tinyxml2/tinyxml2.h"

USING_NS_CC;
USING_NS_CC_EXT;

constexpr auto IMAGE_BACKGROUND = "Background/background.png";

constexpr auto IMAGE_MENU_START_NORMAL = "Button/btn1_normal.png";
constexpr auto IMAGE_MENU_START_SELECT = "Button/btn1_push.png";
constexpr auto IMAGE_MENU_ABOUT_NORMAL = "Button/btn2_normal.png";
constexpr auto IMAGE_MENU_ABOUT_SELECT = "Button/btn2_push.png";
constexpr auto IMAGE_MENU_QUIT_NORMAL = "Button/btn3_normal.png";
constexpr auto IMAGE_MENU_QUIT_SELECT = "Button/btn3_push.png";
constexpr auto IMAGE_MENU_BACK_NORMAL = "Button/btn_back_normal.png";
constexpr auto IMAGE_MENU_BACK_SELECT = "Button/btn_back_press.png";

constexpr auto XML_ABOUT = "About/about.xml";
constexpr auto PLIST_ABOUT = "About/about.plist";
constexpr auto JSON_ABOUT = "About/about.json";

constexpr auto FONTS_FILE = "fonts/Marker Felt.ttf";
constexpr auto FONTS_NUM_FILE = "fonts/num.jpg";

constexpr auto ANI_BOOM = "Plane/PFBoom.plist";
#endif