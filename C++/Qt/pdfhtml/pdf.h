#ifndef PDF_H
#define PDF_H
#include <QGuiApplication>
#include <QDesktopServices>
#include <QTextDocument>
#include <QPrinter>
#include <QDebug>

class PDF
{
public:
    PDF();
    void createPDF(QString path); //pdf dosyasını oluşturur
    void createPDFStructure(); //pdfin yapısını oluşturur
    void addDefaultStylingToPDF(); //pdfe center left right classlarını ekler
    void addStylingToPDF(QString styling); //pdfe ekstra eklenmek istenen tasarımlar için
    void addContentToPDF(QString content); //pdfe içerik eklemek için
    void createTable(QVector<QString> titles, QList<QStringList> rows, QString position = "center"); //pdfe tablo ekler
    void createTitle(QString titleText, int size, QString position = "center", QString fontStyle = "normal",
                      QString fontWeight = "normal", QString fontFamily = "Times New Roman", QString color = "black"); //pdfe başlık ekler
    void createParagraph(QString text, QString position = "center", QString fontSize = "medium",
                         QString fontStyle = "normal", QString fontWeight = "normal", QString fontFamily = "Times New Roman", QString color = "black"); //pdfe paragraf ekler
    void createMargin(int times); //pdfe boşluk ekler
    void createImage(QString path, int width, int height, QString position = "center"); //pdfe resim ekler
    void createHeader(QString path, int width, int height, QString position = "center"); //pdfe üst bilgi ekler

    //getter functions
    QString getDoc_content();
    QString getHeaderContent();

   //setter functions
    void setHeaderIsSet(bool isSet);

private:
    //variables
    QString doc_content;
    bool headerIsSet;
    float pageDensity;
    float volatilePageDensity;
    float defaultPageDensity;
    QString headerContent;

    //functions
    void calculatePageContent(int content, int subcontent);
    void calculateRemainingSpaceAfterHeader(int height);
    void createMarginForTable();
    void newPageOperations();
};

#endif // PDF_H
