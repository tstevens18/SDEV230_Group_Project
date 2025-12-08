#ifndef TEACHER_H
#define TEACHER_H

#include "User.h"

/*
 * Class: Teacher
 * Purpose: Represents a teacher user in the system.
 *          Inherits from User and adds a teacher ID.
 */
class Teacher : public User {
private:
    int teacherId;  // unique numeric ID for the teacher

public:
    Teacher();
    Teacher(int id,
            const std::string& name,
            const std::string& email,
            const std::string& password);

    int getTeacherId() const;
    void setTeacherId(int id);

    // CSV helpers
    std::string toCSVRow() const;
    static Teacher fromCSVRow(const std::string& line);
};

#endif
