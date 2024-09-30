#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <string>
#include <vector>

using namespace std;

void log(const string& message);

class Downloader {
public:
    Downloader(const string& output_dir, int max_conc_downloads);
    void download_files(const vector<string>& urls);

private:
    string getFilename(const string& url, const string& contentDisposition);
    string sanitizeFilename(const string& filename);
    void download_file(const string& url);
    string output_directory;
    int max_concurrent_downloads;
};

#endif // DOWNLOADER_H
