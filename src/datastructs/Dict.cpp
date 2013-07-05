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

	return rez;
}

void Dict::parse(const String stringToParse) {
	//printf(">parse<\n");

	if(stringToParse == "") return;

	Vector<String> vsItems = splitString(stringToParse, ',');
	Vector<String> vsBuff;
	String sBuff;

	for(int i = 0; i < vsItems.size(); i++){
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

	if(buff.first != ""){
		items_.add(buff);
	}
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

void Shoplist455::Dict::addItem(const p_si item) {
	bool exist = false;

	for(int i = 0; i < items_.size() && !exist; i++){
		if(items_[i].first == item.first){
			exist = true;
		}
	}

	if(!exist){
		items_.add(p_si(item.first, item.second));
	}
}

void Dict::remove(const String itemName) {
	for(int i = 0; i < items_.size(); i++){
		if(items_[i].first == itemName){
			items_.remove(i);
		}
	}
}

p_si Shoplist455::Dict::getItem(const int index)const {
	if(index >= 0 && index < items_.size()){
		return items_[index];
	}

	return p_si("", -1);
}

void Shoplist455::Dict::sortDictByUsage() {
	if(items_.size() < 1) return;

	bool exchanged = true;

	while(exchanged){

		exchanged = false;

		for(int i = 0; i < items_.size() - 1; i++){

			if(items_[i].second < items_[i+1].second){
					//swap items if second item has bigger usage
				swapItems(items_[i], items_[i+1]);
				exchanged = true;

			}else if(items_[i].second == items_[i+1].second){

				if(items_[i].first > items_[i+1].first){
						//if both items has equal usage, exchange on alpha basis
					swapItems(items_[i], items_[i+1]);
					exchanged = true;
				}
			}
		}
	}
}

void Shoplist455::Dict::sordDictByAlpha() {
	if(items_.size() < 1) return;

	bool exchanged = true;

	while(exchanged){
		exchanged = false;
		for(int i = 0; i < items_.size() - 1; i++){
			if(items_[i].first > items_[i+1].first){
				swapItems(items_[i], items_[i+1]);
				exchanged = true;
			}
		}
	}
}

void Shoplist455::Dict::filtrateByShoplist(const Shoplist455::Shoplist shoplist) {
	int shoplistSize = shoplist.getSize();
	for(int i = 0; i < items_.size(); i++){
		for(int j = 0; j < shoplistSize; j++){
			if(shoplist.getItem(j) == items_[i].first){
				items_.remove(i);
			}
		}
	}
}

void Shoplist455::Dict::filtrateByItem(const String filterString) {
	if(filterString == "") return;

	for(int i = items_.size() - 1; i != -1; i--){
		if(items_[i].first.find(filterString) == String::npos){
			items_.remove(i);
		}
	}
}

void Shoplist455::Dict::adsorbShoplist(const Shoplist455::Shoplist shoplist) {
	int shoplistSize = shoplist.getSize();
	if(!shoplistSize) return;

	bool newItem;

	for(int i = 0; i < shoplistSize; i++){
		newItem = true;

		for(int j = 0; j < items_.size() && newItem; j++){
			if(items_[j].first == shoplist.getItem(i)){
				newItem = false;
			}
		}

		if(newItem){
			items_.add(p_si(shoplist.getItem(i), 1));
		}
	}
}

void Shoplist455::Dict::dropStat() {
	for(int i = 0; i < items_.size(); i++){
		items_[i].second = 0;
	}
}

void Shoplist455::Dict::increaseUsageByName(const String itemName,
		const int incrementValue) {
	for(int i = 0; i < items_.size(); i++){
		if(items_[i].first == itemName){
			items_[i].second++;
			break;
		}
	}
}

void Shoplist455::Dict::swapItems(p_si& item1, p_si& item2) {
	p_si buff;

	buff = item1;
	item1 = item2;
	item2 = buff;
}
