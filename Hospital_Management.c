#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
struct Data
{
    int CustomerNo;
    char Name[20];
    int Age;
    long long int Number;
    int MonthDoB;
    int DayDoB;
    int YearDoB;
    int MonthAPP;
    int DayAPP;
    int YearAPP;
    int VisitNo;
    int Serv;
    char Prescryption[200];
};
void clearscreen()
{
    #ifdef _WIN32
	system("cls");
    #elif __linux__
	system("clear");
    #elif __APPLE__	
	system("clear");
    #elif __unix__
	system("clear");
    #else
	return;
    #endif
}
void pausescreen()
{
    #ifdef _WIN32
        system("pause");
    #elif __linux__
        system("sleep 2");
    #elif __APPLE__	
        system("clear");
    #elif __unix__
        system("clear");
    #else
        return;
    #endif
}
void Loading_Screen()
{
    int i;


    for(i=0;i<10;i++)
    {
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("[--------------------------]%d%c",i*10,'%');
    sleep(1);
    clearscreen();
    }

}
void Cross()
{
    int i;
   printf("\n\t\t\t\t\t\t\t      ==================================\n");
    for(i=0;i<5;i++)
    {
      printf("\t\t\t\t\t\t\t     ||           **********           ||");
    printf("\n");
    }
    for(i=0;i<4;i++)
    {
      printf("\t\t\t\t\t\t\t     ||  ****************************  ||");
    printf("\n");
    }
    for(i=0;i<5;i++)
    {
      printf("\t\t\t\t\t\t\t     ||           **********           ||");
    printf("\n");
    }
printf("\t\t\t\t\t\t\t      ==================================\n");

}

void Swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
int Partition (int Elem[], int low, int high)
{
    int pivot = Elem[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (Elem[j] < pivot)
        {
            i++;
            Swap(&Elem[i], &Elem[j]);
        }
    }
    Swap(&Elem[i + 1], &Elem[high]);
    return (i + 1);
}
void QuickSort(int Elem[], int low, int high)
{
    if (low < high)
    {
        int pi = Partition(Elem, low, high);
        QuickSort(Elem, low, pi - 1);
        QuickSort(Elem, pi + 1, high);
    }
}

int NoMatch(int key,int index,int patients[25])
{
    int i,flag=0;
    for(i=0;i<index;i++)
    {
        if(patients[i]==key)
            flag++;
    }
    if(flag==0)
        return(1);
    else
        return(0);
}

void TakeAtRandom(int Elements,int patients[Elements])
{
    int key,i;
    srand(time(0));
    for(i=0;i<Elements;i++)
    {
        key=rand()%470;
        if(NoMatch(key,i,patients) || key ==0)
            patients[i]=key;
        else
            i--;
    }
}

void RandomData(int Elements,int RArray[Elements])
{
    int arr[Elements];
    struct Data dat;

    int temp;
    FILE *fp1, *fp2;
    fp1 = fopen("files\\MasterIndex.txt", "r+");
    fp2 = fopen("files\\Index.txt", "a");

    int m = 1,n=0;
    do{
        fscanf(fp1, "%d\t%s\t%d\t%d-%d-%d\t%lld\t%d\n", &dat.CustomerNo, dat.Name, &dat.Age, &dat.DayAPP, &dat.MonthAPP, &dat.YearAPP, &dat.Number, &dat.Serv);
        if (RArray[m] == dat.CustomerNo)
        {
            fprintf(fp2, "%d\t%s\t%d\t%d-%d-%d\t%lld\t%d\n", dat.CustomerNo, dat.Name, dat.Age, dat.DayAPP, dat.MonthAPP, dat.YearAPP, dat.Number, dat.Serv);
            m++;

        }
        n++;
    }while(m<Elements-1);
    fclose(fp1);
    fclose(fp2);
}

void CreateMatrix(int DataMatrix[25][25],int DoctorNo,int NoOfEachService,int Elements,int DArray[50][3])
{
    FILE *fp1;
    struct Data *data;
    data = malloc(sizeof(struct Data));
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < DoctorNo; j++)
        {
            DataMatrix[j][i] = 0;
        }
    }

    struct Data dat[25];
    //int DArray[50][3];

    fp1 = fopen("files\\Index.txt", "r+");
    int u = 0;
    for (int l = 0; l < Elements; l++)
    {
        fscanf(fp1, "%d\t%s\t%d\t%d-%d-%d\t%lld\t%d\n", &dat[u].CustomerNo, dat[u].Name, &dat[u].Age, &dat[u].DayAPP, &dat[u].MonthAPP, &dat[u].YearAPP, &dat[u].Number, &dat[u].Serv);
        u++;
    }
    int m = 0;
    for (int i = 0; i < 35; i++)
    {
        int oneval = 0, twoval = 0, threeval = 0, fourval = 0;
        for (int j = 0; j < DoctorNo; j++)
        {
            int tempi = i, tempj = j;
            if (dat[m].Serv == 1 && DataMatrix[tempj][tempi] == 0 && oneval < NoOfEachService && DataMatrix[tempj][24] < 12)
            {
                DArray[m][0]=dat[m].CustomerNo;
                DArray[m][1]=tempj;
                DArray[m][2]=tempi;

                DataMatrix[tempj][tempi] = dat[m].CustomerNo;
                oneval++;
                DataMatrix[tempj][24] += 1;
                m++;
            }
            tempi = i;
            tempj = j;
            if (dat[m].Serv == 2 && DataMatrix[tempj][tempi] == 0 && DataMatrix[tempj][tempi + 1] == 0 && twoval < NoOfEachService && DataMatrix[tempj][24] < 11)
            {
                DArray[m][0]=dat[m].CustomerNo;
                DArray[m][1]=tempj;
                DArray[m][2]=tempi;

                DataMatrix[tempj][tempi] = DataMatrix[tempj][tempi + 1] = dat[m].CustomerNo;
                twoval++;
                DataMatrix[tempj][24] += 2;
                m++;
            }
            tempi = i;
            tempj = j;
            if (dat[m].Serv == 3 && DataMatrix[tempj][tempi] == 0 && DataMatrix[tempj][tempi + 1] == 0 && DataMatrix[tempj][tempi + 2] == 0 && threeval < NoOfEachService && DataMatrix[tempj][24] < 10)
            {
                DArray[m][0]=dat[m].CustomerNo;
                DArray[m][1]=tempj;
                DArray[m][2]=tempi;

                DataMatrix[tempj][tempi] = DataMatrix[tempj][tempi + 1] = DataMatrix[tempj][tempi + 2] = dat[m].CustomerNo;
                threeval++;
                DataMatrix[tempj][24] += 3;
                m++;
            }
            tempi = i;
            tempj = j;
            if (dat[m].Serv == 4 && DataMatrix[tempj][tempi] == 0 && DataMatrix[tempj][tempi + 1] == 0 && DataMatrix[tempj][tempi + 2] == 0 && DataMatrix[tempj][tempi + 3] == 0 && fourval < NoOfEachService && DataMatrix[tempj][24] < 9)
            {
                DArray[m][0]=dat[m].CustomerNo;
                DArray[m][1]=tempj;
                DArray[m][2]=tempi;

                DataMatrix[tempj][tempi] = DataMatrix[tempj][tempi + 1] = DataMatrix[tempj][tempi + 2] = DataMatrix[tempj][tempi + 3] = dat[m].CustomerNo;
                fourval++;
                DataMatrix[tempj][24] += 4;
                m++;
            }
        }
    }
    fclose(fp1);
}

void PrintHospitalSchedule(int Data[25][25],int DoctorNo)
{
    printf("Matrix\nDoctors ");
    for (int x=1; x < DoctorNo+1; x++)
        printf("D%d\t", x);
    printf("\n");
    for (int i = 0; i < 24; i++)
    {
        printf("T%d-%d\t", i,i+1);
        for (int j = 0; j < DoctorNo; j++)
        {
            printf("%d\t", Data[j][i]);
        }
        printf("\n");
    }
    printf("Total\t");
    for (int j = 0; j < DoctorNo; j++)
    {
        printf("%d\t", Data[j][24]);
    }
    printf("\n");
}
void HospitalscheduleFile(int Data[25][25],int DoctorNo)
{
    FILE *fp1;
    fp1 = fopen("files\\Matrix.txt", "w");
    fprintf(fp1,"Matrix\nDoctors ");
    for (int x=1; x < DoctorNo+1; x++)
        fprintf(fp1,"D%d\t", x);
    fprintf(fp1,"\n");
    for (int i = 0; i < 25; i++)
    {
        fprintf(fp1,"T%d-\t", i);
        for (int j = 0; j < DoctorNo; j++)
        {
            fprintf(fp1,"%d\t", Data[j][i]);
        }
        fprintf(fp1,"\n");
    }
    fclose(fp1);
}
void PatientsData()
{
    FILE *fp1;
    char CustomerNo[3];
    char location1[50] = "files\\Patients\\";
    char location2[5] = ".txt";
    printf("Enter Customer no:-");
    scanf("%s",CustomerNo);
    strcat(location1,CustomerNo);
    strcat(location1,location2);
    fp1 = fopen(location1, "r");
    char c;
    if (fp1 == NULL)
    {
        printf("Patient appointment not today\n");
    }
    else{
        while((c=fgetc(fp1))!=EOF)
            putchar(c);
        printf("\n\n");
    }
    fclose(fp1);
}
void PatientRecords(int DArray[50][3],int Elements)
{
    FILE *fp1;
    struct Data dat;
    fp1 = fopen("files\\Index.txt", "r");

    char tempC[5];
    for (int l = 0; l < Elements; l++)
    {
        char sera[4]="No",serb[4]="No",serc[4]="No",serd[4]="No";
        char location1[50] = "files\\Patients\\";
        char location2[5] = ".txt";
        char tempC[5];
        fscanf(fp1, "%s\t%s\t%d\t%d-%d-%d\t%lld\t%d\n", tempC, dat.Name, &dat.Age, &dat.DayAPP, &dat.MonthAPP, &dat.YearAPP, &dat.Number, &dat.Serv);
        if(dat.Serv == 1)
            strcpy(sera,"yes");
        else if(dat.Serv == 2)
            strcpy(serb,"yes");
        else if(dat.Serv == 3)
            strcpy(serc,"yes");
        else
            strcpy(serd,"yes");
        FILE *fp2;
        strcat(location1,tempC);
        strcat(location1,location2);
        fp2 = fopen(location1,"w");

        fprintf(fp2, "Customer_No: %s\nName: %s\nAge: %d\nDate_of_Birth: %d/%d/%d\nNumber: %lld\nServices Selected: \nCough|Cold|Fever: %s\nENT: %s\nRegular: %s\nSurgery: %s\nDoctor_No: %d\nTime: %d-%d\nPrescription: ", tempC, dat.Name, dat.Age, dat.DayAPP, dat.MonthAPP, dat.YearAPP, dat.Number,sera,serb,serc,serd,DArray[l][1]+1,DArray[l][2],DArray[l][2]+dat.Serv);
        fclose(fp2);
    }
    fclose(fp1);
}
void PrintpatientsData(int Security)
{
    int choise;
    FILE *fp1,*fp2,*fp3,*fp4;
    char CustomerNo[3];
    char location1[50] = "files\\Patients\\";
    char locationE[70] = "files\\PatientsInfoEncrypted\\";
    char locationD[70] = "files\\PatientsInfoDecrypted\\";
    char location2[5] = ".txt";
    printf("Enter Customer no :-");
    scanf("%s",CustomerNo);
    strcat(location1,CustomerNo);
    strcat(location1,location2);
    strcat(locationE,CustomerNo);
    strcat(locationE,location2);
    strcat(locationD,CustomerNo);
    strcat(locationD,location2);
    printf("Encrypted or Decrypted file (0|1)");
    scanf("%d",&choise);
    if(choise==0)
    {
        fp1 = fopen(location1, "r");
        fp2 = fopen(locationE, "w");
        char c;
        if (fp1 == NULL)
        {
            printf("Patient appointment not today\n");
        }
        else{
            while((c=fgetc(fp1))!=EOF)
            {
                c=c+Security;
                fputc(c, fp2);
            }
            printf("File Encrypted\n");
        }
        fclose(fp1);
        fclose(fp2);
    }
    else if(choise==1)
    {
        fp2 = fopen(locationE, "r");
        fp3 = fopen(locationD, "w");
        char d;
        if (fp2 == NULL)
        {
            printf("Encrypted file not found\n");
        }
        else{
            while((d=fgetc(fp2))!=EOF)
            {
                d=d-Security;

                fputc(d, fp3);
            }
            printf("File Decrypted\n");
        }
        fclose(fp2);
        fclose(fp3);
    }
    else
        printf("Enter either 1 or 0");


}

void main()
{
    int ch, DoctorNo = 15 ,NoOfEachService = 2,DoctorSelect,Elements=25,Security=100;
    int DataMatrix[25][25],DArray[50][3];
    int patients[25];
    int FilePrint,result;
    char Password[20];

    printf("\n\n\n\n\n\n\t\t\t\t\t\t\t        SJM Multi speciality Hospital \n\t\t\t\t\t\t\t\t\t\t\t-since ages\n");
    Cross();
    pausescreen();
    clearscreen();
    Loading_Screen();
    while (1)
    {
    A:
        sleep(1);
        printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tEnter Case.val\n\t\t\t\t\t\t\t\t1->Upload data from File\n\t\t\t\t\t\t\t\t2->Print Hospital schedule\n\t\t\t\t\t\t\t\t3->Patient records\n\t\t\t\t\t\t\t\t4->Print patient records\n\t\t\t\t\t\t\t\t5->Doctors schedule\n\t\t\t\t\t\t\t\t6->Setting\n\t\t\t\t\t\t\t\t7->exit\n");

        scanf("%d", &ch);

        pausescreen();

        switch (ch)
        {
        case 1:
            //Appointment Setting module to be inserted here
            TakeAtRandom(Elements,patients);
            QuickSort(patients,-1, Elements);
            RandomData(Elements,patients);
            CreateMatrix(DataMatrix,DoctorNo,NoOfEachService,Elements,DArray);
            PatientRecords(DArray,Elements);
            Loading_Screen();
            printf("Data inserted\n");
            pausescreen();
            clearscreen();
            break;
        case 2:
            //Hospital schedule for the day
            PrintHospitalSchedule(DataMatrix,DoctorNo);
            printf("Do you want a printed file (1|0) :-");
            scanf("%d",&FilePrint);
            if(FilePrint == 1)
                HospitalscheduleFile(DataMatrix,DoctorNo);
            pausescreen();
            clearscreen();
            break;
        case 3:
            // Module to Display patient record to appointed doctor
            PatientsData();
            pausescreen();
            clearscreen();
            break;
        case 4:
            // Module to print patient record
            PrintpatientsData(Security);
            pausescreen();
            clearscreen();
            break;
        case 5:
            //Display Doctors schedule for the day
            printf("Enter Your Doctor NO :-");
            scanf("%d",&DoctorSelect);
            printf("Time\tPatient No\n");
            for(int i=0;i<24;i++)
                printf("%d-%d\t%d\n",i,i+1,DataMatrix[DoctorSelect-1][i]);
            printf("Total\t%d\n",DataMatrix[DoctorSelect-1][24]);
            pausescreen();
            clearscreen();
            break;
        case 6:
            //Setting
            printf("Enter password :-");
            scanf("%s",Password);
            result = strcmp(Password, "abcd");
            if(result ==0)
            {
                printf("Edit setting\nEnter no of Doctors :-");
                scanf("%d",&DoctorNo);
                printf("Enter no of Rooms for services :-");
                scanf("%d",&NoOfEachService);
                printf("Enter encryption value:-");
                scanf("%d",&Security);
            }
            else
                printf("Wrong password\n");

            pausescreen();
            clearscreen();
            break;
        case 7:
            exit(0);
        default:
            printf("Please Enter Valid options (1, 2, 3, 4, 5, 6)\n");
            pausescreen();
            clearscreen();
            goto A;
            break;
        }
    }
}
