#include <iostream>
#include <windows.h>
#include <string>

using std::string;

const int FREQUENCY = 641;
const int DOTLENGTHMS = 60;

const static string alphabetIndices = "abcdefghijklmnopqrstuvwxyz1234567890";
const static string morseAlphabet[36] = 
{   ".-", "-....", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..",
    "--", "-.", "---", ".--.", "--.-", ".-.", "....", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
    ".----", "..---", "....-", ".....", "-....", "--...", "---..", "----.", "-----"
};

int main(int argc, char **argv)
{
    if(argc <= 1){std::cout << "Usage: Enter text you wish to listen/convert to morse code as command line argument" << std::endl; exit(1);}

    string input = "";
    for(int i = 1; i < argc; i++)
    {
        input.append(argv[i]);
        if(i != argc - 1){input.append(" ");}
    }

    
    //Convert all to lowercase
    for(int i = 0; i < input.size(); i++)
    {
        input[i] = tolower(input[i]);
    }

    //Error check
    for(int i = 0; i < input.size(); i++)
    {
        if(alphabetIndices.find(input[i]) == string::npos && input[i] != ' '){std::cout << "Input contains letters not found in the morse code alphabet. Terminating" << std::endl; exit(1);}
    }


    //Actual morseing
    std::cout << "Morse code for " + input + ":" << std::endl;
    for(int i = 0; i < input.size(); i++)
    {
        if(input[i] != ' ')
        {
            string morse = morseAlphabet[alphabetIndices.find(input[i])];
            for(int j = 0; j < morse.size(); j++)
            {
                if(morse[j] == '.'){Beep(FREQUENCY, DOTLENGTHMS);}
                if(morse[j] == '-'){Beep(FREQUENCY, DOTLENGTHMS * 3);}
                Sleep(DOTLENGTHMS); //Wait for part of letter switch
                std::cout << morse[j];
            }

            
            Sleep(DOTLENGTHMS * 3); //Wait for letter switch
            std::cout << " ";
        }

        else
        {
            Sleep(DOTLENGTHMS * 7); // Wait for word switch
            std::cout << " / ";
        }
    }
    

    return 0;
}