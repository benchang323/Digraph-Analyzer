// digraph_functions.cpp
// Include header files
#include "digraph_functions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// Use standard strippedlate library
using std::cout;
using std::cin;
using std::endl;
using std::map;
using std::string;
using std::vector;
using std::ifstream;
using std::iterator;
using std::pair;

/**
 * print_initial_results
 * ---------------------
 * Functionality:
 *  Print the initial results
 * 
 * Parameters:
 *  const map<string, vector<string>>& results: map to be printed
 *  const string& arg: order of the search (a, r, c)
 * 
 * Returns:
 *  None
 */
void print_initial_results(const map<string, vector<string>>& results, const string& arg) {
    // ASCII order
    if (arg == "a") {
        // Print results directly from ordered map in direct order
        for (map<string, vector<string>>::const_iterator it = results.begin(); it != results.end(); it++) {
            cout << it->first << ": [";
            for (vector<string>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
                cout << *it2;
                if (it2 != it->second.end() - 1) {
                    cout << ", ";
                }
            }
            cout << "]" << endl;
        }
    }
    // Reverse ASCII order
    else if (arg == "r") {
        // Print results directly from ordered map but in reverse order
        for (map<string, vector<string>>::const_reverse_iterator it = results.rbegin(); it != results.rend(); it++) {
            cout << it->first << ": [";
            for (vector<string>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
                cout << *it2;
                if (it2 != it->second.end() - 1) {
                    cout << ", ";
                }
            }
            cout << "]" << endl;
        }
    }
    // Ordered from largest to smallest, with ties broken by ASCII order
    else if (arg == "c") {
        // Loop through map to store key and size
        vector<pair<string, int>> info;
        for (map<string, vector<string>>::const_iterator it = results.begin(); it != results.end(); it++) {
            info.push_back(pair<string, int>(it->first, it->second.size()));
        }

        // Sort the info vector based on size
        for (long unsigned int i = 0; i < info.size(); i++) {
            for (long unsigned int j = i + 1; j < info.size(); j++) {
                if (info[i].second < info[j].second) {
                    pair<string, int> temp = info[i];
                    info[i] = info[j];
                    info[j] = temp;
                }
                // Sort based on ASCII order if size is same
                else if (info[i].second == info[j].second) {
                    if (info[i].first > info[j].first) {
                        pair<string, int> temp = info[i];
                        info[i] = info[j];
                        info[j] = temp;
                    }
                }
            }
        }

        // Print results based on vector order
        for (long unsigned int i = 0; i < info.size(); i++) {
            cout << info[i].first << ": [";
            for (vector<string>::const_iterator it2 = results.find(info[i].first)->second.begin(); it2 != results.find(info[i].first)->second.end(); it2++) {
                cout << *it2;
                if (it2 != results.find(info[i].first)->second.end() - 1) {
                    cout << ", ";
                }
            }
            cout << "]" << endl;
        }
    }
}

/**
 * in_list
 * -------
 * Functionality:
 *  Check if the word is in the list of di/trigraphs
 * 
 * Parameters:
 *  const string& word: word to be checked
 *  const vector<string>& list: list of di/trigraphs
 * 
 * Returns:
 *  True: if found
 *  False: if not found
 */
bool in_list(const vector<string>& list, const string& word) {
    // Loop through the list to check if word exists
    for (vector<string>::const_iterator it = list.begin(); it != list.end(); it++) {
        if (*it == word) {
            return true;
        }
    }
    return false;
}

/**
 * di_trigraph_search
 * ------------------
 * Functionality:
 *  Search and categorize the di/trigraphs in the input file
 * 
 * Parameters:
 *  const vector<string>& list: list of di/trigraphs
 *  const string& arg: order of the search (a, r, c)
 *  ifstream& input: text file to be searched
 *  
 * Returns:
 *  A map that contains the search results where the key (map<int, string>)
 *  stores the number of occurances and the di/trigraph. The matching words are stored
 *  in vector<string>.
 */
map<string, vector<string>> di_trigraph_search(const vector<string>& list, ifstream& input, const string& arg) {
    // Create a map to store the search results
    map<string, vector<string>> results;

    // Loop through text in the file
    string word;
    while (input >> word) {
        // Loop through the list of di/trigraphs
        for (long unsigned int i = 0; i < list.size(); i++) {
            // Case insensitive, remove punctuation (! . ? ,)
            string stripped = word;
            for (long unsigned int j = 0; j < stripped.size(); j++) {
                stripped[j] = tolower(stripped[j]);
                if (stripped[j] == '!' || stripped[j] == '.' || stripped[j] == '?' || stripped[j] == ',') {
                    stripped.erase(j, 1);
                }
            }
            // Search for di/trigraphs and store results
            if (stripped.find(list[i]) != string::npos) {
                results[list[i]].push_back(stripped);
            }
        }
    }

    // If di/trigraphs not found, store empty vector
    for (long unsigned int i = 0; i < list.size(); i++) {
        if (results.find(list[i]) == results.end()) {
            results[list[i]] = vector<string>();
        }
    }

    // Print
    print_initial_results(results, arg);

    return results;
}