#ifndef __SceneScore_H__
#define __SceneScore_H__

#include "Common.h"

class SceneScore : public CCLayer
{
public:
	SceneScore();
	~SceneScore();

	static int _score;

	CREATE_FUNC(SceneScore);
	bool init();

	
	void Back(CCObject*);
	void sendScore();
	void response(CCHttpClient* client, CCHttpResponse* response);

	CCLabelTTF* _labelScore[10];
	void createScoreLabel();
	CCMenu* _menu;
};

#endif
