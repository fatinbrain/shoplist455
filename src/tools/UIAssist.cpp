/* UIAssist.cpp @28.02.2013 */

#include "UIAssist.h"

void setupTopPanel(VerticalLayout* lMain, HorizontalLayout* lTop,
		Button* btnAccept = NULL, Label* lbMain = NULL, Button* btnDecline = NULL,
		VerticalLayout* lContent = NULL) {

	if(lMain != NULL){
		lMain->fillSpaceHorizontally();
		lMain->fillSpaceVertically();
		lMain->setBackgroundColor(0x333333);
	}else{
		return;
	}

	if(lTop != NULL){
		lTop->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);
		lTop->setScrollable(true);
		lTop->setBackgroundColor(0x555555);
	}else{
		return;
	}

	if(btnAccept != NULL){
		btnAccept->setText("<<");
		btnAccept->setFontSize(Styler::szfTopPanelButton);
		btnAccept->setBackgroundColor(0x55aa55);
		lTop->addChild(btnAccept);
	}

	if(lbMain != NULL){
		lbMain->setFontSize(Styler::szfTopPanelLabel);
		lbMain->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		lbMain->fillSpaceHorizontally();
		lTop->addChild(lbMain);
	}

	if(btnDecline != NULL){
		btnDecline->setText(" X ");
		btnDecline->setFontSize(Styler::szfTopPanelButton);
		btnDecline->setBackgroundColor(0xaa5555);
		lTop->addChild(btnDecline);
	}


	lMain->addChild(lTop);

	if(lContent != NULL){
		lContent->fillSpaceHorizontally();
		lContent->fillSpaceVertically();
		lContent->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		Styler::setlayoutPaddings2(lContent, 0, Styler::szPaddingNormal);
	}
}
