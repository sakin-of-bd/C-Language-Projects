#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
//#define ll long long
//#define int long long
#define fi1(i,n) for(int i=0;i<n;i++)
#define fi2(i,n) for(int i=1;i<=n;i++)
#define fd1(i,n) for(int i=n-1;i>=0;i--)
#define fd2(i,n) for(int i=n;i>0;i--)

struct subject
{
    float mark[10];
};


struct student 
{
    char name[100];
    char id[100];
    struct subject sub;
    float total;
};


void create() 
{
    int n,p;

    printf("\nEnter the number of students: ");
    scanf("%d",&n);

    //printf("\n");
    
    printf("\nEnter the number of subjects: ");
    scanf("%d",&p);

    printf("\n\n");

    struct student person[n];
    FILE *st;

    st=fopen("mystudents.txt","w");

    if(st==NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    for (int i=0;i<n;i++) 
    {
        person[i].total=0;

        printf("Enter the name of student no. %d: ",i+1);
        getchar();
        fgets(person[i].name,sizeof(person[i].name),stdin);
        strtok(person[i].name,"\n"); 

        printf("Enter the student id of %s: ", person[i].name);
        fgets(person[i].id,sizeof(person[i].id),stdin);
        strtok(person[i].id,"\n"); 

        for(int j=0;j<p;j++) 
        {
            printf("Enter the mark of subject %d: ",j+1);
            scanf("%f",&person[i].sub.mark[j]);

            person[i].total+=person[i].sub.mark[j];
        }

        fwrite(&person[i],sizeof(struct student),1,st);

        printf("\n");
    }

    fclose(st);
}



int partition(struct student arr[],int low,int high)
{
    float pivot=arr[high].total;

    int i=low-1;

    for(int j=low;j<high;j++)
    {
        if(arr[j].total<pivot)
        {
            i++;

            struct student temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
    }

    struct student temp=arr[i+1];
    arr[i+1]=arr[high];
    arr[high]=temp;

    return i+1;
}


void quickSort(struct student arr[],int low,int high)
{
    if (low<high)
    {
        int pi = partition(arr,low,high);

        quickSort(arr,low,pi-1);
        quickSort(arr,pi+1,high);
    }
}

void display_in_ascending()
{
    FILE *st;

    struct student person[100];

    int count=0;

    st=fopen("mystudents.txt","r");

    if(st==NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    while(fread(&person[count],sizeof(struct student),1,st))
    {
        count++;
    }

    fclose(st);

    quickSort(person,0,count-1);

    printf("--------------------------------------------------------------\n");
    printf("%-30s%-20s%-10s\n","Name","ID","Total Mark");
    printf("--------------------------------------------------------------\n");

    for(int i=0;i<count;i++)
    {
        printf("%-30s%-20s%-10.2f\n",person[i].name,person[i].id,person[i].total);
    }
}


void display_in_descending()
{
    FILE *st;

    struct student person[100];

    int count=0;

    st=fopen("mystudents.txt","r");

    if(st==NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    while(fread(&person[count],sizeof(struct student),1,st))
    {
        count++;
    }
    
    fclose(st);

    quickSort(person,0,count-1);

    printf("--------------------------------------------------------------\n");
    printf("%-30s%-20s%-10s\n","Name","ID","Total Mark");
    printf("--------------------------------------------------------------\n");
    
    for(int i=count-1; i>=0; i--)
    {
        printf("%-30s%-20s%-10.2f\n",person[i].name,person[i].id,person[i].total);
    }
}


int main() 
{
    //system("COLOR DA");
    system("COLOR E5");
    printf("\n\t\t\t\t\t    Student Record Manager\n\n");

    printf("\n\t\t\t\t\t\tHello Everyone\n\n");

    int choose;

    do{
        printf("\n1. Create.");
        printf("\n2. Display in Ascending Order (Using Quick Sort Algorithm).");
        printf("\n3. Display in Descending Order (Using Quick Sort Algorithm).");
        printf("\n0. Exit.\n\n");

        printf("\nEnter Your Choice: ");
        scanf("%d",&choose);

        printf("\n");

        switch(choose) 
        {
            case 1:
                create();
                break;
            case 2:
                display_in_ascending();
                break;
            case 3:
                display_in_descending();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while(choose!=0);

    return 0;
}