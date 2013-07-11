#include "ScreenPopulateShoplist.h"

using Shoplist455::Dict;

ScreenPopulateShoplist::ScreenPopulateShoplist(Screen* parent) :
        isRemoveMode(false), parent_(parent) {

    callbacker = NULL;

    createUI();
    readDict();
    renderDict();
    colorizeFilter();
    updateMode();
    buttonAvailbilityCheck();
}

ScreenPopulateShoplist::~ScreenPopulateShoplist() {
    Environment::getEnvironment().removeKeyListener(this);
    btnAccept->removeButtonListener(this);
    btnAddItem->removeButtonListener(this);
    btnClearFilter->removeButtonListener(this);
    btnDecline->removeButtonListener(this);
}


void ScreenPopulateShoplist::hide() {
    if (parent_) {
        parent_->show();
    }
}


void ScreenPopulateShoplist::createUI() {
    addOptionsMenuItem("Drop stat");
    addOptionsMenuItem("Remove item");
    addScreenListener(this);

    lMain = new VerticalLayout();
    lTop = new HorizontalLayout();
    btnAccept = new Button();
    btnAccept->addButtonListener(this);
    lbMain = new Label("Add items");
    btnDecline = new Button();
    btnDecline->addButtonListener(this);
    setupTopPanel(lMain, lTop, btnAccept, lbMain, btnDecline, NULL);

    lvDict = new ListView();
    lvDict->fillSpaceHorizontally();
    lvDict->addListViewListener(this);

    lMain->addChild(lvDict);

    lFilter = new VerticalLayout();
    lFilter->setScrollable(true);
    lFilter->fillSpaceHorizontally();
    lFilter->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);
    lFilter->setBackgroundColor(Styler::clPopoulateEditsBG);
    Styler::setlayoutPaddings1(lFilter, 5);

    lFilterCtrls = new HorizontalLayout();
    lFilterCtrls->fillSpaceHorizontally();
    Styler::setlayoutPaddings1(lFilterCtrls, 0);
    lFilterCtrls->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);

    ebFilter = new EditBox();
    ebFilter->fillSpaceHorizontally();
    ebFilter->addEditBoxListener(this);
    lFilterCtrls->addChild(ebFilter);

    btnAddItem = new Button();
    btnAddItem->setText(" + ");
    btnAddItem->addButtonListener(this);
    btnAddItem->setFontSize(Styler::szf18);
    lFilterCtrls->addChild(btnAddItem);

    btnClearFilter = new Button();
    btnClearFilter->setText("  x  ");
    btnClearFilter->addButtonListener(this);
    btnClearFilter->setFontSize(Styler::szf18);
    lFilterCtrls->addChild(btnClearFilter);

    lFilter->addChild(lFilterCtrls);
    lMain->addChild(lFilter);

    setMainWidget(lMain);
}

void ScreenPopulateShoplist::readDict() {
    StorageWorks sw(STORAGE_DICT);
    String strDict = sw.read();

    if (strDict.length() > 0) {
        strDict = strDict.substr(0, strDict.find("|"));
        dictOrig_.parse(strDict);
    } else {
        dictOrig_.parse(DEFAULT_DICT);
    }

    resetWorkingDict();
}

void ScreenPopulateShoplist::writeDict() {
    StorageWorks sw(STORAGE_DICT);
    sw.rm();
    String writeBuff = dictOrig_.toString();
    writeBuff += "|";
    sw.write(writeBuff);
}

void ScreenPopulateShoplist::renderDict() {
    lvDict->setEnabled(false);

    dictOrig_.adsorbShoplist(shoplist_);
    dictWork_.filtrateByShoplist(shoplist_);
    dictWork_.filtrateByItem(ebFilter->getText());
    dictWork_.sordDictByAlpha();

    while (lvDict->getChild(0)) {
        lvDict->removeChild(lvDict->getChild(0));
    }

    String name = "";
    String usage = "";

    for (int i = 0; i < dictWork_.size(); i++) {
        lvi = new ListViewItem();

        name = dictWork_.getItem(i).first;
        usage = Convert::toString(dictWork_.getItem(i).second);

        HorizontalLayout* lItem = new HorizontalLayout();
        lItem->fillSpaceHorizontally();

        Label* lbName = new Label();
        lbName->setFontSize(Styler::szf18);
        lbName->fillSpaceHorizontally();
        lbName->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
        lbName->setText(name);

        lItem->addChild(lbName);

        if (dictWork_.getItem(i).second > 0) {
            Label* lbUsage = new Label();
            lbUsage->setText(usage);
            lbUsage->setWidth(Styler::normalize(40));
            lbUsage->setFontSize(Styler::szf18);
            lbUsage->setBackgroundColor(0x5555aa);

            lItem->addChild(lbUsage);
        }

        lvi->addChild(lItem);

        lvDict->addChild(lvi);
    }

    lvDict->setEnabled(true);
}

void ScreenPopulateShoplist::buttonClicked(Widget* button) {
    if (button == btnAccept) {
        actAcceptList();

        parent_->show();

    } else if (button == btnDecline) {
        writeDict();
        parent_->show();

    } else if (button == btnClearFilter) {
        ebFilter->setText("");

    } else if (button == btnAddItem) {
        shoplist_.add(ebFilter->getText());
        ebFilter->setText("");
        ebFilter->hideKeyboard();
    }
}

void ScreenPopulateShoplist::setShoplist(Shoplist455::Shoplist shoplist) {
    shoplist_ = shoplist;
    resetWorkingDict();
    renderDict();
}

void ScreenPopulateShoplist::optionsMenuItemSelected(Screen* screen,
        int index) {

    switch (index) {
    case 0:
        //drop stat
        dictOrig_.dropStat();
        resetWorkingDict();
        writeDict();
        renderDict();
        break;
    case 1:
        //remove item
        isRemoveMode = true;
        //lvDict->setBackgroundColor(0xaa5555);
        updateMode();
        break;
    case 2:
        //import dict
        maMessageBox("in future",
                "this feature will be available in deep future.");
        //debug
        maMessageBox("current dict", dictWork_.toString().c_str());
        break;
    default:
        break;
    }
}

void ScreenPopulateShoplist::editBoxReturn(EditBox* editBox) {
}

void ScreenPopulateShoplist::colorizeFilter() {
    if (ebFilter->getText() == "") {
        lFilter->setBackgroundColor(0x333333);
    } else if (!dictWork_.size()) {
        lFilter->setBackgroundColor(0xaa5555);
    } else {
        lFilter->setBackgroundColor(0x55aa55);
    }
}

void ScreenPopulateShoplist::buttonAvailbilityCheck() {
    if (ebFilter->getText() == "") {
        btnClearFilter->setEnabled(false);
        btnAddItem->setEnabled(false);
    } else {
        btnClearFilter->setEnabled(true);
        if (dictWork_.size()) {
            btnAddItem->setEnabled(false);
        } else {
            btnAddItem->setEnabled(true);
        }
    }
}

void ScreenPopulateShoplist::setCallback(
        void (*callback)(Shoplist455::Shoplist shoplist)) {
    callbacker = callback;
}

void ScreenPopulateShoplist::editBoxTextChanged(EditBox* editBox,
        const MAUtil::String& text) {
    lvDict->setEnabled(false);
    //readDict();
    resetWorkingDict();
    renderDict();
    colorizeFilter();
    buttonAvailbilityCheck();
    lvDict->setEnabled(true);
}

void ScreenPopulateShoplist::resetWorkingDict() {
    dictWork_ = dictOrig_;
}

void ScreenPopulateShoplist::activate() {
    Environment::getEnvironment().addKeyListener(this);
    this->show();
}

void ScreenPopulateShoplist::keyPressEvent(int keyCode, int nativeCode) {
    if (MAK_BACK == keyCode) {
        if(!isRemoveMode){
            actAcceptList();

            if (this->isShown()) {
                hide();
            }
        }else{
            isRemoveMode = false;
            updateMode();
        }
    }
}

void ScreenPopulateShoplist::actAcceptList() {
    writeDict();

    if (callbacker) {
        callbacker(shoplist_);
    }
}

void ScreenPopulateShoplist::updateMode() {
    lvDict->setBackgroundColor(isRemoveMode ? 0xaa5555 : 0x333333);
    lTop->setVisible(!isRemoveMode);

}

void ScreenPopulateShoplist::listViewItemClicked(ListView* listView,
        int index) {
    if (!isRemoveMode) {
        String itemName = dictWork_.getItem(index).first;
        dictOrig_.increaseUsageByName(itemName);
        shoplist_.add(itemName);
        lvDict->removeChild(lvDict->getChild(index));
        dictWork_.remove(index);

    } else {
        isRemoveMode = false;
        updateMode();
        dictOrig_.remove(dictWork_.getItem(index).first);
        writeDict();
        resetWorkingDict();
        renderDict();
    }
}
