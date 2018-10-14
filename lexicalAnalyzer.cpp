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
    ifstream s;
    vector<Token> tokens;

    Lexer(string _s)
    {
        s.open(_s);
    }

    void generateTokens()
    {
        while (s.peek() != EOF)
        {
            tokens.push_back(nextToken());
        }
        cout << "TOKENS: " << endl;
        printTokens();
    }

    Token nextToken()
    {
        if (idChar(s.peek()))
        {
            return readId();
        }
        return Token(getNewTID(), "temp");
    }

    Token readId()
    {
        string id = "";
        while (true)
        {
            char c;
            s.get(c);
            if (!idChar(c))
            {
                return Token(getNewTID(), id);
            }
            id += c;
        }
    }

    bool idChar(char val)
    {
        if (isalpha(val) || isdigit(val) || val == 'c')
            return true;
        return false;
    }

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