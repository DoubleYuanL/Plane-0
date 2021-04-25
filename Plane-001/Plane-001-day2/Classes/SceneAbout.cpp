#include "SceneAbout.h"
#include "SceneStart.h"
#include "Util.h"

bool SceneAbout::init()
{
    Layer::init();

    Util::addSpriteBackGround(this, IMAGE_BACKGROUND);

    ccMenuCallback buttonFun = std::bind(&SceneAbout::Back, this);
    Util::createButton(this, buttonFun,
        IMAGE_MENU_BACK_NORMAL, IMAGE_MENU_BACK_SELECT,
        winSize.width / 2 - itemSize.width / 12, itemSize.height / 12 - winSize.height / 2);

	//readXml();

	//readPlist();

	readJson();

    return true;
}

void SceneAbout::readXml()
{
	auto doc = new tinyxml2::XMLDocument();
	doc->Parse(FileUtils::getInstance()->getStringFromFile(XML_ABOUT).c_str());
	auto root = doc->RootElement();											//plist

	int i = -2;
	for (auto e = root->FirstChildElement(); e; e = e->NextSiblingElement())//dict
	{
		string str = "";
		for (auto attr = e->FirstAttribute(); attr; attr=attr->Next())//key string
		{
			str += attr->Name();
			str += attr->Value();
		}

		Util::setLabelTTF(this, str, winSize.width / 2, winSize.height / 2 - i++ * 100, 
			36, Color4B::BLACK, Vec2::ANCHOR_MIDDLE);
	}
	CC_SAFE_DELETE(doc);
}

void SceneAbout::readPlist()
{
	ValueMap vm = FileUtils::getInstance()->getValueMapFromFile(PLIST_ABOUT);
	int i = -2;
	for (auto it = vm.begin(); it != vm.end(); ++it)
	{
		string str = "";
		str += it->first.c_str();
		str += it->second.asString().c_str();

		Util::setLabelTTF(this, str, winSize.width / 2, winSize.height / 2 - i++ * 100,
			36, Color4B::BLACK, Vec2::ANCHOR_MIDDLE);
	}
}

void SceneAbout::readJson()
{
	rapidjson::Document d;
	d.Parse<0>(FileUtils::getInstance()->getStringFromFile(JSON_ABOUT).c_str());

	//log("%s", d[0]["Studio"].GetString());
	cocos2d::ccMessageBox(Util::format( d[1].IsArray()), "JSON");
}

void SceneAbout::Back()
{
    Util::replaceLayer(SceneStart::create());
}