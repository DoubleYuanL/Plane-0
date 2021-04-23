#ifndef __Plane_H__
#define __Plane_H__

#include "Common.h"

class Plane : public CCSprite
{
public:
	Plane();
	~Plane();

	CREATE_FUNC(Plane);
	bool init();

	CC_PROPERTY(int, _type, Type);
	CC_SYNTHESIZE(int, _hp, HP);

	CC_SYNTHESIZE(int, _damage, Damage);
	CC_SYNTHESIZE(int, _cd, CD);  // Éä»÷¼ä¸ô
	CC_SYNTHESIZE(int, _curCD, CurCD); //

	void update(float);

	void fire();
	void fire(CCSprite* bullet, const CCPoint& start, const CCPoint& end);
	void fireUp(const CCPoint& startOffset = ccp(0, 0));
	void fireDown(const CCPoint& startOffset = ccp(0, 0));
	void fireLeft(const CCPoint& startOffset = ccp(0, 0));
	void fireRight(const CCPoint& startOffset = ccp(0, 0));
	void fireUp30L();
	void fireUp30R();
	void fireLT();
	void fireLB();
	void fireRT();
	void fireRB();

	CCArray* _bullets;
	void takeBackBullet();
};

#endif

