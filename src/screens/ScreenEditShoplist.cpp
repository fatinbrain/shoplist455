#include "ScreenEditShoplist.h"

using namespace Shoplist455;

ScreenEditShoplist* transScreenEditShoplist;

ScreenEditShoplist::ScreenEditShoplist
	(/*Shoplist455::Dictionary dictionary, Shoplist455::Shoplist shoplist, */Screen* parent){
//	dictionary_(dictionary), shoplist_(shoplist), parent_(parent) {
//
//	transScreenEditShoplist = this;
//
//	scrPopulateShoplist = new ScreenPopulateShoplist(dictionary_, shoplist_, this);
//	scrPopulateShoplist->setCallback(callbackShoplistPopulate);
//
	createUI();
//	renderShoplist();
}

ScreenEditShoplist::~ScreenEditShoplist() {
}


void ScreenEditShoplist::hide() {
	if(parent_){
		parent_->show();
	}
}

void ScreenEditShoplist::createUI() {
	lMain = new VerticalLayout();
//	lMain->fillSpaceHorizontally();
//	lMain->fillSpaceVertically();
//	lMain->setBackgroundColor(0x333333);
//
//	///top panel
	HorizontalLayout* lTop = new HorizontalLayout();
//	lTop->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);
//	lTop->setScrollable(true);
//	lTop->setBackgroundColor(0x555555);
//
	btnAccept = new Button();
//	btnAccept->setText("<<");
//	btnAccept->setFontSize(17);
	btnAccept->addButtonListener(this);
//	btnAccept->setBackgroundColor(0x55aa55);
//	lTop->addChild(btnAccept);
//
	lbMain = new Label("Edit shoplist");
//	lbMain->setFontSize(20);
//	lbMain->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
//	lbMain->fillSpaceHorizontally();
//	lTop->addChild(lbMain);
//
	btnDecline = new Button();
//	btnDecline->setText(" X ");
//	btnDecline->setFontSize(17);
	btnDecline->addButtonListener(this);
//	btnDecline->setBackgroundColor(0xaa5555);
//	lTop->addChild(btnDecline);
//
//	lMain->addChild(lTop);
//
//	///screen content
	VerticalLayout* lContent = new VerticalLayout();
//	lContent->fillSpaceHorizontally();
//	lContent->fillSpaceVertically();
//	lContent->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);
//	lContent->setPaddingLeft(20);
//	lContent->setPaddingRight(20);
//	lContent->setPaddingTop(0);

	setupTopPanel(lMain, lTop, btnAccept, lbMain, btnDecline, lContent);


	Label* lbShoplistName = new Label("Shoplist name");
	lbShoplistName->setFontSize(Styler::szf18);
	lbShoplistName->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
	lContent->addChild(lbShoplistName);

	ebShoplistName = new EditBox();
	ebShoplistName->fillSpaceHorizontally();
	ebShoplistName->addEditBoxListener(this);
	lContent->addChild(ebShoplistName);

	String sBuff = STR_LIST_COUNT + "0";
	lbListItemsCount = new Label(sBuff.c_str());
	lbListItemsCount->setFontSize(Styler::szf18);
	lbListItemsCount->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
	lContent->addChild(lbListItemsCount);

	btnPopulateShoplist = new Button();
	btnPopulateShoplist->setText("Fill shoplist");
	btnPopulateShoplist->fillSpaceHorizontally();
	btnPopulateShoplist->addButtonListener(this);
	btnPopulateShoplist->setFontSize(Styler::szf20);
	lContent->addChild(btnPopulateShoplist);

	Label* lbcItems = new Label("Shoplist items:");
	lbcItems->fillSpaceHorizontally();
	lbcItems->setFontSize(Styler::szf18);
	lContent->addChild(lbcItems);

	lvShoplistItems = new ListView();
	lvShoplistItems->fillSpaceHorizontally();
	lvShoplistItems->fillSpaceVertically();
	lvShoplistItems->addListViewListener(this);
	lContent->addChild(lvShoplistItems);

	lMain->addChild(lContent);

	setMainWidget(lMain);
}

void ScreenEditShoplist::buttonClicked(Widget* button) {
//	if(button == btnAccept){
//		if(ebShoplistName->getText().length() == 0){
//			shoplist_.setName("nonamelist");
//		}else{
//			shoplist_.setName(ebShoplistName->getText());
//		}
//		dictionary_.incrementItemsUsageByShoplist(shoplist_);
////			maMessageBox("dictionary after new list", dictionary_.toStringFull().c_str());
//		callbackDone_(dictionary_, shoplist_);
//		parent_->show();
//	}else if(button == btnDecline){
//		parent_->show();
//	}else if(button == btnPopulateShoplist){
//		shoplist_.setName(ebShoplistName->getText());
//		scrPopulateShoplist->setShoplist(shoplist_);
//		scrPopulateShoplist->show();
//	}
}

void ScreenEditShoplist::editBoxReturn(EditBox* editBox) {
}

//void ScreenEditShoplist::setCallback(
//		void (*callback)(Shoplist455::Dictionary dictionary,
//				Shoplist455::Shoplist shoplist)) {
//	callbackDone_ = callback;
//}

void ScreenEditShoplist::updateShoplistInfo() {
	String sBuff;
	sBuff += STR_LIST_COUNT;
	sBuff += Convert::toString(shoplist_.getSize());
	lbListItemsCount->setText(sBuff.c_str());
//	ebShoplistName->setText(shoplist_.getName());
}

void ScreenEditShoplist::setShoplist(Shoplist455::Shoplist shoplist) {
	shoplist_ = shoplist;
	updateShoplistInfo();
	renderShoplist();
}

//void ScreenEditShoplist::setDictionary(Shoplist455::Dictionary dictionary) {
//	dictionary_ = dictionary;
//	updateDictionary();
//}
//
//void ScreenEditShoplist::updateDictionary() {
//	scrPopulateShoplist->setDataStructs(dictionary_, shoplist_);
//}

void ScreenEditShoplist::resetEditboxes() {
	ebShoplistName->setEnabled(false);
	ebShoplistName->setVisible(false);

	ebShoplistName->setVisible(true);
	ebShoplistName->setEnabled(true);
}

void ScreenEditShoplist::renderShoplist() {
	lvShoplistItems->setEnabled(false);

	while(lvShoplistItems->getChild(0) != NULL){
		lvShoplistItems->removeChild(lvShoplistItems->getChild(0));
	}

	for(int i = 0; i < shoplist_.getSize(); i++){
//		Label* l = new Label(Convert::toString(i + 1) + " " + shoplist_.getItem(i).type + ":" + shoplist_.getItem(i).name);
//		l->fillSpaceHorizontally();
//		l->setFontSize(Styler::szf16);
//		l->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
//		lvShoplistItems->addChild(l);
	}

	lvShoplistItems->setEnabled(true);
}

void ScreenEditShoplist::listViewItemClicked(ListView* listView, int index) {
	shoplist_.removeAt(index);
	lvShoplistItems->removeChild(lvShoplistItems->getChild(index));
	updateShoplistInfo();
}

//void callbackShoplistPopulate(
//		Shoplist455::Dictionary dictionary, Shoplist455::Shoplist shoplist) {
//	transScreenEditShoplist->dictionary_ = dictionary;
//	transScreenEditShoplist->shoplist_ = shoplist;
//	transScreenEditShoplist->updateShoplistInfo();
//	transScreenEditShoplist->renderShoplist();
//}
