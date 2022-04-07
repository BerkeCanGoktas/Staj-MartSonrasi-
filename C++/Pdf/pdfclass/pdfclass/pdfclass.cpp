// pdfclass.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "PDF.h"

using namespace System;
using namespace Aspose::Pdf;
using namespace Aspose::Pdf::Text;
using namespace Aspose::Pdf::Annotations;

std::vector<std::map<std::string, std::string>> getJSON(std::string path) {
    // Create a text string, which is used to output the text file
    std::string myText;
    std::string array;
    std::map<std::string, std::string> mapOfElement;
    std::vector<std::map<std::string, std::string>> vector;

    // Read from the text file
    std::ifstream MyReadFile(path);

    // Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, myText)) {
        // Output the text from the file
        array += myText;
    }


    // Close the file
    MyReadFile.close();
    array.erase(remove(array.begin(), array.end(), '['), array.end());
    array.erase(remove(array.begin(), array.end(), ']'), array.end());
    array.erase(remove(array.begin(), array.end(), ' '), array.end());
    array.erase(remove(array.begin(), array.end(), ','), array.end());
    int rowCount = std::count(array.begin(), array.end(), '{');
    int elementCount = std::count(array.begin(), array.end(), ':');
    array.erase(remove(array.begin(), array.end(), '{'), array.end());
    array.erase(remove(array.begin(), array.end(), '}'), array.end());
    array.erase(remove(array.begin(), array.end(), ':'), array.end());
    //std::cout << array << std::endl;
    array.erase(0, 1);
    int counter = 0;
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < elementCount / rowCount; j++) {
            auto end = array.find('"');
            std::string key = array.substr(0, end);
            array.erase(0, end + 1);
            //std::cout << array;
            end = array.find("\"\"");
            std::string value = array.substr(1, end - 1);
            array.erase(0, end + 2);
            if (i == rowCount - 1 && j == elementCount / rowCount - 1) {
                value.erase(remove(value.begin(), value.end(), '\"'), value.end());
            }
            mapOfElement.insert(std::pair<std::string, std::string>(key, value));
        }
        vector.push_back(mapOfElement);
        mapOfElement.clear();
    }
    return vector;
}

int main()
{

    std::string arrayofRows[8] = {"Player", "Games-Played", "Goals", "Assists"};
    std::string arrayofTitleNames[] = { "PLAYER", "GAMES PLAYED", "GOALS", "ASSISTS" };

    std::vector<std::map<std::string, std::string>> vect = getJSON("C:\\Programming\\table.json");
    std::string width = std::to_string(280 / (sizeof(arrayofRows) / sizeof(arrayofRows[0])-4));
    PDF pdfObj;
    pdfObj.set_dataDir(String("C:\\Programming\\"));
    pdfObj.setFileName(String("pdfClass.pdf"));
    pdfObj.initializePDFFile();
    pdfObj.addPage();
    pdfObj.addWatermark(String("C:\\Programming\\piton.png"), 1);
    pdfObj.addHeader(u"New ferry routes in Fall 2020", u"Arial", 24, HorizontalAlignment::Center, 130, 720);
    pdfObj.addDescription(u"Visitors must buy tickets online and tickets are limited to 5,000 per day. Ferry service is operating at half capacity and on a reduced schedule. Expect lineups.", u"Times New Roman", 14, HorizontalAlignment::Left);
 
    pdfObj.addTable(static_cast<System::String>(width), u"Helvetica", arrayofRows, vect, arrayofTitleNames);

    pdfObj.addTable(static_cast<System::String>(width), u"Helvetica", arrayofRows, vect, arrayofTitleNames);

    pdfObj.addTable(static_cast<System::String>(width), u"Helvetica", arrayofRows, vect, arrayofTitleNames);
    pdfObj.addTable(static_cast<System::String>(width), u"Helvetica", arrayofRows, vect, arrayofTitleNames);
    pdfObj.addTable(static_cast<System::String>(width), u"Helvetica", arrayofRows, vect, arrayofTitleNames);
    pdfObj.addTable(static_cast<System::String>(width), u"Helvetica", arrayofRows, vect, arrayofTitleNames);
    pdfObj.addTable(static_cast<System::String>(width), u"Helvetica", arrayofRows, vect, arrayofTitleNames);
    pdfObj.addTable(static_cast<System::String>(width), u"Helvetica", arrayofRows, vect, arrayofTitleNames);
    pdfObj.addTable(static_cast<System::String>(width), u"Helvetica", arrayofRows, vect, arrayofTitleNames);
    pdfObj.addTable(static_cast<System::String>(width), u"Helvetica", arrayofRows, vect, arrayofTitleNames);
    pdfObj.addTable(static_cast<System::String>(width), u"Helvetica", arrayofRows, vect, arrayofTitleNames);
    pdfObj.addTable(static_cast<System::String>(width), u"Helvetica", arrayofRows, vect, arrayofTitleNames);
    pdfObj.addTable(static_cast<System::String>(width), u"Helvetica", arrayofRows, vect, arrayofTitleNames);
    pdfObj.addTable(static_cast<System::String>(width), u"Helvetica", arrayofRows, vect, arrayofTitleNames);
    //pdfObj.addTable(u"25", u"Helvetica", arrayofRows, vect, arrayofTitleNames);
    pdfObj.savePDF();
    pdfObj.CropPagesPDF();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
