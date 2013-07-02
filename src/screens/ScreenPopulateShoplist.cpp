#include "ScreenPopulateShoplist.h"

using Shoplist455::Dict;

ScreenPopulateShoplist::ScreenPopulateShoplist(Screen* parent):
	parent_(parent){

	createUI();
	readDict();
	renderDict();
}

ScreenPopulateShoplist::~ScreenPopulateShoplist() {
}

void ScreenPopulateShoplist::hide() {
	if (parent_) {
		parent_->show();
	}
}

void ScreenPopulateShoplist::createUI() {
	addOptionsMenuItem("Drop stat");
	addOptionsMenuItem("Export dict");
	addOptionsMenuItem("Import dict");

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

	lvsUsed = new ListViewSection(LIST_VIEW_SECTION_TYPE_SEGMENTED);
	lvsUsed->setHeaderFontSize(12);
	lvsUsed->setFooterFontSize(1);
	lvsUsed->setHeaderTextHorizontalAlignment(MAW_ALIGNMENT_RIGHT);
	lvsUsed->setHeaderText("Used items");

	lvsUnused = new ListViewSection(LIST_VIEW_SECTION_TYPE_SEGMENTED);
	lvsUnused->setHeaderFontSize(12);
	lvsUnused->setFooterFontSize(1);
	lvsUnused->setHeaderTextHorizontalAlignment(MAW_ALIGNMENT_RIGHT);
	lvsUnused->setHeaderText("Unused items");

	lvDict->addChild(lvsUsed);
	lvDict->addChild(lvsUnused);

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
	lFilterCtrls->addChild(btnClearFilter);

	lFilter->addChild(lFilterCtrls);
	lMain->addChild(lFilter);

	setMainWidget(lMain);
}


void ScreenPopulateShoplist::readDict() {
#if 0
	StorageWorks sw(STORAGE_DICT);
	String strDict = sw.read();

	if(strDict.length() > 0){
		strDict = strDict.substr(0, strDict.find("|"));
		dict_.parse(strDict);
//		maMessageBox("device dict", dict_.toString().c_str());
	}else{
//		maMessageBox("initstr", DEFAULT_DICT.c_str());
		dict_.parse(DEFAULT_DICT);
//		maMessageBox("default dict", dict_.toString().c_str());
	}
#else
	dict_.parse(DEFAULT_DICT);
	//maMessageBox("default dict items count", Convert::toString(dict_.count()).c_str());
#endif
}

void ScreenPopulateShoplist::writeDict() {
	StorageWorks sw(STORAGE_DICT);
	String writeBuff = dict_.toString();
	writeBuff += "|";
	sw.write(writeBuff);
}

void ScreenPopulateShoplist::renderDict() {
	Dict dUsed;
	Dict dUnused;


	dict_.asorbShoplist(shoplist_);
	dict_.filtrateByShoplist(shoplist_);
	dict_.filtrateByItem(ebFilter->getText());

		//split dict into used and unused sections
	for(int i = 0; i < dict_.count(); i++){
		if(dict_.getItem(i).second > 0){
			dUsed.addItem(dict_.getItem(i));
		}else{
			dUnused.addItem(dict_.getItem(i));
		}
	}

//	String dbg = "us:";
//	dbg += Convert::toString(dUsed.count());
//	dbg += " un:";
//	dbg += Convert::toString(dUnused.count());
//
//	maMessageBox("render counts", dbg.c_str());

	dUsed.sortDictByUsage();
	dUnused.sordDictByAlpha();


		//render used items
	lvsUsed->setVisible(dUsed.count() > 0);
//	for(int i = 0; i < lvsUsed->countChildWidgets(); i++){
//		lvsUsed->removeItem(0);
//	}
	while(lvsUsed->getChild(0)){
		lvsUsed->removeItem(0);
	}

	for(int i = 0; i < dUsed.count(); i++){
		lvi = new ListViewItem();
		String name = dUsed.getItem(i).first;
		String usage = Convert::toString(dUsed.getItem(i).second);

		HorizontalLayout* lItem = new HorizontalLayout();
		lItem->fillSpaceHorizontally();

		Label* lbName = new Label();
		lbName->setFontSize(15);
		lbName->fillSpaceHorizontally();
		lbName->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
		lbName->setText(name);

		Label* lbUsage = new Label();
		lbUsage->setText(usage);
		lbUsage->setFontSize(16);
		lbUsage->setWidth(40);
		lbUsage->setBackgroundColor(0x5555ee);

		lItem->addChild(lbName);
		lItem->addChild(lbUsage);

		lvi->addChild(lItem);

		lvsUsed->addItem(lvi);
	}

		//render unused items
	lvsUnused->setVisible(dUnused.count() > 0);
	while(lvsUnused->getChild(0)){
		lvsUnused->removeItem(0);
	}
//	for(int i = 0; i < lvsUnused->countChildWidgets(); i++){
//		lvsUnused->removeItem(0);
//	}

	for(int i = 0; i < dUnused.count(); i++){
		lvi = new ListViewItem();
		lvi->setText(dUnused.getItem(i).first.c_str());
		lvi->setHeight(17);
		lvi->setFontSize(15);
		lvsUnused->addItem(lvi);
	}
}

void ScreenPopulateShoplist::buttonClicked(Widget* button) {
	if(button == btnAccept){
		writeDict();
		parent_->show();
	}else if(button == btnDecline){
		writeDict();
		parent_->show();
	}else if(button == btnClearFilter){
		ebFilter->setText("");
	}
}

void ScreenPopulateShoplist::setShoplist(Shoplist455::Shoplist shoplist) {
	shoplist_ = shoplist;
	renderDict();
}

void ScreenPopulateShoplist::optionsMenuItemSelected(Screen* screen,
		int index) {
	maMessageBox("in future", "this feature will be available in deep future.");
	switch (index) {
		case 0:
			//drop stat
			break;
		case 1:
			//drop stat
			break;
		case 2:
			//drop stat
			break;
		default:
			break;
	}
}

void ScreenPopulateShoplist::editBoxReturn(EditBox* editBox) {
}

void ScreenPopulateShoplist::editBoxTextChanged(EditBox* editBox,
		const MAUtil::String& text) {
	renderDict();
}
