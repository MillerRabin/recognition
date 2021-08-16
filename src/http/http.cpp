#include <http/http.h>

//------------HttpRequestParams-----------------

HttpRequestParams::HttpRequestParams(const std::string url, const std::string method, Headers headers, std::string body) :
	url(url),
	method(method),
	headers(headers),
	body(body)
{}

//-----------HttpRequest-------------

unsigned int HttpRequest::refCount = 0;

size_t HttpRequest::write_data(char* ptr, size_t size, size_t nmemb, std::string* data)
{
	if (!data) return 0;
	data->append(ptr, size * nmemb);
	return size * nmemb;	
}

HttpRequest::HttpRequest() {
	if (refCount == 0)
		curl_global_init(CURL_GLOBAL_DEFAULT);
	refCount++;
}

HttpRequest::~HttpRequest() {
	refCount--;
	if (refCount == 0)
		curl_global_cleanup();	
}

HttpResponse HttpRequest::request(HttpRequestParams params) {
	CURL* curl = curl_easy_init();
		
	struct curl_slist* headers = NULL;
	for (auto& item : params.headers) {
		headers = curl_slist_append(headers, item.c_str());
	}
	
	if (!curl)
		return { CURLE_FAILED_INIT };

	std::string content;
	
	curl_easy_setopt(curl, CURLOPT_URL, params.url.c_str());
	
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	if (params.body != "") {
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.body.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, -1L);
	}

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HttpRequest::write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);	
	CURLcode res = curl_easy_perform(curl);	
	curl_easy_cleanup(curl);
	return { res, content };
}

