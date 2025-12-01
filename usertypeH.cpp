#ifndef USERTYPEH_CPP
#define USERTYPEH_CPP

#include <string>
using namespace std;
class userType
{
private:
    // Each user ID is based on what class it is derived from, student has STUD, instructors have TEACH, admin has ADMN
    const string userID;

public:
    string getUserId();
    bool isAdmin();
    bool isInstructor();
};

class adminType : public userType
{
private:
    // Each course name is given a unique ID (COUR101 etc), this function returns the new course ID
    string addCourse(string courseName);
    // Returns unique student ID created after student is made
    string addStudent(string studentName);
    // Add student to course with ID, returns true if student was successfully added to course
    bool addStudentToCourse(string studentID, string courseID);
    // Add instructor to course with ID, returns true if instructor was succesfully added, will return false if course already has instructor
    bool addInstructorToCourse(string instructorID, string courseID);
    // Remove a student from course, returns true if student is successfully removed
    bool removeStudentFromCourse(string studentID, string courseID);
    // Remove instructor from course, returns true if teacher is succesfully removed
    bool removeInstructorFromCourse(string instructorID, string courseID);
    // Print all students
    void printAllStudents();
    // Print all courses
    void printAllCourses();
    // Print all Instructors
    void printAllInstructors();
};

class instructorType : public userType
{
    // Shares many functions with admin, but does not offer the same amount of control as an admin account
    // Add student to course with ID, returns true if student was successfully added to course, (Will only allow teacher to add students to courses they are the registered instructor of)
    bool addStudentToCourse(string studentID, string courseID);
    // Remove a student from course, returns true if student is successfully removed (Only allows removal of students to courses teacher is registered instrucor of)
    bool removeStudentFromCourse(string studentID, string courseID);
    // Remove instructor from course, returns true if teacher is succesfully removed
    bool removeInstructorFromCourse(string instructorID, string courseID);
    // Print all students in instructors courses
    void printAllStudents();
    // Print all courses
    void printAllCourses();
    // Print courses Teacher is registered to
    void viewMyCourses();
};

class studentType : public userType
{
    // Returns true if student is successfully registered to class
    bool registerForCourse(string courseID);
    // Prints all courses student is currently registered to
    void viewMyCourses();
    // Shows grades for all current courses registered to
    void viewAllGrades();
    // Shows grades for course entered in ID
    void viewGradesforCourse(string courseID);
    // Print all courses
    void printAllCourses();
};

class infoMap
{
private:
};
#endif