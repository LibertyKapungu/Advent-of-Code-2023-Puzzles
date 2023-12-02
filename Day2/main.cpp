#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

string removePunctuations(string& str);

class Games{

public:

    int getSum();

    void updatePower();

    int getPower();

    bool validateInput(int num,  string colour);

    void processInput(string unpunctLine);

private:

    int m_sum = 0;
    int m_power = 0;

    vector<int> m_validIds;
    vector<int> m_maxColour = {0,0,0};
    vector<int> m_minSet;
};

int Games::getSum(){

    for(int elem : m_validIds){
        m_sum += elem;
    }

    return m_sum;
}

void Games::updatePower(){

    m_power += m_maxColour[0] * m_maxColour[1] * m_maxColour[2];

    m_maxColour[0] = 0;
    m_maxColour[1] = 0;
    m_maxColour[2] = 0;
}

int Games::getPower(){
    return m_power;
}

bool Games::validateInput(int num,  string colour){

    bool valid = false;

    if(colour == "red"){

        if(num > m_maxColour[0]){
            m_maxColour[0] = num;
        }

        if(num <= 12){
            valid = true;
        }
    }

    else if(colour == "blue"){

        if(num > m_maxColour[1]){
            m_maxColour[1] = num;
        }

        if(num <= 14){
            valid = true;
        }
    }

    else if(colour == "green"){

        if(num > m_maxColour[2]){
            m_maxColour[2] = num;
        }

        if(num <= 13){
            valid = true;
        }
    }

    return valid;
}

void Games::processInput(string unpunctLine){

    stringstream inputStream(unpunctLine);

    string gameWord;
    int id;

    inputStream >> gameWord >> id;

    string colour;
    int num;

    bool canAdd = true;
    bool valid = false;

    while(inputStream >> num >> colour){

        valid = validateInput(num , colour);

        if(!valid){
            canAdd = false;
        }
    }

    if(canAdd){
        m_validIds.push_back(id);
    }
}

int main()
{
    Games data;

    string inputFileName = "day2.txt";

    ifstream inputFile(inputFileName);

    if(!inputFile.is_open()){
        return -1;
    }

    string line;

    while(getline(inputFile, line)){

        string unpunctLine = removePunctuations(line);

        data.processInput(unpunctLine);
        data.updatePower();
    }

    cout << "Sum = " << data.getSum() << endl;
    cout << "Powers = " << data.getPower() << endl;

    return 0;
}


string removePunctuations(string& str){

    string result = "";

    for (char punc : str) {

        if (!ispunct(punc)) {

            result += punc;
        }
    }

    str = result;

    return str;
}
