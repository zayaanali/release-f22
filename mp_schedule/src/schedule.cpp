/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>
#include <fstream>

using namespace std;

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!
    V2D ret;
    string line, word;
    int row=0;
    int col=0;
    ifstream infile(filename);
    
    while (getline(infile, line)) {
        ret.push_back(vector<string>());
        for (auto ch: line) { // for each character in the line
            if (ch==',') 
                { ret[row].push_back(word); word=""; col++; } // set word
            else if (ch==' ')
                { continue; }
            else
                { word.push_back(ch); } // or create word
        }
        ret[row].push_back(word);
        col=0;
        row++;
        word="";
    }
    return ret;
    

}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & student){
    // YOUR CODE HERE
    V2D ret;
    vector<string> students, classes, students_taking_class;
    string cur_class;
    string cur_student;
    int cur_row=-1;

    for (unsigned long i=0; i<cv.size(); i++) { // for each course
        cur_class = cv[i][0]; 
        students_taking_class = check_class(cur_class, student); // get which students are taking course
        //cout << i;
        if (check_duplicate(cv[i], students_taking_class)) { // if there are students taking the course
            cur_row++;
            ret.push_back(vector<string>());
            ret[cur_row].push_back(cur_class);
            
            for (unsigned long z=1; z<cv[i].size(); z++) { // add them
                //cout << "here";
                if (check_existence(cv[i][z], students_taking_class)) 
                    {//cout << i << " ";
                    ret[cur_row].push_back(cv[i][z]); }
            }
        }
    }
    return ret;

}
bool check_duplicate (vector<string> arr1, vector<string> arr2) {
    
    for (auto it: arr1)
        for (auto it2: arr2) 
            if (it==it2) return true;
    
    return false;

}
bool check_existence(string input, vector<string> array) {
    bool ret=false;
    for (auto it: array)
        if (input==it) ret = true;
    
    return ret;
}

vector<string> check_class(string cur_class, V2D students) {
    vector<string> ret;
    bool exists;
    for (unsigned int i=0; i<students.size(); i++) { // for each student
        if (check_existence(cur_class, students[i])) // check if student is taking the class
            ret.push_back(students[i][0]); // add to array if student is taking class
    }
    return ret;
}
/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
    // Your code here!
    V2D v1;
    return v1;

}