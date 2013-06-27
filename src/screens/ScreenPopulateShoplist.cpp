#include "ScreenPopulateShoplist.h"

using Shoplist455::Dict;

ScreenPopulateShoplist::ScreenPopulateShoplist(Screen* parent):
	parent_(parent){

	createUI();
	readDict();
}

ScreenPopulateShoplist::~ScreenPopulateShoplist() {
}

void ScreenPopulateShoplist::hide() {
	if (parent_) {
		parent_->show();
	}
}

void ScreenPopulateShoplist::createUI() {
	lMain = new VerticalLayout();
	HorizontalLayout* lTop = new HorizontalLayout();
	btnAccept = new Button();
	btnAccept->addButtonListener(this);
	lbMain = new Label("Add items");
	btnDecline = new Button();
	btnDecline->addButtonListener(this);
	setupTopPanel(lMain, lTop, btnAccept, lbMain, btnDecline, NULL);

	lvDict = new ListView();
	lvDict->fillSpaceHorizontally();
	lvDict->fillSpaceVertically();
	lMain->addChild(lvDict);

	VerticalLayout* lFilter = new VerticalLayout();
	lFilter->setScrollable(true);
	lFilter->fillSpaceHorizontally();
	lFilter->setBackgroundColor(Styler::clPopoulateEditsBG);
	lFilter->setPaddingBottom(0);
	lFilter->setPaddingTop(0);

	lFilterCtrls = new HorizontalLayout();
	lFilterCtrls->fillSpaceHorizontally();
	lFilterCtrls->setPaddingBottom(0);
	lFilterCtrls->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);

	ebFilter = new EditBox();
	ebFilter->fillSpaceHorizontally();
	lFilterCtrls->addChild(ebFilter);

	btnAddItem = new Button();
	btnAddItem->setText(" + ");
	btnAddItem->addButtonListener(this);
	btnAddItem->setFontSize(Styler::szf18);
	lFilterCtrls->addChild(btnAddItem);

	btnClearFilter = new Button();
	btnClearFilter->setText("  X  ");
	btnClearFilter->addButtonListener(this);
	lFilterCtrls->addChild(btnClearFilter);

	lFilter->addChild(lFilterCtrls);

	lMain->addChild(lFilter);
	setMainWidget(lMain);
}


void ScreenPopulateShoplist::readDict() {
	StorageWorks sw(STORAGE_DICT);
	String strDict = sw.read();
	if(strDict.length() > 0){
		dict_.parse(strDict);
		maMessageBox("device dict", dict_.toString().c_str());
	}else{
		dict_.parse(DEFAULT_DICT);
		maMessageBox("default dict", dict_.toString().c_str());
	}
}

void ScreenPopulateShoplist::writeDict() {
	StorageWorks sw(STORAGE_DICT);
	sw.write(dict_.toString());
}

void ScreenPopulateShoplist::buttonClicked(Widget* button) {
	if(button == btnAccept){
		parent_->show();
	}else if(button == btnDecline){
		parent_->show();
	}else if(button == btnClearFilter){
		ebFilter->setText("");
	}
}
