#include "ScreenPopulateShoplist.h"

using Shoplist455::Dict;

ScreenPopulateShoplist::ScreenPopulateShoplist(/*Shoplist455::Shoplist slist, */Screen* parent){
	createUI();
//	updateScreenLabel();

//	filtrateDict();
//	renderDict();

}

ScreenPopulateShoplist::~ScreenPopulateShoplist() {
}

void ScreenPopulateShoplist::hide() {
	if (parent_) {
		parent_->show();
	}
}

void ScreenPopulateShoplist::createUI() {

	addOptionsMenuItem("debug");
//	addScreenListener(this);

	lMain = new VerticalLayout();
	HorizontalLayout* lTop = new HorizontalLayout();
	btnAccept = new Button();
//	btnAccept->addButtonListener(this);
//	lbMain = new Label("TS_POPSHOP_FILLSHOPLIST));
	lbMain = new Label("TS_POPSHOP_FILLSHOPLIST");
	btnDecline = new Button();
//	btnDecline->addButtonListener(this);
	setupTopPanel(lMain, lTop, btnAccept, lbMain, btnDecline, NULL);

	lvDict = new ListView();
	lvDict->fillSpaceHorizontally();
	lvDict->fillSpaceVertically();
//	lvDict->addListViewListener(this);
	lMain->addChild(lvDict);

	///filter/new item edit boxes and add button
	VerticalLayout* lEdits = new VerticalLayout();
	lEdits->setScrollable(true);
	lEdits->fillSpaceHorizontally();
	lEdits->setBackgroundColor(Styler::clPopoulateEditsBG);
	lEdits->setPaddingBottom(0);
	lEdits->setPaddingTop(0);

	///type edit field
	lType = new HorizontalLayout();
	lType->fillSpaceHorizontally();
	lType->setPaddingBottom(0);
//	lType->setPaddingTop(0);
	lType->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);
	Label* lbType = new Label("TS_POPSHOP_TYPE");
	lbType->setFontSize(Styler::szf16);
	lType->addChild(lbType);

	ebItemType = new EditBox();
//	ebItemType->addEditBoxListener(this);
	ebItemType->fillSpaceHorizontally();
	lType->addChild(ebItemType);

	btnTypeEbClear = new Button();
	btnTypeEbClear->setText("TS_POPSHOP_CLEAR");
//	btnTypeEbClear->addButtonListener(this);
	lType->addChild(btnTypeEbClear);

	lEdits->addChild(lType);

	///name edit field
	lName = new HorizontalLayout();
	lName->fillSpaceHorizontally();
	lName->setPaddingBottom(0);
	lName->setPaddingTop(0);
	lName->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);

	Label* lbName = new Label("TS_POPSHOP_NAME");
	lbName->setFontSize(Styler::szf16);
	lName->addChild(lbName);

	ebItemName = new EditBox();
//	ebItemName->addEditBoxListener(this);
	ebItemName->fillSpaceHorizontally();
	lName->addChild(ebItemName);

	btnNameEbClear = new Button();
	btnNameEbClear->setText("TS_POPSHOP_CLEAR");
//	btnNameEbClear->addButtonListener(this);
	lName->addChild(btnNameEbClear);

	lEdits->addChild(lName);

	btnAddItemToShoplist = new Button();
	btnAddItemToShoplist->setText("TS_POPSHOP_ADDITEM");
//	btnAddItemToShoplist->addButtonListener(this);
	btnAddItemToShoplist->setFontSize(Styler::szf18);
	btnAddItemToShoplist->fillSpaceHorizontally();
	lEdits->addChild(btnAddItemToShoplist);

	lMain->addChild(lEdits);

	setMainWidget(lMain);
}

//void ScreenPopulateShoplist::editBoxTextChanged(EditBox* editBox,
//		const MAUtil::String& text) {
////	filtrateDict();
////	renderDict();
//
//	///color adjust
//	if (editBox == ebItemType) {
//		if (text.length() != 0) {
//			lType->setBackgroundColor(
////					Dict_.items.size() > 0 ? Styler::clPopoulateGoodBG : Styler::clPopoulateBadBG);
//		} else {
//	//		setEbLayoutDefaultBackground(editBox);
//		}
//	} else if (editBox == ebItemName) {
//		if (text.length() != 0) {
//			lName->setBackgroundColor(
//		//			Dict_.items.size() > 0 ? Styler::clPopoulateGoodBG : Styler::clPopoulateBadBG);
//		} else {
//			setEbLayoutDefaultBackground(editBox);
//		}
//	}
//}

//void ScreenPopulateShoplist::editBoxReturn(EditBox* editBox) {
//	setEbLayoutDefaultBackground(editBox);
//}

//void ScreenPopulateShoplist::updateScreenLabel() {
//	lbMain->setText("TS_POPSHOP_ITEMSINLIST) + Convert::toString(shoplist_.getSize()));
//}
//
//void ScreenPopulateShoplist::renderDict() {
//	fillList();
//}

//void ScreenPopulateShoplist::buttonClicked(Widget* button) {
//	if (button == btnAddItemToShoplist) {
//		///new item create
//		String sType = ebItemType->getText();
//		String sName = ebItemName->getText();
//		if (sType.length() != 0 || sName.length() != 0) {
//			ShoplistItem sli(sType, sName);
//			updateScreenLabel();
//			DictInit_.items.add(sli);
//			ebItemType->setText("");
//			ebItemName->setText("");
//		}
//	} else if (button == btnAccept) {
//		ASSERT_MSG(callbackDone_ != NULL, "empty callback");
//		callbackDone_(DictInit_, shoplist_);
//		parent_->show();
//	} else if (button == btnDecline) {
//		///??? ask user if he sure to clear list
//
//		shoplist_.clear();
//
//		ASSERT_MSG(parent_ != NULL, "empty parent");
//		parent_->show();
//	} else if (button == btnTypeEbClear) {
//		ebItemType->setText("");
//		setEbLayoutDefaultBackground(ebItemType);
//	} else if (button == btnNameEbClear) {
//		ebItemName->setText("");
//		setEbLayoutDefaultBackground(ebItemName);
//	}
//}
//
//void ScreenPopulateShoplist::setDataStructs(Shoplist455::Dict Dict,
//		Shoplist455::Shoplist shoplist) {
//	Dict_ = Dict;
//	DictInit_ = Dict;
//	shoplist_ = shoplist;
//	renderDict();
//}

//void ScreenPopulateShoplist::addItemToShoplist(ShoplistItem item) {
//	shoplist_.add(item);
//	updateScreenLabel();
//}

//void ScreenPopulateShoplist::editBoxEditingDidBegin(EditBox* editBox) {
//}
//
//void ScreenPopulateShoplist::editBoxEditingDidEnd(EditBox* editBox) {
////	setEbLayoutDefaultBackground(editBox);
//}

//void ScreenPopulateShoplist::setEbLayoutDefaultBackground(EditBox* editbox =
//		NULL) {
//	if (editbox != NULL) {
//		if (editbox == ebItemName) {
//			lName->setBackgroundColor(Styler::clPopoulateEditsBG);
//		} else if (editbox == ebItemType) {
//			lType->setBackgroundColor(Styler::clPopoulateEditsBG);
//		}
//	} else {
//		lType->setBackgroundColor(Styler::clPopoulateEditsBG);
//		lName->setBackgroundColor(Styler::clPopoulateEditsBG);
//	}
//}

//
//void ScreenPopulateShoplist::filtrateDict() {
//	String fltrType = ebItemType->getText();
//	String fltrName = ebItemName->getText();
//
//	Dict_ = DictInit_;
//
//	String sBuffType;
//	String sBuffName;
//	for (int i = 0; i < Dict_.items.size(); i++) {
//		sBuffType = Dict_.items[i].type;
//		sBuffName = Dict_.items[i].name;
//
//		if (fltrType.length() > 0 && sBuffType.find(fltrType) == String::npos) {
//			Dict_.items.remove(i);
//			i--;
//		} else {
//			if (fltrName.length() > 0
//					&& sBuffName.find(fltrName) == String::npos) {
//				Dict_.items.remove(i);
//				i--;
//			}
//		}
//	}
//
//	filtrateByShoplist();
//}
//
//void ScreenPopulateShoplist::filtrateByShoplist() {
//	bool filtrate;
//	for (int i = 0; i < Dict_.items.size(); i++) {
//		filtrate = false;
//
//		for (int j = 0; j < shoplist_.getSize() && !filtrate; j++) {
//			String sType = shoplist_.getItem(j).type;
//			String sName = shoplist_.getItem(j).name;
//			String ssType = Dict_.items[i].type;
//			String ssName = Dict_.items[i].name;
//			if ((ssType == sType) && (ssName == sName)) {
//				filtrate = true;
//			}
//		}
//
//		if (filtrate) {
//			Dict_.items.remove(i);
//			i--;
//		}
//	}
//}

//void ScreenPopulateShoplist::optionsMenuItemSelected(Screen* screen,
//		int index) {
//	switch (index) {
//	default:
//		dbgAct();
//		break;
//	}
//}
//
//void ScreenPopulateShoplist::dbgAct() {
//	maMessageBox("debug action", "\nfiltrating directory\n");
//	filtrateDict();
//	renderDict();
//}
//
//void ScreenPopulateShoplist::renderShoplist() {
//	updateScreenLabel();
//}
//
//void ScreenPopulateShoplist::setCallback(
//		void (*callback)(Shoplist455::Dict Dict,
//				Shoplist455::Shoplist shoplist)) {
//	callbackDone_ = callback;
//}
//
//void ScreenPopulateShoplist::setShoplist(Shoplist455::Shoplist shoplist) {
//	shoplist_ = shoplist;
//	renderShoplist();
//	filtrateDict();
//	renderDict();
//}
//
//void ScreenPopulateShoplist::clearList() {
//	while (lvDict->getChild(0) != NULL) {
//		lvDict->removeChild(lvDict->getChild(0));
//	}
//}
//
//void ScreenPopulateShoplist::fillList() {
//	lvDict->setEnabled(false);
//	clearList();
//	Dict_.sortByUsage(false);
//	for (int i = 0; i < Dict_.items.size(); i++) {
//		HorizontalLayout* lItem = new HorizontalLayout();
//		lItem->fillSpaceHorizontally();
//		lItem->setChildHorizontalAlignment(MAW_ALIGNMENT_LEFT);
//		lItem->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);
//
//		String sBuff;
//		Label* lbType = new Label("[" + Dict_.items[i].type + "] ");
//		lbType->setFontSize(Styler::szf16);
//		lbType->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
//		lbType->setBackgroundColor(Styler::clListsLabelGray);
//		lItem->addChild(lbType);
//
//		Label* l = new Label(Dict_.items[i].name.c_str());
//		l->setFontSize(Styler::szf18);
//		l->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
//		l->fillSpaceHorizontally();
//		lItem->addChild(l);
//
//		Label* lNum = new Label(" " + Convert::toString(Dict_.items[i].usage));
//		lNum->setFontSize(Styler::szf16);
//		lNum->setBackgroundColor(Styler::clListsLabelDarkGray);
//		lNum->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
//		lItem->addChild(lNum);
//
//		lvDict->addChild(lItem);
//	}
//	lvDict->setEnabled(true);
//}

//void ScreenPopulateShoplist::listViewItemClicked(ListView* listView,
//		int index) {
////	addItemToShoplist(Dict_.items[index]);
////	filtrateDict();
////	lvDict->removeChild(lvDict->getChild(index));
//}