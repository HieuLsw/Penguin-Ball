#include <iostream>
#include <cstdlib>

using namespace std;

void printGreeting(int population) {
    if (population == 0) {
        cout << "And then there were none..." << endl;
    }
    else if (population < 100) {
        cout << "It's a small world after all!" << endl;
    }
    else {
        cout << "It's a big world out there!" << endl;
    }
    return;
}

int main() {
    cout << "Hello World!" << endl;
    cout << "How many people are there?" << endl;
    int pop;
    cin >> pop;
    printGreeting(pop);
    cout << "Goodbye World!" << endl;
    return 0;
}
