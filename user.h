#ifndef USER_H
#define USER_H

#include <string>

/*
 * Class: User
 * Purpose: Base class for all users (students and teachers).
 *          Stores common fields like name, email, and password.
 *          Provides basic validation helpers and accessors.
 */
class User {
protected:
    std::string name;      // full name of the user
    std::string email;     // user email, used as a unique login field
    std::string password;  // user password in plain text (for demo only)

public:
    User();
    User(const std::string& name,
         const std::string& email,
         const std::string& password);

    // Getters
    std::string getName() const;
    std::string getEmail() const;
    std::string getPassword() const;

    // Setters
    void setName(const std::string& value);
    void setEmail(const std::string& value);
    void setPassword(const std::string& value);

    // Basic validation helpers
    static bool isNonEmpty(const std::string& value);
    static bool isValidEmail(const std::string& value);
    static bool isValidPassword(const std::string& value);
    static bool containsComma(const std::string& value);
};

#endif
