/* UIAssist.cpp @28.02.2013 */

#include "UIAssist.h"

void setupTopPanel(VerticalLayout* lMain, HorizontalLayout* lTop,
		Button* btnAccept, Label* lbMain, Button* btnDecline,
		VerticalLayout* lContent) {

	lMain->fillSpaceHorizontally();
	lMain->fillSpaceVertically();
	lMain->setBackgroundColor(0x333333);

	///top panel
	lTop->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);
	lTop->setScrollable(true);
	lTop->setBackgroundColor(0x555555);

	btnAccept->setText("<<");
	btnAccept->setFontSize(Styler::szfTopPanelButton);
	btnAccept->setBackgroundColor(0x55aa55);
	lTop->addChild(btnAccept);

	lbMain->setFontSize(Styler::szfTopPanelLabel);
	lbMain->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	lbMain->fillSpaceHorizontally();
	lTop->addChild(lbMain);

	btnDecline->setText(" X ");
	btnDecline->setFontSize(Styler::szfTopPanelButton);
	btnDecline->setBackgroundColor(0xaa5555);
	lTop->addChild(btnDecline);

	lMain->addChild(lTop);

	if(lContent != NULL){
		lContent->fillSpaceHorizontally();
		lContent->fillSpaceVertically();
		lContent->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		Styler::setlayoutPaddings2(lContent, 0, Styler::szPaddingNormal);
	}
}
