#ifndef __UTIL_H__
#define __UTIL_H__

#include "Common.h"
#define winSize Director::getInstance()->getWinSize()
#define itemSize Director::getInstance()->getWinSize()
#define visibleSize Director::getInstance()->getVisibleSize()

#define windowsSize Director::getInstance()->getOpenGLView()->getFrameSize()

struct Util
{
	static void replaceLayer(Layer* layer)
	{
		Scene* scene = Scene::create();
		scene->addChild(layer);
		//Director::getInstance()->replaceScene(scene);
		Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
		//Director::getInstance()->replaceScene(TransitionFadeBL::create(1, scene));
		//Director::getInstance()->replaceScene(TransitionFadeDown::create(1, scene));
		//Director::getInstance()->replaceScene(TransitionFadeTR::create(1, scene));
		//Director::getInstance()->replaceScene(TransitionFadeUp::create(1, scene));
		//Director::getInstance()->replaceScene(TransitionCrossFade::create(1, scene));
		//Director::getInstance()->replaceScene(TransitionFlipAngular::create(1, scene));
		//Director::getInstance()->replaceScene(TransitionJumpZoom::create(1, scene));
		//Director::getInstance()->replaceScene(TransitionPageTurn::create(1, scene, true));

	}

	static void runWithLayer(Layer* layer)
	{
		Scene* scene = Scene::create();
		scene->addChild(layer);
		Director::getInstance()->runWithScene(scene);
	}

	static Sprite* addSpriteBackGround(Node* parent, const char* filename, int tag = 0)
	{
		Sprite* sprite = Sprite::create(filename);
		sprite->setAnchorPoint(Vec2(0, 0));
		Texture2D::TexParams tp = { backend::SamplerFilter::LINEAR , backend::SamplerFilter::LINEAR,
			backend::SamplerAddressMode::MIRROR_REPEAT , backend::SamplerAddressMode::MIRROR_REPEAT };
		sprite->getTexture()->setTexParameters(tp);
		auto rect = Rect(0, 0, visibleSize.width, visibleSize.height);
		sprite->setTextureRect(rect);
		parent->addChild(sprite);
		sprite->setTag(tag);
		return sprite;
	}


	static MenuItem* createButton(Node *parent, ccMenuCallback& callback,
		const char* fileName1, const char* fileName2, float posX, float posY)
	{
		MenuItem* item = MenuItemImage::create(fileName1, fileName2);
		item->setCallback(callback);
		item->setPosition(posX, posY);
		Menu* menu = Menu::createWithItem(item);
		parent->addChild(menu, 0);

		return item;
	} 

};
#endif // !__Util_H__