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
}

void ScreenShoplistImport::hide() {
    Environment::getEnvironment().removeKeyListener(this);
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

    lbtParse = new Label("\n1.paste\n2.press accept button\n");
    lbtParse->fillSpaceHorizontally();
    lbtParse->setFontSize(Styler::szf20);
    lContent->addChild(lbtParse);

    ebParseFrom = new EditBox();
    ebParseFrom->fillSpaceHorizontally();
    ebParseFrom->addEditBoxListener(this);
    lContent->addChild(ebParseFrom);

    lMain->addChild(lContent);

    setMainWidget(lMain);
}

void ScreenShoplistImport::buttonClicked(Widget* button) {
    Environment::getEnvironment().removeKeyListener(this);

    if (button == btnAccept) {
        actAccept();
        parent_->show();

    } else if (button == btnDecline) {
        parent_->show();

    }
}

void ScreenShoplistImport::editBoxTextChanged(EditBox* editBox,
        const MAUtil::String& text) {
    if (ebParseFrom->getText().length() > 0) {
        btnAccept->setVisible(true);

    } else {
        btnAccept->setVisible(false);
    }
}

void ScreenShoplistImport::setCallback(
        void (*callback)(Shoplist455::Shoplist shoplist)) {
    if (callback) {
        callbackDone_ = callback;
    }
}

void ScreenShoplistImport::activate() {
    Environment::getEnvironment().addKeyListener(this);
    this->show();
}

void ScreenShoplistImport::editBoxReturn(EditBox* editBox) {
    actParse();
    actAccept();
}

void ScreenShoplistImport::actParse() {
    if(ebParseFrom->getText().length() > 0){
        shoplist_.parse(ebParseFrom->getText());
    }
}

void ScreenShoplistImport::actAccept() {
    if(shoplist_.size() == 0){
        return;
    }

    if (callbackDone_) {
        callbackDone_(shoplist_);
    } else {
        maMessageBox("Warning",
                "[screenShoplistImport]\nCallback function does not set.");
    }
    ebParseFrom->setText("");
    shoplist_.clear();
}

void ScreenShoplistImport::keyPressEvent(int keyCode, int nativeCode) {
    if (MAK_BACK == keyCode) {
        actParse();
        actAccept();
        if (this->isShown()) {
            hide();
        }
    }
}
