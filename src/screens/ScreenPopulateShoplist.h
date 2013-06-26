#ifndef SCREENPOPULATESHOPLIST_H_
#define SCREENPOPULATESHOPLIST_H_

#include "Styler.h"
#include "Lang.h"
#include "UIAssist.h"
#include "Shoplist.h"
#include "ShoplistItem.h"
#include "Dictionary.h"
#include "Convert.h"
#include <NativeUI/Widgets.h>
#include <MAUtil/String.h>

using namespace NativeUI;
using namespace MAUtil;
using Shoplist455::Dictionary;
using Shoplist455::ShoplistItem;


class ScreenPopulateShoplist: public Screen,
		public EditBoxListener,
		public ButtonListener,
		public ScreenListener,
		public ListViewListener {
public:
	ScreenPopulateShoplist(Shoplist455::Dictionary dict,
			Shoplist455::Shoplist slist, Screen* parent = NULL);
	~ScreenPopulateShoplist();

	void hide();
	void setDataStructs(Shoplist455::Dictionary dict,
			Shoplist455::Shoplist slist);
	void setShoplist(Shoplist455::Shoplist shoplist);
	void setCallback(
			void (*callback)(Shoplist455::Dictionary dictionary,
					Shoplist455::Shoplist shoplist));

private:
	Screen* parent_;
	Shoplist455::Dictionary dictionary_;
	Shoplist455::Dictionary dictionaryInit_;
	Shoplist455::Shoplist shoplist_;

	void (*callbackDone_)(Shoplist455::Dictionary dictionary,
			Shoplist455::Shoplist shoplist);

	VerticalLayout* lMain;
	Label* lbMain;

	Label* lbDbg;

	HorizontalLayout* lEdit;
	Button* btnAccept;
	Button* btnDecline;
	ListView* lvDict;
	EditBox* ebItemType;
	HorizontalLayout* lType;
	Button* btnTypeEbClear;
	HorizontalLayout* lName;
	EditBox* ebItemName;
	Button* btnNameEbClear;
	Button* btnAddItemToShoplist;

	TabScreen* ts;

	void addItemToShoplist(ShoplistItem item);
	void createUI();
	void dbgAct();
	void filtrateByShoplist();
	void filtrateDictionary();
	void setEbLayoutDefaultBackground(EditBox* editbox);
	void renderDictionary();
	void renderShoplist();
	void updateScreenLabel();
	void fillList();
	void clearList();

	virtual void editBoxTextChanged(EditBox* editBox,
			const MAUtil::String& text);
	virtual void editBoxEditingDidBegin(EditBox* editBox);
	virtual void editBoxEditingDidEnd(EditBox* editBox);
	virtual void editBoxReturn(EditBox* editBox);
	virtual void buttonClicked(Widget* button);
	virtual void optionsMenuItemSelected(Screen* screen, int index);
	virtual void listViewItemClicked(ListView* listView, int index);
};

#endif /* SCREENPOPULATESHOPLIST_H_ */

