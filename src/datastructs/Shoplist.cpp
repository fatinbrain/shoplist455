/* Shoplist.cpp @30.01.2013 */

#include "Shoplist.h"

using Shoplist455::Shoplist;

Shoplist::Shoplist(){
}

Shoplist::~Shoplist() {
}

void Shoplist::removeAt(const int index) {
	items_.remove(index);
}

void Shoplist::add(const String item) {
	items_.add(item);
}


void Shoplist::clear() {
	items_.clear();
}

String Shoplist::toString() const {
	String sBuff = "";

	sBuff += ";";
	for(int i = 0; i < items_.size(); i++){
		sBuff += items_[i];
		sBuff += ",";
	}
	if(sBuff.length() > 0){
		sBuff[sBuff.length()-1] = '|';
	}

	return sBuff;
}

void Shoplist::parse(const String strToParse) {
	String str = strToParse;

	if(str.length() < MIN_SHOPLIST_LENGHT){
		return;
	}

	if(str[str.length() - 1] == '|'){
		str = str.substr(0, str.length() - 1);
	}

	this->clear();

	String itemsString;
	if(str.find(";") == String::npos){
		itemsString = str;
	}else{
		itemsString = str.substr(str.find(";") + 1, str.length() - str.find(";") - 1);
	}

//	maMessageBox("itemsstirng::", itemsString.c_str());
	Vector<String> items = splitString(itemsString, ',');
	//printf("!!![%s]:%d\n", itemsString.c_str(), items.size());

	String sliBuff;
	for(int i = 0; i < items.size(); i++){
//		printf("***%d[%s]\n", i , items[i].c_str());
//		sliBuff.parse(items[i]);
		sliBuff = items[i];
		items_.add(sliBuff);
//		if(i == 0){
//			String s;
//			s = "itemtoparse:" +items[i] + "\n";
//			s += "parseditem:" + sliBuff.toString();
////			maMessageBox("item0stringtoparse::", s.c_str());
//		}
	}
}


String Shoplist::getItem(const int index) {
	return items_[index];
}


int Shoplist::getSize() const {
	return items_.size();
}
