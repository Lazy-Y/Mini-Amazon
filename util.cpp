#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
string convToLower(string src)
{
    transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
set<string> parseStringToWords(string rawWord) {
    //find the keywords
    rawWord=convToLower(rawWord);
    set<string> keys;
    stringstream words(rawWord);
    while (!words.fail()) {
        string word;
        words >> word;
        int x=0;
        for (unsigned int i=0; i<word.size(); i++) {
            if (ispunct(word[i])) {
                string sub=word.substr(x,i-x);
                x=i+1;
                if (sub.size()>1) {
                    keys.insert(sub);
                }
            }
        }
        string sub=word.substr(x,word.size());
        if (sub.size()>1) {
            keys.insert(sub);
        }
    }
    return keys;
}
