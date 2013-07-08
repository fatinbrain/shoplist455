#ifndef SCREENINSHOP_H_
#define SCREENINSHOP_H_

//#include "screens/ScreenMain.h"
#include "tools/Styler.h"
#include "tools/UIAssist.h"
#include "datastructs/Shoplist.h"
#include "tools/StorageWorks.h"
#include "common.h"

#include <NativeUI/Widgets.h>

using Shoplist455::Shoplist;
//using Shoplist455::ScreenMain;
using namespace NativeUI;

namespace Shoplist455 {

static const String STR_LISTNAME = "";

class ScreenInShop: public Screen,
        public ButtonListener,
        public ListViewListener,
        public KeyListener {

public:
    ScreenInShop(Screen* parent = NULL);
    ~ScreenInShop();

    void hide();
    void activate();
    void setShoplist(Shoplist shoplist);
    void updateData();

private:
    Screen* parent_;

    Shoplist shoplist_;
    Shoplist shoplistToBuy_;

    VerticalLayout* lMain;
    Label* lbMain;
    Button* btnAccept;
    Button* btnDecline;
    ListView* lvToBuy;
    ProgressBar* pbShopProgress;
    Label* lbShopProgress;

    Label* lbDbg;

    void clearListview();
    void createUI();
    void readDataFromDevice();
    void removeDataFromDevice();
    void renderShoplist();
//	void setNameLabel(String ListName);

    void shoplistChanged();
    void updateProgressBar();
    void writeDataToDevice();

    virtual void buttonClicked(Widget* button);
    virtual void listViewItemClicked(ListView* listView, int index);
    virtual void keyPressEvent(int keyCode, int nativeCode);
};

}
#endif /* SCREENINSHOP_H_ */

