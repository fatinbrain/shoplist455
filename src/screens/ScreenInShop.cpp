#include "ScreenInShop.h"

using namespace Shoplist455;

ScreenInShop* transInShop;

ScreenInShop::ScreenInShop(Screen* parent) :
        parent_(parent) {
    transInShop = this;

    createUI();

    readDataFromDevice();
    renderShoplist();
    updateProgressBar();
}

ScreenInShop::~ScreenInShop() {
}

void ScreenInShop::hide() {
//	Environment::getEnvironment().removeKeyListener(this);

    if (parent_) {
        parent_->show();
    }
}

void ScreenInShop::createUI() {
    lMain = new VerticalLayout();
    HorizontalLayout* lTop = new HorizontalLayout();
    btnAccept = new Button();
    btnAccept->addButtonListener(this);
    lbMain = new Label("In Shop");
    btnDecline = new Button();
    btnDecline->addButtonListener(this);
    VerticalLayout* lContent = new VerticalLayout();

    setupTopPanel(lMain, lTop, btnAccept, lbMain, btnDecline, lContent);
    Styler::setlayoutPaddings1(lContent, 0);

    HorizontalLayout* lInfo = new HorizontalLayout();
    lInfo->fillSpaceHorizontally();
    lInfo->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);
    lInfo->setScrollable(true);

    pbShopProgress = new ProgressBar();
    pbShopProgress->fillSpaceHorizontally();
    pbShopProgress->setMaximumValue(1);
    pbShopProgress->setProgress(0);
    lInfo->addChild(pbShopProgress);

    lbShopProgress = new Label("--%");
    lbShopProgress->setFontSize(Styler::szf18);
    lInfo->addChild(lbShopProgress);

    lContent->addChild(lInfo);

    lvToBuy = new ListView();
    lvToBuy->fillSpaceHorizontally();
    lvToBuy->fillSpaceVertically();
    lvToBuy->addListViewListener(this);
    lContent->addChild(lvToBuy);

    lMain->addChild(lContent);

    setMainWidget(lMain);
}

void ScreenInShop::setShoplist(Shoplist shoplist) {
    shoplist_ = shoplist;
    shoplistToBuy_ = shoplist;
    shoplistChanged();
}

void ScreenInShop::shoplistChanged() {
    renderShoplist();
    updateProgressBar();
}

void ScreenInShop::readDataFromDevice() {
    shoplist_.clear();

    StorageWorks sw(STORE_SHOPLIST_ACTIVE);
    String strListAcitve = sw.read();
    if (strListAcitve.length() > 0) {
        shoplist_.parse(strListAcitve);
    }

    shoplistToBuy_.clear();
    StorageWorks sw2(STORE_INSHOP_TOBUY);
    String listToBuy = sw2.read();
    if (listToBuy.length() > 0) {
        shoplistToBuy_.parse(listToBuy);
    }

    updateProgressBar();
}

void ScreenInShop::updateData() {
    readDataFromDevice();
    renderShoplist();
}

void ScreenInShop::removeDataFromDevice() {
    StorageWorks sw2(STORE_INSHOP_TOBUY);
    sw2.rm();
}

void ScreenInShop::buttonClicked(Widget* button) {
    if (button == btnAccept) {
        if (shoplistToBuy_.size() == 0) {
            readDataFromDevice();
            shoplistToBuy_.clear();
        }
        parent_->show();
    } else if (button == btnDecline) {
        removeDataFromDevice();
        shoplistToBuy_.clear();
        parent_->show();
    }
    updateProgressBar();
}

void ScreenInShop::updateProgressBar() {
    if (shoplist_.size() == 0) {
        pbShopProgress->setMaximumValue(1);
        pbShopProgress->setProgress(0);
        lbShopProgress->setText("--%");
    } else {
        pbShopProgress->setMaximumValue(shoplist_.size());
        int progress = shoplist_.size() - shoplistToBuy_.size();
        pbShopProgress->setProgress(progress);
        String sBuff = " "
                + Convert::toString(progress * 100 / shoplist_.size()) + "%";
        lbShopProgress->setText(sBuff.c_str());
    }
}

void ScreenInShop::writeDataToDevice() {
    StorageWorks sw(STORE_INSHOP_TOBUY);
    sw.write(shoplistToBuy_.toString());
}

void ScreenInShop::clearListview() {
    while (lvToBuy->getChild(0) != NULL) {
        lvToBuy->removeChild(lvToBuy->getChild(0));
    }
}

void ScreenInShop::renderShoplist() {
    lvToBuy->setEnabled(false);
    clearListview();
    String sBuff;
    for (int i = 0; i < shoplistToBuy_.size(); i++) {
        sBuff = "";
        sBuff += Convert::toString(i + 1);

        HorizontalLayout* lItem = new HorizontalLayout();
        lItem->fillSpaceHorizontally();
        lItem->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);

        Label* lbNum = new Label(sBuff.c_str());
        lbNum->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
        lbNum->setBackgroundColor(Styler::clListsLabelGray);
        lbNum->setFontSize(Styler::szf28);
        lbNum->setWidth(Styler::normalize(40));
        lbNum->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
        lItem->addChild(lbNum);

        sBuff = " ";
        sBuff += shoplistToBuy_.getItem(i);

        Label* l = new Label(sBuff.c_str());
        l->fillSpaceHorizontally();
        l->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
        l->setFontSize(Styler::szf28);
        lItem->addChild(l);

        lvToBuy->addChild(lItem);
    }
    lvToBuy->setEnabled(true);
}

void ScreenInShop::listViewItemClicked(ListView* listView, int index) {
    shoplistToBuy_.removeAt(index);
    lvToBuy->removeChild(lvToBuy->getChild(index));
    updateProgressBar();
    writeDataToDevice();
}

void Shoplist455::ScreenInShop::activate() {
    Environment::getEnvironment().addKeyListener(this);

    this->show();
}

void Shoplist455::ScreenInShop::keyPressEvent(int keyCode, int nativeCode) {
    if (keyCode == MAK_BACK) {
        if (this->isShown()) {
            hide();
        }
    }
}
