#ifndef __ScnenMenu_H__
#define __SceneMenu_H__
#include "Util.h"
#include "LayerScrollBackground.h"

class SceneMenu :public Layer
{
public:
    SceneMenu() {};
    ~SceneMenu() {};

    CREATE_FUNC(SceneMenu);
    bool init();

    void Back(Ref* pSender);

    void addScrollMenu();

    void selectPlane(Ref* pSender);

private:
    LayerScrollBackground* _scrollBackground;
};

#endif // ! __ScnenMenu_H__


