// digraph_functions.h
// Header guard
#ifndef DIGRAPH_FUNCTIONS_H
#define DIGRAPH_FUNCTIONS_H

// Include header files
#include <map>
#include <string>
#include <vector>
#include <fstream>

/**
 * di_trigraph_search
 * ------------------
 * Functionality:
 *  Search and categorize the di/trigraphs in the input file
 * 
 * Parameters:
 *  const std::vector<std::string>& list: list of di/trigraphs
 *  const std::string& arg: order of the search (a, r, c)
 *  ifstream& input: text file to be searched
 *  
 * Returns:
 *  A std::map that contains the search results where the di/trigraphs are the keys that stores the words that contain the di/trigraphs
 */
std::map<std::string, std::vector<std::string>> di_trigraph_search(const std::vector<std::string>& list, std::ifstream& input, const std::string& arg);

/**
 * in_list
 * -------
 * Functionality:
 *  Check if the word is in the list of di/trigraphs
 * 
 * Parameters:
 *  const std::string& word: word to be checked
 *  const std::vector<std::string>& list: list of di/trigraphs
 * 
 * Returns:
 *  True: if found
 *  False: if not found
 */
bool in_list(const std::vector<std::string>& list, const std::string& word);

/**
 * print_initial_results
 * ---------------------
 * Functionality:
 *  Print the initial results
 * 
 * Parameters:
 *  const std::map<std::string, std::vector<std::string>>& results: std::map to be printed
 *  const std::string& arg: order of the search (a, r, c)
 * 
 * Returns:
 *  None
 */
void print_initial_results(const std::map<std::string, std::vector<std::string>>& results, const std::string& arg);

// End of header guard
#endif