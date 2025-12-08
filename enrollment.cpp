#include "Enrollment.h"
#include <sstream>
#include <vector>

/*
 * Helper Function: splitCSVLineEnrollment
 * Purpose: Splits a CSV line into tokens separated by commas.
 */
static std::vector<std::string> splitCSVLineEnrollment(const std::string& line) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(line);

    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    return tokens;
}

/*
 * Function: toCSVRow
 * Purpose:  Converts an Enrollment into a CSV row.
 * Format:   studentID,classID
 */
std::string Enrollment::toCSVRow() const {
    std::stringstream ss;
    ss << studentId << "," << classId;
    return ss.str();
}

/*
 * Function: fromCSVRow
 * Purpose:  Parses a CSV row string into an Enrollment object.
 */
Enrollment Enrollment::fromCSVRow(const std::string& line) {
    Enrollment e{};
    std::vector<std::string> tokens = splitCSVLineEnrollment(line);
    if (tokens.size() < 2) {
        e.studentId = 0;
        e.classId = 0;
        return e;
    }
    e.studentId = std::stoi(tokens[0]);
    e.classId = std::stoi(tokens[1]);
    return e;
}
