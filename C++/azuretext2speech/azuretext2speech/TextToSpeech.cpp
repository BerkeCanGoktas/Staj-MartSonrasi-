#include "TextToSpeech.h"

//Set Functions
void TextToSpeech::setCredientals(string key, string region) {
	this->key = key;
	this->region = region;
}

void TextToSpeech::setSSmlPath(string path) {
    this->ssmlPath = path;
}

void TextToSpeech::setAudioPath(string path) {
    this->audioPath = path;
}


//Get Functions
string TextToSpeech::getKey() {
    return this->key;
}

string TextToSpeech::getRegion() {
    return this->region;
}

string TextToSpeech::getSssmlPath() {
    return this->ssmlPath;
}

string TextToSpeech::getAudioPath() {
    return this->audioPath;
}


//Member Functions
void TextToSpeech::synthesizeSpeech()
{
    auto config = SpeechConfig::FromSubscription(getKey(), getRegion());
    auto synthesizer = SpeechSynthesizer::FromConfig(config, NULL);

    std::ifstream file(getSssmlPath());
    std::string ssml, line;
    while (std::getline(file, line))
    {
        ssml += line;
        ssml.push_back('\n');
    }
    auto result = synthesizer->SpeakSsmlAsync(ssml).get();

    auto stream = AudioDataStream::FromResult(result);
    stream->SaveToWavFileAsync(getAudioPath()).get();
}

void TextToSpeech::createSsmlFile(wstring language, wstring voice, wstring text) {
    wstring ssml = L"<speak version = \"1.0\" xmlns = \"http://www.w3.org/2001/10/synthesis\" xml:lang = \"" + language + L"\">";
    ssml += L"<voice name = \"" + voice + L"\"> ";
    ssml += text;
    ssml += L" </voice>";
    ssml += L"</speak>";
    //std::wstring widestr = std::wstring(ssml.begin(), ssml.end());
    const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());
    wofstream file(getSssmlPath());
    file.imbue(utf8_locale);
  /*  std::wcout << widestr;
    std::cout << ssml;*/
    file << ssml;
    file.close();
}


