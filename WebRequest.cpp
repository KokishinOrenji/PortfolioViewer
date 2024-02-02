#include <string>
#include <curl/curl.h>
#include <iostream>
#include "WebRequest.h"

WebRequest::WebRequest(const std::string &certLocation, bool verbose)
:certLocation(certLocation)
{
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_CAINFO, certLocation.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, verbose);
}

std::string WebRequest::Get(const std::string & url)
{
    CURLcode res;
    std::string readBuffer;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        std::cout << readBuffer << std::endl; // Print the response to standard output
    }
    return readBuffer;
}
WebRequest::~WebRequest()
{
    curl_easy_cleanup(curl);
}

size_t WebRequest::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp)
{
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}
