#ifndef TEST_WEBREQUEST_H
#define TEST_WEBREQUEST_H

#include <curl/curl.h> // For libcurl

class IWebRequest {
public:
    virtual std::string Get(const std::string & url) = 0;
    virtual ~IWebRequest() {}
};

class WebRequest : public IWebRequest {
private:
    const std::string certLocation;
    CURL * curl;
public:
    WebRequest(const std::string & certLocation, bool verbose = false);
    std::string Get(const std::string & url);
    ~WebRequest();
private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
};

#endif //TEST_WEBREQUEST_H
