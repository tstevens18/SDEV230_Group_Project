#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <string>

/*
 * Struct: Enrollment
 * Purpose: Represents a student enrollment in a class.
 *          Stored in enrollments.csv as: studentID,classID
 */
struct Enrollment {
    int studentId;    // ID of the enrolled student
    int classId;      // ID of the class

    std::string toCSVRow() const;
    static Enrollment fromCSVRow(const std::string& line);
};

#endif
