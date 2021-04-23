#ifndef __SceneGame_H__
#define __SceenGame_H__

#include "Common.h"
#include "Plane.h"
#include "AI.h"

class SceneGame : public CCLayer
{
public:
	SceneGame();
	~SceneGame();

	static int _planeID;

	CREATE_FUNC(SceneGame);
	bool init();
	void Back(CCObject*);

	void addHeroPlane();

	Plane*		_plane;   // 战斗机
	AI*			_ai;
	CCLabelTTF* _labelScore; // 分数
	CCLabelTTF* _labelHP;		// 血

	bool ccTouchBegan(CCTouch* t, CCEvent* e);
	void ccTouchMoved(CCTouch* t, CCEvent* e);

	void update(float);
	void killEnemy(Enemy* e);
	void addLabel();
};
#endif

