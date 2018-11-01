#pragma once
#include <QString>

using namespace std;

//QStringÓëStringµÄ×ª»» ·ÀÖ¹ÂÒÂë
QString str2qstr(const string str) { 
	return QString::fromLocal8Bit(str.data()); 
}
string qstr2str(const QString qstr) {
	QByteArray cdata = qstr.toLocal8Bit();
	return string(cdata);
}
