#include "SceneMenu.h"
#include "SceneStart.h"
#include "SceneGame.h"
#include "LayerScrollBackground.h"
#include "cocos/ui/UIScrollView.h"

bool SceneMenu::init()
{
    Layer::init();

	_scrollBackground = LayerScrollBackground::create();
	this->addChild(_scrollBackground);

	addScrollMenu();

    return true;
}

void SceneMenu::Back(Ref* pSender)
{
    Util::replaceLayer(SceneStart::create());
}

void SceneMenu::addScrollMenu()
{
	string str = "Select Plane";
	Util::setLabelTTF(this, str, winSize.width / 2.f - str.size() / 2.f, winSize.height - 100.f,
		48, Color4B::RED, Point::ANCHOR_MIDDLE_TOP);

    Menu* menu = Menu::create();
	for (int i = 0; i < 5; ++i)
	{
		Sprite* sprite = Sprite::create(Util::format(i + 1, "Plane/Player", ".png"));
		MenuItemSprite* item = MenuItemSprite::create(sprite, sprite, CC_CALLBACK_1(SceneMenu::selectPlane, this));
		item->setTag(i);
		item->setPosition(winSize.width * i + winSize.width / 2, winSize.height / 2);
		menu->addChild(item);
	}

	extension::ScrollView* view = extension::ScrollView::create(winSize, menu);
	view->setContentSize(Size(winSize.width * 5, winSize.height));
	view->setDirection(extension::ScrollView::Direction::HORIZONTAL);
	this->addChild(view);

	ccMenuCallback buttonFun = std::bind(&SceneMenu::Back, this, std::placeholders::_1);
	Util::createButton(this, buttonFun,
		IMAGE_MENU_BACK_NORMAL, IMAGE_MENU_BACK_SELECT,
		winSize.width / 2 - itemSize.width / 12, itemSize.height / 12 - winSize.height / 2);
}

void SceneMenu::selectPlane(Ref* pSender)
{
	Node* menuItem = (Node*)pSender;
	Util::replaceLayer(SceneGame::create(menuItem->getTag()));
}


