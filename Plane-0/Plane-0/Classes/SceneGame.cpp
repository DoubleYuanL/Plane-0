#include "SceneGame.h"
#include "LayerScrollBackground.h"
#include "SceneMenu.h"
#include "Plane.h"
#include "SceneScore.h"
int SceneGame::_planeID = 0;

SceneGame::SceneGame()
{
}


SceneGame::~SceneGame()
{
}

bool SceneGame::init()
{
	CCLayer::init();

	// ��������
	LayerScrollBackground* layer = LayerScrollBackground::create();
	addChild(layer);

	// ��һ�����ذ�ť
	Util::createMenuItemRB(this, IMAGE_MENU_BACK_NORMAL,
		IMAGE_MENU_BACK_SELECT, this, menu_selector(SceneGame::Back));

	// ҵ�����
	addHeroPlane();

	_ai = AI::create();
	addChild(_ai);

	// ������HP��ʾ
	addLabel();

	// ��ײ���
	scheduleUpdate();

	return true;
}

void SceneGame::addLabel()
{
	int off = 10;

	this->_labelHP = CCLabelTTF::create(Util::format(_plane->getHP()), "Arial", 50);
	this->_labelScore = CCLabelTTF::create("0", "Arial", 50);
	addChild(this->_labelScore);
	addChild(this->_labelHP);

	_labelHP->setAnchorPoint(ccp(1, 1));
	_labelHP->setPosition(ccp(winSize.width-off, winSize.height-off));

	_labelScore->setAnchorPoint(ccp(0, 1));
	_labelScore->setPosition(ccp(0+off, winSize.height-off));

	_labelHP->setZOrder(100);
	_labelScore->setZOrder(100);
}

void SceneGame::killEnemy(Enemy* e)
{
	_ai->_enemys->removeObject(e);

	CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_BOOM);
	CCAnimate* animate = CCAnimate::create(animation);
	CCCallFunc* call = CCCallFunc::create(e, callfunc_selector(CCSprite::removeFromParent));
	e->runAction(CCSequence::create(animate, call, NULL));
}

void SceneGame::update(float)
{
	// ��ײ���
	int eCount = _ai->_enemys->count();
	for (int i = eCount - 1; i >= 0; --i)
	{
		Enemy* e = (Enemy*)_ai->_enemys->objectAtIndex(i);

		// �л����ҷ��ɻ���ײ
		if (e->boundingBox().intersectsRect(_plane->boundingBox()))
		{
			Util::changeValue(this->_labelScore, e->_score);
			Util::changeValue(this->_labelHP, -e->_hp);

			killEnemy(e);

			_plane->setHP(_plane->getHP() - e->_hp);
			if (_plane->getHP() <= 0)
			{
				SceneScore::_score = atoi(this->_labelScore->getString());
				Util::replaceLayer(SceneScore::create());
			}
			continue; // �õл��Ѿ�over������Ҫ�ټ����жϺ��ӵ��ĳ�ͻ
		}
		
		int bCount = _plane->_bullets->count();
		for (int j = bCount - 1; j >= 0; --j)
		{
			CCSprite* bullet = (CCSprite*)_plane->_bullets->objectAtIndex(j);
			if (bullet->boundingBox().intersectsRect(e->boundingBox()))
			{
				bullet->removeFromParent();
				_plane->_bullets->removeObject(bullet);

				e->_hp -= _plane->getDamage();
				if (e->_hp <= 0)
				{
					Util::changeValue(this->_labelScore, e->_score);

					killEnemy(e);
					break;
				}

			}
		}
	}
}

void SceneGame::addHeroPlane()
{
	_plane = Plane::create();
	addChild(_plane);
	_plane->setPosition(ccp(winSize.width / 2, _plane->getContentSize().height));
	_plane->setZOrder(100);

	enableTouch();
}

void SceneGame::Back(CCObject*)
{
	Util::replaceLayer(SceneMenu::create());
}

bool SceneGame::ccTouchBegan(CCTouch* t, CCEvent* e)
{
	if (_plane->boundingBox().containsPoint(t->getLocation()))
		return true;
	return false;
}

void SceneGame::ccTouchMoved(CCTouch* t, CCEvent* e)
{
	CCPoint pt = _plane->getPosition();

	float minx = pt.x + t->getDelta().x - _plane->boundingBox().size.width / 2;
	if (minx < 0)
		return;
	float maxx = pt.x + t->getDelta().x + _plane->boundingBox().size.width / 2;
	if (maxx > winSize.width)
		return;
	float miny = pt.y + t->getDelta().y - _plane->boundingBox().size.height / 2;
	if (miny < 0)
		return;
	float maxy = pt.y + t->getDelta().y + _plane->boundingBox().size.height / 2;
	if (maxy > winSize.height)
		return;

	Util::moveNode(_plane, t->getDelta());
}