/* Dict.h @24.06.2013 */

#ifndef DICT_H_
#define DICT_H_

#include <conprint.h>
#include <MAUtil/String.h>
#include "tools/Tools.h"
#include "tools/Convert.h"
#include "datastructs/Shoplist.h"

#include <MAUtil/collection_common.h>

using namespace MAUtil;

namespace Shoplist455{

typedef Pair<String, int> p_si;
typedef Vector<p_si> vp_si_t;

class Dict{

public:
	Dict();
	~Dict();

	String toString();
	void parse(const String stringToParse);

	void addItem(const String itemName, const int itemUsage = 0);
	void addItem(const p_si item);
	const int count() const;
	void clear();
	void remove(const int index);
	void remove(const String itemName);
	p_si getItem(const int index) const;
	void sortDictByUsage();
	void sordDictByAlpha();
	void filtrateByShoplist(const Shoplist455::Shoplist shoplist);
	void filtrateByItem(const String filterString);
	void adsorbShoplist(const Shoplist455::Shoplist shoplist);
	void dropStat();
	void increaseUsageByName(const String itemName, const int incrementValue = 1);

private:
	vp_si_t items_;

	void swapItems(p_si& item1, p_si& item2);
};

}

#endif /* DICT_H_ */
