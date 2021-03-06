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
	items_.add(simplifyString(item));
}


void Shoplist::clear() {
	items_.clear();
}

String Shoplist::toString() const {

	if(items_.size() == 0) return "|";

	String sBuff = "";

	for(int i = 0; i < items_.size(); i++){
		sBuff += simplifyString(items_[i]);
		sBuff += ",";
	}

	//sBuff = sBuff.substr(0, sBuff.length() - 1);
	sBuff += "|";
//	if(sBuff.length() > 0){
//		sBuff[sBuff.length()-1] = '|';
//	}

//	maMessageBox("shoplist2text:", sBuff.c_str());
	return sBuff;
}

void Shoplist::parse(const String strToParse) {
	String str = strToParse;

	if(str.length() < MIN_SHOPLIST_LENGHT){
		return;
	}

//	if(str[str.length() - 1] == '|'){
//		str = str.substr(0, str.length() - 2);
//	}

	this->clear();

	items_ = splitString(strToParse, ',');


	if(items_[items_.size() -1].find("|") != String::npos){
		items_.remove(items_.size() - 1);
	}
}


String Shoplist::getItem(const int index)const{
	return items_[index];
}


int Shoplist::size() const {
	return items_.size();
}
