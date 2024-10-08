#include "curl/curl.h"
#include <iostream>
#include "downloader.h"
#include <thread>
#include <mutex>
#include <queue>

using namespace std;

mutex queue_mutex;
queue<string> download_queue;

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    return fwrite(ptr, size, nmemb, stream);
}

void Downloader::download_file(const string& url) {
    CURL* curl;
    FILE* fp;
    CURLcode res;

    string filename;
    
    log("Starting download: " + url);
    
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(filename.c_str(), "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            log("Error downloading " + url + ": " + curl_easy_strerror(res));
        } else {
            log("Finished downloading: " + url);
        }
        
        fclose(fp);
        curl_easy_cleanup(curl);
    }
}

Downloader::Downloader(const string& output_dir, int max_conc_downloads) {
    output_directory = output_dir;
    max_conc_downloads = max_concurrent_downloads;
}


void Downloader::download_files(const vector<string>& urls) {
    vector<thread> threads;

        for (const auto& url : urls) {
            threads.emplace_back(&Downloader::download_file, this, url);
            if (threads.size() >= max_concurrent_downloads) {
                for (auto& t : threads) {
                    t.join();
                }
                threads.clear();
            }
        }

        for (auto& t : threads) {
            t.join();
        }
}

string Downloader::sanitizeFilename(const string& filename) {
    string sanitized = filename;
    for (char& c : sanitized) {
        if (!(isalnum(c) || c == '.' || c == '_' || c == '-')) {
            c = '_';
        }
    }
    return sanitized;
}
