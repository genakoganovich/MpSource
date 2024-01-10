#include <QFile>
#include <QFileInfo>
#include <QTextCodec>
#include <iostream>

#include "xmlread.h"


const QString XmlRead::TemplateXml = "c:/data/xml_reader/text_header_template.xml";
const QString XmlRead::InfoXml = "c:/data/xml_reader/project_info.xml";


XmlRead::XmlRead()
{
    templateDoc = QDomDocument("template");
    infoDoc = QDomDocument("info");
    templateElem = setContent(TemplateXml, templateDoc).documentElement();
    infoElem = setContent(InfoXml, infoDoc).documentElement();
    total_width = templateElem.elementsByTagName("total_width").at(0).toElement().text().toInt();
    left_width = templateElem.elementsByTagName("left_width").at(0).toElement().text().toInt();
    lines = templateElem.elementsByTagName("line");
}

QDomDocument XmlRead::setContent(const QString &name, QDomDocument& doc)
{
    QFile file(name);

    if (!file.open(QIODevice::ReadOnly))
        return doc;
    if (!doc.setContent(&file)) {
        file.close();
        return doc;
    }
    file.close();
    return doc;
}

QString XmlRead::run(SeisFile* sf)
{
    QDomNodeList parts;
    QString result;
    QString curLine;
    QDomElement curElem;
    QMap<QString, QString> map;
    QFileInfo fi(sf->Fname().data());
    QString fileName = fi.fileName();

    map["line"] = fileName.left(fileName.indexOf('_'));
    map["sample_interval"] = QString::number(sf->Si() * 1000);
    map["trace_length"] = QString::number((sf->Si() * 1000) * sf->Ns());

    for (int i = 0; i < lines.length(); ++i) {
        curLine = "";
        parts = lines.at(i).toElement().elementsByTagName("part");
        for (int j = 0; j < parts.length(); ++j) {
            curElem = parts.at(j).toElement();
            if(curElem.attribute("info").startsWith("xml")) {
                curLine.append(infoElem.elementsByTagName(curElem.attribute("info").split(" ")[1]).at(0).toElement().text());
            }
            if(curElem.attribute("info").startsWith("sgy")) {
                curLine.append(map[curElem.attribute("info").split(" ")[1]]);
            }
            curLine.append(curElem.text());
            if(!curElem.hasAttribute("column")) {
                curLine.append(" ");
            } else {
                curLine = curLine.leftJustified(left_width, ' ');
            }

        }
        curLine = curLine.leftJustified(total_width, ' ');
        curLine.append("\n");
        result.append(curLine);
    }

    return result;
}
