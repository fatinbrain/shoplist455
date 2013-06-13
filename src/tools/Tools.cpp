/* Tools.cpp @30.01.2013 */

#include "Tools.h"

Vector<String> splitString(const String s, const char splitter){
	String sBuff = "";
	String sTmp = "";
	Vector<String> rez;

	sBuff += s;
	if(sBuff[sBuff.length() + 1] != splitter){
		sBuff += splitter;
	}

	if(sBuff[0] == splitter){
		rez.add("");
	}

	int pos = 0;

	while(pos < sBuff.length()){
		if(sBuff[pos] != splitter &&
				sBuff[pos] != '\0'){
			sTmp += sBuff[pos];
		}else{
			if(sTmp.length() > 0){
				while(isspace(sTmp[0])){
					sTmp = sTmp.substr(1, sTmp.length() - 1);
				}
				rez.add(sTmp);
			}

			sTmp = "";
		}
		pos++;
	}

	return rez;
}
