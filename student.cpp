#include "Student.h"
#include <sstream>
#include <vector>

/*
 * Helper Function: splitCSVLine
 * Purpose: Splits a CSV line into tokens separated by commas.
 */
static std::vector<std::string> splitCSVLine(const std::string& line) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(line);

    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    return tokens;
}

Student::Student() : User(), studentId(0) {}

Student::Student(int id,
                 const std::string& name,
                 const std::string& email,
                 const std::string& password)
    : User(name, email, password), studentId(id) {}

int Student::getStudentId() const {
    return studentId;
}

void Student::setStudentId(int id) {
    studentId = id;
}

/*
 * Function: toCSVRow
 * Purpose:  Converts a Student object into a CSV string.
 * Format:   studentID,name,email,password
 */
std::string Student::toCSVRow() const {
    std::stringstream ss;
    ss << studentId << "," << name << "," << email << "," << password;
    return ss.str();
}

/*
 * Function: fromCSVRow
 * Purpose:  Creates a Student object from a CSV row string.
 */
Student Student::fromCSVRow(const std::string& line) {
    std::vector<std::string> tokens = splitCSVLine(line);
    if (tokens.size() < 4) {
        // Return a default student if parsing fails
        return Student();
    }

    int id = std::stoi(tokens[0]);
    std::string sname = tokens[1];
    std::string semail = tokens[2];
    std::string spassword = tokens[3];

    return Student(id, sname, semail, spassword);
}
