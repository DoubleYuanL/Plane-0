#include "SceneStart.h"
#include "SceneAbout.h"
#include "SceneMenu.h"

bool SceneStart::init()
{
	Layer::init();

	auto _back = Util::addSpriteBackGround(this, IMAGE_BACKGROUND);

	Menu* menu = Menu::create();
	addChild(menu);

	MenuItem* itemStart = MenuItemImage::create(IMAGE_MENU_START_NORMAL,
		IMAGE_MENU_START_SELECT);
	itemStart->setCallback(CC_CALLBACK_0(SceneStart::Start, this));
	MenuItem* itemAbout = MenuItemImage::create(IMAGE_MENU_ABOUT_NORMAL,
		IMAGE_MENU_ABOUT_SELECT, CC_CALLBACK_0(SceneStart::About, this));
	MenuItem* itemQuit = MenuItemImage::create(IMAGE_MENU_QUIT_NORMAL,
		IMAGE_MENU_QUIT_SELECT, CC_CALLBACK_0(SceneStart::Quit, this));

	menu->addChild(itemStart);
	menu->addChild(itemAbout);
	menu->addChild(itemQuit);
	menu->alignItemsVertically();

	return true;
}

void SceneStart::Start()
{
	Util::replaceLayer(SceneMenu::create());
}
void SceneStart::About()
{
	Util::replaceLayer(SceneAbout::create());
}
void SceneStart::Quit()
{
	Director::getInstance()->end();
	exit(0);
}
