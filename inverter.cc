// Project 1 - Implementation of an inverted index.
// @file inverter.cc
// @author Kevin Li
// The Slack Code: scheduler

#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;


/*
 * Reads a file, separates strings in the file by
 * spaces, then returns a string vector that contains
 * all the strings.
 * @param textname: the name of the file that
 * 		we want to open and read.
 * @return a vector containing strings of the
 * 		file that was read.
 */
vector<string> readtext(string textname) {
    vector<string> text_vector;
    ifstream fileStream;
    fileStream.open(textname);
    string word;
    while (fileStream >> word) {
        text_vector.push_back(word);
    }	
    return text_vector;
}


/*
 * Filters a string vector by iterating through the
 * vector and seeing if there are any non-alpha
 * characters in each string. If all characters in
 * a string are alpha characters, we leave the string
 * as is and push it into a new 'filtered' string vector.
 * If there are non-alpha characters in a string,
 * we split the string into multiple strings based
 * off of the non-alpha characters, then push it into
 * the new vector.
 * @param curr_file_words: the 'unfiltered' string
 * 			vector of strings from a file
 * @return a 'filtered' string vector
 */
vector<string> filter(vector<string> curr_file_words) {
    vector<string> filter_words;
    string curr_word;
    for (unsigned int i = 0; i < curr_file_words.size(); i++) {
	curr_word = curr_file_words[i];
	if (all_of(curr_word.begin(), curr_word.end(), \
				[](char c) {return isalpha(c);})) {
	    filter_words.push_back(curr_word);
	}
	else {
	    vector<string> divide_word;
	    string sub_word = "";
	    for (unsigned int i = 0; i < curr_word.size(); i++) {
	        if (isalpha(curr_word[i])) {
		    sub_word += curr_word[i];
		}
		else {
		    if (sub_word != "") {
		        divide_word.push_back(sub_word);
		        sub_word = "";
		    }
		}
            }
	    if (sub_word != "") {
	        divide_word.push_back(sub_word);
	        sub_word = "";
	    }
            for (string word: divide_word) {
	        filter_words.push_back(word);
	    }
        }
    }
    return filter_words;
}


/*
 * A function that populates the map structure
 * of the inverted index. Uses functions
 * readtext() and filter(). Iterates a string
 * vector that contains the names of the files
 * that will be included in the inverted index.
 * We read all the strings inside each file and
 * filters it of non-alpha characters. Then, we
 * iterate through the strings of that file,
 * add new strings and the file number to the
 * map, or add the file number to existing keys
 * of the map.
 * @param files: the string vector that contains
 * 	the names of the files that's strings
 * 	will be added to the inverted index.
 * @return a map that represents and inverted
 * 	index.
 */
map<string, set<int>> populate_map(vector<string> files) {     
    vector<string> curr_file_words; 
    map<string, set<int>> invertedIndex;
    unsigned int file_counter = 0;
    for (string file: files) {
	set<int> curr_file_num;
	ifstream fileStream;
        fileStream.open(file);
	if (fileStream) {
	    curr_file_words = readtext(file);
            curr_file_words = filter(curr_file_words);
            for (unsigned int i = 0; i < curr_file_words.size(); i++) {
                if (invertedIndex.find(curr_file_words[i]) \
				== invertedIndex.end()) {
                    curr_file_num.insert(file_counter);
	            invertedIndex.insert(make_pair(curr_file_words[i],\
					    curr_file_num));
	        }
	        else {
	            set<int> exist_set = invertedIndex[curr_file_words[i]];
	            exist_set.insert(file_counter);
	            invertedIndex[curr_file_words[i]] = exist_set;
                }
            }
	    file_counter++;
	}
    }
    return invertedIndex;
}


/*
 * Prints the content in the inverted index
 * map in the required format for the
 * autograder.
 * @param invertedIndex: the inverted index
 * 			map structure.
 * @return none
 *
 */
void print_output(map<string, set<int>> invertedIndex) { 
    for (auto& elem: invertedIndex) {
	string file_nums;
	for (auto& num: elem.second) {
            file_nums += " " + to_string(num);
	}
	cout << elem.first << ":" << file_nums << endl;
    }
}

/*
 * Main function
 */
int main(int argc, char** argv) {
    map<string, set<int>> invertedIndex;
    vector<string> files;
    files = readtext(argv[1]);
    invertedIndex = populate_map(files);
    print_output(invertedIndex);
    return 0;
}


