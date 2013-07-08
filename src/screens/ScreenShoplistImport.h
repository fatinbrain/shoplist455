#ifndef SCREENSHOPLISTIMPORT_H_
#define SCREENSHOPLISTIMPORT_H_

#include "datastructs/Shoplist.h"
#include "tools/Styler.h"
#include "tools/UIAssist.h"

#include <NativeUI/Widgets.h>

using namespace NativeUI;
using namespace Shoplist455;

class ScreenShoplistImport: public Screen,
        public ButtonListener,
        public EditBoxListener,
        public KeyListener {

public:
    ScreenShoplistImport(Screen* parent = NULL);
    ~ScreenShoplistImport();

    void hide();
    void activate();
    void setCallback(void (*callback)(Shoplist455::Shoplist shoplist));

private:
    Screen* parent_;
    Shoplist shoplist_;

    void (*callbackDone_)(Shoplist455::Shoplist shoplist);

    VerticalLayout* lMain;
    Label* lbMain;
    Button* btnAccept;
    Button* btnDecline;

    EditBox* ebParseFrom;
    Button* btnParse;
    Label* lbtParse;
    Label* lbParsedShoplist;

    void createUI();
//	void parseShoplist(String strToParse);
    void renderShoplist();

    virtual void buttonClicked(Widget* button);
    virtual void editBoxTextChanged(EditBox* editBox,
            const MAUtil::String& text);
    virtual void editBoxReturn(EditBox* editBox);
    virtual void keyPressEvent(int keyCode, int nativeCode);
};

#endif /* SCREENSHOPLISTIMPORT_H_ */

