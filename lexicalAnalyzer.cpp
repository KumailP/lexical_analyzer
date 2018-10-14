#include <iostream>
#include <fstream>

using namespace std;

class Lexer
{
  public:
    ifstream s;
    char next;

    Lexer(string _s)
    {
        s.open(_s);
        s.get(next);
        cout << "Value of next is: " << next;
    }
};

int main()
{
    string inputFileName = "text.txt";
    Lexer lexer(inputFileName);
    return 0;
}