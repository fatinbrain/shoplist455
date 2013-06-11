#ifndef SCREENMAIN_H_
#define SCREENMAIN_H_

#include "screens/ScreenInShop.h"
//#include "ScreenEditShoplist.h"
#include "tools/Styler.h"
//#include "Lang.h"
#include <NativeUI/Widgets.h>
#include <MAUtil/String.h>

using namespace NativeUI;
using namespace MAUtil;

namespace shoplist455{

class ScreenMain:
	public Screen, public ButtonListener{
public:
	ScreenMain(Screen* parent = NULL);
	~ScreenMain();

	void hide();

private:
	Screen* parent_;
//	ScreenEditShoplist* scrEditShoplist;
	ScreenInShop* scrInShop;

	VerticalLayout* lMain;
	Label* lbMain;

	VerticalLayout* lMenu;
	Button* btnLists;
	Button* btnInShop;
	Button* btnExit;

	void createUI();

	virtual void buttonClicked(Widget* button);

};

}

#endif /* SCREENMAIN_H_ */

