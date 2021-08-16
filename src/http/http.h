#ifndef http_h

#define http_h
#define CURL_STATICLIB

#include <string>
#include <vector>
#include <curl/curl.h>
#include <cjson/cJSON.h>

typedef std::vector<std::string> Headers;

class HttpRequestParams {
public: 
	const std::string url;
	const std::string method;
	Headers headers;
	std::string body;
	HttpRequestParams(const std::string url, const std::string method = "GET", Headers headers = {}, std::string body = "");
};

class HttpResponse {
public:
	CURLcode code;
	std::string text;
};


class HttpRequest {
public: 
	static size_t HttpRequest::write_data(char* ptr, size_t size, size_t nmemb, std::string* data);
	static unsigned int refCount;
	HttpRequest();
	~HttpRequest();
	HttpResponse request(HttpRequestParams params);
};

#endif // !http
