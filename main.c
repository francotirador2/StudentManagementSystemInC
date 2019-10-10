#include <stdio.h>
#include <ctype.h>

#include "List.h"
#include "Tree.h"
#include "utils.h"



//===============STUDENT===========
typedef struct Student {
	char * name;
	int regNo;
	char * deptCode;
	Tree scores;
} Student;

char * studentToString(void * student) {
	Student tmp = *(Student*)student;
	char * result = newString(128);
	result[0] = '('; result[1] = '\0';
	strcat(result,intToString(tmp.regNo)); strcat(result,",");
	strcat(result,tmp.name); strcat(result,",");
	strcat(result,tmp.deptCode);
	strcat(result,")");
	return result;
}

char * studentKey(void * student) {
	Student tmp = *(Student*)student;
	return intToString(tmp.regNo);
}

int studentEqual(void * a, void * b) {
	Student ca = *(Student*)a;
	Student cb = *(Student*)b;
	return (ca.regNo == cb.regNo);
}

Tree students; 
//=================================


//========DEPARTMENT===============
typedef struct Dept {
	char * name;
	char * code;
	char * hodName;
} Dept;

char * deptToString(void * dept) {
	Dept tmp = *(Dept*)dept;
	char * result = newString(128);
	result[0] = '('; result[1] = '\0';
	strcat(result,tmp.code); strcat(result,",");
	strcat(result,tmp.name); strcat(result,",");
	strcat(result,tmp.hodName);
	strcat(result,")");
	return result;
}

char * deptKey(void * dept) {
	Dept tmp = *(Dept*)dept;
	return tmp.code;
}

int deptEqual(void * a, void * b) {
	Dept ca = *(Dept*)a;
	Dept cb = *(Dept*)b;
	return (strcmp(ca.code,cb.code) == 0);
}

Tree depts;
//================================

//===========COURSE===============
typedef struct Course {
	char * name;
	char * code;
	int credits;
} Course;

char * courseToString(void * course) {
	Course tmp = *(Course*)course;
	char * result = newString(128);
	result[0] = '('; result[1] = '\0';
	strcat(result,tmp.code); strcat(result,", ");
	strcat(result,tmp.name); strcat(result,", ");
	strcat(result,intToString(tmp.credits)); 
	strcat(result,")");
	return result;
}

char * courseKey(void * course) {
	Course tmp = *(Course*)course;
	return tmp.code;
}

int courseEqual(void * a, void * b) {
	Course ca = *(Course*)a;
	Course cb = *(Course*)b;
	return (strcmp(ca.code,cb.code) == 0);
}

Tree courses;
//================================

//=============SCORES=============
typedef struct Score {
	char * courseCode;
	int grade;
} Score;


char * scoreToString(void * score) {
	Score tmp = *(Score*)score;
	char * result = newString(128);
	result[0] = '('; result[1] = '\0';
	strcat(result,tmp.courseCode); strcat(result,", ");
	strcat(result,intToString(tmp.grade));
	strcat(result,")");
	return result;
} 

char * scoreKey(void * score) {
	Score tmp = *(Score*)score;
	return tmp.courseCode;
}

int scoreEqual(void * a, void * b) {
	Score ca = *(Score*)a;
	Score cb = *(Score*)b;
	return (strcmp(ca.courseCode,cb.courseCode) == 0);
}
//================================



void addStudent() {
	
	int tmpRegNo = readInt("RegNo: ");
	TreeNode * node = findInTree(students,students.root,intToString(tmpRegNo));
	if (node != NULL) {
		printf("Student with that ID already exists");
		return;
	}
	
	char * tmpName = readString("Name: ");
	
	char * tmpDeptCode = readString("DeptCode: ");
	node = findInTree(depts,depts.root,tmpDeptCode);
	
	if (node != NULL) {
	
		Tree tmpScoresTree = newTree(scoreToString,scoreKey,courseEqual);
		Student * newStudent = (Student*)malloc(sizeof(Student));
		*newStudent = (Student) {tmpName,tmpRegNo,tmpDeptCode,tmpScoresTree};
		students.root = insertInTree(students,students.root,newStudent);
		
	} else printf("Invalid dept code\n");
}

void addDept() {
	
	char * tmpCode = readString("Code: ");
	
	TreeNode * node = findInTree(depts,depts.root,tmpCode);
	if (node != NULL) printf("Dept with given code already exists");
	else {
		
		char * tmpName = readString("Name: ");
		char * tmpHodName = readString("HOD's' Name: ");
	
		Dept * newDept = (Dept*)malloc(sizeof(Dept));
		*newDept = (Dept) {tmpName,tmpCode,tmpHodName};
		depts.root = insertInTree(depts,depts.root,newDept);
		
	}
	
}

void addCourse() {
	
	char * tmpCourseCode = readString("CourseID: ");
	toUpper(tmpCourseCode);
	
	TreeNode * node = findInTree(courses,courses.root,tmpCourseCode);
	if (node) printf("Course with that ID already exists");
	else {
	
		char * tmpCourseName = readString("CourseName: ");
		int tmpCredits = readInt("Credits: ");
		Course * course = (Course*)	 malloc(sizeof(Course));
		*course = (Course) {tmpCourseName,tmpCourseCode,tmpCredits};
		courses.root = insertInTree(courses,courses.root,course);
	}
}

void addGrades() {
	
	int regNo = readInt("StudentID: ");
	TreeNode * node = findInTree(students,students.root,intToString(regNo));
	
	if (node) {
		
		Tree * scores = &(((Student*)(node->data))->scores);
	
		while (1) {
			
			char * tmpCode = readString("CourseCode: ");
			node = findInTree(*scores,scores->root,tmpCode);
			
			if (node != NULL) {
				printf("That course already exists for that student");
				
			} else {
						

				TreeNode * tmp = findInTree(courses,courses.root,tmpCode);
				if (!tmp) printf("Invalid course ID\n");
				else {
					
					int tmpGrade = readInt("Grade: ");
					Score * score = (Score*) malloc(sizeof(Score));
					*score = (Score){tmpCode,tmpGrade};
					scores->root = insertInTree(*scores,scores->root,score);
				}
				
			}
			
			char * ch = readString("Add another course? (y/n)");
			if (ch[0] == 'n') break;
		}
		
	} else {
		printf("Invalid StudentID\n");
	}
} 

void viewAllStudents() {
	printTree(students);
}

void viewAllDepts() {
	printTree(depts);
}

void viewAllCourses() {
	printTree(courses);
}

void viewScoresOfStudent() {
	int id = readInt("StudentID: ");
	char * ids = intToString(id);
	TreeNode * node = findInTree(students,students.root,ids);
	if (!node) printf("Invalid student ID\n");
	else {
		Student *tmp = (Student*)node->data;
		printList(getTreeAsList(tmp->scores));
	}
}

void calculateGPA() {
	
	int regNo = readInt("Student RegNo: ");
	TreeNode * node = findInTree(students,students.root,intToString(regNo));
	
	if (node == NULL) printf("Invalid Student ID");
	else {
		
		double D = 0, N = 0;
		Tree scores = ((Student*)(node->data))->scores;
		List list = getTreeAsList(scores);
		ListNode * cur = list.head;
		
		while (cur) {
			
			Score tmpScore = *(Score*)cur->data;
			TreeNode * tmpNode = findInTree(courses,courses.root,tmpScore.courseCode);
			Course tmpCourse = *(Course*)(tmpNode->data);
			D += tmpCourse.credits;
			N += tmpScore.grade * tmpCourse.credits;
			cur = cur->next;
		}
		
		if (D != 0) printf("GPA: %.2f",N/D);
		else printf("No courses enrolled\n");
	}
}

List getStudentsInDept(char * deptCode) {
	
	List list = getTreeAsList(students);
	ListNode * cur = list.head;
	List result = newList(studentToString,studentEqual);
	while (cur) {
		Student * tmp = (Student*)cur->data;
		if (strcmp(tmp->deptCode,deptCode) == 0) appendToList(&result,cur->data);
		cur = cur->next;
	}
	return result;
}

void viewStudentsInDept() {
	
	char * tmpDeptCode = readString("DeptCode: ");
	List result = getStudentsInDept(tmpDeptCode);
	printList(result);
}

void removeStudent() {
	
	int tmpRegNo = readInt("RegNo: ");
	students.root = deleteFromTree(students,students.root,intToString(tmpRegNo));
}

void removeDept() {
	
	char * ch = readString("All students in specified dept will be deleted! Are you sure? (y/n)...");
	if (ch[0] == 'y') {
		char * tmpDeptCode = readString("DeptCode: ");
		List deptStudents = getStudentsInDept(tmpDeptCode);
		ListNode * cur = deptStudents.head;
		while (cur) {
			students.root = deleteFromTree(students,students.root,studentKey(cur->data));
			cur = cur->next;
		}
		depts.root = deleteFromTree(depts,depts.root,tmpDeptCode);
	}
	
}

void (*fns[])()   = { addStudent, addDept, addCourse, addGrades, viewAllStudents, viewAllDepts, viewAllCourses, viewScoresOfStudent, calculateGPA, viewStudentsInDept, 
				   removeStudent, removeDept };

int main() {
	
	students = newTree(studentToString,studentKey,studentEqual);
	depts = newTree(deptToString,deptKey,deptEqual);
	courses = newTree(courseToString,courseKey,courseEqual);
	
	while (1) {

		printf("\n");
		printf("================================\n");
		printf("Student record management system\n");
		printf("================================\n\n");
		printf("0 - add a new student record\n");
		printf("1 - add a new department\n");
		printf("2 - add a new course\n");
		printf("3 - add grade details for student\n");
		printf("4 - view all students\n");
		printf("5 - view all departments\n");
		printf("6 - view all courses\n");
		printf("7 - view scores of a student\n");
		printf("8 - calculate GPA of a student\n");
		printf("9 - view all students in a department\n");
		printf("10 - remove a student record\n");
		printf("11 - remove a department\n");
		printf("12 - exit\n" );
		printf("Enter your choice here...");
		int ch;
		scanf("%d",&ch);
		
		if (ch >= 0 && ch <= 12) {
			if (ch < 12) fns[ch]();
			else {
				"Thank you!!\n";
				break;
			}
		}
		else printf("Invalid choice :(\n");
		
	}
	
	return 0;
}
