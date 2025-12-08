#include "ClassRecord.h"
#include <sstream>
#include <vector>

/*
 * Helper Function: splitCSVLineClass
 * Purpose: Splits a CSV line into tokens separated by commas.
 */
static std::vector<std::string> splitCSVLineClass(const std::string& line) {
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
 * Purpose:  Converts a ClassRecord into a CSV row string.
 * Format:   classID,teacherID,className
 */
std::string ClassRecord::toCSVRow() const {
    std::stringstream ss;
    ss << classId << "," << teacherId << "," << name;
    return ss.str();
}

/*
 * Function: fromCSVRow
 * Purpose:  Parses a CSV row and returns a ClassRecord.
 */
ClassRecord ClassRecord::fromCSVRow(const std::string& line) {
    std::vector<std::string> tokens = splitCSVLineClass(line);
    ClassRecord rec{};
    if (tokens.size() < 3) {
        rec.classId = 0;
        rec.teacherId = 0;
        rec.name = "";
        return rec;
    }

    rec.classId = std::stoi(tokens[0]);
    rec.teacherId = std::stoi(tokens[1]);
    rec.name = tokens[2];

    return rec;
}
