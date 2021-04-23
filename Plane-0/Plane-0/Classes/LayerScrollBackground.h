
#ifndef __LayerScrollBackground_H__
#define __LayerScrollBackground_H__

#include "Common.h"

class LayerScrollBackground : public CCLayer
{
public:
	LayerScrollBackground();
	~LayerScrollBackground();
	CREATE_FUNC(LayerScrollBackground);
	bool init()
	{
		CCLayer::init();

		CCSprite* bg = Util::addSprite(this, IMAGE_BACKGROUND);
		bg->setAnchorPoint(ccp(0, 0));
		bg->setPosition(CCPointZero);

		CCMoveBy* moveBy = CCMoveBy::create(10, ccp(0, -winSize.height));
		CCPlace* place = CCPlace::create(CCPointZero);
		CCSequence* seq = CCSequence::create(moveBy, place, NULL);
		CCRepeatForever* rep = CCRepeatForever::create(seq);
		bg->runAction(rep);

		return true;
	}
};

#endif
