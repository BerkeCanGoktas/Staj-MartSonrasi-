#include <QGuiApplication>
#include<QDebug>
#include <QDesktopServices>
#include <QTextDocument>
#include <QPrinter>
#include <QJsonObject>
#include <QJsonDocument>
#include "pdf.h"


int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    PDF pdf;
    pdf.createPDFStructure();
    pdf.addDefaultStylingToPDF();
    pdf.addStylingToPDF(                                      "table, th, td {"
                                                              "  border: 1px solid black;"
                                                              "  border-collapse: collapse;"
                                                              "}"
                                                              "th, td {"
                                                              "  padding: 5px;"
                                                              "  text-align: left;"
                                                              "}"
                                                              "table.names th {"
                                                              "  background-color: black;"
                                                              "  color: white"
                                                              "}");

    QVector<QString> titles = {"Firstname", "Lastname", "Age"};
    QStringList firstnames = {"Jill", "Eve", "John", "Micheal", "Jane"};
    QStringList lastnames = {"Smith", "Jackson", "Doe","Black", "White"};
    QStringList ages = {"50", "94", "80","20", "28"};
    QList<QStringList> rows = {firstnames, lastnames, ages};

    //pdf.createHeader("/home/berke/Downloads/piton.png", 400, 250); //947 -> height
    pdf.createTitle("Başlık", 1, "center", "italic", "bold", "Ariel", "red"); //18 -> h1 22 -> h2 26 -> h3 31 -> h4 35 -> h5 52 -> h6
    pdf.createParagraph("Paragraph Paragraph Paragraph Paragraph Paragraph Paragraph", "left", "medium", "italic", "bold", "Ariel", "red"); //35 -> s 31 -> m 28 -> l 24 -> xl 20 -> xxl
    pdf.createParagraph("Paragraph Paragraph Paragraph Paragraph Paragraph Paragraph", "center", "small", "italic", "bold", "Ariel", "red");
    pdf.createMargin(2); //27
    pdf.createTable(titles, rows); //32 -> row
    pdf.createTable(titles, rows);
    pdf.createTable(titles, rows);
    //pdf.setHeaderIsSet(false);
    pdf.createTitle("Başlık", 2, "left", "italic", "bold", "Ariel", "red");
    pdf.createParagraph("Paragraph Paragraph Paragraph Paragraph Paragraph Paragraph", "right", "large", "normal", "bold", "Ariel", "green");
    pdf.createTitle("Başlık", 3, "left", "italic", "bold", "Ariel", "red");
    pdf.createParagraph("Paragraph Paragraph Paragraph Paragraph Paragraph Paragraph", "right", "x-large", "normal", "bold", "Ariel", "green");
    pdf.createTitle("Başlık", 4, "right", "italic", "bold", "Ariel", "red");
    pdf.createParagraph("Paragraph Paragraph Paragraph Paragraph Paragraph Paragraph", "right", "xx-large", "normal", "bold", "Ariel", "green");
    pdf.createTitle("Başlık", 5, "left", "italic", "bold", "Ariel", "red");
    pdf.createTitle("Başlık", 6, "left", "italic", "bold", "Ariel", "red");
    pdf.createTable(titles, rows);
    pdf.createTable(titles, rows);
    pdf.createTable(titles, rows);
    pdf.createImage("/home/berke/Downloads/piton.png", 400, 500);
    pdf.createTable(titles, rows);
    pdf.createTable(titles, rows);

    pdf.createPDF("html.pdf");
    //qDebug() << pdf.getDoc_content();
    return a.exec();
}
