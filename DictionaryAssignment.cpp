/*
AUTHOR: GARVIT MARWAH
DATE: 25TH MARCH,2024
FOR MORE PSEUDOCODE/COMMENTS SEE BELOW
*/
#include <fstream> //allows program to interact with files used for input and output operations 
#include <iostream> //it has capabilities for handling standard input and output operations and using streams like cin for input as well as cout for outputs
#include <string> //for std::string
#include <vector>//an array which adjusts its size as elements can be added or can be removed
#include <algorithm> //used for sorting, searching and other manipulations on data structures
#include <cctype> //includes functions such as checking character types (if they are alphabetic or numeric) and also useful for converting characters from uppercase to lowercase

using namespace std;

struct Word {
    string name;
    string type;
    string definition;
};
/*
The function below picks up a string as an input, in order to remove any non-letter character and it also converts every letter to their lowercase form. After that, it would return this modified string where only lowercase alphabetical characters are included from original input
*/
string toLowercaseLetters(const string& str) {
    string lowercaseOnly;
    for (char c : str) {
        if (std::isalpha(c)) { // Keep only alphabetical characters
            lowercaseOnly += std::tolower(c); // Convert to lowercase
        }
    }
    return lowercaseOnly;
}
/*
The function below starts by trying to read from file that the uer inputs. If the file cannot be open because the files name is wrong or it doesnt exist then a "File could not be found" message will be displayed and then it will open the preloaded file a.ka "dictionary_2024S1.txt. it can't open this backup file either, it will tell you "Failed to open any dictionary file." and stop running. But, if everything goes well and it can open the file, it will say "Perfect loading dictionary now!" which means it's ready to load the dictionary from the file. Then, it gets ready to read the words from the file by setting up something called currentWord to store each word it finds.
*/
void loadDictionaryEntries(vector<Word>& dictionary, const string& filepath) {
    ifstream file(filepath); //ifstream is used for reading from files 
    if (!file.is_open()) {
        std::cout << "File could not found!" << endl;
        std::cout << "Opening dictionary_2024S1.txt instead" << endl;
        file.open("dictionary_2024S1.txt"); // Attempt to open the default file
        if (!file.is_open()) {
            std::cout << "Unfortunately, the dictionary file could not be opened" << endl;
            exit(1); // Exit if no file could be opened
        }
    }
    else {
        std::cout << "Perfect loading dictionary now!" << endl; // Acknowledge correct file input
    }
    /*
    The function below is a continuation from the LoadDictionaryEntries function. It reads each line from the file one by one. For each line, it changes all the letters to lowercase to make it easier to figure out if the line tells us the word's type, definition, or the word itself.
    If the line starts with "type", it saves the type to currentWord. If it says "definition", it saves the definition. And if it says "word", it saves the word after making it all lowercase, and then adds currentWord with all its details into the dictionary.
    After saving the word, it gets ready to read the next word by resetting currentWord. Once there are no more lines to read, it closes the file.

    */
    Word currentWord;
    string line;
    while (getline(file, line)) {
        string processedLine = toLowercaseLetters(line);
        if (processedLine.substr(0, 4) == "type") {
            currentWord.type = line.substr(6);
        }
        else if (processedLine.substr(0, 10) == "definition") {
            currentWord.definition = line.substr(12);
        }
        else if (processedLine.substr(0, 4) == "word") {
            currentWord.name = toLowercaseLetters(line.substr(6));
            dictionary.push_back(currentWord);
            currentWord = Word();
        }
    }
    file.close();
}

int main() {
    /*
    Garvit's Dictionary Program
    In this program, an already preloaded file known as "dictionary_2024S1.txt' is used by the users of this program to look up for words and in return users get the word's type and definition. The entire program is case insensitive and the program will continue to run until the user inputs "end Program"
    INPUTS:
    -> User is required to input filename or just get directed to the default filename which is "dictionary_2024S1.txt"
    -> User is prompted to input a word

    OUTPUTS:
    -> The words type and definition is shown as the output

    Author: Garvit Marwah
    Date: 25th March,2024
    */
    vector<Word> dictionary;
    std::cout << "Welcome to the Dictionary Program!" << endl;
    std::cout << "Type the dictionary's file name or just click enter to use the preloaded one: " << endl;
    string filepath;
    getline(cin, filepath);
    if (filepath.empty()) {
        filepath = "dictionary_2024S1.txt"; // Use default file if no input
    }
    else {
        filepath += (filepath.find(".txt") == std::string::npos) ? ".txt" : ""; // Ensure correct file extension
    }

    loadDictionaryEntries(dictionary, filepath);

    std::cout << "Input a word to find its type and definition or input 'End Program' (Space, Case and Hyper insensitive) to terminate the program: " << endl;
    string input;
    while (getline(cin, input)) {
        string processedInput = toLowercaseLetters(input);

        // Check if input indicates program termination
        if (processedInput == "endprogram" || processedInput == "end-program" || processedInput == "end program") {
            break;
        }

        bool found = false;
        for (const auto& word : dictionary) {
            if (word.name == processedInput) {
                cout << "Word: " << input << endl;
                cout << "Type: " << word.type << endl;
                cout << "Definition: " << word.definition << endl << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "Word not found. " << endl;
        }
        std::cout << "Input a word to find its type and definition or input 'End Program' (Space, Case and Hyper insensitive) to terminate the program: " << endl;
    }

    return 0;
}
