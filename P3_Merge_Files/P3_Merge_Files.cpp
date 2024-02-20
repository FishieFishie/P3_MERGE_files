// P3_Merge_Files.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <algorithm>

//<string> allows us to interact and manipulate a string of characters for the provided txt files
//<vector> allows us to work with lists; in addition, it allows us to create an additional list
//<algorithm> allows us addtional help with lists such as sorting and searching

using namespace std;
//Throughout this program, we will be reusing string and vector multiple times
struct Entry {
    string key;
    string data;
};
//Throughout this program, we will be seeing multiple ...const... and ...&... 
//'const' indicates that the string, or filename, can't be altered/modified meanwhile, '&' allows changes we want to make

//Establish a function to merge two sorted vectors of entries
vector<Entry> MERGEentries(const vector<Entry>& entry1, const vector<Entry>& entry2) {
    vector<Entry> merged;
    int i = 0, j = 0;
    while (i < entry1.size() && j < entry2.size()) {
        if (entry1[i].key < entry2[j].key) {
            merged.push_back(entry1[i++]);
        }
        else {
            merged.push_back(entry2[j++]);
        }
    }
    while (i < entry1.size()) {
        merged.push_back(entry1[i++]);
    }
    while (j < entry2.size()) {
        merged.push_back(entry2[j++]);
    }
    return merged;
}

//Establish a function to read entries from the provided files
vector<Entry> READentries(const string& filename) {
    ifstream file(filename);
    vector<Entry> entries;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Entry entry;
            entry.key = line.substr(0, line.find(','));
            entry.data = line;
            entries.push_back(entry);
        }
        file.close();
    }
    else {
        cout << "Error: Unable to open file " << filename << "." << endl;
    }
    return entries;
}

//Establish a function to write both entries into one file, the OUTPUT.txt file
void WRITTENentries(const vector<Entry>& entries, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& entry : entries) {
            file << entry.data << endl;
        }
        file.close();
    }
    else {
        cout << "Error: Unable to open file " << filename << " for writing." << endl;
    }
}

int main() {

    //Read entries from both files, the file1 and file2.txt
    vector<Entry> entry1 = READentries("file1.txt");
    vector<Entry> entry2 = READentries("file2.txt");

    //Merge the entries, or rather combine it into one file, the OUTPUT.txt file
    vector<Entry> merged = MERGEentries(entry1, entry2);

    //Give the merged entries a name, "OUTPUT.txt"
    WRITTENentries(merged, "OUTPUT.txt");

    //Confirm that the merge is successful in the output
    cout << "Merged Successful!" << endl;

    return 0;
}