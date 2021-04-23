#ifndef __SceneStart_H__
#define __SceneStart_H__

#include "Common.h"

class SceneStart : public CCLayer
{
public:
	SceneStart();
	~SceneStart();

	CREATE_FUNC(SceneStart);
	bool init();

	void Start(CCObject*);
	void About(CCObject*);
	void Quit(CCObject*);
};

#endif

