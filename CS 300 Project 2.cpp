//==========================================================
// Name : CS 300 Project 2
// Author : Oscar Rosa
// Version : 1.0
// Copyright : Copyright © 2017 SNHU COCE
// Description : CS 300 Project 2 in C++,
//==========================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>


using namespace std;

// Define Course structure
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Function to load course data from a file into the data structure
void loadDataStructure(vector<Course>& courses, const string& fileName) {
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        Course course;
        istringstream iss(line);
        getline(iss, course.courseNumber, ',');
        getline(iss, course.courseTitle, ',');

        string prerequisite;
        while (getline(iss, prerequisite, ',')) {
            if (!prerequisite.empty()) {
                course.prerequisites.push_back(prerequisite);
            }
        }

        courses.push_back(course);
    }

    inputFile.close();
}
 // Function to print course list alphanumerically
void printCourseList(const vector<Course>& courses) {
    vector<Course> sortedCourses = courses;
    sort(sortedCourses.begin(), sortedCourses.end(),
        [](const Course& a, const Course& b) {
            return a.courseNumber < b.courseNumber;
        });

    cout << "Alphanumeric list of courses:" << endl;
    for (const Course& course : sortedCourses) {
        cout << course.courseNumber << " - " << course.courseTitle << endl;
    }
}
 // Function to print course information
void printCourseInformation(const vector<Course>& courses, const string& courseNumber) {
    for (const Course& course : courses) {
        if (course.courseNumber == courseNumber) {
            cout << "Course Title: " << course.courseTitle << endl;
            if (!course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (const string& prerequisite : course.prerequisites) {
                    cout << prerequisite << " ";
                }
                cout << endl;
            }
            return;
        }
    }
    cout << "Course not found." << endl;
}

int main() {
    vector<Course> courses;
    string fileName = "abcu_courses.csv"; // File name

    // Load data from the file into the data structure
    loadDataStructure(courses, fileName);

    int choice;
    while (true) {
        cout << "\nPlease select an option:\n";
        cout << "1. Load Data Structure\n";
        cout << "2. Print Course List\n";
        cout << "3. Print Course Information\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            loadDataStructure(courses, fileName);
            break;
        case 2:
            printCourseList(courses);
            break;
        case 3: {
            string courseNumber;
            cout << "Enter course number: ";
            cin >> courseNumber;
            printCourseInformation(courses, courseNumber);
            break;
        }
        case 9:
            cout << "Exiting the program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please select a valid option.\n";
            break;
        }
    }

    return 0;
}