#include <string>
#include <curl/curl.h>
#include <iostream>
#include "HttpClient.h"

HttpClient::HttpClient(const std::string &certLocation, bool verbose)
:certLocation(certLocation)
,verbose(verbose)
{
}

std::future<std::string> HttpClient::GetAsync(const std::string &url) {
    return std::async(std::launch::async, [this, url]() -> std::string {
        auto curl = curl_easy_init();
        CURLcode res;
        try
        {
            curl_easy_setopt(curl, CURLOPT_CAINFO, certLocation.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_VERBOSE, verbose);
            std::string readBuffer;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            return readBuffer;
        }
        catch (const std::exception & e)
        {
            std::cout << e.what() << std::endl;
            curl_easy_cleanup(curl);
        };
        if (!curl) {
            throw new std::exception("Could not initialise curl.");
        }
        if (res != CURLE_OK) {
            auto error = std::string("cURL error: ") + curl_easy_strerror(res);
            throw new std::exception(error.c_str());
        }
    });
}

HttpClient::~HttpClient()
{
}

size_t HttpClient::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp)
{
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}
