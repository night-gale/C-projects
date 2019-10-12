#include <iostream>
#include <sstream>

using namespace std;

int main(void) {
    cout << "Enter the length of the array" << endl;
    int length = cin.get();
    string line, temp;
    stringstream ss;
    cin.get();  //get the line-switching operator
    cout << "Enter the line" << endl;
    std::getline(cin, line);
    ss << line;
    cout << ss.str() << endl;
    for(int i = 0; i < length; i++) {
        ss >> temp;
        cout << temp << endl;
        cout << ss.str() << endl;
    }
    cin.get();
}