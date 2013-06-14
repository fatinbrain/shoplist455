#ifndef SCREENEDITSHOPLIST_H_
#define SCREENEDITSHOPLIST_H_

#include "datastructs/Shoplist.h"
//#include "Dictionary.h"
//#include "ScreenPopulateShoplist.h"
#include "tools/Styler.h"
#include "tools/UIAssist.h"
#include "tools/StorageWorks.h"
#include "common.h"

#include <NativeUI/Widgets.h>
#include <MAUtil/String.h>

using namespace NativeUI;
using namespace MAUtil;

namespace Shoplist455{

static const String STR_LIST_COUNT = "Shoplist items count: ";

class ScreenEditShoplist: public Screen,
		public ButtonListener,
		public EditBoxListener,
		public ListViewListener,
		public KeyListener,
		public ScreenListener{

public:
	ScreenEditShoplist(/*Shoplist455::Dictionary dictionary,
			Shoplist455::Shoplist shoplist, */Screen* parent = NULL);
	~ScreenEditShoplist();

	void hide();
	void activate();
	void setShoplist(Shoplist455::Shoplist shoplist);
//	void setDictionary(Shoplist455::Dictionary dictionary);
	void resetEditboxes();

//	void setCallback(
//			void (*callback)(Shoplist455::Dictionary dictionary,
//					Shoplist455::Shoplist shoplist));

//	bool acceptExit;

private:
	Screen* parent_;
//	ScreenPopulateShoplist* scrPopulateShoplist;

	Shoplist455::Shoplist shoplist_;
//	Shoplist455::Dictionary dictionary_;
//
//	void (*callbackDone_)(Shoplist455::Dictionary dictionary,
//			Shoplist455::Shoplist shoplist);

	VerticalLayout* lMain;
	Label* lbMain;
	Button* btnAccept;
	Button* btnDecline;
	EditBox* ebShoplistName;
	Label* lbListItemsCount;
	Button* btnPopulateShoplist;
	ListView* lvShoplistItems;

	void createUI();

	void updateShoplistInfo();
//	void updateDictionary();
	void renderShoplist();
	void writeActivationShoplistDataToDevice();

	virtual void buttonClicked(Widget* button);
	virtual void editBoxReturn(EditBox* editBox);
	virtual void listViewItemClicked(ListView* listView, int index);

	virtual void optionsMenuItemSelected(Screen* screen, int index);
	virtual void keyPressEvent(int keyCode, int nativeCode);

//	friend void callbackShoplistPopulate(Shoplist455::Dictionary dictionary,
//			Shoplist455::Shoplist shoplist);
};

}
#endif /* SCREENEDITSHOPLIST_H_ */

