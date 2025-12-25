#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class student {
public:
    int id;
    string name;
    float gpa;
    string password;
    student* pnext;
};

class course {
public:
    string coursename;
    int courseid;
    int maxseats;
    int currentseats;
    course* pnext;
};

class enrollment {
public:
    int enrollmentid;
    int studentid;
    int courseid;
    float grade;
    enrollment* pnext;
};

class admin {
public:
    int adminid;
    string adminname;
    string adminpass;
    admin* pnext;
};

class Cliststudent {
public:
    student* phead;
    student* ptail;

    Cliststudent() {
        phead = NULL;
        ptail = NULL;
    }

    ~Cliststudent() {
        student* ptrap;
        ptrap = phead;
        while (phead != NULL) {
            phead = ptrap->pnext;
            ptrap->pnext = NULL;
            delete ptrap;
            ptrap = phead;
        }
    }

    void attach(student* pnn) {
        if (phead == NULL) {
            phead = pnn;
            ptail = pnn;
        }
        else {
            ptail->pnext = pnn;
            ptail = pnn;
        }
    }

    void Display() {
        student* ptrav;
        ptrav = phead;
        while (ptrav != NULL) {
            cout << ptrav->id << " " << ptrav->name << " " << ptrav->gpa << " " << ptrav->password << endl;
            ptrav = ptrav->pnext;
        }
    }
};

class Clistcourse {
public:
    course* phead;
    course* ptail;

    Clistcourse() {
        phead = NULL;
        ptail = NULL;
    }

    ~Clistcourse() {
        course* ptrap;
        ptrap = phead;
        while (phead != NULL) {
            phead = ptrap->pnext;
            ptrap->pnext = NULL;
            delete ptrap;
            ptrap = phead;
        }
    }

    void attach(course* pnn) {
        if (phead == NULL) {
            phead = pnn;
            ptail = pnn;
        }
        else {
            ptail->pnext = pnn;
            ptail = pnn;
        }
    }

    void Display() {
        course* ptrav;
        ptrav = phead;
        while (ptrav != NULL) {
            cout << ptrav->courseid << " " << ptrav->coursename << " " << ptrav->maxseats << " " << ptrav->currentseats << endl;
            ptrav = ptrav->pnext;
        }
    }
};

class Clistenrollment {
public:
    enrollment* phead;
    enrollment* ptail;

    Clistenrollment() {
        phead = NULL;
        ptail = NULL;
    }

    ~Clistenrollment() {
        enrollment* ptrap;
        ptrap = phead;
        while (phead != NULL) {
            phead = ptrap->pnext;
            ptrap->pnext = NULL;
            delete ptrap;
            ptrap = phead;
        }
    }

    void attach(enrollment* pnn) {
        if (phead == NULL) {
            phead = pnn;
            ptail = pnn;
        }
        else {
            ptail->pnext = pnn;
            ptail = pnn;
        }
    }

    void Display() {
        enrollment* ptrav;
        ptrav = phead;
        while (ptrav != NULL) {
            cout << ptrav->enrollmentid << " " << ptrav->studentid << " " << ptrav->courseid << " " << ptrav->grade << endl;
            ptrav = ptrav->pnext;
        }
    }
};

class Clistadmin {
public:
    admin* phead;
    admin* ptail;

    Clistadmin() {
        phead = NULL;
        ptail = NULL;
    }

    ~Clistadmin() {
        admin* ptrap;
        ptrap = phead;
        while (phead != NULL) {
            phead = ptrap->pnext;
            ptrap->pnext = NULL;
            delete ptrap;
            ptrap = phead;
        }
    }

    void attach(admin* pnn) {
        if (phead == NULL) {
            phead = pnn;
            ptail = pnn;
        }
        else {
            ptail->pnext = pnn;
            ptail = pnn;
        }
    }

    void Display() {
        admin* ptrav;
        ptrav = phead;
        while (ptrav != NULL) {
            cout << ptrav->adminid << " " << ptrav->adminname << " " << ptrav->adminpass << endl;
            ptrav = ptrav->pnext;
        }
    }
};

void saveStudentsToFile(Cliststudent& lsStudent, string filename);
void saveCoursesToFile(Clistcourse& lsCourse, string filename);
void saveEnrollmentsToFile(Clistenrollment& lsEnrollment, string filename);
void saveAdminsToFile(Clistadmin& lsAdmin, string filename);
void Enroll(int studentId, Clistcourse& lsCourse, Clistenrollment& lsEnrollment);
void viewTranscript(int studentId, Clistcourse& lsCourse, Clistenrollment& lsEnrollment);
course* findCourseById(int courseId, Clistcourse& lsCourse);

void saveStudentsToFile(Cliststudent& lsStudent, string filename) {
    ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        cout << "Could not open the file " << filename << " for writing." << endl;
        return;
    }
    file << "ID,NAME,GPA,PASSWORD\n";
    student* ptrav = lsStudent.phead;
    while (ptrav != NULL) {
        file << ptrav->id << "," << ptrav->name << "," << ptrav->gpa << "," << ptrav->password << "\n";
        ptrav = ptrav->pnext;
    }
    file.close();
}

void registerStudent(Cliststudent& lsStudent, string name, string password, float gpa) {
    student* pnew = new student;
    if (lsStudent.phead == NULL) {
        pnew->id = 1;
    }
    else pnew->id = lsStudent.ptail->id + 1;

    pnew->name = name;
    pnew->password = password;
    pnew->gpa = gpa;
    pnew->pnext = NULL;
    cout << "Student registered with ID: " << pnew->id << endl;
    lsStudent.attach(pnew);
    saveStudentsToFile(lsStudent, "Students.txt");
}

student* loginStudent(Cliststudent& lsStudent, int id, string password) {
    student* ptrav = lsStudent.phead;
    while (ptrav != NULL) {
        if (ptrav->id == id && ptrav->password == password) {
            cout << "Login successful. Welcome " << ptrav->name << " !" << endl;
            return ptrav;  
        }
        ptrav = ptrav->pnext;
    }
    cout << "Invalid ID or password." << endl;
    return NULL;  
}

void loadStudentsFromFile(Cliststudent& lsStudent, string filename) {
    fstream file;
    file.open(filename);
    if (!file.is_open()) {
        cout << "Could not open the file " << filename << endl;
        return;
    }
    string line;
    getline(file, line); 
    while (getline(file, line)) {
        student* pnew = new student;
        string temp[4]; int it = 0;
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ',') it++;
            else temp[it] += line[i];
        }
        pnew->id = stoi(temp[0]);
        pnew->name = temp[1];
        pnew->gpa = stof(temp[2]);
        pnew->password = temp[3];
        pnew->pnext = NULL;

        lsStudent.attach(pnew);
    }
    file.close();
}


int studentisEnrolled(int studentId, int courseId, Clistenrollment& lsEnrollment) {
    enrollment* ptrav = lsEnrollment.phead;
    while (ptrav != NULL) {
        if (ptrav->studentid == studentId && ptrav->courseid == courseId) {
            return 1;
        }
        ptrav = ptrav->pnext;
    }
    return 0;
}

void viewTranscript(int studentId, Clistcourse& lsCourse, Clistenrollment& lsEnrollment) {
  cout << endl << "----- Your Transcript -----" << endl;
  cout << "Course Name\tGrade" << endl;
  enrollment* ptrav = lsEnrollment.phead;
  int found = 0;
  while(ptrav != NULL) {
    if(ptrav->studentid == studentId) {
      course* findCourse = findCourseById(ptrav->courseid, lsCourse);
      if(findCourse != NULL) {
        cout << findCourse->coursename << "\t" << ptrav->grade << endl;
        found = 1;
      }
    }
    ptrav = ptrav->pnext;
  }
  if(!found) {
    cout << "No courses enrolled yet." << endl;
  }
}

course* findCourseById(int courseId, Clistcourse& lsCourse) {
  course* ptrav = lsCourse.phead;
  while(ptrav != NULL) {
    if(ptrav->courseid == courseId) {
      return ptrav;
    }
    ptrav = ptrav->pnext;  
  }
  return NULL;
}


void Enroll(int studentId, Clistcourse& lsCourse, Clistenrollment& lsEnrollment) {
  int courseId;
  cout << "Enter Course ID to enroll: ";
  cin >> courseId;
  course* findCourse = findCourseById(courseId, lsCourse);
  if(findCourse == NULL) {
    cout << "Course not found." << endl;
    return;
  }
  if(studentisEnrolled(studentId, courseId, lsEnrollment)) {
    cout << "You are already enrolled in this course." << endl;
    return;
  }
  if(findCourse->currentseats >= findCourse->maxseats) {
    cout << "Course is full. Cannot enroll." << endl;
    return;
  }

  enrollment* pnew = new enrollment;
  if(lsEnrollment.phead == NULL) {
    pnew->enrollmentid = 1;
  } else {
    pnew->enrollmentid = lsEnrollment.ptail->enrollmentid + 1;
  }
  pnew->studentid = studentId;
  pnew->courseid = courseId;
  pnew->grade = 0.0; 
  pnew->pnext = NULL;
  lsEnrollment.attach(pnew);
  findCourse->currentseats += 1; 
  cout << "Enrolled successfully in " << findCourse->coursename << "!" << endl;
}


void studentMenu(Cliststudent& lsStudent, Clistcourse& lsCourse, Clistenrollment& lsEnrollment) {
    while (true)
    {
        int option;
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Display All Students (Test)\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> option;

        if (option == 1) {
            string name, password;
            float gpa;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter GPA: ";
            cin >> gpa;
            registerStudent(lsStudent, name, password, gpa);
            cout << "Registration successful!" << endl;
            saveStudentsToFile(lsStudent, "Students.txt");
        }
        else if (option == 2) {
            int id;
            string password;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter password: ";
            cin >> password;
            student* loggedInStudent = loginStudent(lsStudent, id, password);

            if (loggedInStudent == NULL) {
                cout << "Please try again.\n";
            }
            else {
                int studentOption;
                while (true)
                {
									cout << "1. View Courses\n";
									cout << "2. Enroll in Course\n";
									cout << "3. View Transcript\n";
									cout << "4. Logout\n";
									cout << "Choose an option: ";
									cin >> studentOption;  

									if (studentOption == 1) {
											lsCourse.Display();
									}
									else if (studentOption == 2) {
											Enroll(loggedInStudent->id, lsCourse, lsEnrollment);
											saveCoursesToFile(lsCourse, "Courses.txt");
											saveEnrollmentsToFile(lsEnrollment, "Enrollments.txt");
									}
									else if (studentOption == 3) {
										viewTranscript(loggedInStudent->id, lsCourse, lsEnrollment);
									}
									else if (studentOption == 4) {
											cout << "Logging out..." << endl;
											break;
									}
									else {
											cout << "Invalid option. Please try again." << endl;
									}
            	  }
            } 
        }
        else if (option == 3) {
            cout << "\n----- All Students -----\n";
            cout << "ID\tName\tGPA\tPassword\n";
            lsStudent.Display();
            cout << "------------------------\n\n";
        }
        else if (option == 4) {
            break;
        }
        else {
            cout << "Invalid option. Please try again." << endl;
        }
    }
}

void loadCoursesFromFile(Clistcourse& lsCourse, string filename) {
    fstream file;
    file.open(filename);
    if (!file.is_open()) {
        cout << "Could not open the file " << filename << endl;
        return;
    }
    string line;
    getline(file, line); 
    while (getline(file, line)) {
        course* pnew = new course;
        string temp[4]; int it = 0;
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ',') it++;
            else temp[it] += line[i];
        }
        pnew->courseid = stoi(temp[0]);
        pnew->coursename = temp[1];
        pnew->maxseats = stoi(temp[2]);
        pnew->currentseats = stoi(temp[3]);
        pnew->pnext = NULL;
        lsCourse.attach(pnew);
    }
    file.close();
}

void saveCoursesToFile(Clistcourse& lsCourse, string filename) {
    ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        cout << "Could not open the file " << filename << " for writing." << endl;
        return;
    }
    file << "COURSEID,COURSENAME,MAXSEATS,CURRENTSEATS\n";
    course* ptrav = lsCourse.phead;
    while (ptrav != NULL) {
        file << ptrav->courseid << "," << ptrav->coursename << "," << ptrav->maxseats << "," << ptrav->currentseats << "\n";
        ptrav = ptrav->pnext;
    }
    file.close();
}

void loadEnrollmentsFromFile(Clistenrollment& lsEnrollment, string filename) {
    fstream file;
    file.open(filename);
    if (!file.is_open()) {
        cout << "Could not open the file " << filename << endl;
        return;
    }
    string line;
    getline(file, line); 
    while (getline(file, line)) {
        enrollment* pnew = new enrollment;
        string temp[4]; int it = 0;
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ',') it++;
            else temp[it] += line[i];
        }
        pnew->enrollmentid = stoi(temp[0]);
        pnew->studentid = stoi(temp[1]);
        pnew->courseid = stoi(temp[2]);
        pnew->grade = stof(temp[3]);
        pnew->pnext = NULL;
        lsEnrollment.attach(pnew);
    }
    file.close();
}

void saveEnrollmentsToFile(Clistenrollment& lsEnrollment, string filename) {
    ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        cout << "Could not open the file " << filename << " for writing." << endl;
        return;
    }
    file << "ENROLLMENTID,STUDENTID,COURSEID,GRADE\n";
    enrollment* ptrav = lsEnrollment.phead;
    while (ptrav != NULL) {
        file << ptrav->enrollmentid << "," << ptrav->studentid << "," << ptrav->courseid << "," << ptrav->grade << "\n";
        ptrav = ptrav->pnext;
    }
    file.close();
}

void loadAdminsFromFile(Clistadmin& lsAdmin, string filename) {
    fstream file;
    file.open(filename);
    if (!file.is_open()) {
        cout << "Could not open the file " << filename << endl;
        return;
    }
    string line;
    getline(file, line); 
    while (getline(file, line)) {
        admin* pnew = new admin;
        string temp[3]; int it = 0;
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ',') it++;
            else temp[it] += line[i];
        }
        pnew->adminid = stoi(temp[0]);
        pnew->adminname = temp[1];
        pnew->adminpass = temp[2];
        pnew->pnext = NULL;
        lsAdmin.attach(pnew);
    }
    file.close();
}

void saveAdminsToFile(Clistadmin& lsAdmin, string filename) {
    ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        cout << "Could not open the file " << filename << " for writing." << endl;
        return;
    }
    file << "ADMINID,ADMINNAME,ADMINPASS\n";
    admin* ptrav = lsAdmin.phead;
    while (ptrav != NULL) {
        file << ptrav->adminid << "," << ptrav->adminname << "," << ptrav->adminpass << "\n";
        ptrav = ptrav->pnext;
    }
    file.close();
}

int loginadmin(Clistadmin& lsAdmin, int id, string password) {
    admin* ptrav = lsAdmin.phead;
    while (ptrav != NULL) {
        if (ptrav->adminid == id && ptrav->adminpass == password) {
            cout << "Login successful. Welcome " << ptrav->adminname << " !" << endl;
            return 1;
        }
        ptrav = ptrav->pnext;
    }
    cout << "Invalid name or password." << endl;
    return 0;
}

void removestundetenrollment(int studentid, Clistenrollment& lsEnrollment) {
    enrollment* ptrav = lsEnrollment.phead;
    enrollment* prev = NULL;
    while (ptrav != NULL) {
        if (ptrav->studentid == studentid) {
            if (prev == NULL) {
                lsEnrollment.phead = ptrav->pnext;
            }
            else {
                prev->pnext = ptrav->pnext;
            }
            delete ptrav;
            cout << "Enrollments for student ID " << studentid << " deleted successfully." << endl;
            saveEnrollmentsToFile(lsEnrollment, "Enrollments.txt");
            return;
        }
        prev = ptrav;
        ptrav = ptrav->pnext;
    }
}

void admincrud(Cliststudent& lsStudent, Clistcourse& lsCourse, Clistenrollment& lsEnrollment)
{
    int option;
    cout << "1. update student\n";
    cout << "2. update course\n";
    cout << "3. course report\n";
    cout << "4.enrollemnt report\n";
    cin >> option;
    if (option == 1) {
        int studentid;
        cout << "Enter student id to update: ";
        cin >> studentid;

        int studentoption;
        cout << "1. create student\n";
        cout << "2. read student\n";
        cout << "3. update student\n";
        cout << "4. delete student\n";
        cout << "5.Update student gpa\n";
        cin >> studentoption;
        if (studentoption == 1) {
            string name, password;
            float gpa;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter GPA: ";
            cin >> gpa;
            registerStudent(lsStudent, name, password, gpa);
            cout << "Registration successful!" << endl;
            saveStudentsToFile(lsStudent, "Students.txt");
        }
        if (studentoption == 2) {
            cout << "Student Details:" << endl;
            student* ptrav = lsStudent.phead;
            while (ptrav != NULL) {
                if (ptrav->id == studentid) {
                    cout << ptrav->id << " " << ptrav->name << " " << ptrav->gpa << " " << ptrav->password << endl;
                    return;
                }
                ptrav = ptrav->pnext;
            }
        }
        if (studentoption == 3) {
            string name, password;
            float gpa;
            cout << "Enter new name: ";
            cin >> name;
            cout << "Enter new password: ";
            cin >> password;
            cout << "Enter new GPA: ";
            cin >> gpa;
            student* ptrav = lsStudent.phead;
            while (ptrav != NULL) {
                if (ptrav->id == studentid) {
                    ptrav->name = name;
                    ptrav->password = password;
                    ptrav->gpa = gpa;
                    cout << "Student updated successfully." << endl;
                    saveStudentsToFile(lsStudent, "Students.txt");
                    return;
                }
                ptrav = ptrav->pnext;
            }
        }
        if (studentoption == 4) {
            student* ptrav = lsStudent.phead;
            student* prev = NULL;
            while (ptrav != NULL) {
                if (ptrav->id == studentid) {
                    if (prev == NULL) {
                        lsStudent.phead = ptrav->pnext;
                    }
                    else {
                        prev->pnext = ptrav->pnext;
                    }
                    delete ptrav;

                    cout << "Student deleted successfully." << endl;
                    saveStudentsToFile(lsStudent, "Students.txt");
                    removestundetenrollment(studentid, lsEnrollment);
                    return;
                }
                prev = ptrav;
                ptrav = ptrav->pnext;
            }
        }
        if (studentoption == 5) {
            float gpa;
            cout << "Enter new GPA: ";
            cin >> gpa;
            student* ptrav = lsStudent.phead;
            while (ptrav != NULL) {
                if (ptrav->id == studentid) {
                    ptrav->gpa = gpa;
                    cout << "GPA updated successfully." << endl;
                    saveStudentsToFile(lsStudent, "Students.txt");
                    return;
                }
                ptrav = ptrav->pnext;
            }
        }
    }

    if (option == 2) {
        int courseid;
        cout << "Enter course id to update: ";
        cin >> courseid;

        int courseoption;
        cout << "1. create course\n";
        cout << "2. read course\n";
        cout << "3. update course\n";
        cout << "4. delete course\n";
        cin >> courseoption;
        if (courseoption == 1) {
            string coursename;
            int maxseats;
            cout << "Enter course name: ";
            cin >> coursename;
            cout << "Enter max seats: ";
            cin >> maxseats;
            course* pnew = new course;
            if (lsCourse.phead == NULL) {
                pnew->courseid = 1;
            }
            else pnew->courseid = lsCourse.ptail->courseid + 1;

            pnew->coursename = coursename;
            pnew->maxseats = maxseats;
            pnew->currentseats = 0;
            pnew->pnext = NULL;
            cout << "Course created with ID: " << pnew->courseid << endl;
            lsCourse.attach(pnew);
            saveCoursesToFile(lsCourse, "Courses.txt");
        }
        if (courseoption == 2) {
            cout << "Course Details:" << endl;
            course* ptrav = lsCourse.phead;
            while (ptrav != NULL) {
                if (ptrav->courseid == courseid) {
                    cout << ptrav->courseid << " " << ptrav->coursename << " " << ptrav->maxseats << " " << ptrav->currentseats << endl;
                    return;
                }
                ptrav = ptrav->pnext;
            }
        }
        if (courseoption == 3) {
            string coursename;
            int maxseats;
            cout << "Enter new course name: ";
            cin >> coursename;
            cout << "Enter new max seats: ";
            cin >> maxseats;
            course* ptrav = lsCourse.phead;
            while (ptrav != NULL) {
                if (ptrav->courseid == courseid) {
                    ptrav->coursename = coursename;
                    ptrav->maxseats = maxseats;
                    cout << "Course updated successfully." << endl;
                    saveCoursesToFile(lsCourse, "Courses.txt");
                    return;
                }
                ptrav = ptrav->pnext;
            }
        }
        if (courseoption == 4) {
            course* ptrav = lsCourse.phead;
            course* prev = NULL;
            while (ptrav != NULL) {
                if (ptrav->courseid == courseid) {
                    if (prev == NULL) {
                        lsCourse.phead = ptrav->pnext;
                    }
                    else {
                        prev->pnext = ptrav->pnext;
                    }
                    delete ptrav;
                    cout << "Course deleted successfully." << endl;
                    saveCoursesToFile(lsCourse, "Courses.txt");
                    return;
                }
                prev = ptrav;
                ptrav = ptrav->pnext;
            }
        }
    }

    if (option == 3)
    {
        cout << "Course report\n";
        int courseid;
        cout << "Enter course id: ";
        cin >> courseid;

        cout << "Students enrolled in course ID " << courseid << ":\n";
        cout << "StudentID\tGrade\n";
        enrollment* ptrav = lsEnrollment.phead;
        while (ptrav != NULL)
        {

            if (ptrav->courseid == courseid)
            {
                cout << ptrav->studentid << "\t" << ptrav->grade << endl;
            }
            ptrav = ptrav->pnext;
        }
    }

    if (option == 4)
    {
        cout << "course warning\n";
        course* ptravc = lsCourse.phead;
        while (ptravc != NULL)
        {
            int nowseats = ptravc->currentseats;
            int maxseats = ptravc->maxseats;
            float percent = (nowseats / maxseats) * 100;
            if (percent >= 80)
            {
                cout << "Course ID: " << ptravc->courseid << " is at " << percent << "Capacity.\n";
            }
            ptravc = ptravc->pnext;
        }
    }
}


void adminMenu(Clistadmin& lsAdmin, Cliststudent& lsStudent, Clistcourse& lsCourse, Clistenrollment& lsEnrollment) {

    int option;
    cout << "Admin Menu" << endl;
    cout << "1. login" << endl;
    cout << "2. Exit" << endl;
    cin >> option;
    if (option == 1) {
        string password;
        int id;
        cout << "Enter Admin id: ";
        cin >> id;
        cout << "Enter Admin password: ";
        cin >> password;
        if (loginadmin(lsAdmin, id, password) == 1) {
            cout << "Admin logged in successfully." << endl;
            admincrud(lsStudent, lsCourse, lsEnrollment);
            return;
        }
        else {
            cout << "Invalid Admin id or password." << endl;
            return;
        }

    }
    if (option == 2) {
        return;
    }

}


int main() {
    Cliststudent lsStudent;
    Clistcourse lsCourse;
    Clistenrollment lsEnrollment;
    Clistadmin lsAdmin;

    loadStudentsFromFile(lsStudent, "Students.txt");
    loadCoursesFromFile(lsCourse, "Courses.txt");
    loadEnrollmentsFromFile(lsEnrollment, "Enrollments.txt");
    loadAdminsFromFile(lsAdmin, "Admins.txt");


    cout << "Welcome to the Student Management System!" << endl;
    int choice;
    while (true) {
        cout << "----- Main Menu -----" << endl;
        cout << "1. Student Portal" << endl;
        cout << "2. Admin Portal" << endl;
        cout << "3. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;
        if (choice == 1) {
            studentMenu(lsStudent, lsCourse, lsEnrollment);
        }
        else if (choice == 2) {
            adminMenu(lsAdmin, lsStudent, lsCourse, lsEnrollment);
        }
        else if (choice == 3) {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid option. Please try again." << endl;
        }
    }
    saveStudentsToFile(lsStudent, "Students.txt");
		saveCoursesToFile(lsCourse, "Courses.txt");
		saveEnrollmentsToFile(lsEnrollment, "Enrollments.txt");
		saveAdminsToFile(lsAdmin, "Admins.txt");

    cout << "Program started successfully!" << endl;
    return 0;
}