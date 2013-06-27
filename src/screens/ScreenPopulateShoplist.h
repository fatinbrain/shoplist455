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


class ScreenPopulateShoplist: public Screen,
		public ButtonListener
{
public:
	ScreenPopulateShoplist(Screen* parent = NULL);
	~ScreenPopulateShoplist();

	void hide();

private:
	Screen* parent_;
	Shoplist455::Dict Dict_;
	Shoplist455::Dict DictInit_;
	Shoplist455::Shoplist shoplist_;

	VerticalLayout* lMain;
	Label* lbMain;

	Label* lbDbg;

	HorizontalLayout* lEdit;
	Button* btnAccept;
	Button* btnDecline;
	ListView* lvDict;
	EditBox* ebFilter;
	HorizontalLayout* lFilterCtrls;
	Button* btnClearFilter;
	Button* btnAddItem;

	void createUI();
	virtual void buttonClicked(Widget* button);
};

#endif /* SCREENPOPULATESHOPLIST_H_ */

