#ifndef __SceneAbout_H__
#define __ScnenAbout_H__
#include "Util.h"

class SceneAbout :public Layer
{
public:
    SceneAbout() {};
    ~SceneAbout() {};

    CREATE_FUNC(SceneAbout);
    bool init();

    void SceneAbout::Back();

    void readXml();

    void readPlist();

    void readJson();
};

#endif // !__SceneAbout_H__




