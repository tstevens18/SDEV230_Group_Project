#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

/*
 * Class: Student
 * Purpose: Represents a student user in the system.
 *          Inherits from User and adds a student ID.
 */
class Student : public User {
private:
    int studentId;  // unique numeric ID for the student

public:
    Student();
    Student(int id,
            const std::string& name,
            const std::string& email,
            const std::string& password);

    int getStudentId() const;
    void setStudentId(int id);

    // CSV helpers
    std::string toCSVRow() const;
    static Student fromCSVRow(const std::string& line);
};

#endif
