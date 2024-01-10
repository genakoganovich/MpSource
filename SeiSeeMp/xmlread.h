#ifndef XMLREAD_H
#define XMLREAD_H

#include <QDomDocument>
#include "seisfile.h"

class XmlRead
{
private:
    QDomDocument templateDoc;
    QDomDocument infoDoc;
    QDomElement templateElem;
    QDomElement infoElem;
    int total_width;
    int left_width;
    QDomNodeList lines;

public:
    XmlRead();
    QDomDocument setContent(const QString &name, QDomDocument& doc);
    QString run(SeisFile* sf);
    static const QString TemplateXml;
    static const QString InfoXml;
};

#endif // XMLREAD_H
