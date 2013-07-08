#ifndef SCREENPOPULATESHOPLIST_H_
#define SCREENPOPULATESHOPLIST_H_

#include "tools/Styler.h"
#include "tools/UIAssist.h"
#include "tools/Convert.h"
#include "tools/StorageWorks.h"

#include "datastructs/Shoplist.h"
#include "datastructs/Dict.h"

#include <NativeUI/Widgets.h>
#include <MAUtil/String.h>

using namespace NativeUI;
using namespace MAUtil;
using Shoplist455::Dict;

const String DEFAULT_DICT =
        "кефир,д кефир,молоко,д молоко,сметана,сыр,творог,масло,маргарин,подсолнечное,мясо,фарш,кура,рыба,лук,лук репчатый,капуста,огурцы,морковь,горошек,петрушка,кабак,картошка,салат,помидор,чеснок,бананы,яблоки,лимон,хлеб,батон,мука,сдоба,гречка,овес,рис,манка,перловка,пшено,д яблоки,д капуста,чай,шоколад";
const String STORAGE_DICT = "sl455dict";

class ScreenPopulateShoplist: public Screen,
        public ButtonListener,
        public ScreenListener,
        public EditBoxListener,
        public ListViewListener,
        public KeyListener {
public:
    ScreenPopulateShoplist(Screen* parent = NULL);
    ~ScreenPopulateShoplist();

    void hide();
    void activate();
    void setShoplist(Shoplist455::Shoplist shoplist);
    void setCallback(void (*callback)(Shoplist455::Shoplist shoplist));

private:
    Screen* parent_;
    Shoplist455::Dict dictWork_;
    Shoplist455::Dict dictOrig_;
    Shoplist455::Dict dUsed_;
    Shoplist455::Dict dUnused_;
    Shoplist455::Shoplist shoplist_;

    void (*callbacker)(Shoplist455::Shoplist);

    VerticalLayout* lMain;
    Label* lbMain;
    Label* lbDbg;

    VerticalLayout* lFilter;
    HorizontalLayout* lEdit;
    Button* btnAccept;
    Button* btnDecline;
    EditBox* ebFilter;
    HorizontalLayout* lFilterCtrls;
    Button* btnClearFilter;
    Button* btnAddItem;

    ListView* lvDict;
    ListViewSection* lvsUsed;
    ListViewSection* lvsUnused;
    ListViewItem* lvi;

    void actAcceptList();
    void createUI();
    void readDict();
    void resetWorkingDict();
    void writeDict();
    void renderDict();
    void colorizeFilter();
    void buttonAvailbilityCheck();

    virtual void buttonClicked(Widget* button);
    virtual void optionsMenuItemSelected(Screen* screen, int index);
    virtual void editBoxReturn(EditBox* editBox);
    virtual void keyPressEvent(int keyCode, int nativeCode);
    virtual void editBoxTextChanged(EditBox* editBox,
            const MAUtil::String& text);

    virtual void segmentedListViewItemClicked(ListView* listView,
            int sectionIndex, int itemIndex);
};

#endif /* SCREENPOPULATESHOPLIST_H_ */

