#ifndef __SceneMenu_H__
#define __SceneMenu_H__


#include "Common.h"
class SceneMenu : public CCLayer
{
public:
	SceneMenu();
	~SceneMenu();

	CREATE_FUNC(SceneMenu);
	bool init();

	void Back(CCObject*);
	void addScrollMenu();
	void SelectPlane(CCObject*);

	bool ccTouchBegan(CCTouch*, CCEvent*) override;
	void ccTouchEnded(CCTouch*, CCEvent*) override;
	void ccTouchMoved(CCTouch*, CCEvent*) override;
	void ccTouchCancelled(CCTouch*, CCEvent*) override;

	CCScrollView* _view;
	bool _viewTouch;
	CCMenu* _menu;
	bool _menuTouch;
	bool _isTouch; // Scroll
};

#endif

