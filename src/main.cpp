#include "curl/curl.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include "downloader.h"

using namespace std;
using namespace std::chrono;

string current_time() {
    auto now = system_clock::now();
    auto time_now = system_clock::to_time_t(now);
    ostringstream oss;
    oss << put_time(localtime(&time_now), "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void log(const string& message) {
    cout << "[" << current_time() << "] " << message << endl;
}

int main() {

    string urls_file;
    string output_directory;
    int max_concurrent_downloads;

    cin >> urls_file >> output_directory >> max_concurrent_downloads;

    log("Starting program");
    log("Parameters: " + urls_file + ", " + output_directory + ", " + to_string(max_concurrent_downloads));

    vector<string> urls;
    ifstream infile(urls_file);
    string url;

    while (getline(infile, url)) {
        if (!url.empty()) {
            urls.push_back(url);
        }
    }

    Downloader downloader(output_directory, max_concurrent_downloads);
    downloader.download_files(urls);

    log("Program finished");
    return 0;
}
