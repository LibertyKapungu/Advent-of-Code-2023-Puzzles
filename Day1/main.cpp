#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class SnowProduction{

public:

    void setLine(string line);

    size_t wordFound(const string word);

    size_t multiWordFound(const string word, size_t index);

    int mergeNums(int units, int tens);

    int stringToInt(string& word);

    int processInput();

    void displayMap();

private:

    string m_line;

    vector<string> m_numbersInWords = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    vector<string> m_numberDigits = {"0", "1", "2", "3", "4", "5", "6", "7" ,"8", "9"};

    map<int, string> m_map;
};

void SnowProduction::setLine(string line){
    m_line = line;
}

 size_t SnowProduction::wordFound(const string word){

    return m_line.find(word);
}

 size_t SnowProduction::multiWordFound(const string word, size_t index){

    return m_line.find(word, index);
}

int SnowProduction::mergeNums(int units, int tens){

    int factor = 1;

    while(factor <= tens){
        factor *= 10;
    }

    return units * factor + tens;
}

int SnowProduction::stringToInt(string& word){

    if(word == "0" || word == "zero"){
        return 0;
    }

    else if(word == "1" || word == "one"){
        return 1;
    }

    else if(word == "2" || word == "two"){
        return 2;
    }

    else if(word == "3" || word == "three"){
        return 3;
    }

    else if(word == "4" || word == "four"){
        return 4;
    }

    else if(word == "5" || word == "five"){
        return 5;
    }

    else if(word == "6" || word == "six"){
        return 6;
    }

    else if(word == "7" || word == "seven"){
        return 7;
    }

    else if(word == "8" || word == "eight"){
        return 8;
    }

    else if(word == "9" || word == "nine"){
        return 9;
    }
}

int SnowProduction::processInput(){

    for(int i = 1; i < 10; i++){

        size_t pos = wordFound(m_numbersInWords[i]);

        if(pos != string::npos){
            m_map[pos] = m_numbersInWords[i];
        }

        while (pos != string::npos){

            pos = multiWordFound(m_numbersInWords[i], pos + 1); // Find next occurrence after pos
            m_map[pos] = m_numbersInWords[i];
        }

        pos = wordFound( m_numberDigits[i]);

        if(pos != string::npos){
            m_map[pos] = m_numberDigits[i];
        }

        while (pos != string::npos) {
            pos = multiWordFound(m_numberDigits[i], pos + 1); // Find next occurrence after pos
            m_map[pos] = m_numberDigits[i];
        }
    }

    int units = stringToInt( (++m_map.begin())->second);
    int tens = stringToInt(m_map.rbegin()->second);

    int number = mergeNums(units, tens);
    //cout << "\n Number: "<< number << endl;

    m_map.clear();

    return number;
}

void SnowProduction::displayMap(){

    cout << "#########################################" << endl;

    for (auto i = m_map.begin(); i != m_map.end(); i++){

        std::cout << i->first
                  << " : "
                  << i->second
                  << '\n';
    }

    cout << "#########################################" << endl;
    cout << endl;
}

int main()
{
    SnowProduction data;

    fstream inputFile("day1.txt");

    int sum = 0;

    if(!inputFile.is_open()){
        return -1;
    }

    string line;

    while(getline(inputFile, line)){

        data.setLine(line);
        sum += data.processInput();
    }

    cout << "Sum of all of the calibration values : " << sum << endl;

    return 0;
}
