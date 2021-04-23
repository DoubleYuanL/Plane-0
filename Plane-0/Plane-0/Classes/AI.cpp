#include "AI.h"


AI::AI()
{
	this->_enemys = CCArray::create();
	this->_enemys->retain();
}


AI::~AI()
{
	this->_enemys->release();
}

bool AI::init()
{
	CCNode::init();

	schedule(schedule_selector(AI::GenSmall), 1);
	schedule(schedule_selector(AI::GenMiddle), 5);
	schedule(schedule_selector(AI::GenBig), 30);

	scheduleUpdate();

	return true;
}

void AI::update(float dt)
{
	// �жϵл��Ƿ��Ѿ��ɳ�����
	int count = _enemys->count();
	for (int i = count - 1; i >= 0; i--)
	{
		Enemy* e = (Enemy*)_enemys->objectAtIndex(i);
		CCRect rc = e->boundingBox();
		if (rc.getMaxY() < 0)
		{
			e->removeFromParent();
			_enemys->removeObject(e);
		}
	}
}

void AI::GenSmall(float)
{
	GenEnemy(Enemy::T_SMALL);
}
void AI::GenMiddle(float)
{
	GenEnemy(Enemy::T_MID);
}
void AI::GenBig(float)
{
	GenEnemy(Enemy::T_BIG);
}

void AI::GenEnemy(Enemy::TYPE t)
{
	Enemy* e = Enemy::create(t);
	e->setAnchorPoint(ccp(0, 0));
	getParent()->addChild(e);
	_enemys->addObject(e);

//	setPosition(...);
	float x = CCRANDOM_0_1() * (winSize.width - e->boundingBox().size.width);
	float y = winSize.height;
	e->setPosition(ccp(x, y));

}
