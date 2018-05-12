// Author: Matt McGuiness

#include <stdio.h>
#include <math.h>

typedef struct {
    int hw[15];
    int lab[15];
    int midtermScore;
    int finalScore;
    char studentID[20];
    char firstName[20];
    char lastName[20];
} Student;

double calcHWAverage(int n, Student *student);
double calcLabAverage(int n, Student *student);
double Average(double lab, double hw, int midtermScore, int finalScore);

int main() {

    FILE *inFile;
    int status;

    inFile = fopen("grades_2017.csv","r");
    if (inFile==NULL) {                 // exit program if file not found
        printf("Error: grades_2017.csv not found!!\n");
        return 1;
    }
    Student array[3];
    int count = 0;

    char buffer[1000];
    fgets(buffer, 1000, inFile);
    while (1) {                         // read the lines of data

        status = fscanf(inFile,"%[^,],\"", &array[count].studentID);
        status = fscanf(inFile,"%[^,], ", &array[count].lastName);
        status = fscanf(inFile,"%[^\"]", &array[count].firstName);
        status = fscanf(inFile,"%[^,],", &array[count].hw[0]);
        for (int i = 0; i < 15; i++) {
             status = fscanf(inFile,"%[^,],", &array[count].hw[i]);
        }
        for (int i = 0; i < 15; i++) {
            status = fscanf(inFile,"%[^,],", &array[count].lab[i]);
        }
        status = fscanf(inFile,"%[^,],", &array[count].midtermScore);
        status = fscanf(inFile,"%[^\t]", &array[count].finalScore);
        
        if (status==EOF) break;
        printf("%s \n%s \n%s\n %d\n",array[count].studentID, array[count].lastName, array[count].firstName, array[count].hw[0]);
        // for (int i= 0; i < 15; i++) {
        //     printf("%d\n", array[count].hw[i]);
        // }
        count++;
    }

    fclose(inFile);

    for (int j = 0; j < 3; j++) {
        double hw = calcHWAverage(15, *array[i]);
        double lab = calcLabAverage(15, *array[i]);
        double average = (lab, hw, array[i].midtermScore, array[i].finalScore);

        printf("The average is: %lf \n", average);
    }
    

    return 0;
}

double calcHWAverage(int n, Student *student) {
    double average = 0.0;

    for (int i = 0; i < 15; i++) {
        average += (*student).hw[i];
    }

    return average / 15.0;
}

double calcLabAverage(int n, Student *student) {
    double average = 0.0;

    for (int i = 0; i < 15; i++) {
        average += (*student).lab[i];
    }

    return average / 15.0;
}

double Average(double lab, double hw, int midtermScore, int finalScore) {
    double grade = 0;
    grade = grade + lab * .4;
    grade = grade + hw * .15;
    grade = grade + midtermScore * .2;
    grade = grade + finalScore * .25;
    return grade;
}