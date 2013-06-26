#ifndef SCREENPOPULATESHOPLIST_H_
#define SCREENPOPULATESHOPLIST_H_

#include "tools/Styler.h"
#include "tools/UIAssist.h"
#include "tools/Convert.h"

#include "datastructs/Shoplist.h"
#include "datastructs/Dict.h"

#include <NativeUI/Widgets.h>
#include <MAUtil/String.h>

using namespace NativeUI;
using namespace MAUtil;
using Shoplist455::Dict;


class ScreenPopulateShoplist: public Screen//,
//		public EditBoxListener,
//		public ButtonListener,
//		public ScreenListener,
//		public ListViewListener
{
public:
	ScreenPopulateShoplist(/*Shoplist455::Shoplist slist, */Screen* parent = NULL);
	~ScreenPopulateShoplist();

	void hide();
//	void setDataStructs(Shoplist455::Dict dict,
//			Shoplist455::Shoplist slist);
//	void setShoplist(Shoplist455::Shoplist shoplist);
//	void setCallback(
//			void (*callback)(Shoplist455::Dict Dict,
//					Shoplist455::Shoplist shoplist));

private:
	Screen* parent_;
	Shoplist455::Dict Dict_;
	Shoplist455::Dict DictInit_;
	Shoplist455::Shoplist shoplist_;

	void (*callbackDone_)(Shoplist455::Dict Dict,
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

	//void addItemToShoplist(ShoplistItem item);
	void createUI();
//	void dbgAct();
//	void filtrateByShoplist();
//	void filtrateDict();
//	void setEbLayoutDefaultBackground(EditBox* editbox);
//	void renderDict();
//	void renderShoplist();
//	void updateScreenLabel();
//	void fillList();
//	void clearList();

//	virtual void editBoxTextChanged(EditBox* editBox,
//			const MAUtil::String& text);
//	virtual void editBoxEditingDidBegin(EditBox* editBox);
//	virtual void editBoxEditingDidEnd(EditBox* editBox);
//	virtual void editBoxReturn(EditBox* editBox);
//	virtual void buttonClicked(Widget* button);
//	virtual void optionsMenuItemSelected(Screen* screen, int index);
//	virtual void listViewItemClicked(ListView* listView, int index);
};

#endif /* SCREENPOPULATESHOPLIST_H_ */

