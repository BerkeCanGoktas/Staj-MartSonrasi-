// azuretext2speech.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream> // cin, cout
#include <speechapi_cxx.h>
#include "TextToSpeech.h"

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

auto YourSubscriptionKey = "xxxx";
auto YourServiceRegion = "xxxx";

void synthesizeSpeech()
{
    auto config = SpeechConfig::FromSubscription("xxxx", "xxxx");
    auto synthesizer = SpeechSynthesizer::FromConfig(config, NULL);

    std::ifstream file("C:/Programming/ssml.xml");
    std::string ssml, line;
    while (std::getline(file, line))
    {
        ssml += line;
        //std::cout << ssml << std::endl;
        ssml.push_back('\n');
    }
    auto result = synthesizer->SpeakSsmlAsync(ssml).get();
    //synthesizer->SpeakSsml(ssml);

    auto stream = AudioDataStream::FromResult(result);
    stream->SaveToWavFileAsync("C:/Programming/result.wav").get();
}

int main()
{
    //synthesizeSpeech();
    
    TextToSpeech t2sObj;
    t2sObj.setCredientals("xxxx", "xxxx");
    t2sObj.setSSmlPath("C:/Programming/ssml.xml");
    t2sObj.setAudioPath("C:/Programming/result.wav");
    t2sObj.createSsmlFile(L"tr-Tr", L"tr-TR-EmelNeural", L"Sınıf için türkçe metin testi");
    t2sObj.synthesizeSpeech();



}



//Konsol kullanarak dosya oluşturmadan çalıştırma örneği (türkçe karakter kullanmak konsolun exception ile terminate edilmesine sebep oluyor

//    auto speechConfig = SpeechConfig::FromSubscription(YourSubscriptionKey, YourServiceRegion);

//    // The language of the voice that speaks.
//    speechConfig->SetSpeechSynthesisVoiceName("tr-TR-EmelNeural");

//    auto synthesizer = SpeechSynthesizer::FromConfig(speechConfig);

//    // Get text from the console and synthesize to the default speaker.
//    cout << "Enter some text that you want to speak >" << std::endl;
//    std::string text;
//    getline(cin, text);

//    auto result = synthesizer->SpeakTextAsync(text).get();
//    //std::string ssml = "<speak version = \"1.0\" xmlns = \"http://www.w3.org/2001/10/synthesis\" xml:lang = \"en-US\"><voice name = \"en-US-JennyNeural\">This is the text that is spoken.< / voice>< / speak>";
//    //synthesizer->SpeakSsml(ssml);       

//    // Checks result.
//    if (result->Reason == ResultReason::SynthesizingAudioCompleted)
//    {
//        cout << "Speech synthesized to speaker for text [" << text << "]" << std::endl;
//        auto audioConfig = AudioConfig::FromWavFileOutput("C:/Programming/result.wav");
//        auto synthesizer = SpeechSynthesizer::FromConfig(speechConfig, audioConfig);
//        auto result = synthesizer->SpeakTextAsync(text).get();
//    }
//    else if (result->Reason == ResultReason::Canceled)
//    {
//        auto cancellation = SpeechSynthesisCancellationDetails::FromResult(result);
//        cout << "CANCELED: Reason=" << (int)cancellation->Reason << std::endl;

//        if (cancellation->Reason == CancellationReason::Error)
//        {
//            cout << "CANCELED: ErrorCode=" << (int)cancellation->ErrorCode << std::endl;
//            cout << "CANCELED: ErrorDetails=[" << cancellation->ErrorDetails << "]" << std::endl;
//            cout << "CANCELED: Did you update the subscription info?" << std::endl;
//        }
//    }

//    cout << "Press enter to exit..." << std::endl;
//    cin.get();
