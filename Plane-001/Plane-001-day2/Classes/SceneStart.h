#ifndef __SceneStart_H__
#define __SceneStart_H__

#include "Util.h"

class SceneStart :public Layer
{
public:
	SceneStart() {};
	~SceneStart() {};

	CREATE_FUNC(SceneStart);
	bool init();

	void Start();
	void About();
	void Quit();
};
#endif

