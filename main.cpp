
#include "App.h"

/*
 * Program: Student Data Management App
 * Purpose: Simple console application that allows students and teachers
 *          to register, log in, and manage classes (create/delete or add/drop).
 * Notes:   Uses CSV files for persistent storage.
 */
int main() {
    App app;    // main application object
    app.run();  // start the menu loop
    return 0;
}

