#include <ptz/ptz.h>

//----------------PTZ---------------
PTZ::PTZ(const std::string cameraIp) :
	cameraIP(cameraIp)
{};

bool PTZ::login(std::string login, std::string password) {
	HttpRequest req;
	HttpResponse res = req.request({ "https://raintech.su" });
	return true;
}
