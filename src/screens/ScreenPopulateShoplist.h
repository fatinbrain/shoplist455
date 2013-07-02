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

const String DEFAULT_DICT = "мясо,молоко:7,яблоки:113,бананы:23,дет кефир,молоко,творог:100,сметана,чай,хлеб,рыба,";
const String STORAGE_DICT = "sl455dict";

class ScreenPopulateShoplist: public Screen,
		public ButtonListener,
		public ScreenListener,
		public EditBoxListener
{
public:
	ScreenPopulateShoplist(Screen* parent = NULL);
	~ScreenPopulateShoplist();

	void hide();
	void setShoplist(Shoplist455::Shoplist shoplist);


private:
	Screen* parent_;
	Shoplist455::Dict dict_;
	Shoplist455::Shoplist shoplist_;

	VerticalLayout* lMain;
	Label* lbMain;
	Label* lbDbg;

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

	void createUI();
	void readDict();
	void writeDict();
	void renderDict();


	virtual void buttonClicked(Widget* button);
	virtual void optionsMenuItemSelected(Screen* screen, int index);
	virtual void editBoxReturn(EditBox* editBox);
	virtual void editBoxTextChanged(
	            EditBox* editBox,
	            const MAUtil::String& text);
};

#endif /* SCREENPOPULATESHOPLIST_H_ */

