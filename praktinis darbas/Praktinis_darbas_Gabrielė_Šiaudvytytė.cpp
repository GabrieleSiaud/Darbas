#include <iostream>
#include <string> 
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>    
using namespace std;

void CreateGroup() {
    cout << "New group name:" << endl;
    string name; 
    cin >> name; 
    fstream group("group.txt", ios::app); 
    fstream lecture("lecture.txt", ios::app);
    group << name<<":" << endl;
    lecture << name << ":" << endl;  
    while (true) {
        system("cls");
        cout << "Group created.\n\nDo you want to create another group? (y/n)\n" << endl;
        string answer; 
        cin >> answer;
        if (answer == "y" || answer == "Y") {
            system("cls"); 
            cout << "\nNew group name:" << endl; 
            cin >> name;
            group << name <<":" << endl;
            lecture << name << ":" << endl; 
        }
        else if (answer == "n" || answer == "N") {
            break;
        }
        else {
            cout << "Invalid answer, try again" << endl;  
        }
    }
    group.close(); 
    lecture.close(); 
}

void DeleteGroup() {
    bool groupFound = false;  
    do {
        cout << "Enter the group name to delete:" << endl;
        string groupName;
        cin >> groupName;

        ifstream groupFile("group.txt");
        vector<string> lines;
        string line;
        bool inGroup = false;

        while (getline(groupFile, line)) {
            if (line == groupName + ":") {
                groupFound = true;
                inGroup = true;
                continue;
            }

            if (inGroup) {
                if (line.empty() || line.find(":") != string::npos) {
                    inGroup = false;
                }
                if (inGroup) {
                    continue; 
                }
            }

            lines.push_back(line);
        }

        groupFile.close();

        if (!groupFound) {
            system("cls"); 
            cout << "Invalid answer, try again:" << endl;
        }
        else {
            ofstream outputGroup("group.txt", ios::trunc);
            ofstream outputLecture("lecture.txt", ios::trunc);
            for (const auto& l : lines) {
                outputGroup << l << endl;
                outputLecture << l << endl;
            }
            outputLecture.close();
            outputGroup.close();
            cout << "\nGroup is deleted\n\nFINISH (f)" << endl;
            string answer;
            cin >> answer;
            if (answer == "f" || answer == "F") {
                cout << "" << endl;
            }
        }
    } while (!groupFound); 
}

void AddStudents() {
    bool groupFound = false;
    do {
        cout << "Enter the group you want to add students to:" << endl;
        string groupName;
        cin >> groupName;

        vector<string> lines;
        string line;

        ifstream groupFile("group.txt");
        while (getline(groupFile, line)) {
            lines.push_back(line);
            if (line == groupName + ":") {
                groupFound = true;
            }
        }
        groupFile.close();

        if (!groupFound) {
            system("cls"); 
            cout << "Invalid answer, try again:\n" << endl;
        }
        else {
            cout << "\nFINISH (f)\n\nEnter student names to add to:" << endl;
            string student;
            vector<string> students;
            cin.ignore(); 

            while (true) {
                getline(cin, student); 
                if (student == "f" || student == "F") {
                    break;
                }
                students.push_back(student);
            }

            ofstream output("group.txt", ios::trunc);
            for (const auto& line : lines) {
                output << line << endl;
                if (line == groupName + ":") {
                    for (const auto& newstudent : students) { 
                        output << newstudent << endl; 
                    }
                }
            }
            output.close();
        }
    } while (!groupFound); 
}

void RemoveStudents() {
    bool groupFound = false;
    bool inGroup = false;   
    do {
        cout << "Type the group you want to remove students from:" << endl;
        string groupName;
        cin >> groupName;

        vector<string> lines;
        string line;

        ifstream groupFile("group.txt");
        while (getline(groupFile, line)) {
            if (line == groupName + ":") {
                groupFound = true;
                inGroup = true;
            }

            if (inGroup && line.find(':') != string::npos && line != groupName + ":") {
                inGroup = false;
            }

            lines.push_back(line);
        }
        groupFile.close();

        if (!groupFound) {
            system("cls");
            cout << "Invalid answer, try again:\n" << endl;
        }
        else {
             cout << "\nFINISH (f)\n\nEnter student names to remove:" << endl;
             string studentRemove;
             vector<string> studentsRemove;

             while (true) {
                cin >> studentRemove;
                if (studentRemove == "f" || studentRemove == "F") {
                    break;
                }
                studentsRemove.push_back(studentRemove);
             }

             vector<string> updatedLines;
             inGroup = false;
             for (const auto& currentLine : lines) {
                 if (currentLine == groupName + ":") {
                     inGroup = true;
                     groupFound = true; 
                     updatedLines.push_back(currentLine);
                     continue;
                 }

                 if (inGroup && currentLine.find(':') != string::npos) {
                     inGroup = false;
                 }

                 if (inGroup) {
                     bool toRemove = false; 
                     for (const auto& student : studentsRemove) {
                         if (currentLine.find(student) != string::npos) {
                             toRemove = true;
                             break; 
                         }
                     }
                     if (!toRemove) {
                         updatedLines.push_back(currentLine);
                     }
                 }
                 else {
                     updatedLines.push_back(currentLine);
                 }

                 ofstream output("group.txt", ios::trunc);
                 for (const auto& outline : updatedLines) {
                     output << outline << endl;
                 }
                 output.close();
             }
        }
    } while (!groupFound); 
}

void AddLectures() {
    bool groupFound = false; 
    do {
        cout << "Enter the group to add lectures: " << endl;
        string Group;
        cin >> Group;
        vector<string> lines;
        string line;

        ifstream lectureFile("lecture.txt");
        while (getline(lectureFile, line)) {
            lines.push_back(line);
            if (line == Group + ":") {
                groupFound = true;
            }
        }
        lectureFile.close();

        if (!groupFound) { 
            system("cls"); 
            cout << "Invalid answer, try again\n" << endl; 
        }
        else {
            cout << "\nFINISH (f)\n\nEnter lecture to add:" << endl;
            string lecture;
            vector<string> lectures;

            while (true) {
                cin >> lecture;  
                if (lecture == "f" || lecture == "F") {
                    break;
                }
                else {
                    fstream teachers("teachers.txt", ios::app);
                    teachers << lecture << ":" << endl;
                    teachers.close();
                }
                lectures.push_back(lecture);
            }

            ofstream output("lecture.txt", ios::trunc);
            for (const auto& line : lines) {
                output << line << endl;
                if (line == Group + ":") {
                    for (const auto& newlecture : lectures) { 
                        output << newlecture << endl; 
                    }
                }
            }
            output.close();
        }
    } while (!groupFound); 
}

void RemoveLectures() {
    bool groupFound = false; 
    do {
        cout << "Enter the group you want to delete" << endl;
        string group;
        cin >> group;

        vector<string> lines;
        bool inGroup = false;
        string line;

        ifstream lectureFile("lecture.txt");
        while (getline(lectureFile, line)) {
            if (line == group + ":") {
                groupFound = true;
                inGroup = true;
            }

            if (inGroup && line.find(':') != string::npos && line != group + ":") {
                inGroup = false;
            }

            lines.push_back(line);
        }
        lectureFile.close();

        if (!groupFound) {
            system("cls");
            cout << "Invalid answer, try again" << endl; 
        }
        else {
            cout << "\nFINISH (f)\n\nEnter lecture to remove:" << endl;
            string lectureRemove;
            vector<string> lecturesRemove;
            cin.ignore();

            while (true) {
                getline(cin, lectureRemove); 
                if (lectureRemove == "f" || lectureRemove == "F") {
                    break;
                }
                else {
                    ifstream teacher("teachers.txt");
                    vector<string> liness;
                    string linee;
                    bool inLecture = false;

                    while (getline(teacher, linee)) {
                        if (linee == lectureRemove + ":") {
                            inLecture = true;
                            continue;
                        }

                        if (inLecture && (linee.empty() || linee.find(":") != string::npos)) {
                            inLecture = false;
                        }

                        if (!inLecture) {
                            liness.push_back(linee);
                        }

                    }
                    teacher.close();

                    ofstream output("teachers.txt", ios::trunc);
                    for (const auto& I : liness) {
                        output << I << endl;
                    }
                    output.close();
                }
                lecturesRemove.push_back(lectureRemove);
            }

            vector<string> updatedLines;
            inGroup = false;
            for (const auto& currentLine : lines) {
                if (currentLine == group + ":") {
                    inGroup = true;
                    updatedLines.push_back(currentLine);
                    continue;
                }

                if (inGroup && currentLine.find(':') != string::npos) {
                    inGroup = false;
                }

                if (inGroup) {
                    if (find(lecturesRemove.begin(), lecturesRemove.end(), currentLine) == lecturesRemove.end()) {
                        updatedLines.push_back(currentLine);
                    }
                }
                else {
                    updatedLines.push_back(currentLine);
                }
            }

            ofstream output("lecture.txt", ios::trunc);
            for (const auto& outline : updatedLines) {
                output << outline << endl;
            }
            output.close();
        }
    } while (!groupFound); 
}

void RemoveTeacher() {
    bool lectureFound = false; 
    do {
        cout << "Enter the lecture you want to remove the teacher from:" << endl;
        string lecture;
        cin >> lecture;  

        vector<string> lines;
        bool inLecture = false;
        string line;

        ifstream teacherFile("teachers.txt");
        while (getline(teacherFile, line)) {
            if (line == lecture + ":") {
                lectureFound = true;
                inLecture = true;
            }

            if (inLecture && line.find(':') != string::npos && line != lecture + ":") {
                inLecture = false;
            }

            lines.push_back(line);
        }
        teacherFile.close();

        if (!lectureFound) {
            system("cls"); 
            cout << "Invalid answer, try again: " << endl; 
        }
        else {
            cout << "\nFINISH (f)\n\nEnter teacher's names to remove:" << endl;
            string teacherRemove;
            vector<string> teachersRemove;

            while (true) {
                getline(cin, teacherRemove); 
                if (teacherRemove == "f" || teacherRemove == "F") {
                    break;
                }
                teachersRemove.push_back(teacherRemove);
            }

            vector<string> updatedLines;
            inLecture = false;
            for (const auto& currentLine : lines) {
                if (currentLine == lecture + ":") {
                    inLecture = true;
                    updatedLines.push_back(currentLine);
                    continue;
                }

                if (inLecture && currentLine.find(':') != string::npos) {
                    inLecture = false;
                }

                if (inLecture) {
                    bool toRemove = false;
                    for (const auto& teacher : teachersRemove) {
                        if (currentLine == teacher != string::npos) {
                            toRemove = true; 
                            break; 
                        }
                        if (!toRemove) {
                            updatedLines.push_back(currentLine); 
                        }
                    }
                }
                else {
                    updatedLines.push_back(currentLine);
                }
            }

            ofstream output("teachers.txt", ios::trunc);
            for (const auto& outline : updatedLines) {
                output << outline << endl;
            }
            output.close();
        }
    } while (!lectureFound); 
}

void AddTeachers() {
    bool lectureFound = false;
    do {
        cout << "Enter the name of the lecture you want to add the teacher:" << endl;
        string lecture;
        cin >> lecture;  

        vector<string> lines;
        string line;

        ifstream teacherFile("teachers.txt");
        while (getline(teacherFile, line)) {
            lines.push_back(line);
            if (line == lecture + ":") {
                lectureFound = true;
            }
        }
        teacherFile.close();

        if (!lectureFound) {
            system("cls");
            cout << "Invalid answer, try again:" << endl;  
        }
        else {
            cout << "\nFINISH (f)\n\nEnter teachers name to add:" << endl;
            string teacher;
            vector<string> teachers;
            cin.ignore();

            while (true) {
                getline(cin, teacher); 
                if (teacher == "f" || teacher == "F") {
                    break;
                }
                teachers.push_back(teacher);
            }

            ofstream output("teachers.txt", ios::trunc);
            for (const auto& line : lines) {
                output << line << endl;
                if (line == lecture + ":") {  
                    for (const auto& newteacher : teachers) { 
                        output << newteacher << endl; 
                    }
                }
            }
            output.close();
        }
    } while (!lectureFound); 
} 

class Administrator {
private: 
    string AdministratorUsername; 
    string AdministratorPassword;  
    string choice;   
public: 
    Administrator() {
        while (true) {
            cout << "Username:" << endl;
            cin >> AdministratorUsername;
            if (AdministratorUsername == "admin") {
                while (true) {
                    cout << "Password:" << endl;
                    cin >> AdministratorPassword;
                    if (AdministratorPassword == "admin") {
                        system("cls");

                        while (true) {
                            system("cls"); 
                            cout << "STUDENT GROUPS (s)   LECTURES (l)   TEACHERS (t)    EXIT (e)\n" << endl; 
                            cin >> choice; 
                            if (choice == "s" || choice == "S") {
                                system("cls");
                                while (true) {
                                    system("cls"); 
                                    cout << "ADD STUDENTS (a)   REMOVE STUDENTS (r)    CREATE A GROUP (c)      DELETE A GROUP (d)       BACK (b)\n" << endl;
                                    cin >> choice; 
                                    if (choice == "a" || choice == "A") {
                                        system("cls"); 
                                        AddStudents();  
                                        system("cls");   
                                    }
                                    else if (choice == "c" || choice == "C") {
                                        system("cls"); 
                                        CreateGroup(); 
                                        system("cls"); 
                                    }
                                    else if (choice == "d" || choice == "D") {
                                        system("cls"); 
                                        DeleteGroup(); 
                                        system("cls");  
                                    }
                                    else if (choice == "r" || choice == "R") {
                                        system("cls"); 
                                        RemoveStudents();  
                                        system("cls"); 
                                    }
                                    else if (choice == "b" || choice == "B") {
                                        break; 
                                    }
                                    else {
                                        system("cls");
                                        cout << "       Invalid choice, try again:\n" << endl;
                                    }
                                }
                            }
                            else if (choice == "t" || choice == "T") {
                                system("cls");
                                while (true) {
                                    cout << "ADD TEACHER (a)      REMOVE TEACHER (r)       BACK (b)" << endl; 
                                    cin >> choice; 
                                    if (choice == "a" || choice == "A") {
                                        system("cls");
                                        AddTeachers();  
                                        system("cls");
                                    }
                                    else if (choice == "r" || choice == "R") {
                                        system("cls");
                                        RemoveTeacher();
                                        system("cls");
                                    }
                                    else if (choice == "b" || choice == "B") {
                                        break;
                                    }
                                    else {
                                        cout << "Invalid answer, try again" << endl; 
                                    }
                                }
                            }
                            else if (choice == "l" || choice == "L") {
                                system("cls");
                                while (true) {
                                    cout << "ADD LECTURES (a)       DELETE (d)    BACK (b)" << endl; 
                                    cin >> choice;
                                    if (choice == "a" || choice == "a") {  
                                        system("cls");
                                        AddLectures(); 
                                        system("cls");
                                    }
                                    else if (choice == "d" || choice == "D") {
                                        system("cls"); 
                                        RemoveLectures(); 
                                        system("cls");
                                    }
                                    else if (choice == "b" || choice == "B") {
                                        break; 
                                    }
                                    else {
                                        cout << "Invalid answer, try again" << endl; 
                                    }
                                }
                            }
                            else if (choice == "e" || choice == "E") {
                                break;
                            }
                            else {
                                system("cls");
                                cout << "Invalid choice, try again\n" << endl; 
                            }
                        }
                        break; 
                    }
                    else {
                        system("cls");
                        cout << "Invalid password, try again\n" << endl;
                    }
                }
                break; 
            }
            else {
                system("cls");
                cout << "Invalid username,try again\n" << endl;
            }
        }
    }
};

void CreateGrade() {
    string group;
    cout << "Enter the group:" << endl;
    cin >> group;

    ifstream groupFile("group.txt");
    if (!groupFile.is_open()) {
        cout << "Error: Unable to open file!" << endl;
        return;
    }

    vector<string> lines;
    string line;
    bool groupFound = false;
    bool inTargetGroup = false;
    vector<string> updatedGroupLines;

    while (getline(groupFile, line)) {
        lines.push_back(line);
    }
    groupFile.close();

    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i] == group + ":") {
            groupFound = true;
            inTargetGroup = true;
            updatedGroupLines.push_back(lines[i]); 
            continue;
        }

        if (inTargetGroup) {
            if (lines[i].empty() || lines[i].back() == ':') {
                inTargetGroup = false; 
                continue;
            }

            cout << lines[i] << endl;
            string newGrade;
            cout << "Enter grade for " << lines[i] << ": ";
            cin >> newGrade;

            updatedGroupLines.push_back(lines[i] + " " + newGrade);
        }
    }

    if (!groupFound) {
        cout << "Invalid group, try again." << endl;
        return;
    }

    ofstream outputFile("group.txt", ios::trunc);
    if (!outputFile.is_open()) {
        cout << "Error: Unable to write to file!" << endl;
        return;
    }

    inTargetGroup = false;
    for (const string& line : lines) {
        if (line == group + ":") {
            inTargetGroup = true;
            outputFile << line << endl;
            for (const string& updatedLine : updatedGroupLines) {
                if (updatedLine != group + ":") {
                    outputFile << updatedLine << endl;
                }
            }
            continue;
        }

        if (inTargetGroup && (line.empty() || line.back() == ':')) {
            inTargetGroup = false;
        }

        if (!inTargetGroup) {
            outputFile << line << endl;
        }
    }

    outputFile.close();
    cout << "Grades updated successfully!" << endl;
}

void EditGrade() {
    string group;
    cout << "Enter the group:" << endl;
    cin >> group;

    ifstream groupFile("group.txt");
    if (!groupFile.is_open()) {
        cout << "Error: Unable to open file!" << endl;
        return;
    }

    vector<string> lines;
    string line;
    bool groupFound = false;
    bool inTargetGroup = false;

    while (getline(groupFile, line)) {
        lines.push_back(line);
    }
    groupFile.close();

    vector<string> updatedLines;
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i] == group + ":") {
            groupFound = true;
            inTargetGroup = true;
            updatedLines.push_back(lines[i]);
            continue;
        }

        if (inTargetGroup) {
            if (lines[i].empty() || lines[i].back() == ':') {
                inTargetGroup = false;
                updatedLines.push_back(lines[i]); 
                continue;
            }

            size_t lastSpace = lines[i].find_last_of(' ');
            string studentName = lines[i].substr(0, lastSpace);
            string existingGrade = (lastSpace != string::npos) ? lines[i].substr(lastSpace + 1) : "";

            cout << "Current grade for " << studentName << ": " << (existingGrade.empty() ? "No grade" : existingGrade) << endl;

            string newGrade;
            cout << "Enter new grade for " << studentName << ": ";
            cin >> newGrade;

            updatedLines.push_back(studentName + " " + newGrade);
        }
        else {
            updatedLines.push_back(lines[i]);
        }
    }

    if (!groupFound) {
        cout << "Invalid group, try again." << endl;
        return;
    }

    ofstream outputFile("group.txt", ios::trunc);
    if (!outputFile.is_open()) {
        cout << "Error: Unable to write to file!" << endl;
        return;
    }

    for (const string& updatedLine : updatedLines) {
        outputFile << updatedLine << endl;
    }

    outputFile.close();
    cout << "Grades edited successfully!" << endl;
}

class Teacher {
private:
    string TeacherUsername;
    string TeacherPassword; 
    string choice; 
public:
    Teacher() {}

    bool Login() {
        while (true) {
            cout << "Username: " << endl;
            cin >> TeacherUsername;
            cout << "Password: " << endl;
            cin >> TeacherPassword;

            if (Validate(TeacherUsername, TeacherPassword)) {
                while (true) {
                    system("cls");
                    cout << "\nCREATE GRADE (c)   EDIT GRADES (e)    EXIT (x)" << endl;
                    cin >> choice;
                    if (choice == "c" || choice == "C") {
                        system("cls");
                        CreateGrade();
                    }
                    else if (choice == "e" || choice == "E") { 
                        system("cls");
                        EditGrade();  
                    }
                    else if (choice == "x" || choice == "X") {
                        break;
                    }
                    else {
                        system("cls");
                        cout << "Invalid answer, try again\n" << endl;
                    }
                }
                return true;
                break; 
            }
            else {
                system("cls");
                cout << "Invalid username or password. Please try again." << endl;
            }
        }
    } 
    bool Validate(const string& username, const string& password) {
        ifstream teachersFile("teachers.txt");

        string line;
        bool lectureSection = false;

        while (getline(teachersFile, line)) {
            if (line.empty()) continue;

            if (line.back() == ':') {
                lectureSection = true;
                continue;
            }

            if (lectureSection) {
                istringstream iss(line);
                string name, surname;
                iss >> name >> surname;

                if (name == username && surname == password) {
                    teachersFile.close();
                    return true;
                }
            }
        }

        teachersFile.close();
        return false;
    }
};

class Student { 
private:
    string StudentUsername; 
    string StudentPassword; 
    string choice; 
public:
    Student() {}  

    bool Login() {
        while (true) {
            cout << "Username: " << endl;
            cin >> StudentUsername;
            cout << "Password: " << endl; 
            cin >> StudentPassword;

            if (Validate(StudentUsername, StudentPassword)) { 
                while (true) {
                    system("cls"); 
                    cout << "ALL GRADES (g)  EXIT (e)" << endl; 
                    cin >> choice; 
                    if (choice == "g" || choice == "G") {
                        system("cls");
                        StudentsGrades(); 
                        break;
                    }
                    else if (choice == "e" || choice == "E") {
                        break; 
                    }
                }
                return true;
                break; 
            }
            else {
                system("cls");
                cout << "Invalid username or password. Please try again.\n" << endl;
            }
        }
    } 

    bool Validate(const string& username, const string& password) {
        ifstream groupFile("group.txt");
        string line;
        bool studentSection = false;

        while (getline(groupFile, line)) {
            if (line.empty()) {
                continue; 
            }
            if (line.back() == ':') {
                studentSection = true; 
                continue; 
            }
            if (studentSection) {
                istringstream iss(line); 
                string name, surname, grade;
                vector<string> grades;  

                iss >> name >> surname; 

                while (iss >> grade) {
                    grades.push_back(grade); 
                }
 
                if (name == username && surname == password) {
                    groupFile.close(); 
                    return true; 
                }
            }
        }
        groupFile.close();
        return false; 

    }

    void StudentsGrades() {
        ifstream groupFile("group.txt");
        string line; 
        bool studentSection = false;

        while (getline(groupFile, line)) {
            if (line.empty()) {
                continue;
            }

            istringstream iss(line);
            string name, surname, grade;
            vector<string> grades; 

            iss >> name >> surname;

            while (iss >> grade) {
                grades.push_back(grade); 
            }
            if (name == StudentUsername && surname == StudentPassword) {
                cout << "Student name: " << name << " " << surname << endl; 
                cout << "Grades: ";
                for (const string& grade : grades) {
                    cout << grade << " ";
                }
                cout << endl; 
                break; 
            }
        }
        groupFile.close(); 
        while (true) {
            cout << "\n\nEXIT (e)" << endl;
            cin >> choice;
            if (choice == "e" || choice == "E") {
                break; 
            }
            else {
                system("cls");
                cout << "Invalid choice, try again:" << endl;
            }
        } 
    }
};

int main()
{
    cout << "                AKADEMINE SISTEMA    \n\n" << endl; 
    while (true) {
        cout << "STUDENT (s)            TEACHER (t)           ADMINISTRATOR (a)\n" << endl;
        string login;
        cin >> login;
        system("cls");

        if (login == "s" || login == "S") {
            Student studentLogin;  
            if (studentLogin.Login()) {
            }
            break;
        }
        else if (login == "t" || login == "T") {
            Teacher teacher;  
            if (teacher.Login()) {  
                break;
            }
            break;
        }
        else if (login == "a" || login == "A") {
            Administrator();
            break;
        }
        else {
            cout << "Invalid choice, try again\n" << endl;
        }
    }

    return 0;
}
