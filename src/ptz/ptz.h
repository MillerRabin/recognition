#ifndef ptz_h

#define ptz_h

#include <string>
#include <http/http.h>

typedef std::string Token;

class PTZ {
private:
	const std::string cameraIP;
public:
	PTZ(const std::string cameraIp);
	Token login(std::string login, std::string password);
	bool control(Token token, std::string operation);
};


#endif
