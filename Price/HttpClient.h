#ifndef PORTFOLIOVIEWER_HTTPCLIENT_H
#define PORTFOLIOVIEWER_HTTPCLIENT_H

#include <curl/curl.h> // For libcurl
#include <future>

class IHttpClient {
public:
    virtual std::future<std::string> GetAsync(const std::string & url) = 0;
    virtual ~IHttpClient() {}
};

class HttpClient : public IHttpClient {
private:
    const std::string certLocation;
    const bool verbose;
public:
    HttpClient(const std::string & certLocation, bool verbose = false);
    std::future<std::string> GetAsync(const std::string & url);
    ~HttpClient();
private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
};

#endif //PORTFOLIOVIEWER_HTTPCLIENT_H
