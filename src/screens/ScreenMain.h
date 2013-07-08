#ifndef SCREENMAIN_H_
#define SCREENMAIN_H_

#include "screens/ScreenInShop.h"
#include "screens/ScreenEditShoplist.h"
#include "tools/Styler.h"
#include <NativeUI/Widgets.h>
#include <MAUtil/String.h>
#include <MAUtil/Moblet.h>

using namespace NativeUI;
using namespace MAUtil;

#define PROG_VER "v0.92"

namespace Shoplist455 {

class ScreenMain: public Screen, public ButtonListener, public KeyListener {
public:
    ScreenMain(Moblet* parent = NULL);
    ~ScreenMain();

private:
    Moblet* parent_;
    ScreenEditShoplist* scrEditShoplist;
    ScreenInShop* screenInShop;

    VerticalLayout* lMain;
    Label* lbMain;

    VerticalLayout* lMenu;
    Button* btnLists;
    Button* btnInShop;
    Button* btnExit;

    void createUI();

    virtual void buttonClicked(Widget* button);
    virtual void keyPressEvent(int keyCode, int nativeCode);
};

}

#endif /* SCREENMAIN_H_ */
