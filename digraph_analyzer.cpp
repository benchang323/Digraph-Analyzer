// digraph_analyzer.cpp
// Include header files 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "digraph_functions.h"

// Use standard template library
using std::cout;
using std::cin;
using std::endl;
using std::map;
using std::string;
using std::vector;
using std::ifstream;
using std::iterator;
using std::pair;


int main(int argc, char * argv[]) {
  // Error check for number of arguments
  if (argc != 3) {
    cout << "Invalid arguments!";
    return 1;
  }

  // Error check for the order of arguments
  string order(argv[2]);
  if (order != "r" && order != "a" && order != "c") {
    cout << "Invalid arguments!";
    return 1;
  }

  // Store the argument (a, r, c)
  string arg(argv[2]);

  // Open input file and do error check
  ifstream input(argv[1]);
  if (!input) {
    cout << "Could not open file!";
    return 1;
  }

  // Scan for the first positive integer
  int num = 0;
  input >> num;

  // Scan for the list of di/trigraphs
  vector<string> list;
  string temp;
  for (int i = 0; i < num; i++) {
    input >> temp;
    // Case insensitive
    for (long unsigned int j = 0; j < temp.length(); j++) {
      temp[j] = tolower(temp[j]);
    }
    list.push_back(temp);
  }

  // Map to store search results
  map<string, vector<string>> results;
  results = di_trigraph_search(list, input, arg);

  // Query section of program
  string query;
  while (query != "exit") {
    cout << "q?>";
    cin >> query;

    // Case insensitive
    for (long unsigned int i = 0; i < query.length(); i++) {
      query[i] = tolower(query[i]);
    }

    // Check if di/trigraph query exists
    if (!in_list(list, query) && query != "exit" && !isdigit(query[0])) {
      cout << "No such digraph" << endl;
    }
    // Check if query is an integer
    else if (isdigit(query[0])) {
      // Search for corresponding maps
      bool found = false;
      for (map<string, vector<string>>::iterator it = results.begin(); it != results.end(); it++) {
        // Loop through the map and compare the integer
        if ((int)it->second.size() == stoi(query)) {
          found = true;
          cout << it->first << ": [";
          for (long unsigned int i = 0; i < it->second.size(); i++) {
            cout << it->second[i];
            // Comma for all but last
            if (i != it->second.size() - 1) {
              cout << ", ";
            }
          }
          cout << "]"<< endl;
        }
      }
      if (!found) {
        cout << "No such digraph" << endl;
      }
    }
    // Check if query is a di/trigraph
    else if (in_list(list, query)) {
      // Print the result based on the query key
      cout << results[query].size() << ": [";
      for (long unsigned int i = 0; i < results[query].size(); i++) {
        cout << results[query][i];
        // Comma for all but last
        if (i != results[query].size() - 1) {
          cout << ", ";
        }
      }
      cout << "]" << endl;
    }

    // End program on "exit"
    if (query == "exit") {
      break;
    }
  }
  return 0;
}