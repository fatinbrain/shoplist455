/* Dict.cpp @24.06.2013 */

#include "Dict.h"

using namespace Shoplist455;


Dict::Dict() {
}

Dict::~Dict() {
}

String Dict::toString() {
	printf(">toString<\n");

	String rez = "";
	String sBuff = "";

	for(int i = 0; i < items_.size(); i++){
		sBuff = items_[i].first;
		sBuff += ":";
		sBuff += Convert::toString(items_[i].second);
		sBuff += ",";
		rez += sBuff;
	}

	//rez[rez.length()-1] = '|';
	return rez;
}

void Dict::parse(const String stringToParse) {
	printf(">parse<\n");

	if(stringToParse == "") return;

	Vector<String> vsItems = splitString(stringToParse, ',');
	Vector<String> vsBuff;
	String sBuff;


	for(int i = 0; i < vsItems.size(); i++){
		printf("%s\n", vsItems[i].c_str());

		sBuff = vsItems[i];
		if(sBuff != ""){
			vsBuff = splitString(sBuff, ':');
			if(vsBuff[0] != ""){
				addItem(simplifyString(vsBuff[0]), Convert::toInt(vsBuff[1]));
			}
		}
	}
}

void Dict::addItem(const String itemName, const int itemUsage){
	Pair<String, int> buff(itemName, itemUsage);

	items_.add(buff);
}

const int Dict::count() const {
	return items_.size();
}

void Dict::clear() {
	items_.clear();
}


void Dict::remove(const int index) {
	items_.remove(index);
}

void Dict::remove(const String itemName) {
	for(int i = 0; i < items_.size(); i++){
		if(items_[i].first == itemName){
			items_.remove(i);
		}
	}
}
