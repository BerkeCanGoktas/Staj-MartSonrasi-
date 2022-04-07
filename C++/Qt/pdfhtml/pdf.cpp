#include "pdf.h"

PDF::PDF()
{
}
void PDF::createPDF(QString path)
{
    //QString path = "html.pdf";
    QTextDocument doc;
    doc.setHtml(doc_content);

    QPrinter file;
    file.setOutputFormat(QPrinter::PdfFormat);
    file.setOutputFileName(path);
    doc.print(&file);

    QDesktopServices::openUrl(QUrl(path));

}
void PDF::createPDFStructure(){
    pageDensity = 0;
    defaultPageDensity = 0;
    doc_content = "<!DOCTYPE html>"
                  "<html>"
                  "<meta name='qrichtext' content='1'>"
                  "<meta name='viewport' content='width=device-width, initial-scale=1'>"
                  "<head>"
                  "<style>"
                  "</style>"
                  "</head>"
                  "<body>"
                  "</body>"
                  "</html>";
}
void PDF::addDefaultStylingToPDF(){
    QStringList token = doc_content.split("<style>");
    QString start = token.first() + "<style>";
    QString end = token.last();
    doc_content = start + "html{"
                          "position: relative;"
                          "min-height: 100%;"
                          "height:1 100%;"
                          "}"
                          ".center{"
                          "text-align:center;"
                          "}"
                          ".left{"
                          "text-align:left;"
                          "}"
                          ".right{"
                          "text-align:right;"
                          "}" + end;
}
void PDF::addStylingToPDF(QString styling){
    QStringList token = doc_content.split("<style>");
    QString start = token.first() + "<style>";
    QString end = token.last();
    doc_content = start + styling + end;
}
void PDF::addContentToPDF(QString content){
    QStringList token = doc_content.split("</body>");
    QString start = token.first();
    QString end =  "</body>" + token.last();
    doc_content = start + content + end;
}
void PDF::createMarginForTable(){
    QString margin = "<br>"
                     "<br />";
    addContentToPDF(margin);
}
void PDF::createTable(QVector<QString> titles, QList<QStringList> rows, QString position){
    /*//calculatePageContent(3, rows[0].length()+1);
    float neededSpace = (rows[0].length()+1) * 29.5;
    float remainingSpace = defaultPageDensity - pageDensity;
    if(neededSpace > remainingSpace){
        while(remainingSpace > 0){
            createMarginForTable();
            remainingSpace -= 35;
        }
    }*/
    //calculatePageContent(3, rows[0].length()+1);
    QString table = "<div class='" + position + "'>"
                    "<table class=""names"">";
    QString header =  "<tr>";
    int widthPercantage = qRound(float (95/titles.length()));
    for(int i = 0; i < titles.length(); i++){
        calculatePageContent(3, 1);
        header +=  "<th width='" + QString::number(widthPercantage) + "%'>" + titles[i] + "</th>";
    }
    header +=  "</tr>";
    table += header;
    QString row;
        for(int j = 0; j < rows[0].length(); j++){
            calculatePageContent(3, 1);
            row = "<tr>";
            for(int k = 0; k < rows.length(); k++){
                row += "<td>" + rows[k][j] + "</td>"; }
            row += "</tr>";
            table += row;
        }
    table += "</table>"
             "</div>";
    addContentToPDF(table);
}
void PDF::createTitle(QString titleText, int size, QString position, QString fontStyle, QString fontWeight, QString fontFamily, QString color){
    calculatePageContent(1, size-1);
    QString title = "<div class='" + position + "'>"
                     "<h" + QString::number(size) + " style='font-style:" + fontStyle + "; font-weight:" + fontWeight + "; font-family:" + fontFamily + "; color:" + color + "'>";
    title += titleText;
    title += "</h" + QString::number(size) + ">"
              "</div>";
    addContentToPDF(title);
}
void PDF::createParagraph(QString text, QString position, QString fontSize, QString fontStyle, QString fontWeight, QString fontFamily, QString color){
   int size;
   if(fontSize == "small"){
       size = 0;
   }
   else if(fontSize == "medium"){
       size = 1;
   }
   else if(fontSize == "large"){
       size = 2;
   }
   else if(fontSize == "x-large"){
       size = 3;
   }
   else if(fontSize == "xx-large"){
       size = 4;
   }
    calculatePageContent(0, size);
    QString paragraph = "<div class='" + position + "'>"
                        "<p style='font-size:" + fontSize + "; font-style:" + fontStyle + "; font-weight:" + fontWeight + "; font-family:" + fontFamily + "; color:" + color + "'>";
    paragraph += text;
    paragraph += "</p>"
                 "</div>";
    addContentToPDF(paragraph);
}
void PDF::createMargin(int times){
    calculatePageContent(4, times);
    QString addMargin = "<br>"
                     "<br />";
    QString margin;
    for(int i = 1; i<=times; i++){
        margin += addMargin;
    }
    addContentToPDF(margin);
}
void PDF::createImage(QString path, int width, int height, QString position){
    calculatePageContent(2, height);
    QString img =   "<div class='" + position + "'>"
                    "<img src='" + path + "' width='" + QString::number(width) + "' height='" + QString::number(height) + "'>"
                    "</div>";
    addContentToPDF(img);
}
void PDF::createHeader(QString path, int width, int height, QString position){
    QString img =   "<div class='" + position + "'>"
                    "<img src='" + path + "' width='" + QString::number(width) + "' height='" + QString::number(height) + "'>"
                    "</div>";
    headerContent = img;
    headerIsSet = true;
    addContentToPDF(headerContent);
    calculateRemainingSpaceAfterHeader(height);
}
QString PDF::getDoc_content(){
    return doc_content;
}
QString PDF::getHeaderContent(){
    return headerContent;
}
void PDF::setHeaderIsSet(bool isSet){
    headerIsSet = isSet;
}
void PDF::calculatePageContent(int content, int subcontent){
    volatilePageDensity = pageDensity;
    switch(content){
    case 0: //paragraph
        switch(subcontent){
        case 0: //small
            pageDensity += 27;
            break;
        case 1: //medium
            pageDensity += 30.5;
            break;
        case 2: //large
            pageDensity += 33.8;
            break;
        case 3: //x-large
            pageDensity += 39.4;
            break;
        case 4: //xx-large
            pageDensity += 47.3;
            break;
        }
        break;
    case 1: //title
        switch(subcontent){
        case 0: //h1
            pageDensity += 52.6;
            break;
        case 1: //h2
            pageDensity += 43;
            break;
        case 2: //h3
            pageDensity += 36.4;
            break;
        case 3: //h4
            pageDensity += 30.5;
            break;
        case 4: //h5
            pageDensity += 27;
            break;
        case 5: //h6
            pageDensity += 18.2;
            break;
        }
        break;
    case 2: //img
        pageDensity += subcontent;
        break;
    case 3: //table
        pageDensity += 29.5 * subcontent;
        break;
    case 4: //margin
        pageDensity += 35 * subcontent;
        break;
    }
    //qDebug() << pageDensity;
    if(defaultPageDensity < pageDensity){
        float remaining = pageDensity - volatilePageDensity;
        pageDensity = 0 + remaining;
        newPageOperations();
    }
}
void PDF::calculateRemainingSpaceAfterHeader(int height){
    defaultPageDensity = 947 - height;
    //qDebug() << "default density: " + QString::number(defaultPageDensity);
}
void PDF::newPageOperations(){
    if(headerIsSet == true){
        addContentToPDF(headerContent);
    }
}
