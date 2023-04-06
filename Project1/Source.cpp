#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream commFile;
ofstream outFile;

void ConditionOutput(string seq, int flag, string additional)
{
    if (flag == 1)
    {
        outFile << "< " << seq << " > " << ": Success" << endl;
    }
    else if (flag == 0)
    {
        outFile << "< " << seq << " > " << ": Failed" << endl;
    }
    else
    {
        outFile << "< " << seq << " > " << additional << endl;
    }
}

int main(int argc, char* argv[])
{

    commFile.open(argv[2]);
    outFile.open(argv[3]);
    string method;
    string cOutput;

    while (commFile >> method)
    {
        bool hasLoaded = false;
        ifstream in;
        cOutput = method;

        if (method == "Load")
        {
            string type;
            commFile >> type;
            cOutput += type;
            if (type == "BoardFile")
            {
                string filename;
                commFile >> filename;
                ifstream in(filename);
                if (in.is_open())
                {
                    ConditionOutput(cOutput, 1, "");
                    hasLoaded = true;
                }
                else
                {
                    ConditionOutput(cOutput, 0, "");
                }
            }
        }
    }
}
