#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#define MAX_LEN 1000

using namespace std;

void PrintCSVLine(const vector<string>& line_data) {
    for (const string& str : line_data) {
        cout << str << " ";
    }
    cout << endl;
}

vector<vector<string>> readCSV(const string& filename) {
    ifstream file(filename);
    vector<vector<string>> data;
    string line;

    while (getline(file, line)) {
        vector<string> row;
        istringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }

    file.close();
    return data;
}

void ReadAll() {
    string fname = "D:\\C++Programming\\project\\original_data.csv";
    ifstream csv_data(fname);

    if (!csv_data.is_open()) {
        cout << "Error: opening file fail" << endl;
        exit(1);
    }
    else {
        string line;
        vector<string> words;
        // 读取标题行
        getline(csv_data, line);

        istringstream sin;
        // 按行读取数据
        while (getline(csv_data, line)) {
            words.clear();
            sin.clear();

            sin.str(line);
            while (getline(sin, line, ',')) {
                words.push_back(line);
            }

            PrintCSVLine(words);
        }

        csv_data.close();
    }
}

void ReadTheSpecifiedLine() {
    int num;
    cin >> num;
    FILE* fp;
    char line[MAX_LEN];
    const char* filename = "D:\\C++Programming\\project\\original_data.csv";
    int line_num = num;

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    int current_line = 0;

    while (fgets(line, MAX_LEN, fp)) {
        if (current_line == line_num - 1) {
            char* token;
            token = strtok(line, ",");
            while (token != NULL) {
                printf("%s", token);
                token = strtok(NULL, ",");
            }
            break;
        }
        current_line++;
    }

    fclose(fp);
}

void VerifyTheData(const string& accurateFile, const string& erroneousFile) {
    vector<vector<string>> accurateData = readCSV(accurateFile);
    vector<vector<string>> erroneousData = readCSV(erroneousFile);

    if (accurateData.size() != erroneousData.size()) {
        cout << "The number of rows is inconsistent" << endl;
        //return;
    }

    for (size_t i = 0; i < accurateData.size(); i++) {
        if (accurateData[i].size() != erroneousData[i].size()) {
            cout << "line number " << i + 1 << " The number of rows and columns is inconsistent" << endl;
            //continue;
        }

        for (size_t j = 0; j < accurateData[i].size(); j++) {
            if (accurateData[i][j] != erroneousData[i][j]) {
                cout << "Data to be corrected:line number;" << i + 1 << " Column number;" << j + 1
                    << " The original value is:" << erroneousData[i][j]
                    << ";It should be corrected as: " << accurateData[i][j] << endl;
            }
        }
    }
}

int main() {
    cout << "\033[32;1mSelect mode: Read All or Read The Specified Line or Verify The Data\033[0m" << endl
        << "\033[32;1mSelect Read All Please type ALL, Select Read by Line Please type LINE and Enter The line Number, Select Verify The Data Please type VERIFY\033[0m"
        << endl;

    string input;
    cin >> input;

    if (input == "ALL") {
        ReadAll();
    }
    else if (input == "LINE") {
        ReadTheSpecifiedLine();
    }
    else if (input == "VERIFY") {
        VerifyTheData("D:\\C++Programming\\project\\original_data.csv", "D:\\C++Programming\\project\\data_for_check.csv");
    }
    else {
        cout << "\033[31;1mERROR!!! UNABLE TO SUPPORT THIS MODE!!! CHECK THAT YOUR INPUT IS IN THE CORRECT FORMAT!!!\033[0m" << endl;
    }

    system("pause");
    return 0;
}