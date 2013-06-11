#include "ScreenMain.h"

using namespace shoplist455;

ScreenMain::ScreenMain(Screen* parent) :
		parent_(parent) {
//	scrEditShoplist = new ScreenEditShoplist(this);
	scrInShop = new ScreenInShop(this);

	createUI();
}

ScreenMain::~ScreenMain() {
}

void ScreenMain::hide() {
	if (parent_) {
		parent_->show();
	}
}

void ScreenMain::createUI() {
	lMain = new VerticalLayout();
	lMain->fillSpaceHorizontally();
	lMain->fillSpaceVertically();

	String sBuff = "";
	sBuff += "..::shoplist455::..\nv0.2\n";
	sBuff += "[init2]";
	Label* lb = new Label(sBuff.c_str());
	lb->fillSpaceHorizontally();
	lb->setFontSize(Styler::szf16);
	lb->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	lMain->addChild(lb);

	lMenu = new VerticalLayout();
	lMenu->fillSpaceHorizontally();
	lMenu->fillSpaceVertically();
	Styler::setlayoutPaddings1(lMain, Styler::szPaddingNormal);

	btnLists = new Button();
//	btnLists->setText(/*"Lists"*/t_(TS_MAINMENU_LISTS));
	btnLists->setText("List");
	btnLists->setFontSize(Styler::szfButtonBig);
	btnLists->fillSpaceHorizontally();
	btnLists->addButtonListener(this);
	lMenu->addChild(btnLists);

	btnInShop = new Button();
//	btnInShop->setText(t_(TS_MAINMENU_INSHOP)/*"InShop"*/);
	btnInShop->setText("InShop");
	btnInShop->setFontSize(Styler::szfButtonBig);
	btnInShop->fillSpaceHorizontally();
	btnInShop->addButtonListener(this);
	lMenu->addChild(btnInShop);

	btnExit = new Button();
//	btnExit->setText(t_(TS_MAINMENU_EXIT)/*"Exit"*/);
	btnExit->setText("Exit");
	btnExit->setFontSize(Styler::szfButtonBig);
	btnExit->fillSpaceHorizontally();
	btnExit->addButtonListener(this);
	lMenu->addChild(btnExit);

	lMain->addChild(lMenu);

	setMainWidget(lMain);
}

void ScreenMain::buttonClicked(Widget* button) {
	if (button == btnLists) {
//		scrEditShoplist->show();
	} else if (button == btnInShop) {
//		scrInShop->updateData();
		scrInShop->show();
	} else if (button == btnExit) {
		maExit(0);
	}
}
