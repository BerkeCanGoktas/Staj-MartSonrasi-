// text2speech.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "BasicVoice.h"
#include "MaleVoice.h"
#include "FemaleVoice.h"
int main()
{
	BasicVoice* b1 = NULL;
	b1 = new MaleVoice;
	int choice;
	do {
		cout << "1 to Output in Male Voice \n2 to Output in Female Voice\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			b1 = new MaleVoice; //  we create a new malevoice object.
			b1->setSpeech();
			b1->outSpeech();
			delete b1; //after outputing that voice , we delete that object
			break;
		case 2:
			b1 = new FemaleVoice;// we create a new femalevoice
			b1->setSpeech();
			b1->outSpeech();
			delete b1;//after outputing that voice , we delete that object
			break;
		case 3:
			b1 = new FemaleVoice;
			b1->byeSpeech();
			b1->outSpeech();
			delete b1;
			break;
		default:
			break;
		}
	} while (choice != 3);
	system("pause");
	return 0;
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
