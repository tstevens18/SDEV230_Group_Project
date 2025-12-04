#include <iostream>
#include "usertypeH.cpp"

using namespace std;

int main()
{
    int choice = 0, studentChoice = 0, instructorChoice = 0, adminChoice = 0;
    string enteredID = 0;
    studentInfo student;
    instructorInfo instructor;

    while (choice != 4)
    {

        // Display Main Menu options
        cout << "\n Menu: \n1. Student Login \n2. Teacher Login \n3. Admin Login \n4. Exit";
        cin >> choice;

        // Handling entered choices
        if (choice == 1)
        {
            // Option 1, student login function
            cout << "Please enter your Student ID: ";
            cin >> enteredID;

            // Display Student Menu and options
            while (enteredID == student.studentID)
            {
                while (studentChoice != 5)

                    cout << "\n Student Menu: \n1. View Courses \n2. Register for Course \n3. View Grades \n4. View Grades for Course \n5. Log Out";
                cin >> studentChoice;

                if (studentChoice == 1)
                {
                    // View course function
                    return;
                }

                else if (studentChoice == 2)
                {
                    // Register for course function
                    return;
                }

                else if (studentChoice == 3)
                {
                    // View grades function
                    return;
                }

                else if (studentChoice == 4)
                {
                    // View course grades function
                    return;
                }

                else
                {
                    // Throw error if number is out of range
                    cout << "Error, please enter a number between 1 and 5";
                    return;
                }
            }
            // Break if 5 is entered
            break;
        }

        if (choice == 2)
        {
            // Option 2, teacher login

            cout << "Please enter your Instructor ID: ";
            cin >> enteredID;

            // Display Instructor Menu and options
            while (enteredID == instructor.instructorID)
            {
                while (instructorChoice != 6)

                    cout << "\n Instructor Menu: \n1. Add Student \n2. View Students \n3. Update Grade \n4. View all Students in Course \n5. View all Courses \n6. Log Out";
                cin >> instructorChoice;

                if (instructorChoice == 1)
                {
                    // Add Student function
                    return;
                }

                else if (instructorChoice == 2)
                {
                    // View Student function
                    return;
                }

                else if (instructorChoice == 3)
                {
                    // Update Grade function
                    return;
                }

                else if (instructorChoice == 4)
                {
                    // View all Students in Course function
                    return;
                }

                else if (instructorChoice == 5)
                {
                    // View all Courses function
                    return;
                }

                else
                {
                    // Throw error if number is out of range
                    cout << "Error, please enter a number between 1 and 5";
                    return;
                }
            }
            // Break if 6 is entered
            break;
        }

        if (choice == 3)
        {
            // Option 3, admin login

            cout << "Please enter your Admin ID: ";
            cin >> enteredID;

            // the - while (enteredID == instructor.instructorID) - will be replaced with admin info once it's a struct in the usertypeH file.
            while (enteredID == instructor.instructorID)
            {
                while (adminChoice != 8)

                    // Display Admin Menu and options
                    cout << "\n Admin Menu: \n1. Add Course \n2. Add Student \n3. Add Instructor \n4. Add Student to Course \n5. Add Instructor to Course \n6. View all Courses \n7. View all Students \n8. Log Out";
                cin >> adminChoice;

                if (adminChoice == 1)
                {
                    // Add Course function
                    return;
                }

                else if (adminChoice == 2)
                {
                    // Add Student function
                    return;
                }

                else if (adminChoice == 3)
                {
                    // Add Instructor function
                    return;
                }

                else if (adminChoice == 4)
                {
                    // Add Student to Course function
                    return;
                }

                else if (adminChoice == 5)
                {
                    // Add Instructor to Course function
                    return;
                }

                else if (adminChoice == 6)
                {
                    // View all Courses function
                    return;
                }

                else if (adminChoice == 7)
                {
                    // View all Students function
                    return;
                }

                else
                {
                    // Throw error if number is out of range
                    cout << "Error, please enter a number between 1 and 5";
                    return;
                }
            }
            // Break if 8 is entered
            break;
        }

        else
        {
            // Throw error if number is out of range
            cout << "Error, please enter a number between 1 and 5";
            return;
        }

        // Exit if 4 is entered
        return 0;
    }
}