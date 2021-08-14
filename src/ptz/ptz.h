#ifndef ptz_h

#define ptz_h

#include <string>
#include <http/http.h>

class PTZ {
private:
	const std::string cameraIP;
public:
	PTZ(const std::string cameraIp);
	bool login(std::string login, std::string password);
};


#endif
