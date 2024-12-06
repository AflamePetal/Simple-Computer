#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream>
#include <unordered_map>

using namespace std;

#define FILE_NAME "TuringLongDivision.asm" //Change it to the LOCATION\NAME of your file that you want to assemble

#define HEX true         // Change it to 'true' if you want the hex output instead of bin
#define FOR_LOGISIM true // Change it to 'true' if It's for using in logism

// This output function will create a text file containing machine\hex code.
void output(const bitset<32> binNum, ofstream *txtFile)
{
    if (HEX)
        *txtFile << hex << binNum.to_ulong() << endl;
    else
        *txtFile << binNum << endl;
}

int main()
{
    // We'll then use this as instructions map
    unordered_map<string, int> instMap = {
        {"JMP", 0}, {"JRP", 1}, {"LDN", 2}, {"STO", 3}, {"SKN", 4},
         {"SUB", 5}, {"ADD", 6}, {"MUL", 7}, {"DIV", 8}, {"HLT", 9}
         };

    //Change the name of the file to the name of the file you want to work on
    ifstream asmFile(FILE_NAME);
    if (!asmFile.is_open())
        cout << "Error, openening the file";

    // This is the file that will contain the machine code
    ofstream txtFile("machineCode.txt", ios::out);
    if(!txtFile.is_open())
        cout << "Error opening the file";

    // specifically for logisim if you want to load an image for the RAM
    if (FOR_LOGISIM)
        txtFile << "v2.0 raw\n";

    string line;
    int loc = 0;
    while (getline(asmFile, line))
    {
        // amitting the comment part of the line if exist
        size_t pos = line.find("--");
        string asmCode = line.substr(0, pos);

        // deleting blank characters at the back of the asmCode
        string whitespaces(" \t\f\v\n\r");
        size_t found = asmCode.find_last_not_of(whitespaces);
        if (found != string::npos)
            asmCode.erase(found + 1);
        else
            asmCode.clear();

        // tokenizing the asmCode into parts for further processes
        stringstream sStr(asmCode);
        string parts[3];
        int idx = 0;
        while (!sStr.eof())
            getline(sStr, parts[idx++], ' ');

        parts[0].pop_back();
        int thisloc = stoi(parts[0], nullptr, 10);

        bitset<32> code(0);
        // converting to machine code
        if (parts[1] == "NUM")
        {
            int num = stoi(parts[2], nullptr, 10);
            bitset<32> code2(num);
            code |= code2;
        }
        else
        {
            bitset<4> inst(instMap[parts[1]]);
            if (parts[2] == "")
                parts[2] = "0";
            int opnd = stoi(parts[2], nullptr, 10);
            bitset<16> operand(opnd);

            string operandStr = operand.to_string();
            string instStr = inst.to_string();
            instStr.append(operandStr);
            bitset<32> code2(instStr);
            code |= code2;
        }
        output(code, &txtFile);
        loc = thisloc + 1;
    }

    txtFile.close();
    asmFile.close();
    return 0;
}
