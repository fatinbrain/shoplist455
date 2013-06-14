#include "ScreenEditShoplist.h"

using namespace Shoplist455;

ScreenEditShoplist* transScreenEditShoplist;

ScreenEditShoplist::ScreenEditShoplist
	(Screen* parent):
	parent_(parent){
//	transScreenEditShoplist = this;
//	scrPopulateShoplist = new ScreenPopulateShoplist(dictionary_, shoplist_, this);
//	scrPopulateShoplist->setCallback(callbackShoplistPopulate);
	createUI();
//	renderShoplist();
//	acceptExit = true;
}

ScreenEditShoplist::~ScreenEditShoplist() {
}


void ScreenEditShoplist::hide() {

	Environment::getEnvironment().removeKeyListener(this);

	if(parent_){
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

//	Label* lbcItems = new Label("Shoplist items:");
//	lbcItems->fillSpaceHorizontally();
//	lbcItems->setFontSize(Styler::szf18);
//	lContent->addChild(lbcItems);

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
	Environment::getEnvironment().removeKeyListener(this);

//	acceptExit = false;

	if(button == btnAccept){
		parent_->show();
		writeActivationShoplistDataToDevice();
	}else if(button == btnDecline){
		parent_->show();
	}

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
		Label* l = new Label(Convert::toString(i + 1) + " " + shoplist_.getItem(i));
		l->fillSpaceHorizontally();
		l->setFontSize(Styler::szf16);
		l->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
		lvShoplistItems->addChild(l);
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

void ScreenEditShoplist::writeActivationShoplistDataToDevice() {
	StorageWorks sw2(STORE_INSHOP_ACTIVE);
	Shoplist slBuff = shoplist_;
	sw2.write(slBuff.toString());

	StorageWorks sw(STORE_INSHOP_TOBUY);
	sw.write(slBuff.toString());
}

void Shoplist455::ScreenEditShoplist::optionsMenuItemSelected(Screen* screen,
		int index) {
	switch (index) {
		case 0:
			shoplist_.clear();
			renderShoplist();
			updateShoplistInfo();
			break;
		case 1:
//			maMessageBox("act", "export");
			if(!screenShoplistExport){
				screenShoplistExport = new ScreenShoplistExport(this);
			}
			screenShoplistExport->setText(shoplist_.toString());
			screenShoplistExport->show();
			break;
		case 2:
			maMessageBox("act", "import");
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
//	acceptExit = false;

//	maMessageBox("key", "inner");

	if (MAK_BACK == keyCode)
	{
		if(parent_){
			parent_->show();
		}
	}
}
