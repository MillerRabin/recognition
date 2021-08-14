#ifndef http_h

#define http_h
#define CURL_STATICLIB

#include <string>
#include <map>
#include <curl/curl.h>

typedef std::map<std::string, std::string> BodyMap;
typedef std::map<std::string, std::string> HeadersMap;


class HttpRequestParams {
public: 
	const std::string url;
	const std::string method;
	HeadersMap headers;
	BodyMap body;
	HttpRequestParams(const std::string url, const std::string method = "GET", HeadersMap headers = {}, BodyMap body = {});
};

class HttpResponse {
public:
	CURLcode code;
	std::string content;
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
