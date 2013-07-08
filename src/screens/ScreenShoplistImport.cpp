#include "ScreenShoplistImport.h"

ScreenShoplistImport::ScreenShoplistImport(Screen* parent) :
        parent_(parent) {
    callbackDone_ = NULL;
    createUI();
}

ScreenShoplistImport::~ScreenShoplistImport() {
    Environment::getEnvironment().removeKeyListener(this);
    btnAccept->removeButtonListener(this);
    btnDecline->removeButtonListener(this);
    btnParse->removeButtonListener(this);
}

void ScreenShoplistImport::hide() {
    if (parent_) {
        parent_->show();
    }
}

void ScreenShoplistImport::createUI() {
    lMain = new VerticalLayout();
    HorizontalLayout* lTop = new HorizontalLayout();
    btnAccept = new Button();
    btnAccept->setVisible(false);
    btnAccept->addButtonListener(this);
    lbMain = new Label("Shoplist import");
    btnDecline = new Button();
    btnDecline->addButtonListener(this);
    VerticalLayout* lContent = new VerticalLayout();

    setupTopPanel(lMain, lTop, btnAccept, lbMain, btnDecline, lContent);

    ebParseFrom = new EditBox();
    ebParseFrom->fillSpaceHorizontally();
    ebParseFrom->addEditBoxListener(this);
    lContent->addChild(ebParseFrom);

    btnParse = new Button();
    btnParse->setText("Parse list");
    btnParse->fillSpaceHorizontally();
    btnParse->setFontSize(Styler::szf18);
    btnParse->setEnabled(false);
    btnParse->addButtonListener(this);
    lContent->addChild(btnParse);

    lbtParse = new Label("\n1.paste\n2.press parse\n3.press accept button\n\n");
    lbtParse->fillSpaceHorizontally();
    lbtParse->setFontSize(Styler::szf20);
    lContent->addChild(lbtParse);

    lbParsedShoplist = new Label("NOTPARSED");
    lbParsedShoplist->fillSpaceHorizontally();
    lbParsedShoplist->setFontSize(Styler::szf18);
    lContent->addChild(lbParsedShoplist);

    lMain->addChild(lContent);

    setMainWidget(lMain);
}

void ScreenShoplistImport::buttonClicked(Widget* button) {
    if (button == btnAccept) {
        if (callbackDone_) {
            callbackDone_(shoplist_);
        } else {
            maMessageBox("Warning",
                    "[screenShoplistImport]\nCallback function does not set.");
        }
        ebParseFrom->setText("");
        shoplist_.clear();
        parent_->show();

    } else if (button == btnDecline) {
        parent_->show();

    } else if (button == btnParse) {
        btnAccept->setVisible(true);
        ebParseFrom->hideKeyboard();
        shoplist_.parse(ebParseFrom->getText());
        renderShoplist();
    }
}

void ScreenShoplistImport::editBoxTextChanged(EditBox* editBox,
        const MAUtil::String& text) {
    if (ebParseFrom->getText().length() > 0) {
        btnParse->setEnabled(true);

    } else {
        btnParse->setEnabled(false);
    }
}

void ScreenShoplistImport::setCallback(
        void (*callback)(Shoplist455::Shoplist shoplist)) {
    if (callback) {
        callbackDone_ = callback;
    }
}

void ScreenShoplistImport::renderShoplist() {
    lbParsedShoplist->setText(shoplist_.toString());
}

void ScreenShoplistImport::activate() {
    Environment::getEnvironment().addKeyListener(this);
    this->show();
}

void ScreenShoplistImport::editBoxReturn(EditBox* editBox) {
}

void ScreenShoplistImport::keyPressEvent(int keyCode, int nativeCode) {
    if (MAK_BACK == keyCode) {
        if (this->isShown()) {
            hide();
        }
    }
}
