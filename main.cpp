#include <_types/_uint8_t.h>
#include <cstdint>
#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <set>
#define hu uint16_t
#define f first
#define s second
using namespace std;

struct Class {
  hu grade;
  hu room;
  Class (hu g, hu r) : grade(g), room(r) {}
};

class TimeTable {
public:
  struct Period {
    hu subject;
    hu teacher;
    string room;
    string text;
    Period() {}
    Period(hu subject, hu teacher, string room): subject(subject), teacher(teacher), room(room) {}
  };struct Room {
    string roomName;
    map<hu, hu> subjectsTeacherth;
    Period** periods[5];
  };struct Class {
    string gradeName;
    stack<hu> emptyRoomIndexes;
    map<hu, Room> rooms;
  };

  hu maxPeriod;
  static stack<hu> emptyGradeIndexes;
  static map<hu, Class> grades;

  TimeTable(hu maxPeriod) : maxPeriod(maxPeriod) {}

  void display() {
    if (!emptyGradeIndexes.empty()) cout << "\ttop empty grade index: " << emptyGradeIndexes.top();
    for (auto i: grades) {
      cout << "Grade " << i.f << '(' << i.s.gradeName << "):\n";
      if (!i.s.emptyRoomIndexes.empty()) cout << "\ttop empty room index: " << i.s.emptyRoomIndexes.top();
      for (auto j: i.s.rooms) {
        cout << "\tRoom " << j.f << '(' << j.s.roomName << "):\n\t\t(subjects: teachers): ";
        for (auto k: j.s.subjectsTeacherth) cout << k.f << ": " << k.s << ", ";
        cout << '\n';
        for (hu k = 0; k < 5; k++) {
          cout << "\t\tDay " << k << ":\n";
          for (hu l = 0; l < maxPeriod; l++) cout << "\t\t\tperiod " << l << ": " << j.s.periods[k][l]->subject << ", " <<  j.s.periods[k][l]->teacher << ", " <<  j.s.periods[k][l]->room << ", " << j.s.periods[k][l]->text << '\n';
          cout << '\n';
        }
      }
    }
  }

  void addGrade(string name) {
    grades[emptyGradeIndexes.empty() ? (!grades.empty() ? grades.rbegin()->f + 1 : 0) : emptyGradeIndexes.top()].gradeName = name;
    if (!emptyGradeIndexes.empty()) emptyGradeIndexes.pop();
  }

  bool removeGrade(hu id) {
    if (grades.find(id) == grades.end()) return false;
    emptyGradeIndexes.push(id);
    grades.erase(id);
    return true;
  }

  bool addRoom(hu gradeId, string name) {
    if (grades.find(gradeId) == grades.end()) return false;
    auto thisGrade = &grades[gradeId];
    auto thisRoom =  &(*thisGrade).rooms[(*thisGrade).emptyRoomIndexes.empty() ? (!(*thisGrade).rooms.empty() ? (*thisGrade).rooms.rbegin()->f + 1 : 0) : (*thisGrade).emptyRoomIndexes.top()];
    for (hu i = 0; i < 5; i++) {
      (*thisRoom).periods[i] = new Period*[maxPeriod];
      for (hu j = 0; j < maxPeriod; j++) (*thisRoom).periods[i][j] = new Period();
    }(*thisRoom).roomName = name;

    if (!(*thisGrade).emptyRoomIndexes.empty()) (*thisGrade).emptyRoomIndexes.pop();
    return true;
  }

  bool removeRoom(hu gradeId, hu id) {
    if (grades.find(gradeId) == grades.end() || ((grades[gradeId]).rooms.find(id) == (grades[gradeId]).rooms.end())) return false;
    auto thisGrade = &grades[gradeId];
    (*thisGrade).emptyRoomIndexes.push(id);
    (*thisGrade).rooms.erase(id);
    return true;
  }
};map<hu, TimeTable::Class> TimeTable::grades;
stack<hu> TimeTable::emptyGradeIndexes;
TimeTable timetable(8);

class Subjects {
public:
  struct Subject {
    string name;
    uint8_t factor;
    map<hu, set<Class> > teacheresClassesth;
  };

  static stack<hu> emptySubjectIndexes;
  static map<hu, Subject> subjects;

  bool addSubject(string name, uint8_t factor) {
    //a
    subjects[emptySubjectIndexes.empty() ? (!subjects.empty() ? subjects.rbegin()->f + 1 : 0) : emptySubjectIndexes.top()];
    if (!emptySubjectIndexes.empty()) emptySubjectIndexes.pop();
    return true;
  }

  bool removeSubject(hu id) {
    if (subjects.find(id) == subjects.end()) return false;
    emptySubjectIndexes.push(id);
    subjects.erase(id);
    return true;
  }
};map<hu, Subjects::Subject> Subjects::subjects;

class Teachers {
public:
  struct Teacher {
    string name;
    map<hu, set<Class> > subjectsClassesth;
  };

  static stack<hu> emptyTeacherIndexes;
  static map<hu, Teacher> teachers;

  bool addTeacher(string name) {
    teachers[emptyTeacherIndexes.empty() ? (!teachers.empty() ? teachers.rbegin()->f + 1 : 0) : emptyTeacherIndexes.top()].name = name;
    if (!emptyTeacherIndexes.empty()) emptyTeacherIndexes.pop();
    return true;
  }

  bool removeSubject(hu id) {
    if (teachers.find(id) == teachers.end()) return false;
    emptyTeacherIndexes.push(id);
    teachers.erase(id);
    return true;
  }
};

int main() {
  timetable.addGrade("a");
  timetable.addRoom(0, "B");
  timetable.addRoom(0, "c");
  timetable.addRoom(0, "d");
  timetable.removeRoom(0, 1);
  timetable.addRoom(0, "f");
  TimeTable::grades[0].rooms[1].subjectsTeacherth[1] = 2;
  TimeTable::grades[0].rooms[1].subjectsTeacherth[2] = 3;
  timetable.display();
}

