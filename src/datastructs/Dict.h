/* Dict.h @24.06.2013 */

#ifndef DICT_H_
#define DICT_H_

#include <conprint.h>
#include <MAUtil/String.h>
#include "tools/Tools.h"
#include "tools/Convert.h"

//#include <MAUtil/Vector.h>
#include <MAUtil/collection_common.h>

using namespace MAUtil;

namespace Shoplist455{

typedef Vector<Pair<String, int> > vp_si_t;

class Dict{

public:
	Dict();
	~Dict();

	String toString();
	void parse(const String stringToParse);

	void addItem(const String itemName, const int itemUsage = 0);
	const int count() const;
	void clear();
	void remove(const int index);
	void remove(const String itemName);

private:
	vp_si_t items_;
};

}

#endif /* DICT_H_ */
