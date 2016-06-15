#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define LenOfID 10
#define LenOfName 20
#define MaxCntOfStu 100
#define LongLen 1000
#define FormartOutput "%8s%8s%4s%8s%8s%8s%8s%8s%8s%8s\n", "ID", "NAME", "SEX", "SCORE1", "SCORE2", "SCORE3", "SCORE4", "SCORE5", "total", "avg"

typedef struct student {
    char ID[LenOfID];
    char name[LenOfName];
    char sex;
    float score[5];
    float total;
    float avg;
}STU;

void load(STU stu[], int *nPtr);
void save(STU stu[], int n);

void add(STU stu[], int *nPtr);
int inputRecord(STU stu[], int i);
int inputScore(STU stu[], int i);
int stringInput(char *t, int lens, char *notice);

void sort(STU stu[], int n);
void find(STU stu[], int n);
void edit(STU stu[], int n);
void del(STU stu[], int *nPtr);

void printMenu();
void output(STU stu[], int n);
void printRecord(STU *sPtr);

int main()
{
    STU stu[MaxCntOfStu];

    int n;
    int keyInput = 0;

    load(stu, &n);

    while (1)
    {
        printMenu();
        scanf("%d", &keyInput);
        switch (keyInput)
        {
        case 1:
            add(stu, &n);
            break;
        case 2:
            edit(stu, n);
            break;
        case 3:
            sort(stu, n);
            break;
        case 4:
            find(stu, n);
            break;
        case 5:
            del(stu, &n);
            break;
        case 6:
            output(stu, n);
            break;
        case 7:
            return 0;
        default:
            printf("please enter a number 0 ~ 7\n");
            break;
        }
    }
}

void printMenu()
{
    system("cls"); //调用DOS命令清屏

    printf("                        Welcom\n");
    printf("                                                                 \n");
    printf("    ************************* main menu *************************\n");
    printf("    *                                                           *\n");
    printf("    *           1 add contact            2 print contants       *\n");
    printf("    *                                                           *\n");
    printf("    *           3 delete contant         4 search contant       *\n");
    printf("    *                                                           *\n");
    printf("    *           5 edit contant           6 insert contant       *\n");
    printf("    *                                                           *\n");
    printf("    *           7 sort contant           8 save                 *\n");
    printf("    *                                                           *\n");
    printf("    *           0 exit                                          *\n");
    printf("    *                                                           *\n");
    printf("    *************************************************************\n");
}

void load(STU stu[], int *nPtr)
{
    FILE *fp;
    int i;

    if ((fp = fopen("d:\\student.dat", "r")) == NULL)
    {
        *nPtr = 0;
        return;
    }
    for (i = 0; fread(&stu[i], sizeof(STU), 1, fp) != 0; i++)

        *nPtr = i;
    fclose(fp);
}

void save(STU stu[], int n)
{
    FILE *fp;
    if ((fp = fopen("d:\\student.dat", "w")) == NULL)
    {
        printf("打开文件失败\n");
        exit(0);
    }

    fwrite(stu, n * sizeof(stu[0]), 1, fp);
    fclose(fp);
}

void output(STU stu[], int n)
{
    int i;

    printf(FormartOutput);
    for (i = 0; i < n; i++)
        printRecord(&stu[i]);

    system("pause");
}

void printRecord(STU * sPtr)
{
    printf("%8s%8s%4c", sPtr->ID, sPtr->name, sPtr->sex);

    for (int i = 0; i < 5; i++)
    {
        printf("%8.2f", sPtr->score[i]);
    }

    printf("%8.2f%8.2f", sPtr->total, sPtr->avg);
    printf("\n");
}

void add(STU stu[], int *nPtr)
{
    int i = 0;
    char sel = 'y';

    while (sel == 'y')
    {
        if (inputRecord(stu, (*nPtr)++) && inputScore(stu, (*nPtr)++))
        {
            printf("是否继续添加(yes--y,no--others)\n>>>");
            scanf(" %c", &sel);
        }
        else
        {
            sel = 0;
            break;
        }
    }

    save(stu, *nPtr);
}

int inputRecord(STU stu[], int i)
{
    printf("请输入第%d个学生信息\n", i + 1);

    if (stringInput(stu[i].ID, LenOfID, "请输入学生学号(学号小于9位数字组成)"))
        if (stringInput(stu[i].name, LenOfName, "请输入姓名(姓名小于20位字符组成)"))
            if (stringInput(stu[i].sex, 10, "请输入性别 m/f"))
                return 1;
    return 0;
}
int inputScore(STU stu[], int i)
{
    printf("请输入五门课成绩(0~100)\n");
    stu[i].total = 0;

    for (int j = 0; j < 5; j++)
    {
        scanf("%lf", &stu[i].total);
        stu[i].total += stu[i].total;
    }

    stu[i].avg = stu[i].total / 5;
    return 1;
}

int stringInput(char *t, int lens, char *notice) //safe input a string 
{
    char str[LongLen];
    puts(notice);
    printf(">>>");

    scanf(" ");
    gets(str);

    printf("\n");
    if (lens > strlen(str))
    {
        strcpy(t, str);
        return 1;
    }

    else
    {
        printf("Input Error, return main menu\n");
        return 0;
    }
}

void edit(STU stu[], int n)
{
    char sel;
    char str[20];

    stringInput(str, LenOfID, "input ID");

    int index = findByNum(stu, n, str);

    if (index < 0)
    {
        printf("该学生信息不存在\n");
        return;
    }

    printf("a record founded：\n");
    printRecord(&stu[index]);

    printf("是否修改姓名？请输入 y or n:\n>>>");
    scanf(" %c", &sel);

    if (sel == 'y')
    {
        printf("请输入姓名:\n>>>");
        scanf("%s", stu[index].name);
    }

    printf("是否修改性别？请输入 y or n:\n>>>");
    scanf(" %c", &sel);
    if (sel == 'y')
    {
        printf("请输入 f or m:\n>>>");
        scanf(" %c", &stu[index].sex);
    }

    printf("是否修改成绩？input y or n:\n>>>");
    scanf(" %c", &sel);
    if (sel == 'y')
    {
        stu[index].total = 0;

        printf("输入5门学科成绩：\n>>>");
        for (int i = 0; i < 5; i++)
        {
            scanf("%lf", &stu[index].total);
            stu[index].total = stu[index].total + stu[index].total;
        }

        stu[index].avg = stu[index].total / 5;
    }

    save(stu, n);
}

int findByNum(STU stu[], int n, char *str)
{
    int i;

    for (i = 0; i < n; i++)
        if (strcmp(stu[i].ID, str) == 0)
            return i;
    return -1;
}

void sort(STU stu[], int n)
{
    int select, i, j;
    int(*cmp)(STU a, STU b);

    int ScoreAsc(STU a, STU b);
    int ScoreDes(STU a, STU b);
    int NameAsc(STU a, STU b);

    printf("1 按总分升序排列\n");
    printf("2 按总分降序排列\n");
    printf("3 按姓名排列\n");

    switch (select)
    {
    case 1:
        cmp = ScoreAsc;
        break;
    case 2:
        cmp = ScoreDes;
        break;
    case 3:
        cmp = NameAsc;
        break;
    default:
        return;
    }

    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if ((*cmp)(stu[i], stu[j]) > 0)
            {
                STU temp;
                temp = stu[i];
                stu[i] = stu[j];
                stu[j] = temp;
            }

    output(stu, n);
}

int ScoreAsc(STU a, STU b)
{
    return a.total > b.total ? 1 : -1;
}

int ScoreDes(STU a, STU b)
{
    return a.total < b.total ? 1 : -1;
}

int NameAsc(STU a, STU b)
{
    return strcmp(a.name, b.name);
}


void del(STU stu[], int *nPtr)
{
    int i, index;
    char str[20];

    printf("请输入学号:\n");
    scanf("%s", str);
    index = findByNum(stu, *nPtr, str);

    if (index < 0)
    {
        printf("\n 该学生信息不存在\n");
        return;
    }

    for (i = index; i < *nPtr - 1; i++)
        stu[i] = stu[i + 1];
    (*nPtr)--;

    printf("\n删除成功\n");
    save(stu, *nPtr);
}

void find(STU stu[], int n)
{
    int index;
    char str[20];

    printf("请输入学号：\n");
    scanf("%s", str);
    index = findByNum(stu, n, str);

    if (index >= 0)
        printRecord(&stu[index]);
    else
        printf("该学生信息不存在\n");

    system("pause");
}

