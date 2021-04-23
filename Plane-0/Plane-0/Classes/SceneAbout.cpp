#include "SceneAbout.h"
#include "SceneStart.h"

SceneAbout::SceneAbout()
{
}


SceneAbout::~SceneAbout()
{
}

bool SceneAbout::init()
{
	CCLayer::init();

	Util::addSprite(this, IMAGE_BACKGROUND);

	// 加一个返回按钮
	Util::createMenuItemRB(this, IMAGE_MENU_BACK_NORMAL, IMAGE_MENU_BACK_SELECT, this, menu_selector(SceneAbout::Back));

	// 显示About内容
	CCDictionary* dict = CCDictionary::createWithContentsOfFile("about.xml");
	CCArray* keys = dict->allKeys();
	CCObject * obj;
	int i = 1;
	float xoff = 50;
	float yoff = 50;
	float space = 10;
	CCARRAY_FOREACH(keys, obj)
	{
		CCString* key = (CCString*)obj;
		const CCString* value = dict->valueForKey(key->getCString());
		CCLabelTTF* ttf = CCLabelTTF::create(value->getCString(), "Arial", 36);
		addChild(ttf);

		ttf->setAnchorPoint(ccp(0, 0));
		ttf->setPosition(ccp(xoff, winSize.height - ttf->boundingBox().size.height*i - yoff-i*space));
		i++;

	}
	return true;
}

void SceneAbout::Back(CCObject*)
{
	Util::replaceLayer(SceneStart::create());
}