#ifndef SCREENEDITSHOPLIST_H_
#define SCREENEDITSHOPLIST_H_

#include "datastructs/Shoplist.h"
#include "ScreenShoplistExport.h"
#include "ScreenShoplistImport.h"
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
	ScreenEditShoplist(Screen* parent = NULL);
	~ScreenEditShoplist();

	void hide();
	void activate();
	void setShoplist(Shoplist455::Shoplist shoplist);
	void resetEditboxes();

private:
	Screen* parent_;
	Shoplist455::Shoplist shoplist_;

	VerticalLayout* lMain;
	Label* lbMain;
	Button* btnAccept;
	Button* btnDecline;
	EditBox* ebShoplistName;
	Label* lbListItemsCount;
	Button* btnPopulateShoplist;
	ListView* lvShoplistItems;

	ScreenShoplistExport* screenShoplistExport;
	ScreenShoplistImport* screenShoplistImport;


	void createUI();

	void updateShoplistInfo();
	void renderShoplist();
	void writeActivationShoplistDataToDevice();
	void callbacker(Shoplist455::Shoplist shoplist);

	virtual void buttonClicked(Widget* button);
	virtual void editBoxReturn(EditBox* editBox);
	virtual void listViewItemClicked(ListView* listView, int index);

	virtual void optionsMenuItemSelected(Screen* screen, int index);
	virtual void keyPressEvent(int keyCode, int nativeCode);

	friend void callbacker(Shoplist455::Shoplist);
};

}
#endif /* SCREENEDITSHOPLIST_H_ */

