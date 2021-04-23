#include "SceneScore.h"
#include "LayerScrollBackground.h"
#include "SceneMenu.h"
int SceneScore::_score = 0;

SceneScore::SceneScore()
{
}


SceneScore::~SceneScore()
{
}

bool SceneScore::init()
{
	CCLayer::init();

	// ��������
	LayerScrollBackground* layer = LayerScrollBackground::create();
	addChild(layer);

	// ��һ�����ذ�ť
	Util::createMenuItemRB(this, IMAGE_MENU_BACK_NORMAL,
		IMAGE_MENU_BACK_SELECT, this, menu_selector(SceneScore::Back));

	// ��ʾ���а�
	sendScore();

	// showScore
	createScoreLabel();

	return true;
}

void SceneScore::createScoreLabel()
{
	CCMenu* menu = CCMenu::create();
	addChild(menu);
	for (int i = 0; i < 10; i++)
	{
		this->_labelScore[i] = CCLabelTTF::create("no user", "Arial", 36);
		CCMenuItem* menuItem = CCMenuItemLabel::create(_labelScore[i]);
		menu->addChild(menuItem);
		menuItem->setEnabled(false);;
	}
	menu->alignItemsVertically();

	_menu = menu;
}

void SceneScore::sendScore()
{
	CCHttpClient* client = CCHttpClient::getInstance();

	CCHttpRequest* req = new CCHttpRequest();

	req->setUrl(Util::format(_score, "http://192.168.192.140/cgi-bin/scoreHandle.cgi?"));
	CCLog("score is %d", _score);
	req->setRequestType(CCHttpRequest::kHttpGet);
//	req->setTag("sendScore");
	req->setResponseCallback(this, httpresponse_selector(SceneScore::response));

	client->send(req);
	req->release();
}

void SceneScore::response(CCHttpClient* client, CCHttpResponse* resp)
{
//	resp->getHttpRequest()->getTag()

	if (resp->getResponseCode() == 200)
	{
		std::vector<char>* data = resp->getResponseData();
		std::string str;
		for (int i = 0; i < data->size(); i++)
		{
			str += (*data)[i];
		}
		CCLog("%s", str.c_str());

		char* buf = new char[str.size() + 1];
		buf[str.size()] = 0;
		strcpy(buf, str.c_str());

		int i = 0;
		char* result = strtok(buf, ":");
		if (strcmp(result, "OK") == 0)
		{
			while (1)
			{
				char* score = strtok(NULL, "|");
				if (score == NULL)break;
				if (strlen(score) == 0)break;
				// ��ʾ����
				//CCMenuItemLabel* label = (CCMenuItemLabel*)_menu->getChildren()->objectAtIndex(i++);
				_labelScore[i++]->setString(score);
				//label->setString(score);
			}
		}
		else
		{
			CCLog("%s", str.c_str());
		}

		delete[]buf;
	}
}

void SceneScore::Back(CCObject*)
{
	Util::replaceLayer(SceneMenu::create());
}