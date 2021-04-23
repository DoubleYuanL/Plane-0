
#ifndef __AI_H__
#define __AI_H__

#include "Common.h"

class Enemy : public CCSprite
{
public:
	enum TYPE {T_SMALL, T_MID, T_BIG};
	static Enemy* create(TYPE type)
	{
		Enemy* e = new Enemy;
		e->init(type);
		e->autorelease();
		return e;
	}

	bool init(TYPE type)
	{
		CCSprite::init();

		char* pngfile = Util::format(type + 1, "Enemy", ".png");
		Util::setTexture(this, pngfile);
		
		float speed[3] = {150, 100, 50};
		_speed = speed[type];

		int hp[3] = { 10, 50, 300 };
		_hp = hp[type];

		int score[3] = { 1000, 5000, 20000 };
		_score = score[type];

		scheduleUpdate();

		return true;
	}

	void update(float dt)
	{
		Util::moveNode(this, ccp(0, -dt* _speed));
	}

	float _speed;
	int _hp;
	int _score;
};

// �����л�
// �����л�
class AI : public CCNode
{
public:
	AI();
	~AI();
	CREATE_FUNC(AI);
	bool init();

	CCArray* _enemys;

	void GenSmall(float);
	void GenMiddle(float);
	void GenBig(float);
	void GenEnemy(Enemy::TYPE t);

	void update(float dt);
};

#endif

