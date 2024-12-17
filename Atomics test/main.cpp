#include <iostream>
#include <string>
#include <pthread.h>//unix utility, won`t work on windows
#include <vector>
#include <cctype>
#include <atomic> // Added for atomic operations
using namespace std;

// Global variables
string phrase;
vector<string> words;
atomic<int> indexx{ 0 }; // Using atomic integer

void* alpha(void*);
void* numeric(void*);
void splitInputPhrase();

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cout << "Enter a phrase" << endl;
        getline(cin, phrase);
    }

    splitInputPhrase();

    pthread_t tid_alpha_thread;
    pthread_t tid_numeric_thread;
    pthread_create(&tid_alpha_thread, NULL, alpha, NULL);
    pthread_create(&tid_numeric_thread, NULL, numeric, NULL);

    pthread_join(tid_alpha_thread, NULL);
    pthread_join(tid_numeric_thread, NULL);

    return 0;
}

void* alpha(void* arg) {
    do {
        // Using atomic operations to increment indexx and get the current value
        int current_index = indexx++;
        if (current_index >= words.size()) break; // Make sure we don't go out of bounds
        if (isalpha(words[current_index][0]) || ispunct(words[current_index][0])) {
            cout << "alpha: " << words[current_index] << endl;
        }
    } while (true);

    pthread_exit(0);
}

void* numeric(void* arg) {
    do {
        // Using atomic operations to increment indexx and get the current value
        int current_index = indexx++;
        if (current_index >= words.size()) break; // Make sure we don't go out of bounds
        if (isdigit(words[current_index][0])) {
            cout << "numeric: " << words[current_index] << endl;
        }
    } while (true);

    pthread_exit(0);
}

void splitInputPhrase() {
    string word = "";
    for (char c : phrase) {
        if (c == ' ') {
            words.push_back(word);
            word = "";
        }
        else {
            word += c;
        }
    }
    words.push_back(word);
}