#pragma once
#include "AsposePDF.h"

using namespace System;
using namespace Aspose::Pdf;
using namespace Aspose::Pdf::Text;
using namespace Aspose::Pdf::Annotations;

class PDF
{
public:
    void initializePDFFile();

    void addPage();
    
    void addWatermark(String imageFileName, int i);

    void addHeader(String text, String font, int fontSize, HorizontalAlignment alignment, int positionX, int positionY);

    void addDescription(String text, String font, int fontSize, HorizontalAlignment alignment);

    void addTable(String columnWidths, String font, std::string rows[], std::vector<std::map<std::string, std::string>> vector, std::string arrayOfTitles[]);

    void savePDF();

    void setOutputFileName(String outputFileName_);
    
    void set_dataDir(String _dataDir_);

    void setFileName(String fileName_);
    
    void CropPagesPDF();

private:
    // String for output file name.
	String outputFileName;

    // String for path name.
    String _dataDir;

    // String for file name.
    String filename;

    // Document object.
    System::SmartPtr<Aspose::Pdf::Document> document;

    // Page object.
    System::SmartPtr<Aspose::Pdf::Page> page;
};

