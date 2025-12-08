#include "User.h"
#include <cctype>   // for std::isspace

User::User() : name(""), email(""), password("") {}

User::User(const std::string& name,
           const std::string& email,
           const std::string& password)
    : name(name), email(email), password(password) {}

std::string User::getName() const {
    return name;
}

std::string User::getEmail() const {
    return email;
}

std::string User::getPassword() const {
    return password;
}

void User::setName(const std::string& value) {
    name = value;
}

void User::setEmail(const std::string& value) {
    email = value;
}

void User::setPassword(const std::string& value) {
    password = value;
}

/*
 * Function: isNonEmpty
 * Purpose:  Checks that a string is not empty and not just whitespace.
 */
bool User::isNonEmpty(const std::string& value) {
    if (value.empty()) {
        return false;
    }
    for (char ch : value) {
        if (!std::isspace(static_cast<unsigned char>(ch))) {
            return true;
        }
    }
    return false;
}

/*
 * Function: isValidEmail
 * Purpose:  Performs a simple email validation by checking for '@' and '.'.
 *           This is intentionally simple for this assignment.
 */
bool User::isValidEmail(const std::string& value) {
    std::size_t atPos = value.find('@');
    std::size_t dotPos = value.find('.');
    return (atPos != std::string::npos &&
            dotPos != std::string::npos &&
            atPos < dotPos);
}

/*
 * Function: isValidPassword
 * Purpose:  Enforces a minimum password length for basic security.
 */
bool User::isValidPassword(const std::string& value) {
    const std::size_t MIN_LENGTH = 4; // simple demo rule
    return value.length() >= MIN_LENGTH;
}

/*
 * Function: containsComma
 * Purpose:  Checks whether a string contains a comma.
 *           We disallow commas to keep CSV parsing simple and safe.
 */
bool User::containsComma(const std::string& value) {
    return value.find(',') != std::string::npos;
}
