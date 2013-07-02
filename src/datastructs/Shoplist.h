/* Shoplist.h @30.01.2013 */

#ifndef SHOPLIST_H_
#define SHOPLIST_H_

#include "tools/Tools.h"
#include <MAUtil/String.h>
#include <MAUtil/Vector.h>

using namespace MAUtil;

namespace Shoplist455{

const int MIN_SHOPLIST_LENGHT = 3;

class Shoplist{

public:
	Shoplist();
	~Shoplist();

	void removeAt(const int index);
	void add(const String item);
	String getItem(const int index) const;
	int getSize()const;
	void clear();
	String toString() const;
	void parse(const String strToParse);

//	static Shoplist empty;
private:
	Vector<String> items_;
};

}

#endif /* SHOPLIST_H_ */
