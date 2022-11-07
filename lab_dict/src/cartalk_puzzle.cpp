/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    string s, w1, w2;
    ifstream file(word_list_fname);
    if (file.is_open()) {
        while (getline(file, s)) {
            if (s.size()==5) {
                w1= s.substr(1, s.size()-1);
                w2= s[0] + s.substr(2,s.size()-1);
                if (d.homophones(s,w1)&&d.homophones(s,w2)) {
                    ret.push_back(tuple<string, string, string>(s, w1, w2));
                }
            }
        }
    }
    file.close();
    return ret;
}
