/* Tools.h @30.01.2013 */
/*
 * v1.1
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <MAUtil/String.h>
#include <MAUtil/Vector.h>
#include <mactype.h>

using namespace MAUtil;

Vector<String> splitString(const String s, const char splitter);
String simplifyString(const String s);


#endif /* TOOLS_H_ */
