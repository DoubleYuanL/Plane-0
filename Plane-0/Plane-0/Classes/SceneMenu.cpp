#include "SceneMenu.h"
#include "SceneStart.h"
#include "SceneGame.h"
#include "LayerScrollBackground.h"

SceneMenu::SceneMenu()
{
}


SceneMenu::~SceneMenu()
{
}


bool SceneMenu::init()
{
	CCLayer::init();

	// ��������
	LayerScrollBackground* layer = LayerScrollBackground::create();
	addChild(layer);

	// ��һ�����ذ�ť
	Util::createMenuItemRB(this, IMAGE_MENU_BACK_NORMAL, 
		IMAGE_MENU_BACK_SELECT, this, menu_selector(SceneMenu::Back));

	// CCScrollView
	addScrollMenu();

	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
	setTouchPriority(-127);

	return true;
}

void SceneMenu::Back(CCObject*)
{
	Util::replaceLayer(SceneStart::create());
}

void SceneMenu::addScrollMenu()
{
	CCMenu* node = CCMenu::create();
	// init node...
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("chooselevel.plist");
	for (int i = 0; i < 5; ++i)
	{
		char* name = Util::format(i + 1, "ChooseLevel", ".png");
		CCSprite* sprite = CCSprite::createWithSpriteFrameName(name);
		CCSprite* sprite1 = CCSprite::createWithSpriteFrameName(name);

		CCMenuItem* item = CCMenuItemSprite::create(sprite, sprite1, 
			this, menu_selector(SceneMenu::SelectPlane));
		item->setTag(i+1000);
		item->setPosition(ccp(winSize.width*i+winSize.width/2, winSize.height/2));
		node->addChild(item);
	}

	CCScrollView* view = CCScrollView::create(winSize, node);
	view->setContentSize(CCSize(winSize.width * 5, winSize.height));
	view->setDirection(k CC Scroll View Direction Horizontal);

	addChild(view);

	_view = view;
	_menu = node;
	_menu->setTouchPriority(-120);
}
void SceneMenu::SelectPlane(CCObject* sender)
{
	if (_isTouch)
	{
		CCNode* menuItem = (CCNode*)sender;
		SceneGame::_planeID = menuItem->getTag() - 1000;
		Util::replaceLayer(SceneGame::create());
	}
}

bool SceneMenu::ccTouchBegan(CCTouch*t, CCEvent*v)
{
	_viewTouch = _view->ccTouchBegan(t, v);
	_menuTouch = _menu->ccTouchBegan(t, v);
	return true;
}
void SceneMenu::ccTouchEnded(CCTouch*t, CCEvent*v)
{
	//���touch�ǻ����� ����_isTouch=false
	CCPoint ptEnd = t->getLocation();
	CCPoint ptStart = t->getStartLocation();
	_isTouch = ptEnd.getDistanceSq(ptStart) < 25;

	if (_viewTouch) _view->ccTouchEnded(t, v);
	if (_menuTouch) _menu->ccTouchEnded(t, v);
}
void SceneMenu::ccTouchMoved(CCTouch*t, CCEvent*v)
{
	if (_viewTouch) _view->ccTouchMoved(t, v);
	if (_menuTouch) _menu->ccTouchMoved(t, v);
}
void SceneMenu::ccTouchCancelled(CCTouch*t, CCEvent*v)
{
	if (_viewTouch) _view->ccTouchCancelled(t, v);
	if (_menuTouch) _menu->ccTouchCancelled(t, v);
}