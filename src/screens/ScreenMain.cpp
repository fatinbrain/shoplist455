#include "ScreenMain.h"

#include "datastructs/Shoplist.h"
#include "tools/Convert.h"

using namespace Shoplist455;

ScreenMain* transmitter;

ScreenMain::ScreenMain(Moblet* parent) :
        parent_(parent),
        screenEditShoplist(NULL),
        screenInShop(NULL){

    Styler s;

    transmitter = this;

    createUI();

    Environment::getEnvironment().addKeyListener(this);
}

ScreenMain::~ScreenMain() {
}

void ScreenMain::createUI() {
    lMain = new VerticalLayout();
    lMain->fillSpaceHorizontally();
    lMain->fillSpaceVertically();

    String sBuff = "";
    sBuff += "..::shoplist455::..\n";
    sBuff += PROG_VER;
    sBuff += ""
            "";
    Label* lb = new Label(sBuff.c_str());
    lb->fillSpaceHorizontally();
    lb->setFontSize(Styler::szf18);
    lb->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
    lMain->addChild(lb);

    lMenu = new VerticalLayout();
    lMenu->fillSpaceHorizontally();
    lMenu->fillSpaceVertically();
    lMenu->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);
    Styler::setlayoutPaddings1(lMain, Styler::szPaddingNormal);

    btnLists = new Button();
    btnLists->setText("List");
    btnLists->setFontSize(Styler::szfButtonBig);
    btnLists->fillSpaceHorizontally();
    btnLists->addButtonListener(this);
    lMenu->addChild(btnLists);

    btnInShop = new Button();
    btnInShop->setText("InShop");
    btnInShop->setFontSize(Styler::szfButtonBig);
    btnInShop->fillSpaceHorizontally();
    btnInShop->addButtonListener(this);
    lMenu->addChild(btnInShop);

    btnExit = new Button();
    btnExit->setText("Exit");
    btnExit->setFontSize(Styler::szfButtonBig);
    btnExit->fillSpaceHorizontally();
    btnExit->addButtonListener(this);
    lMenu->addChild(btnExit);

    lMain->addChild(lMenu);

    setMainWidget(lMain);
}

void ScreenMain::buttonClicked(Widget* button) {
    //Environment::getEnvironment().removeKeyListener(this);

    if (button == btnLists) {
        Shoplist455::Shoplist s;

        StorageWorks sw(STORE_SHOPLIST_ACTIVE);
        String strListAcitve = sw.read();
        if (strListAcitve.length() > 0) {
            s.parse(strListAcitve);
        }

        if (screenEditShoplist == NULL) {
            screenEditShoplist = new ScreenEditShoplist(this);
        }

        screenEditShoplist->setShoplist(s);
        screenEditShoplist->activate();

    } else if (button == btnInShop) {
        if (screenInShop == NULL) {
            screenInShop = new ScreenInShop(this);
        }

        screenInShop->updateData();
        screenInShop->activate();

    } else if (button == btnExit) {
        maExit(0);
    }
}

void Shoplist455::ScreenMain::keyPressEvent(int keyCode, int nativeCode) {
    if (MAK_BACK == keyCode) {
        if (this->isShown()) {
            maExit(0);
        }
    }
}
