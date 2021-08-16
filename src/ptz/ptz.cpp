#include <ptz/ptz.h>
#include <cjson/cJSON.h>


//----------------PTZ---------------
PTZ::PTZ(const std::string cameraIp) :
	cameraIP(cameraIp)
{};

Token PTZ::login(std::string login, std::string password) {
	const std::string url = "http://" + cameraIP + "/cgi-bin/api.cgi?cmd=Login";	
	HttpRequest req;
	HttpResponse res = req.request({
		url,
		"POST",
		{	
			"Expect:", 
			"Content-Type: application/json"
		},
		"[{"
			"\"cmd\": \"login\","
			"\"action\": 0,"
			"\"param\": {"
				"\"User\": {"
					"\"userName\": \"admin\","
					"\"password\": \"ifyouwanttohave\""
				"}"
			"}"
		"}]"
	});
	cJSON* loginData = cJSON_Parse(res.text.c_str());
	const cJSON* item = NULL;
	cJSON_ArrayForEach(item, loginData) {
		cJSON* value = cJSON_GetObjectItemCaseSensitive(item, "value");
		cJSON* token = cJSON_GetObjectItemCaseSensitive(value, "Token");
		cJSON* name = cJSON_GetObjectItemCaseSensitive(token, "name");
		if (cJSON_IsString(name) && (name->valuestring != NULL)) {
			Token token = name->valuestring;
			return token;
		}
	}		
	return "";
}

bool PTZ::control(Token token, std::string operation) {	
	const std::string url = "http://" + cameraIP + "/cgi-bin/api.cgi?cmd=PtzCtrl&token=" + token;
	
	HttpRequest req;
	HttpResponse res = req.request({
		url,
		"POST",
		{
			"Expect:",
			"Content-Type: application/json"
		},
		"[{"
			"\"cmd\": \"PtzCtrl\","
			"\"action\": 0,"
			"\"param\": {"
				"\"channel\": 0,"
				"\"op\": \"" + operation + "\","
				"\"speed\": 32"
			"}"
		"}]"
		});		
	return true;
}