#include "ScreenEditShoplist.h"

using namespace Shoplist455;

ScreenEditShoplist* transScreenEditShoplist;

ScreenEditShoplist::ScreenEditShoplist(Screen* parent) :
        parent_(parent) {

    transScreenEditShoplist = this;

    createUI();
}

ScreenEditShoplist::~ScreenEditShoplist() {
    Environment::getEnvironment().removeKeyListener(this);
}

void ScreenEditShoplist::hide() {
    if (parent_) {
        parent_->show();
    }
}

void ScreenEditShoplist::createUI() {

    lMain = new VerticalLayout();

    addOptionsMenuItem("Clear list");
    addOptionsMenuItem("Export list");
    addOptionsMenuItem("Import list");
    addScreenListener(this);

    ///top panel
    HorizontalLayout* lTop = new HorizontalLayout();
    btnAccept = new Button();
    btnAccept->addButtonListener(this);
    lbMain = new Label("Edit shoplist");
    btnDecline = new Button();
    btnDecline->addButtonListener(this);

    ///screen content
    VerticalLayout* lContent = new VerticalLayout();

    setupTopPanel(lMain, lTop, btnAccept, lbMain, btnDecline, lContent);

    String sBuff = STR_LIST_COUNT + "0";
    lbListItemsCount = new Label(sBuff.c_str());
    lbListItemsCount->setFontSize(Styler::szf18);
    lbListItemsCount->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
    lContent->addChild(lbListItemsCount);

    lvShoplistItems = new ListView();
    lvShoplistItems->fillSpaceHorizontally();
    lvShoplistItems->fillSpaceVertically();
    lvShoplistItems->addListViewListener(this);
    lContent->addChild(lvShoplistItems);

    btnPopulateShoplist = new Button();
    btnPopulateShoplist->setText("Add items");
    btnPopulateShoplist->fillSpaceHorizontally();
    btnPopulateShoplist->addButtonListener(this);
    btnPopulateShoplist->setFontSize(Styler::szf20);
    lContent->addChild(btnPopulateShoplist);

    lMain->addChild(lContent);

    setMainWidget(lMain);
}

void ScreenEditShoplist::buttonClicked(Widget* button) {
    if (button == btnAccept) {
        if (parent_) {
            parent_->show();
        }
        writeActivationShoplistDataToDevice();

    } else if (button == btnDecline) {
        if (parent_) {
            parent_->show();
        }

    } else if (button == btnPopulateShoplist) {
        if (!screenPopulateShoplist) {
            screenPopulateShoplist = new ScreenPopulateShoplist(this);
            screenPopulateShoplist->setCallback(callbacker);
        }

        screenPopulateShoplist->setShoplist(shoplist_);
        screenPopulateShoplist->activate();
    }
}

void ScreenEditShoplist::editBoxReturn(EditBox* editBox) {
}

void ScreenEditShoplist::updateShoplistInfo() {
    String sBuff;
    sBuff += STR_LIST_COUNT;
    sBuff += Convert::toString(shoplist_.size());
    lbListItemsCount->setText(sBuff.c_str());
}

void ScreenEditShoplist::setShoplist(Shoplist455::Shoplist shoplist) {
    shoplist_ = shoplist;
    updateShoplistInfo();
    renderShoplist();
}

void ScreenEditShoplist::renderShoplist() {
    while (lvShoplistItems->getChild(0) != NULL) {
        lvShoplistItems->removeChild(lvShoplistItems->getChild(0));
    }

    for (int i = 0; i < shoplist_.size(); i++) {
        Label* l = new Label(
                Convert::toString(i + 1) + " " + shoplist_.getItem(i));
        l->fillSpaceHorizontally();
        l->setFontSize(Styler::szf16);
        l->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
        lvShoplistItems->addChild(l);
    }

    updateShoplistInfo();
}

void ScreenEditShoplist::listViewItemClicked(ListView* listView, int index) {
    shoplist_.removeAt(index);
    lvShoplistItems->removeChild(lvShoplistItems->getChild(index));
    updateShoplistInfo();
}

void ScreenEditShoplist::writeActivationShoplistDataToDevice() {
    StorageWorks sw2(STORE_SHOPLIST_ACTIVE);
    Shoplist slBuff = shoplist_;
    sw2.write(slBuff.toString());

    StorageWorks sw(STORE_INSHOP_TOBUY);
    sw.write(slBuff.toString());
}

void Shoplist455::ScreenEditShoplist::optionsMenuItemSelected(Screen* screen,
        int index) {
    switch (index) {
    case 0:
            //clear current shoplist
        shoplist_.clear();

        renderShoplist();
        updateShoplistInfo();
        break;

    case 1:
            //export
        if (!screenShoplistExport) {
            screenShoplistExport = new ScreenShoplistExport(this);
        }
        screenShoplistExport->setText(shoplist_.toString());
        screenShoplistExport->activate();
        break;

    case 2:
            //import
        if (!screenShoplistImport) {
                maMessageBox("dbg", "shoplistimport created");
            screenShoplistImport = new ScreenShoplistImport(this);
            screenShoplistImport->setCallback(Shoplist455::callbacker);
        }
        screenShoplistImport->activate();
        break;

    default:
        break;
    }
}

void Shoplist455::ScreenEditShoplist::activate() {
    Environment::getEnvironment().addKeyListener(this);
    this->show();
}

void Shoplist455::ScreenEditShoplist::keyPressEvent(int keyCode,
        int nativeCode) {
    if (MAK_BACK == keyCode) {
        writeActivationShoplistDataToDevice();

        if (this->isShown()) {
            hide();
        }
    }
}

void Shoplist455::callbacker(Shoplist455::Shoplist shoplist) {
    transScreenEditShoplist->shoplist_ = shoplist;
    transScreenEditShoplist->renderShoplist();
}
