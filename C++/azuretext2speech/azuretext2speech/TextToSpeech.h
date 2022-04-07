#pragma once
#include <speechapi_cxx.h>
#include <fstream>
#include <locale>
#include <codecvt>

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

class TextToSpeech
{
public:
	//Set functions
	void setCredientals(string key, string region);
	void setSSmlPath(string path);
	void setAudioPath(string path);
	
	//Get Functions
	string getKey();
	string getRegion();
	string getSssmlPath();
	string getAudioPath();

	//Member Functions
	void synthesizeSpeech();
	void createSsmlFile(wstring language, wstring voice, wstring text);
private:
	string key;
	string region;
	string ssmlPath;
	string audioPath;
};

