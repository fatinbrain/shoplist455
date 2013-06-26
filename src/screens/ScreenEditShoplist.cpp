#include "ScreenEditShoplist.h"

using namespace Shoplist455;

ScreenEditShoplist* transScreenEditShoplist;

ScreenEditShoplist::ScreenEditShoplist
	(Screen* parent):
	parent_(parent){

	transScreenEditShoplist = this;

	createUI();
}

ScreenEditShoplist::~ScreenEditShoplist() {
	Environment::getEnvironment().removeKeyListener(this);
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

	if(button == btnAccept){
		parent_->show();
		writeActivationShoplistDataToDevice();

	}else if(button == btnDecline){
		parent_->show();

	}else if(button == btnPopulateShoplist){
		maMessageBox("future step", "willbe populated list");

	}
}

void ScreenEditShoplist::editBoxReturn(EditBox* editBox) {
}

void ScreenEditShoplist::updateShoplistInfo() {
	String sBuff;
	sBuff += STR_LIST_COUNT;
	sBuff += Convert::toString(shoplist_.getSize());
	lbListItemsCount->setText(sBuff.c_str());
}

void ScreenEditShoplist::setShoplist(Shoplist455::Shoplist shoplist) {
	shoplist_ = shoplist;
	updateShoplistInfo();
	renderShoplist();
}

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
			shoplist_.clear();
			renderShoplist();
			updateShoplistInfo();
			break;

		case 1:
			if(!screenShoplistExport){
				screenShoplistExport = new ScreenShoplistExport(this);
			}
			screenShoplistExport->setText(shoplist_.toString());
			screenShoplistExport->show();
			break;

		case 2:
			if(!screenShoplistImport){
				screenShoplistImport = new ScreenShoplistImport(this);
			}
			screenShoplistImport->setCallback(Shoplist455::callbacker);
			screenShoplistImport->show();
			break;

		default:
			break;
	}
}

void Shoplist455::ScreenEditShoplist::activate() {
	Environment::getEnvironment().addKeyListener(this);
	this->show();
}

//void Shoplist455::ScreenEditShoplist::callbacker(
//		Shoplist455::Shoplist shoplist) {
//	maMessageBox("callback", shoplist.toString().c_str());
//}

void Shoplist455::ScreenEditShoplist::keyPressEvent(int keyCode,
		int nativeCode) {
	if (MAK_BACK == keyCode)
	{
		if(parent_){
			parent_->show();
		}
	}
}

void Shoplist455::callbacker(
		Shoplist455::Shoplist shoplist) {
//	maMessageBox("callback", shoplist.toString().c_str());
	transScreenEditShoplist->shoplist_ = shoplist;
	transScreenEditShoplist->renderShoplist();
}
