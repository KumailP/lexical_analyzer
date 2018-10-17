#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

static int ID_TID = 0;
static int NUM_TID = 0;
static int STR_TID = 0;

string getTID(string type)
{
    if (type == "id")
    {
        ID_TID++;
        return "ID(" + to_string(ID_TID) + ")";
    }
    if (type == "num")
    {
        NUM_TID++;
        return "NUM(" + to_string(NUM_TID) + ")";
    }
    if (type == "str")
    {
        STR_TID++;
        return "STR(" + to_string(STR_TID) + ")";
    }
    return "err";
}

class Token
{
  public:
    string TID;
    string val;

    Token()
    {
        this->TID = -1;
        this->val = -1;
    }

    Token(string id, string val)
    {
        this->TID = id;
        this->val = val;
    }
};

class Lexer
{
  public:
    ifstream s;           // inputFile
    ofstream outputFile;  //outputFile
    vector<Token> tokens; // list of tokens

    // constructor. opens input file from given file name.
    Lexer(string _s)
    {
        s.open(_s.c_str());
    }

    // generates tokens from given file
    void generateTokens()
    {
        while (s.peek() != EOF) // until file reaches it's end
        {
            char next = s.peek();
            if (next == 13 || next == 10 || next == 32) // ignore CR, 
            {
                s.get();
            }
            else
            {
                tokens.push_back(nextToken()); // get token and add to token list
            }
        }
        cout << "TOKENS: " << endl;
        printTokens();
    }

    // gets next token from file
    Token nextToken()
    {
        if (isalpha(s.peek()) || s.peek() == '_') // if next input from file is char
        {
            return readId();
        }
        if (isdigit(s.peek()))
        {
            return readNumber();
        }
        if ((char)s.peek() == '"')
        {
            return readString();
        }
        cout << "next: " << s.peek() << endl;
        return Token("error", "error"); // temp
    }

    Token readString()
    {
        string str = "";
        s.get();
        while (true)
        {
            if (s.peek() != EOF)
            {
                char c;
                s.get(c);
                if (c == '"')
                {
                    s.get();
                    return Token(getTID("str"), str);
                }
                str += c;
            }
            else
            {
                return Token(getTID("str"), str);
            }
        }
    }

    Token readNumber()
    {
        string num = "";
        while (true)
        {
            if (s.peek() != EOF)
            {
                char c;
                s.get(c);
                if (!isdigit(c))
                {
                    return Token(getTID("num"), num);
                }
                num += c;
            }
            else
            {
                return Token(getTID("num"), num);
            }
        }
    }

    Token readId()
    {
        string id = "";
        while (true)
        {
            if (s.peek() != EOF)
            {
                char c;
                s.get(c);
                if (!idChar(c)) // get new char from file, if it is char then append to current token
                {
                    return Token(getTID("id"), id); // generate new token if keyword has finished (i.e. next input isn't char)
                }
                id += c; // append char to current token
            }
            else
            {
                return Token(getTID("id"), id);
            }
        }
    }

    // return true if argument is alphabet, digit or _
    bool idChar(char val)
    {
        if (isalpha(val) || isdigit(val) || val == '_')
            return true;
        return false;
    }

    // print token list
    bool printTokens()
    {
        for (unsigned int i = 0; i < tokens.size(); i++)
        {
            cout << "<" << tokens[i].TID << "," << tokens[i].val << ">" << endl;
        }
        return true;
    }

    void printTokensInFile(string outFile){
        outputFile.open(outFile.c_str()); 
        for (unsigned int i = 0; i < tokens.size(); i++)
        {
            outputFile << "<" << tokens[i].TID << "," << tokens[i].val << ">" << endl;
        }       
    }
};

int main()
{
    string inputFileName = "text.txt";
    string outputFileName = "outputFile.txt";
    Lexer lexer(inputFileName);

    lexer.generateTokens();
    lexer.printTokensInFile(outputFileName);
    return 0;
}
