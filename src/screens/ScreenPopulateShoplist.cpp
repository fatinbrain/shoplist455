#include "ScreenPopulateShoplist.h"

using Shoplist455::Dict;

ScreenPopulateShoplist::ScreenPopulateShoplist(Screen* parent) :
        parent_(parent) {

    callbacker = NULL;

    createUI();
    readDict();
    renderDict();
    colorizeFilter();
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
//	addOptionsMenuItem("Export dict");
//	addOptionsMenuItem("Import dict");
    addScreenListener(this);

    lMain = new VerticalLayout();
    HorizontalLayout* lTop = new HorizontalLayout();
    btnAccept = new Button();
    btnAccept->addButtonListener(this);
    lbMain = new Label("Add items");
    btnDecline = new Button();
    btnDecline->addButtonListener(this);
    setupTopPanel(lMain, lTop, btnAccept, lbMain, btnDecline, NULL);

    lvDict = new ListView(LIST_VIEW_TYPE_SEGMENTED);
    lvDict->fillSpaceHorizontally();
    lvDict->addListViewListener(this);

    lvsUsed = new ListViewSection(LIST_VIEW_SECTION_TYPE_SEGMENTED);
    lvsUsed->setHeaderFontSize(Styler::normalize(12));
    lvsUsed->setFooterFontSize(1);
    lvsUsed->setHeaderTextHorizontalAlignment(MAW_ALIGNMENT_RIGHT);
    lvsUsed->setHeaderText("Used items");

    lvsUnused = new ListViewSection(LIST_VIEW_SECTION_TYPE_SEGMENTED);
    lvsUnused->setHeaderFontSize(Styler::normalize(12));
    lvsUnused->setFooterFontSize(1);
    lvsUnused->setHeaderTextHorizontalAlignment(MAW_ALIGNMENT_RIGHT);
    lvsUnused->setHeaderText("Unused items");

    lvDict->addChild(lvsUsed);
    lvDict->addChild(lvsUnused);

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
    btnClearFilter->setText("  X  ");
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
    String writeBuff = dictOrig_.toString();
    writeBuff += "|";
    sw.write(writeBuff);
}

void ScreenPopulateShoplist::renderDict() {
    lvDict->setEnabled(false);

    dUsed_.clear();
    dUnused_.clear();

    dictOrig_.adsorbShoplist(shoplist_);
    dictWork_.filtrateByShoplist(shoplist_);
    dictWork_.filtrateByItem(ebFilter->getText());

    //split dict into used and unused sections
    for (int i = 0; i < dictWork_.size(); i++) {
        if (dictWork_.getItem(i).second > 0) {
            dUsed_.addItem(dictWork_.getItem(i));
        } else {
            dUnused_.addItem(dictWork_.getItem(i));
        }
    }

    dUsed_.sortDictByUsage();
    dUnused_.sordDictByAlpha();

    //render used items
    lvsUsed->setEnabled(false);
    lvsUsed->setVisible(dUsed_.size() > 0);
    while (lvsUsed->getChild(0)) {
        lvsUsed->removeItem(0);
    }

    for (int i = 0; i < dUsed_.size(); i++) {
        lvi = new ListViewItem();
        String name = dUsed_.getItem(i).first;
        String usage = Convert::toString(dUsed_.getItem(i).second);

        HorizontalLayout* lItem = new HorizontalLayout();
        lItem->fillSpaceHorizontally();

        Label* lbName = new Label();
        lbName->setFontSize(Styler::szf18);
        lbName->fillSpaceHorizontally();
        lbName->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
        lbName->setText(name);

        Label* lbUsage = new Label();
        lbUsage->setText(usage);
        lbUsage->setWidth(Styler::normalize(40));
        //lbUsage->setFont(maFontLoadWithName(Styler::fnClockopia.c_str(), 40));
        lbUsage->setFontSize(Styler::szf18);
        lbUsage->setBackgroundColor(0x5555aa);

        lItem->addChild(lbName);
        lItem->addChild(lbUsage);

        lvi->addChild(lItem);

        lvsUsed->addItem(lvi);
    }
    lvsUsed->setEnabled(true);

    //render unused items
    lvsUnused->setEnabled(false);
    lvsUnused->setVisible(dUnused_.size() > 0);
    while (lvsUnused->getChild(0)) {
        lvsUnused->removeItem(0);
    }

    for (int i = 0; i < dUnused_.size(); i++) {
        lvi = new ListViewItem();
        lvi->setText(dUnused_.getItem(i).first.c_str());
        lvi->setFontSize(Styler::szf18);
        lvsUnused->addItem(lvi);
    }
    lvsUnused->setEnabled(true);

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
    //readDict();
    resetWorkingDict();
    renderDict();
}

void ScreenPopulateShoplist::optionsMenuItemSelected(Screen* screen,
        int index) {

    switch (index) {
    case 0:
        //drop stat
        dictWork_.dropStat();
        renderDict();
        break;
    case 1:
        //export dict

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
        actAcceptList();

        if (this->isShown()) {
            hide();
        }
    }
}

void ScreenPopulateShoplist::actAcceptList() {
}

void ScreenPopulateShoplist::segmentedListViewItemClicked(ListView* listView,
        int sectionIndex, int itemIndex) {

    String itemName = "";
    if (sectionIndex == 0) {
        itemName = dUsed_.getItem(itemIndex).first;
        dictOrig_.increaseUsageByName(itemName);
        shoplist_.add(itemName);
        lvsUsed->removeItem(itemIndex);
        dUsed_.remove(itemIndex);

    } else {
        itemName = dUnused_.getItem(itemIndex).first;
        dictOrig_.increaseUsageByName(itemName);
        shoplist_.add(itemName);
        lvsUnused->removeItem(itemIndex);
        dUnused_.remove(itemIndex);

    }
    //renderDict();
}
