#ifndef CLASSRECORD_H
#define CLASSRECORD_H

#include <string>

/*
 * Struct: ClassRecord
 * Purpose: Represents a class created by a teacher.
 *          Stored in classes.csv.
 */
struct ClassRecord {
    int classId;          // unique ID for the class
    int teacherId;        // ID of the teacher who owns this class
    std::string name;     // class name (no commas)

    std::string toCSVRow() const;
    static ClassRecord fromCSVRow(const std::string& line);
};

#endif
