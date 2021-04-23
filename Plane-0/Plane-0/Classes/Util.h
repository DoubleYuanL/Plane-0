
#ifndef __UTIL_H__
#define __UTIL_H__

#include "Macro.h"

#define winSize CCDirector::sharedDirector()->getWinSize()

#define enableTouch() do{ \
	setTouchEnabled(true); \
	setTouchMode(kCCTouchesOneByOne); \
}while (0)

struct Util
{
	static void replaceLayer(CCLayer* layer)
	{
		CCScene* scene = CCScene::create();
		scene->addChild(layer);
		CCDirector::sharedDirector()->replaceScene(scene);
	}

	static void runWithLayer(CCLayer* layer)
	{
		CCScene* scene = CCScene::create();
		scene->addChild(layer);
		CCDirector::sharedDirector()->runWithScene(scene);
	}

	static CCSprite* addSprite(CCNode* parent, const char* filename, int zorder = 0, int tag = 0)
	{
		CCSprite* sprite = CCSprite::create(filename);
		parent->addChild(sprite);
		sprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		sprite->setZOrder(zorder);
		sprite->setTag(tag);
		return sprite;
	}

	static void scaleToFitWindow(CCNode* node)
	{
		node->setScaleX(winSize.width / node->getContentSize().width);
		node->setScaleY(winSize.height / node->getContentSize().height);
	}

	static void scaleToFitWindowY(CCNode* node, float margin = 0.0f)
	{
		node->setScale((winSize.height - margin * 2) / node->getContentSize().height);
	}

	static void scaleToFitWindowX(CCNode* node, float margin = 0.0f)
	{
		node->setScale((winSize.width - margin * 2) / node->getContentSize().width);
	}

	static void moveNode(CCNode* node, const CCPoint& off)
	{
		node->setPosition(node->getPosition() + off);
	}

	static char* format(int number, const char* prefix = "", const char* suffix = "")
	{
		static char buf[1024];
		sprintf(buf, "%s%d%s", prefix, number, suffix);
		return buf;
	}

	static void setTexture(CCSprite* sprite, const char* filename)
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(filename);
		sprite->setTexture(texture);
		sprite->setTextureRect(CCRect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
	}

	static void scaleToSize(CCNode* node, const CCSize& size)
	{
		CCSize nodeSize = node->getContentSize();
		node->setScaleX(size.width / nodeSize.width);
		node->setScaleY(size.height / nodeSize.height);
	}

	static CCPoint map2GL(const CCPoint& ptMap, CCTMXTiledMap* map)
	{
		CCPoint ptUI;
		ptUI.x = ptMap.x * map->getTileSize().width;
		ptUI.y = (ptMap.y + 1)* map->getTileSize().height;

		CCPoint ptGL = ptUI;
		ptGL.y = map->getContentSize().height - ptUI.y;
		return ptGL;
	}
	static CCPoint GL2map(const CCPoint& ptGL, CCTMXTiledMap* map)
	{
		CCPoint ptUI = ptGL;
		ptUI.y = map->getContentSize().height - ptGL.y;

		int x = ptUI.x / map->getTileSize().width;
		int y = ptUI.y / map->getTileSize().height;
		return ccp(x, y);
	}

	static CCMenuItem* createMenuItemRB(CCNode* parent, const char* png1, const char* png2,
		CCNode* target, SEL_MenuHandler selector)
	{
		CCMenuItem* item = CCMenuItemImage::create(png1,
			png2, target, selector);
		CCMenu* menu = CCMenu::createWithItem(item);
		parent->addChild(menu);
		item->setPosition(ccp(winSize.width / 2 - item->boundingBox().size.width / 2,
			item->boundingBox().size.height / 2 - winSize.height / 2));
		return item;
	}

	// 改变Label显示的数值，cv指示改变的值
	static void changeValue(CCLabelTTF* ttf, int cv)
	{
		const char* str = ttf->getString();
		int v = 0;
		if (str && strlen(str)>0)
			v = atoi(str);
		v += cv;
		ttf->setString(Util::format(v));
	}

	static bool isOutOfWindow(CCNode* node)
	{
		CCPoint ptNode = node->getPosition();
		CCPoint ptWorld = node->getParent()->convertToWorldSpace(ptNode);
#if 0
		if (ptWorld.x < 0) return true;
		else if (ptWorld.y < 0) return true;
		else if (ptWorld.x > winSize.width) return true;
		else if (ptWorld.y > winSize.height) return true;
#endif
#if 0
		if (ptWorld.x < 0 || ptWorld.y < 0 || ptWorld.x > winSize.width || ptWorld.y > winSize.height)
			return true;
		return false;
#endif

		return isOutOfWindow(ptWorld);
	}
	static bool isOutOfWindow(const CCPoint& ptWorld)
	{
		return (ptWorld.x < 0 || ptWorld.y < 0 || ptWorld.x > winSize.width || ptWorld.y > winSize.height);
	}

	static void loadAnimation(const char* aniName, const char* plist, int frameCount, float delay, const char* prefix, const char* suffix)
	{
		CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile(plist);
		CCArray* arr = CCArray::create();
		for (int i = 0; i < frameCount; i++)
		{
			CCSpriteFrame* frame = cache->spriteFrameByName(Util::format(i + 1, prefix, suffix));
			arr->addObject(frame);
		}

		CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr, delay);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, aniName);
	}
};

#endif