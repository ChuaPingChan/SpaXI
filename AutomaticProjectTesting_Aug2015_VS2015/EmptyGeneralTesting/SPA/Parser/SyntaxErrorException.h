#include <string>
#include <exception>

class SyntaxErrorException : public std::exception
{
public:
    /** Constructor (C strings).
    *  @param message C-style string error message.
    *                 The string contents are copied upon construction.
    *                 Hence, responsibility for deleting the char* lies
    *                 with the caller.
    */
    explicit SyntaxErrorException(const char * message);

    /** Constructor (C++ STL strings).
    *  @param message The error message.
    */
    explicit SyntaxErrorException(const std::string& message);
    
    /** Returns a pointer to the (constant) error description.
    *  @return A pointer to a const char*. The underlying memory
    *          is in possession of the Exception object. Callers must
    *          not attempt to free the memory.
    */
    virtual const char* what() const throw();

protected:
    std::string msg_;
};
