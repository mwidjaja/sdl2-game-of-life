#ifndef _INCLUDED_EXCEPTION_H
#define _INCLUDED_EXCEPTION_H

#include <stdexcept>

class SDLException : public std::runtime_error {
	public:
		explicit SDLException(const std::string& what) :
			std::runtime_error(what) {  }
		explicit SDLException(char const *what) :
			std::runtime_error(what) { }

};
#endif // _INCLUDED_EXCEPTION_H
