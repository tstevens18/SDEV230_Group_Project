#include "App.h"
#include <iostream>
#include <fstream>
#include <limits>

/*
 * Function: run
 * Purpose:  Entry point for the App. Shows the main menu in a loop.
 */
void App::run() {
    bool running = true;        // controls main loop

    while (running) {
        showMainMenu();
        std::cout << "Enter choice: ";
        int choice = getIntChoice(1, 5);

        switch (choice) {
        case 1:
            handleRegisterStudent();
            break;
        case 2:
            handleRegisterTeacher();
            break;
        case 3:
            handleStudentLogin();
            break;
        case 4:
            handleTeacherLogin();
            break;
        case 5:
            std::cout << "Exiting application.\n";
            running = false;
            break;
        default:
            // This should never happen because getIntChoice validates range.
            std::cout << "Invalid option.\n";
            break;
        }
    }
}

/*
 * Function: showMainMenu
 * Purpose:  Displays the main menu using an array of strings.
 */
void App::showMainMenu() {
    std::cout << "\n==== Student Data Management ====\n";
    for (int i = 0; i < MAIN_MENU_SIZE; ++i) {
        std::cout << mainMenuOptions[i] << "\n";
    }
}

/*
 * Function: handleRegisterStudent
 * Purpose:  Collects and validates student information and saves it to students.csv.
 */
void App::handleRegisterStudent() {
    std::cout << "\n--- Student Registration ---\n";

    std::vector<Student> students = loadStudents();
    std::vector<Teacher> teachers = loadTeachers();

    std::string name = promptNonEmptyNoComma("Name");
    std::string email = promptValidEmail();
    // Ensure email is not used by any user type.
    while (emailExists(email, students, teachers)) {
        std::cout << "That email is already in use. Please enter a different email.\n";
        email = promptValidEmail();
    }
    std::string password = promptValidPassword();

    int newId = generateNextStudentId(students);
    Student s(newId, name, email, password);

    appendStudent(s);
    std::cout << "Student registered with ID: " << newId << "\n";
}

/*
 * Function: handleRegisterTeacher
 * Purpose:  Collects and validates teacher information and saves it to teachers.csv.
 */
void App::handleRegisterTeacher() {
    std::cout << "\n--- Teacher Registration ---\n";

    std::vector<Student> students = loadStudents();
    std::vector<Teacher> teachers = loadTeachers();

    std::string name = promptNonEmptyNoComma("Name");
    std::string email = promptValidEmail();
    while (emailExists(email, students, teachers)) {
        std::cout << "That email is already in use. Please enter a different email.\n";
        email = promptValidEmail();
    }
    std::string password = promptValidPassword();

    int newId = generateNextTeacherId(teachers);
    Teacher t(newId, name, email, password);

    appendTeacher(t);
    std::cout << "Teacher registered with ID: " << newId << "\n";
}

/*
 * Function: handleStudentLogin
 * Purpose:  Prompts for email and password and logs in an existing student.
 */
void App::handleStudentLogin() {
    std::cout << "\n--- Student Login ---\n";

    std::vector<Student> students = loadStudents();
    if (students.empty()) {
        std::cout << "No students registered yet.\n";
        return;
    }

    std::string email = promptValidEmail();
    std::string password;
    std::cout << "Password: ";
    std::getline(std::cin, password);

    for (const auto& s : students) {
        if (s.getEmail() == email && s.getPassword() == password) {
            std::cout << "Welcome, " << s.getName() << "!\n";
            showStudentMenu(s);
            return;
        }
    }

    std::cout << "Login failed. Invalid email or password.\n";
}

/*
 * Function: handleTeacherLogin
 * Purpose:  Prompts for email and password and logs in an existing teacher.
 */
void App::handleTeacherLogin() {
    std::cout << "\n--- Teacher Login ---\n";

    std::vector<Teacher> teachers = loadTeachers();
    if (teachers.empty()) {
        std::cout << "No teachers registered yet.\n";
        return;
    }

    std::string email = promptValidEmail();
    std::string password;
    std::cout << "Password: ";
    std::getline(std::cin, password);

    for (const auto& t : teachers) {
        if (t.getEmail() == email && t.getPassword() == password) {
            std::cout << "Welcome, " << t.getName() << "!\n";
            showTeacherMenu(t);
            return;
        }
    }

    std::cout << "Login failed. Invalid email or password.\n";
}

/*
 * Function: showStudentMenu
 * Purpose:  Displays the student menu and allows add/drop/view of classes.
 */
void App::showStudentMenu(const Student& loggedInStudent) {
    bool done = false;

    while (!done) {
        std::cout << "\n--- Student Menu ---\n";
        for (int i = 0; i < STUDENT_MENU_SIZE; ++i) {
            std::cout << studentMenuOptions[i] << "\n";
        }

        std::cout << "Enter choice: ";
        int choice = getIntChoice(1, 4);

        switch (choice) {
        case 1:
            studentAddClass(loggedInStudent);
            break;
        case 2:
            studentDropClass(loggedInStudent);
            break;
        case 3:
            studentViewClasses(loggedInStudent);
            break;
        case 4:
            std::cout << "Logging out.\n";
            done = true;
            break;
        }
    }
}

/*
 * Function: showTeacherMenu
 * Purpose:  Displays the teacher menu and allows class management.
 */
void App::showTeacherMenu(const Teacher& loggedInTeacher) {
    bool done = false;

    while (!done) {
        std::cout << "\n--- Teacher Menu ---\n";
        for (int i = 0; i < TEACHER_MENU_SIZE; ++i) {
            std::cout << teacherMenuOptions[i] << "\n";
        }

        std::cout << "Enter choice: ";
        int choice = getIntChoice(1, 4);

        switch (choice) {
        case 1:
            teacherCreateClass(loggedInTeacher);
            break;
        case 2:
            teacherDeleteClass(loggedInTeacher);
            break;
        case 3:
            teacherViewClasses(loggedInTeacher);
            break;
        case 4:
            std::cout << "Logging out.\n";
            done = true;
            break;
        }
    }
}

/*
 * Function: studentAddClass
 * Purpose:  Enrolls a student in a class by class ID.
 */
void App::studentAddClass(const Student& student) {
    std::vector<ClassRecord> classes = loadClasses();
    std::vector<Enrollment> enrollments = loadEnrollments();

    if (classes.empty()) {
        std::cout << "No classes available to add.\n";
        return;
    }

    std::cout << "\nAvailable classes:\n";
    for (const auto& c : classes) {
        std::cout << "Class ID: " << c.classId
                  << " | Teacher ID: " << c.teacherId
                  << " | Name: " << c.name << "\n";
    }

    std::cout << "Enter Class ID to add: ";
    int classId = getIntChoice(1, 1000000); // wide range for IDs

    // Check class exists
    bool found = false;
    for (const auto& c : classes) {
        if (c.classId == classId) {
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "No class with that ID.\n";
        return;
    }

    // Check if already enrolled
    for (const auto& e : enrollments) {
        if (e.studentId == student.getStudentId() && e.classId == classId) {
            std::cout << "You are already enrolled in that class.\n";
            return;
        }
    }

    Enrollment newEnroll;
    newEnroll.studentId = student.getStudentId();
    newEnroll.classId = classId;
    enrollments.push_back(newEnroll);
    overwriteEnrollments(enrollments);

    std::cout << "Class added successfully.\n";
}

/*
 * Function: studentDropClass
 * Purpose:  Allows a student to drop an enrolled class.
 */
void App::studentDropClass(const Student& student) {
    std::vector<ClassRecord> classes = loadClasses();
    std::vector<Enrollment> enrollments = loadEnrollments();

    if (enrollments.empty()) {
        std::cout << "You are not enrolled in any classes.\n";
        return;
    }

    std::vector<ClassRecord> myClasses = getClassesForStudent(student.getStudentId(),
                                                              classes,
                                                              enrollments);

    if (myClasses.empty()) {
        std::cout << "You are not enrolled in any classes.\n";
        return;
    }

    std::cout << "\nYour classes:\n";
    for (const auto& c : myClasses) {
        std::cout << "Class ID: " << c.classId
                  << " | Name: " << c.name << "\n";
    }

    std::cout << "Enter Class ID to drop: ";
    int classId = getIntChoice(1, 1000000);

    bool removed = false;
    std::vector<Enrollment> updated;
    for (const auto& e : enrollments) {
        if (e.studentId == student.getStudentId() && e.classId == classId) {
            removed = true;
            continue; // skip the one we want to drop
        }
        updated.push_back(e);
    }

    if (!removed) {
        std::cout << "You are not enrolled in that class.\n";
        return;
    }

    overwriteEnrollments(updated);
    std::cout << "Class dropped successfully.\n";
}

/*
 * Function: studentViewClasses
 * Purpose:  Shows all classes in which the student is enrolled.
 */
void App::studentViewClasses(const Student& student) {
    std::vector<ClassRecord> classes = loadClasses();
    std::vector<Enrollment> enrollments = loadEnrollments();
    std::vector<ClassRecord> myClasses = getClassesForStudent(student.getStudentId(),
                                                              classes,
                                                              enrollments);

    if (myClasses.empty()) {
        std::cout << "You are not enrolled in any classes.\n";
        return;
    }

    std::cout << "\nYour classes:\n";
    for (const auto& c : myClasses) {
        std::cout << "Class ID: " << c.classId
                  << " | Name: " << c.name
                  << " | Teacher ID: " << c.teacherId << "\n";
    }
}

/*
 * Function: teacherCreateClass
 * Purpose:  Allows a teacher to create a new class.
 */
void App::teacherCreateClass(const Teacher& teacher) {
    std::vector<ClassRecord> classes = loadClasses();
    std::string className = promptNonEmptyNoComma("Class Name");

    int newId = generateNextClassId(classes);
    ClassRecord rec;
    rec.classId = newId;
    rec.teacherId = teacher.getTeacherId();
    rec.name = className;

    classes.push_back(rec);
    overwriteClasses(classes);

    std::cout << "Class created with ID: " << newId << "\n";
}

/*
 * Function: teacherDeleteClass
 * Purpose:  Allows a teacher to delete a class they own.
 *           Also removes related enrollments.
 */
void App::teacherDeleteClass(const Teacher& teacher) {
    std::vector<ClassRecord> classes = loadClasses();
    std::vector<Enrollment> enrollments = loadEnrollments();

    std::vector<ClassRecord> myClasses = getClassesForTeacher(teacher.getTeacherId(),
                                                              classes);

    if (myClasses.empty()) {
        std::cout << "You have no classes to delete.\n";
        return;
    }

    std::cout << "\nYour classes:\n";
    for (const auto& c : myClasses) {
        std::cout << "Class ID: " << c.classId
                  << " | Name: " << c.name << "\n";
    }

    std::cout << "Enter Class ID to delete: ";
    int classId = getIntChoice(1, 1000000);

    // Remove class from classes list
    bool removed = false;
    std::vector<ClassRecord> updatedClasses;
    for (const auto& c : classes) {
        if (c.classId == classId && c.teacherId == teacher.getTeacherId()) {
            removed = true;
            continue;
        }
        updatedClasses.push_back(c);
    }

    if (!removed) {
        std::cout << "You do not own a class with that ID.\n";
        return;
    }

    overwriteClasses(updatedClasses);

    // Remove related enrollments
    std::vector<Enrollment> updatedEnrollments;
    for (const auto& e : enrollments) {
        if (e.classId == classId) {
            continue;
        }
        updatedEnrollments.push_back(e);
    }
    overwriteEnrollments(updatedEnrollments);

    std::cout << "Class and its enrollments deleted.\n";
}

/*
 * Function: teacherViewClasses
 * Purpose:  Shows all classes owned by the logged-in teacher.
 */
void App::teacherViewClasses(const Teacher& teacher) {
    std::vector<ClassRecord> classes = loadClasses();
    std::vector<ClassRecord> myClasses = getClassesForTeacher(teacher.getTeacherId(),
                                                              classes);

    if (myClasses.empty()) {
        std::cout << "You have no classes.\n";
        return;
    }

    std::cout << "\nYour classes:\n";
    for (const auto& c : myClasses) {
        std::cout << "Class ID: " << c.classId
                  << " | Name: " << c.name << "\n";
    }
}

/*
 * Function: loadStudents
 * Purpose:  Reads students from students.csv.
 * Secure:   Checks for file existence and handles empty file.
 */
std::vector<Student> App::loadStudents() {
    std::vector<Student> students;
    std::ifstream file("students.csv");
    if (!file.is_open()) {
        return students; // file may not exist yet; treat as empty
    }

    std::string line;
    bool firstLine = true;
    while (std::getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue;
        }
        if (!line.empty()) {
            Student s = Student::fromCSVRow(line);
            if (s.getStudentId() != 0) {
                students.push_back(s);
            }
        }
    }

    return students;
}

/*
 * Function: appendStudent
 * Purpose:  Appends a single student record to students.csv.
 */
void App::appendStudent(const Student& student) {
    std::ifstream checkFile("students.csv");
    bool fileExists = checkFile.is_open();
    checkFile.close();

    std::ofstream file("students.csv", std::ios::app);
    if (!file.is_open()) {
        std::cout << "Error: could not open students.csv for writing.\n";
        return;
    }

    if (!fileExists) {
        file << "studentID,name,email,password\n";
    }

    file << student.toCSVRow() << "\n";
}

/*
 * Function: loadTeachers
 * Purpose:  Reads teachers from teachers.csv.
 */
std::vector<Teacher> App::loadTeachers() {
    std::vector<Teacher> teachers;
    std::ifstream file("teachers.csv");
    if (!file.is_open()) {
        return teachers;
    }

    std::string line;
    bool firstLine = true;
    while (std::getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue;
        }
        if (!line.empty()) {
            Teacher t = Teacher::fromCSVRow(line);
            if (t.getTeacherId() != 0) {
                teachers.push_back(t);
            }
        }
    }

    return teachers;
}

/*
 * Function: appendTeacher
 * Purpose:  Appends a single teacher record to teachers.csv.
 */
void App::appendTeacher(const Teacher& teacher) {
    std::ifstream checkFile("teachers.csv");
    bool fileExists = checkFile.is_open();
    checkFile.close();

    std::ofstream file("teachers.csv", std::ios::app);
    if (!file.is_open()) {
        std::cout << "Error: could not open teachers.csv for writing.\n";
        return;
    }

    if (!fileExists) {
        file << "teacherID,name,email,password\n";
    }

    file << teacher.toCSVRow() << "\n";
}

/*
 * Function: loadClasses
 * Purpose:  Reads class records from classes.csv.
 */
std::vector<ClassRecord> App::loadClasses() {
    std::vector<ClassRecord> classes;
    std::ifstream file("classes.csv");
    if (!file.is_open()) {
        return classes;
    }

    std::string line;
    bool firstLine = true;
    while (std::getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue;
        }
        if (!line.empty()) {
            ClassRecord cr = ClassRecord::fromCSVRow(line);
            if (cr.classId != 0) {
                classes.push_back(cr);
            }
        }
    }

    return classes;
}

/*
 * Function: overwriteClasses
 * Purpose:  Rewrites classes.csv with a new list of classes.
 */
void App::overwriteClasses(const std::vector<ClassRecord>& classes) {
    std::ofstream file("classes.csv", std::ios::trunc);
    if (!file.is_open()) {
        std::cout << "Error: could not open classes.csv for writing.\n";
        return;
    }

    file << "classID,teacherID,className\n";
    for (const auto& c : classes) {
        file << c.toCSVRow() << "\n";
    }
}

/*
 * Function: loadEnrollments
 * Purpose:  Reads enrollments from enrollments.csv.
 */
std::vector<Enrollment> App::loadEnrollments() {
    std::vector<Enrollment> enrollments;
    std::ifstream file("enrollments.csv");
    if (!file.is_open()) {
        return enrollments;
    }

    std::string line;
    bool firstLine = true;
    while (std::getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue;
        }
        if (!line.empty()) {
            Enrollment e = Enrollment::fromCSVRow(line);
            if (e.studentId != 0 && e.classId != 0) {
                enrollments.push_back(e);
            }
        }
    }

    return enrollments;
}

/*
 * Function: overwriteEnrollments
 * Purpose:  Rewrites enrollments.csv with a new list of enrollments.
 */
void App::overwriteEnrollments(const std::vector<Enrollment>& enrollments) {
    std::ofstream file("enrollments.csv", std::ios::trunc);
    if (!file.is_open()) {
        std::cout << "Error: could not open enrollments.csv for writing.\n";
        return;
    }

    file << "studentID,classID\n";
    for (const auto& e : enrollments) {
        file << e.toCSVRow() << "\n";
    }
}

/*
 * Function: generateNextStudentId
 * Purpose:  Returns the next available student ID based on current data.
 */
int App::generateNextStudentId(const std::vector<Student>& students) {
    int maxId = 0;
    for (const auto& s : students) {
        if (s.getStudentId() > maxId) {
            maxId = s.getStudentId();
        }
    }
    return maxId + 1;
}

/*
 * Function: generateNextTeacherId
 * Purpose:  Returns the next available teacher ID.
 */
int App::generateNextTeacherId(const std::vector<Teacher>& teachers) {
    int maxId = 0;
    for (const auto& t : teachers) {
        if (t.getTeacherId() > maxId) {
            maxId = t.getTeacherId();
        }
    }
    return maxId + 1;
}

/*
 * Function: generateNextClassId
 * Purpose:  Returns the next available class ID.
 */
int App::generateNextClassId(const std::vector<ClassRecord>& classes) {
    int maxId = 0;
    for (const auto& c : classes) {
        if (c.classId > maxId) {
            maxId = c.classId;
        }
    }
    return maxId + 1;
}

/*
 * Function: getIntChoice
 * Purpose:  Safely reads an integer from input within a given range.
 * Secure:   Uses string parsing to avoid input stream issues.
 */
int App::getIntChoice(int min, int max) {
    while (true) {
        std::string line;
        std::getline(std::cin, line);

        try {
            int value = std::stoi(line);
            if (value < min || value > max) {
                std::cout << "Please enter a number between " << min
                          << " and " << max << ": ";
                continue;
            }
            return value;
        } catch (...) {
            std::cout << "Invalid number. Try again: ";
        }
    }
}

/*
 * Function: promptNonEmptyNoComma
 * Purpose:  Prompts the user for a non-empty string without commas.
 */
std::string App::promptNonEmptyNoComma(const std::string& label) {
    while (true) {
        std::cout << label << ": ";
        std::string value;
        std::getline(std::cin, value);

        if (!User::isNonEmpty(value)) {
            std::cout << label << " cannot be empty.\n";
            continue;
        }
        if (User::containsComma(value)) {
            std::cout << label << " cannot contain commas.\n";
            continue;
        }
        return value;
    }
}

/*
 * Function: promptValidEmail
 * Purpose:  Repeatedly prompts until a valid email string is entered.
 */
std::string App::promptValidEmail() {
    while (true) {
        std::cout << "Email: ";
        std::string email;
        std::getline(std::cin, email);

        if (!User::isNonEmpty(email)) {
            std::cout << "Email cannot be empty.\n";
            continue;
        }
        if (!User::isValidEmail(email)) {
            std::cout << "Please enter a valid email (must contain '@' and '.').\n";
            continue;
        }
        if (User::containsComma(email)) {
            std::cout << "Email cannot contain commas.\n";
            continue;
        }
        return email;
    }
}

/*
 * Function: promptValidPassword
 * Purpose:  Repeatedly prompts until a password meets basic policy.
 */
std::string App::promptValidPassword() {
    while (true) {
        std::cout << "Password (min 4 characters): ";
        std::string password;
        std::getline(std::cin, password);

        if (!User::isNonEmpty(password)) {
            std::cout << "Password cannot be empty.\n";
            continue;
        }
        if (!User::isValidPassword(password)) {
            std::cout << "Password is too short.\n";
            continue;
        }
        if (User::containsComma(password)) {
            std::cout << "Password cannot contain commas.\n";
            continue;
        }

        return password;
    }
}

/*
 * Function: emailExists
 * Purpose:  Checks if an email is already used by a student or teacher.
 */
bool App::emailExists(const std::string& email,
                      const std::vector<Student>& students,
                      const std::vector<Teacher>& teachers) {
    for (const auto& s : students) {
        if (s.getEmail() == email) {
            return true;
        }
    }
    for (const auto& t : teachers) {
        if (t.getEmail() == email) {
            return true;
        }
    }
    return false;
}

/*
 * Function: getClassesForTeacher
 * Purpose:  Returns a list of classes owned by the given teacher ID.
 */
std::vector<ClassRecord> App::getClassesForTeacher(int teacherId,
                                                   const std::vector<ClassRecord>& classes) {
    std::vector<ClassRecord> result;
    for (const auto& c : classes) {
        if (c.teacherId == teacherId) {
            result.push_back(c);
        }
    }
    return result;
}

/*
 * Function: getClassesForStudent
 * Purpose:  Returns a list of classes in which the student is enrolled.
 */
std::vector<ClassRecord> App::getClassesForStudent(int studentId,
                                                   const std::vector<ClassRecord>& classes,
                                                   const std::vector<Enrollment>& enrollments) {
    std::vector<ClassRecord> result;
    for (const auto& e : enrollments) {
        if (e.studentId == studentId) {
            for (const auto& c : classes) {
                if (c.classId == e.classId) {
                    result.push_back(c);
                }
            }
        }
    }
    return result;
}
