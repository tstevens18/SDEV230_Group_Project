#include "Teacher.h"
#include <sstream>
#include <vector>

static std::vector<std::string> splitCSVLineTeacher(const std::string& line) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(line);

    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    return tokens;
}

Teacher::Teacher() : User(), teacherId(0) {}

Teacher::Teacher(int id,
                 const std::string& name,
                 const std::string& email,
                 const std::string& password)
    : User(name, email, password), teacherId(id) {}

int Teacher::getTeacherId() const {
    return teacherId;
}

void Teacher::setTeacherId(int id) {
    teacherId = id;
}

/*
 * Function: toCSVRow
 * Purpose:  Converts a Teacher object into a CSV string.
 * Format:   teacherID,name,email,password
 */
std::string Teacher::toCSVRow() const {
    std::stringstream ss;
    ss << teacherId << "," << name << "," << email << "," << password;
    return ss.str();
}

/*
 * Function: fromCSVRow
 * Purpose:  Creates a Teacher object from a CSV row string.
 */
Teacher Teacher::fromCSVRow(const std::string& line) {
    std::vector<std::string> tokens = splitCSVLineTeacher(line);
    if (tokens.size() < 4) {
        return Teacher();
    }

    int id = std::stoi(tokens[0]);
    std::string tname = tokens[1];
    std::string temail = tokens[2];
    std::string tpassword = tokens[3];

    return Teacher(id, tname, temail, tpassword);
}
