#ifndef APP_H
#define APP_H

#include <string>
#include <vector>
#include "Student.h"
#include "Teacher.h"
#include "ClassRecord.h"
#include "Enrollment.h"

/*
 * Class: App
 * Purpose: Central application controller.
 *          Handles menus, user registration, login, and class management.
 */
class App {
public:
    void run();  // main entry point for the application

private:
    // Menu arrays (satisfy "at least two arrays" requirement)
    static const int MAIN_MENU_SIZE = 5;
    static const int STUDENT_MENU_SIZE = 4;
    static const int TEACHER_MENU_SIZE = 4;

    const std::string mainMenuOptions[MAIN_MENU_SIZE] = {
        "1. Register Student",
        "2. Register Teacher",
        "3. Student Login",
        "4. Teacher Login",
        "5. Exit"
    };

    const std::string studentMenuOptions[STUDENT_MENU_SIZE] = {
        "1. Add Class",
        "2. Drop Class",
        "3. View My Classes",
        "4. Logout"
    };

    const std::string teacherMenuOptions[TEACHER_MENU_SIZE] = {
        "1. Create Class",
        "2. Delete Class",
        "3. View My Classes",
        "4. Logout"
    };

    // Core menu handlers
    void showMainMenu();
    void handleRegisterStudent();
    void handleRegisterTeacher();
    void handleStudentLogin();
    void handleTeacherLogin();

    void showStudentMenu(const Student& loggedInStudent);
    void showTeacherMenu(const Teacher& loggedInTeacher);

    // Student actions
    void studentAddClass(const Student& student);
    void studentDropClass(const Student& student);
    void studentViewClasses(const Student& student);

    // Teacher actions
    void teacherCreateClass(const Teacher& teacher);
    void teacherDeleteClass(const Teacher& teacher);
    void teacherViewClasses(const Teacher& teacher);

    // File helpers
    std::vector<Student> loadStudents();
    void appendStudent(const Student& student);
    std::vector<Teacher> loadTeachers();
    void appendTeacher(const Teacher& teacher);
    std::vector<ClassRecord> loadClasses();
    void overwriteClasses(const std::vector<ClassRecord>& classes);
    std::vector<Enrollment> loadEnrollments();
    void overwriteEnrollments(const std::vector<Enrollment>& enrollments);

    // ID generation
    int generateNextStudentId(const std::vector<Student>& students);
    int generateNextTeacherId(const std::vector<Teacher>& teachers);
    int generateNextClassId(const std::vector<ClassRecord>& classes);

    // Utility helpers
    int getIntChoice(int min, int max);
    std::string promptNonEmptyNoComma(const std::string& label);
    std::string promptValidEmail();
    std::string promptValidPassword();
    bool emailExists(const std::string& email,
                     const std::vector<Student>& students,
                     const std::vector<Teacher>& teachers);

    // Enrollment lookup helpers
    std::vector<ClassRecord> getClassesForTeacher(int teacherId,
                                                  const std::vector<ClassRecord>& classes);
    std::vector<ClassRecord> getClassesForStudent(int studentId,
                                                  const std::vector<ClassRecord>& classes,
                                                  const std::vector<Enrollment>& enrollments);
};

#endif
