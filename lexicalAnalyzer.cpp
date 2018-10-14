#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

static int tokenID = 0;

int getNewTID()
{
    int tkn = tokenID;
    tokenID++;
    return tkn;
}

class Token
{
  public:
    int TID;
    string val;

    Token()
    {
        this->TID = -1;
        this->val = -1;
    }

    Token(int id, string val)
    {
        this->TID = id;
        this->val = val;
    }
};

class Lexer
{
  public:
    ifstream s; // inputFile
    vector<Token> tokens; // list of tokens

    // constructor. opens input file from given file name.
    Lexer(string _s)
    {
        s.open(_s);
    }

    // generates tokens from given file
    void generateTokens()
    {
        while (s.peek() != EOF) // until file reaches it's end
        {
            tokens.push_back(nextToken()); // get token and add to token list
        }
        cout << "TOKENS: " << endl;
        printTokens();
    }

    // gets next token from file
    Token nextToken()
    {
        if (idChar(s.peek())) // if next input from file is char
        {
            return readId();
        }
        return Token(getNewTID(), "temp"); // temp
    }

    Token readId()
    {
        string id = "";
        while (true)
        {
            char c;
            s.get(c);
            if (!idChar(c)) // get new char from file, if it is char then append to current token
            {
                return Token(getNewTID(), id); // generate new token if keyword has finished (i.e. next input isn't char)
            }
            id += c; // append char to current token
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
};

int main()
{
    string inputFileName = "text.txt";
    Lexer lexer(inputFileName);

    lexer.generateTokens();
    return 0;
}