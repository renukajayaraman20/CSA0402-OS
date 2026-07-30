#include <stdio.h>
#include <stdlib.h>

struct Employee
{
    int empId;
    char empName[50];
    float empSalary;
};

int main()
{
    FILE *filePtr;
    struct Employee emp;
    int choice;

    filePtr = fopen("employee.dat", "rb+");

    if(filePtr == NULL)
    {
        filePtr = fopen("employee.dat", "wb+");

        if(filePtr == NULL)
        {
            printf("Error creating file.\n");
            return 1;
        }
    }

    do
    {
        printf("\n===== Employee Database Menu =====\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee Details\n");
        printf("3. Update Employee Details\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:

                printf("Enter Employee ID: ");
                scanf("%d", &emp.empId);

                printf("Enter Employee Name: ");
                scanf("%s", emp.empName);

                printf("Enter Employee Salary: ");
                scanf("%f", &emp.empSalary);

                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                fwrite(&emp, sizeof(struct Employee), 1, filePtr);

                printf("Employee Record Added Successfully.\n");
                break;

            case 2:

                printf("Enter Employee ID to Display: ");
                scanf("%d", &emp.empId);

                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);

                if(fread(&emp, sizeof(struct Employee), 1, filePtr))
                {
                    printf("\nEmployee ID     : %d\n", emp.empId);
                    printf("Employee Name   : %s\n", emp.empName);
                    printf("Employee Salary : %.2f\n", emp.empSalary);
                }
                else
                {
                    printf("Employee Record Not Found.\n");
                }

                break;

            case 3:

                printf("Enter Employee ID to Update: ");
                scanf("%d", &emp.empId);

                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);

                if(fread(&emp, sizeof(struct Employee), 1, filePtr))
                {
                    printf("Enter New Employee Name: ");
                    scanf("%s", emp.empName);

                    printf("Enter New Employee Salary: ");
                    scanf("%f", &emp.empSalary);

                    fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                    fwrite(&emp, sizeof(struct Employee), 1, filePtr);

                    printf("Employee Record Updated Successfully.\n");
                }
                else
                {
                    printf("Employee Record Not Found.\n");
                }

                break;

            case 4:

                printf("Exiting Program...\n");
                break;

            default:

                printf("Invalid Choice.\n");
        }

    } while(choice != 4);

    fclose(filePtr);

    return 0;
}
