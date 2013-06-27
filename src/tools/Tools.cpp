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

String simplifyString(const String s) {
	WString sBuff = L"";
	WString sBuff2 = L"";
	String rez = "";

		//transform to widestring
	for(int i = 0; i < s.length(); i++){
		sBuff += s[i];
	}

		//cut space at begin
	int pos = 0;
	while(pos < sBuff.length() && isspace(sBuff[pos])){
		pos++;
	}
	sBuff = sBuff.substr(pos);

		//cut space at end
	pos = sBuff.length() - 1;
	while(pos > 0 && isspace(sBuff[pos])){
		pos--;
	}
	sBuff = sBuff.substr(0, pos + 1);


		//cut space inside
	bool skip = false;
	for(int i = 0; i < sBuff.length(); i++){
		if(!isspace(sBuff[i])){
			skip = false;
			sBuff2 += sBuff[i];
		}else{
			if(!skip){
				sBuff2 += sBuff[i];
				skip = true;
			}
		}
	}

		//transform to string
	for(int i = 0; i < sBuff.length(); i++){
		rez += sBuff2[i];
	}

	return rez;
}
