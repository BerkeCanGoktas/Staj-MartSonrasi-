#include "PDF.h"

void PDF::initializePDFFile() {
	document = MakeObject<Document>();
}

void PDF::addPage() {
	page = document->get_Pages()->Add();
    /*auto margin = MakeObject<MarginInfo>(50, 50, 50, 50);
    auto pageInfo = page->get_PageInfo();
    pageInfo->set_AnyMargin(margin);*/
}

void PDF::addWatermark(String imageFileName, int i) {

	// Add image to Images collection of Page Resources
	auto rectangle = MakeObject<Rectangle>(0, 600, 600, 800); // lowerLeftX, lowerLeftY, upperRightX, upperRightY
	//page->AddImage(imageFileName, rectangle);
    document->get_Pages()->idx_get(i)->AddImage(imageFileName, rectangle);

  
}

void PDF::addHeader(String text, String font, int fontSize, HorizontalAlignment alignment, int positionX, int positionY) {
    // Add header
    auto header = MakeObject<TextFragment>(text);
    auto textFragementState = header->get_TextState();
    textFragementState->set_Font(FontRepository::FindFont(font));
    textFragementState->set_FontSize(fontSize);
    header->set_HorizontalAlignment(alignment);
    header->set_Margin(MakeObject<MarginInfo>(0, 0, 0, 100));
    auto position = MakeObject<Aspose::Pdf::Text::Position>(positionX, positionY);
    header->set_Position(position);
    page->get_Paragraphs()->Add(header);
}

void PDF::addDescription(String text, String font, int fontSize, HorizontalAlignment alignment) {
    // Add description
    String descriptionText(text);
    auto description = MakeObject<TextFragment>(descriptionText);
    description->get_TextState()->set_Font(FontRepository::FindFont(font));
    description->get_TextState()->set_FontSize(fontSize);
    description->set_HorizontalAlignment(alignment);
    description->set_Margin(MakeObject<MarginInfo>(10, 50, 10, 20));
    page->get_Paragraphs()->Add(description);
}

void PDF::addTable(String columnWidths, String font, std::string rows[], std::vector<std::map<std::string, std::string>> vector, std::string arrayOfTitles[]) {
    // Add table
    auto table = MakeObject<Table>();
    table->set_ColumnWidths(columnWidths);

    table->set_Border(MakeObject<BorderInfo>(Aspose::Pdf::BorderSide::Box, 1.0f, Aspose::Pdf::Color::get_DarkSlateGray())); //*****
    table->set_DefaultCellBorder(MakeObject<BorderInfo>(Aspose::Pdf::BorderSide::Box, .5f, Aspose::Pdf::Color::get_Black())); //****
    table->get_DefaultCellTextState()->set_Font(FontRepository::FindFont(font));

    table->set_Alignment(Aspose::Pdf::HorizontalAlignment::Left);
    table->set_DefaultCellPadding(MakeObject<MarginInfo>(3, 3, 3, 3));
    table->set_Margin(MakeObject<MarginInfo>(0, 20, 0, 20));

    auto headerRow = table->get_Rows()->Add();
    headerRow->get_Cells()->Add(static_cast<String>(arrayOfTitles[0]));
    headerRow->get_Cells()->Add(static_cast<String>(arrayOfTitles[1]));
    headerRow->get_Cells()->Add(static_cast<String>(arrayOfTitles[2]));
    headerRow->get_Cells()->Add(static_cast<String>(arrayOfTitles[3]));

    for (auto headerRowCell : headerRow->get_Cells())
    {
        headerRowCell->set_BackgroundColor(Color::get_Gray());
        headerRowCell->get_DefaultCellTextState()->set_ForegroundColor(Color::get_WhiteSmoke());
    }

    for (int i = 0; i < vector.size(); i++)
    {
        auto dataRow = table->get_Rows()->Add();
        for (int j = 0; j < vector.at(i).size(); j++) {       
            dataRow->get_Cells()->Add(static_cast<System::String>(vector.at(i)[rows[j]]));
        }
    }
    page->get_Paragraphs()->Add(table);
}

void PDF::savePDF() {
    // Save updated PDF
    outputFileName = _dataDir + filename;

    document->Save(outputFileName);
}
void PDF::CropPagesPDF()
{
    using namespace Aspose::Pdf::Facades;

    String _dataDir("C:\\Programming\\");
    String inputFileName("pdfClass.pdf");
    String outputFileName("cropped.pdf");

    PdfFileInfo* info = new PdfFileInfo(String("pdfClass.pdf"));

    // Open source document
    auto document = MakeObject<Document>(_dataDir + inputFileName);
    auto pageCount = document->get_Pages()->get_Count();

    for (int i = 1; i <= pageCount; i++) {
        Console::WriteLine(document->get_Pages()->idx_get(i)->get_CropBox());
        Console::WriteLine(document->get_Pages()->idx_get(i)->get_TrimBox());
        Console::WriteLine(document->get_Pages()->idx_get(i)->get_ArtBox());
        Console::WriteLine(document->get_Pages()->idx_get(i)->get_BleedBox());
        Console::WriteLine(document->get_Pages()->idx_get(i)->get_MediaBox());
    }

    // Create new Box Rectagle
    auto newBox = MakeObject<Rectangle>(0, 0, 595, 800);      // lowerLeftX, lowerLeftY, upperRightX, upperRightY
    for (int i = 1; i <= pageCount; i++) {
        document->get_Pages()->idx_get(i)->set_CropBox(newBox);
        document->get_Pages()->idx_get(i)->set_TrimBox(newBox);
        document->get_Pages()->idx_get(i)->set_ArtBox(newBox);
        document->get_Pages()->idx_get(i)->set_BleedBox(newBox);
        //addWatermark(String("C:\\Programming\\piton.png"), i);
    }
   /* for (int i = 1; i <= pageCount; i++) {
        addWatermark(String("C:\\Programming\\piton.png"));
    }*/
    // Save updated document
    document->Save(_dataDir + outputFileName);
}

void PDF::set_dataDir(String _dataDir_) {
    _dataDir = _dataDir_;
}

void PDF::setFileName(String fileName_) {
    filename = fileName_;
}