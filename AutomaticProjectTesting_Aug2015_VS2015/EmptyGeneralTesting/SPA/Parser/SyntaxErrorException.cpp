#include <string>

#include "SyntaxErrorException.h"

using namespace std;

SyntaxErrorException::SyntaxErrorException(const char* message)
    :msg_(message)
{}

SyntaxErrorException::SyntaxErrorException(const string& message)
    :msg_(message)
{}

const char * SyntaxErrorException::what() const throw() {
    return msg_.c_str();
}

