#include "SceneStart.h"
#include "SceneAbout.h"
#include "SceneMenu.h"

SceneStart::SceneStart()
{
}


SceneStart::~SceneStart()
{
}

bool SceneStart::init()
{
	CCLayer::init();

	Util::addSprite(this, IMAGE_BACKGROUND);

	// 增加三个按钮
	CCMenu* menu = CCMenu::create();
	addChild(menu);

	CCMenuItem* itemStart = CCMenuItemImage::create(IMAGE_MENU_START_NORMAL,
		IMAGE_MENU_START_SELECT, this, menu_selector(SceneStart::Start));
	CCMenuItem* itemAbout = CCMenuItemImage::create(IMAGE_MENU_ABOUT_NORMAL,
		IMAGE_MENU_ABOUT_SELECT, this, menu_selector(SceneStart::About));
	CCMenuItem* itemQuit  = CCMenuItemImage::create(IMAGE_MENU_QUIT_NORMAL,
		IMAGE_MENU_QUIT_SELECT,  this, menu_selector(SceneStart::Quit));

	menu->addChild(itemStart);
	menu->addChild(itemAbout);
	menu->addChild(itemQuit);
	menu->alignItemsVertically();

	return true;
}

void SceneStart::About(CCObject*)
{
	Util::replaceLayer(SceneAbout::create());
}

void SceneStart::Quit(CCObject*)
{
	CCDirector::sharedDirector()->end();
	exit(0);
}

void SceneStart::Start(CCObject*)
{
	Util::replaceLayer(SceneMenu::create());
}

