#include <exception>

class argumentsException : public std::exception {
private:
    char* message;

public:
    argumentsException(char* msg) : message(msg) {}
    char* what() {
        return message;
    }
};

class fileException : public std::exception {
private:
    char* message;

public:
    fileException(char* msg) : message(msg) {}
    char* what() {
        return message;
    }
};

class notImplementedException : public std::exception {
private:
    char* message;

public:
    notImplementedException(char* msg) : message(msg) {}
    char* what() {
        return message;
    }
};
