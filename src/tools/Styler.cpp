#include "Styler.h"

int Styler::clMainLayoutBG = 0x333333;
int Styler::clTopPanelBG = 0x555555;
int Styler::clTopPanelAcceptButtonBG = 0x55aa55;
int Styler::clTopPanelDeclineButtonBG = 0xaa5555;
int Styler::clPopoulateEditsBG = 0x555555;
int Styler::clPopoulateGoodBG = 0x006600;
int Styler::clPopoulateBadBG = 0x660000;
int Styler::clListsLabelGray = 0x555555;
int Styler::clListsLabelDarkGray = 0x444444;

int Styler::szPaddingNormal = 20;
int Styler::szfButtonBig = 40;
int Styler::szfTopPanelButton = 20;
int Styler::szfTopPanelLabel = 20;
int Styler::szf16 = 16;
int Styler::szf18 = 18;
int Styler::szf20 = 20;
int Styler::szf28 = 28;

double Styler::scale = 1.0;

String Styler::fnClockopia = "Clockopia";
MAHandle Styler::fontClockopia = 0;

Styler::Styler() {
	calcConsts();
	fontInit();
}

Styler::~Styler() {
}

void Styler::calcConsts() {
	MAExtent scrSz = maGetScrSize();
	double scrX = EXTENT_X(scrSz);
	double scrY = EXTENT_Y(scrSz);
	double diagonal = (sqrt(scrX * scrX + scrY * scrY));
	double scaleFactor = sqrt(diagonal / szNativeDiagonal);
	scale = scaleFactor;

	szPaddingNormal = static_cast<int>(scaleFactor * szPaddingNormal);
	szfButtonBig = static_cast<int>(scaleFactor * szfButtonBig);
	szfTopPanelButton = static_cast<int>(scaleFactor * szfTopPanelButton);
	szfTopPanelLabel = static_cast<int>(scaleFactor * szfTopPanelButton);
	szf16 = static_cast<int>(scaleFactor * szf16);
	szf18 = static_cast<int>(scaleFactor * szf18);
	szf20 = static_cast<int>(scaleFactor * szf20);
	szf28 = static_cast<int>(scaleFactor * szf28);
}

void Styler::setLayoutPaddings4(Layout* layout, const int top, const int right, const int bottom,
		const int left) {
	if(layout == NULL){
		return;
	}

	if(top >= 0){
		layout->setPaddingTop(top);
	}
	if(right >= 0){
		layout->setPaddingRight(right);
	}
	if(bottom >= 0){
		layout->setPaddingBottom(bottom);
	}
	if(left >= 0){
		layout->setPaddingLeft(left);
	}
}

void Styler::setlayoutPaddings2(Layout* layout, const int top_bottom,
		const int left_right) {
	if(layout == NULL){
		return;
	}

	if(top_bottom >= 0){
		layout->setPaddingTop(top_bottom);
		layout->setPaddingBottom(top_bottom);
	}
	if(left_right >= 0){
		layout->setPaddingRight(left_right);
		layout->setPaddingLeft(left_right);
	}
}

void Styler::setlayoutPaddings1(Layout* layout, const int all) {
	if(layout == NULL){
		return;
	}

	if(all >= 0){
		layout->setPaddingTop(all);
		layout->setPaddingBottom(all);
		layout->setPaddingRight(all);
		layout->setPaddingLeft(all);
	}
}

int Styler::normalize(const int sz) {
	return static_cast<int>(scale * sz);
}

void Styler::fontInit() {
	char x[128];
	int sz = maFontGetCount();

	for (int i = 0; i < sz; i++) {
		maFontGetName(i, x, 128);
	}

	fontClockopia = maFontLoadWithName(Styler::fnClockopia.c_str(), 40);
}
