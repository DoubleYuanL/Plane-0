#include "Plane.h"
#include "SceneGame.h"

Plane::Plane()
{
	_bullets = CCArray::create();
	_bullets->retain();
}


Plane::~Plane()
{
	_bullets->release();
}

bool Plane::init()
{
	CCSprite::init();

	setType(SceneGame::_planeID); // _planeID

	scheduleUpdate();

	return true;
}

void Plane::update(float)
{
	_curCD++;
	if (_curCD == _cd)
	{
		fire();
		_curCD = 0;
	}

	takeBackBullet();
}

void Plane::takeBackBullet()
{
	CCSprite* bullet;
	int count = _bullets->count();
	for (int i = count - 1; i >= 0; i--)
	{
		bullet = (CCSprite*)_bullets->objectAtIndex(i);
		if (Util::isOutOfWindow(bullet))
		{
			bullet->removeFromParent();
			_bullets->removeObject(bullet);
		}
	}
}

void Plane::fire(CCSprite* bullet, const CCPoint& start, const CCPoint& end)
{
	_bullets->addObject(bullet);
	bullet->setZOrder(this->getZOrder() - 1);
	getParent()->addChild(bullet);
	bullet->setPosition(start);
	bullet->runAction(CCMoveTo::create(10, end));
}

void Plane::fireUp(const CCPoint& startOffset)
{
	CCPoint start;
	CCPoint end;
	CCSprite* bullet;

	bullet = CCSprite::create("Bullet.png");
	start = this->getPosition() + ccp(-bullet->boundingBox().size.width / 2,
		this->boundingBox().size.height / 2) + startOffset;
	end = start + ccp(0, winSize.height);

	fire(bullet, start, end);
}

void Plane::fireDown(const CCPoint& startOffset)
{
	CCPoint start;
	CCPoint end;
	CCSprite* bullet;

	bullet = CCSprite::create("Bullet.png");
	start = this->getPosition() + ccp(-bullet->boundingBox().size.width / 2,
		-this->boundingBox().size.height / 2) + startOffset;
	end = start + ccp(0, -winSize.height);

	fire(bullet, start, end);
}

void Plane::fireLeft(const CCPoint& startOffset)
{
	CCPoint start;
	CCPoint end;
	CCSprite* bullet;

	bullet = CCSprite::create("Bullet.png");
	start = this->getPosition() + ccp(-this->boundingBox().size.width/2, 0) + startOffset;
	end = start + ccp(-winSize.height, 0);
	bullet->setRotation(90);

	fire(bullet, start, end);
}

void Plane::fireRight(const CCPoint& startOffset)
{
	CCPoint start;
	CCPoint end;
	CCSprite* bullet;

	bullet = CCSprite::create("Bullet.png");
	start = this->getPosition() + ccp(this->boundingBox().size.width / 2, 0) + startOffset;
	end = start + ccp(winSize.height, 0);
	bullet->setRotation(90);

	fire(bullet, start, end);
}

void Plane::fireUp30L()
{
	CCPoint start;
	CCPoint end;
	CCSprite* bullet;
	bullet = CCSprite::create("Bullet.png");
	start = this->getPosition() + ccp(-60, 30);
	end = start + ccp(-winSize.height / 2, winSize.height / 2 * sqrt(3.0));
	bullet->setRotation(-30);

	fire(bullet, start, end);
}
void Plane::fireUp30R()
{
	CCPoint start;
	CCPoint end;
	CCSprite* bullet;
	bullet = CCSprite::create("Bullet.png");
	start = this->getPosition() + ccp(60, 30);
	end = start + ccp(winSize.height / 2, winSize.height / 2 * sqrt(3.0));
	bullet->setRotation(30);

	fire(bullet, start, end);
}

void Plane::fireLT()
{
	float off = winSize.height / sqrt(2.0);
	CCPoint start;
	CCPoint end;
	CCSprite* bullet;
	bullet = CCSprite::create("Bullet.png");
	

	start = this->getPosition();
	end = start + ccp(-off, off);
	bullet->setRotation(-45);

	fire(bullet, start, end);
}

void Plane::fireLB()
{
	float off = winSize.height / sqrt(2.0);
	CCPoint start;
	CCPoint end;
	CCSprite* bullet;
	bullet = CCSprite::create("Bullet.png");

	start = this->getPosition();
	end = start + ccp(-off, -off);
	bullet->setRotation(-135);

	fire(bullet, start, end);
}

void Plane::fireRB()
{
	float off = winSize.height / sqrt(2.0);
	CCPoint start;
	CCPoint end;
	CCSprite* bullet;
	bullet = CCSprite::create("Bullet.png");


	start = this->getPosition();
	end = start + ccp(off, -off);
	bullet->setRotation(135);

	fire(bullet, start, end);
}

void Plane::fireRT()
{
	float off = winSize.height / sqrt(2.0);
	CCPoint start;
	CCPoint end;
	CCSprite* bullet;
	bullet = CCSprite::create("Bullet.png");

	start = this->getPosition();
	end = start + ccp(off, off);
	bullet->setRotation(45);

	fire(bullet, start, end);
}

void Plane::fire()
{
	switch (_type)
	{
	case 0:
		fireUp();
		break;
	case 1:
		fireUp();
		fireUp(ccp(-this->boundingBox().size.width / 4, -60));
		fireUp(ccp(+this->boundingBox().size.width / 4, -60));
		break;
	case 2:
		fireUp();
		fireUp30L();
		fireUp30R();
		break;
	case 3:
		fireUp();
		fireDown();
		fireLeft();
		fireRight();
		break;
	case 4:
		fireLT();
		fireLB();
		fireRT();
		fireRB();
		break;
	}
}

void Plane::setType(int type)
{
	_type = type;
	
	CCDictionary* dict = CCDictionary::createWithContentsOfFile("planeinfo.xml");

	const CCString* value = dict->valueForKey(Util::format(type+1, "planedamageamount"));//伤害值
	setDamage(value->intValue());

	value = dict->valueForKey(Util::format(type+1, "planeshootspeedrate"));//设计频率
	setCD(value->intValue());

	_curCD = 0;

	value = dict->valueForKey(Util::format(type + 1, "plane", "_hp"));// 血量
	setHP(value->intValue());

	value = dict->valueForKey(Util::format(type + 1, "plane"));//飞机图片
	Util::setTexture(this, value->getCString());
}

int Plane::getType()
{
	return _type;
}
