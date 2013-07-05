#include "ScreenShoplistExport.h"

ScreenShoplistExport::ScreenShoplistExport(Screen* parent):parent_(parent) {
	createUI();
}

ScreenShoplistExport::~ScreenShoplistExport() {
	Environment::getEnvironment().removeKeyListener(this);
	btnAccept->removeButtonListener(this);
}


void ScreenShoplistExport::hide() {
	if(parent_){
		parent_->show();
	}
}

void ScreenShoplistExport::createUI() {
	lMain = new VerticalLayout();
	HorizontalLayout* lTop = new HorizontalLayout();
	btnAccept = new Button();
	btnAccept->addButtonListener(this);
	lbMain = new Label("Shoplist export");

	VerticalLayout* lContent = new VerticalLayout();

	setupTopPanel(lMain, lTop, btnAccept, lbMain, /*btnDecline*/NULL, lContent);

	Label* lbHelp = new Label("\n1.copy contents\n2.transmit to partner\n3.be happy\n");
	lbHelp->fillSpaceHorizontally();
	lbHelp->wrapContentHorizontally();
	lbHelp->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
	lbHelp->setFontSize(Styler::szf18);
	lContent->addChild(lbHelp);

	ebShoplistText = new EditBox();
	ebShoplistText->setWidth(Styler::normalize(200));
	ebShoplistText->fillSpaceHorizontally();
	ebShoplistText->wrapContentHorizontally();
	lContent->addChild(ebShoplistText);

	lMain->addChild(lContent);

	setMainWidget(lMain);
}

void ScreenShoplistExport::setText(const String textToSet) {
	ebShoplistText->setText(textToSet.c_str());
}

void ScreenShoplistExport::buttonClicked(Widget* button) {
	ebShoplistText->setText("");
	parent_->show();
}

void ScreenShoplistExport::activate() {
	Environment::getEnvironment().addKeyListener(this);
	this->show();
}

void ScreenShoplistExport::keyPressEvent(int keyCode, int nativeCode) {
	if(MAK_BACK == keyCode){
		if(this->isShown()){
			hide();
		}
	}
}
