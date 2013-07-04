#ifndef STYLER_H_
#define STYLER_H_

#include "convert.h"
#include "maapi.h"
#include <NativeUI/Widgets.h>

using namespace NativeUI;


const double szNativeDiagonal = 400.0;

class Styler{
public:
	Styler();
	~Styler();

	static int szPaddingNormal;
	static int szfButtonBig;
	static int szfTopPanelButton;
	static int szfTopPanelLabel;
	static int szf16;
	static int szf18;
	static int szf20;
	static int szf28;

	static int clMainLayoutBG;
	static int clTopPanelBG;
	static int clTopPanelAcceptButtonBG;
	static int clTopPanelDeclineButtonBG;
	static int clPopoulateEditsBG;
	static int clPopoulateGoodBG;
	static int clPopoulateBadBG;
	static int clListsLabelGray;
	static int clListsLabelDarkGray;

	static String fnClockopia;

	static void setLayoutPaddings4(Layout* layout, const int top = -1, const int right = -1,
			const int bottom = -1, const int left = -1);
	static void setlayoutPaddings2(Layout* layout, const int top_bottom = -1,
			const int left_right = -1);
	static void setlayoutPaddings1(Layout* layout, const int all = -1);
	static int normalize(const int sz);

	static MAHandle fontClockopia;

private:
	static double scale;

	static void calcConsts();
	static void fontInit();
};


#endif /* STYLER_H_ */
