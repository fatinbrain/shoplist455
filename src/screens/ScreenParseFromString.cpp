#include "ScreenShoplistImport.h"

ScreenShoplistImport::ScreenShoplistImport(Screen* parent):parent_(parent) {
	createUI();
}

ScreenShoplistImport::~ScreenShoplistImport() {
}


void ScreenShoplistImport::hide() {
	if(parent_){
		parent_->show();
	}
}

void ScreenShoplistImport::createUI() {
	lMain = new VerticalLayout();
	HorizontalLayout* lTop = new HorizontalLayout();
	btnAccept = new Button();
	btnAccept->setVisible(false);
	btnAccept->addButtonListener(this);
	lbMain = new Label(t_(TS_PARSE_CAPTION));
	btnDecline = new Button();
	btnDecline->addButtonListener(this);
	VerticalLayout* lContent = new VerticalLayout();

	setupTopPanel(lMain, lTop, btnAccept, lbMain, btnDecline, lContent);

	ebParseFrom = new EditBox();
	ebParseFrom->fillSpaceHorizontally();
	ebParseFrom->addEditBoxListener(this);
	lContent->addChild(ebParseFrom);

	btnParse = new Button();
	btnParse->setText(t_(TS_PARSE_PARSE));
	btnParse->fillSpaceHorizontally();
	btnParse->setFontSize(Styler::szf18);
	btnParse->setEnabled(false);
	btnParse->addButtonListener(this);
	lContent->addChild(btnParse);

	lbtParse = new Label(t_(TS_PARSE_PARSEDLISTS));
	lbtParse->fillSpaceHorizontally();
	lbtParse->setFontSize(Styler::szf20);
	lContent->addChild(lbtParse);

	lbParsedShoplist = new Label(t_(TS_PARSE_NOTPARSED));
	lbParsedShoplist->fillSpaceHorizontally();
	lbParsedShoplist->setFontSize(Styler::szf18);
	lContent->addChild(lbParsedShoplist);

	lMain->addChild(lContent);

	setMainWidget(lMain);
}

void ScreenShoplistImport::buttonClicked(Widget* button) {
	if(button == btnAccept){
		shoplist_.setName(t_(TS_PARSE_PARSED));
		callbackDone_(shoplist_);
		ebParseFrom->setText("");
		shoplist_.clear();
		parent_->show();
	}else if(button == btnDecline){
		parent_->show();
	}else if(button == btnParse){
		btnAccept->setVisible(true);
		ebParseFrom->hideKeyboard();
		parseShoplist(ebParseFrom->getText());
		renderShoplist();
	}
}

void ScreenShoplistImport::editBoxTextChanged(EditBox* editBox,
		const MAUtil::String& text) {
	if(ebParseFrom->getText().length() > 0){
		btnParse->setEnabled(true);
	}else{
		btnParse->setEnabled(false);
	}
}

void ScreenShoplistImport::setCallback(
		void (*callback)(Shoplist455::Shoplist shoplist)) {
	callbackDone_ = callback;
}

void ScreenShoplistImport::parseShoplist(String strToParse) {
	shoplist_.parse(strToParse);
	if(shoplist_.getName() == ""){
		shoplist_.setName(t_(TS_NONAME));
	}
}

void ScreenShoplistImport::renderShoplist() {
	lbParsedShoplist->setText(shoplist_.toString());
}

void ScreenShoplistImport::editBoxReturn(EditBox* editBox) {
}
