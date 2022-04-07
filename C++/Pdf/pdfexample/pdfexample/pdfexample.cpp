// pdfexample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AsposePdf.h"

using namespace System;
using namespace Aspose::Pdf;
using namespace Aspose::Pdf::Text;

void ExampleSimple()
{
    // Buffer to hold combined path.
    String outputFileName;

    // String for path name.
    String _dataDir("C:\\Programming\\");

    // String for file name.
    String filename("HelloWorld_out.pdf");

    auto document = MakeObject<Document>();
    auto page = document->get_Pages()->Add();

    // Add text to new page
    auto text = MakeObject<TextFragment>(u"Hello world!");

    auto paragraphs = page->get_Paragraphs();
    paragraphs->Add(text);

    // Save updated PDF
    outputFileName = _dataDir + filename;

    document->Save(outputFileName);
}

int main()
{
    //ExampleSimple();
    // Open first document
    auto doc1 = MakeObject<Document>(u"C:\\Programming\\1.pdf");

    // Open second document
    auto doc2 = MakeObject<Document>(u"C:\\Programming\\2.pdf");

    // Add pages of second document to the first
    doc1->get_Pages()->Add(doc2->get_Pages());

    // Save concatenated output file
    doc1->Save(u"C:\\Programming\\merged-output.pdf");

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
