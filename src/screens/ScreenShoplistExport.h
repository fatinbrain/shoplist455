#ifndef SCREENSHOPLISTEXPORT_H_
#define SCREENSHOPLISTEXPORT_H_

#include "tools/Styler.h"
#include "tools/UIAssist.h"

#include <NativeUI/Widgets.h>
#include <MAUtil/String.h>

using namespace NativeUI;
using namespace MAUtil;


class ScreenShoplistExport:public Screen,
	public ButtonListener,
	public KeyListener{
public:
	ScreenShoplistExport(Screen* parent = NULL);
	~ScreenShoplistExport();

	void hide();
	void activate();
	void setText(const String textToSet);

private:
	Screen* parent_;

	VerticalLayout* lMain;
	Label* lbMain;
	Button* btnAccept;
//	Button* btnDecline;
	EditBox* ebShoplistText;

	void createUI();
	
	virtual void buttonClicked(Widget* button);
	virtual void keyPressEvent(int keyCode, int nativeCode);
};


#endif /* SCREENGETSHOPLISTTEXT_H_ */
