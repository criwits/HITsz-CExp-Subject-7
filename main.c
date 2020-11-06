/****************************************
** 文件名：main.c
** 创建人：Hans Wan
** 日期：2020 Nov. 2
** 描述：实验七代码，学生成绩管理系统
** 版本：3.0
****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 30
#define NMAX 25
#define CMAX 6


typedef struct database
{
    char cName[NMAX];
    int iStudentID;
    float fScore[CMAX];
    int iRanking;
} DATABASE;


int iStudentNumber = MAX;
//学生人数。
int iIsRecorded = 0;
//是否已经录入。
int iSubjects = 1;
//学科数量。
DATABASE dataList[MAX + 1];
//创建学生成绩数据库。

//总分计算函数。
float GetTotal(float *array, int n)
{
    int i;
    float fTotal = 0.0;
    for (i = 0; i < n; i++)
        fTotal += array[i];
    return fTotal;
}

//平均分计算函数。
float GetAverage(float *array, int n)
{
    return GetTotal(array, n) / n;
}

/***************
** 函数名：Ascending()
** a：float
** b：float
** 返回：布尔值
** 作用：选择排序：升序
***************/
_Bool Ascending(float a, float b)
{
    return a < b;
}

/***************
** 函数名：Descending()
** a：float
** b：float
** 返回：布尔值
** 作用：选择排序：降序
***************/
_Bool Descending(float a, float b)
{
    return a > b;
}

/***************
** 函数名：RecursionSortName()
** *a : DATABASE
** *b : DATABASE
** step : int
** 返回：空
** 作用：比较两个 DATABASE 中名字的第 step 位，如果相同，递归比较第 step + 1 位。然后进行交换，将 ASCII 较小者放在 b。
***************/
void RecursionSortName(DATABASE *a, DATABASE *b, int step)
{
    if (a->cName[step] < b->cName[step])
    {
        DATABASE tmp;
        tmp = *a;
        *a = *b;
        *b = tmp;
        return;
    }
    if (a->cName[step] == b->cName[step])
        RecursionSortName(a, b, step + 1);
    return;
}

/***************
** 函数名：InputRecord()
** 返回：空
** 作用：录入学生信息
***************/
void InputRecord()
{
    //判断是否已经录入过。
    if (iIsRecorded)
    {
        //存储用户的选择。
        char cChoice;
        //提示用户已经录入过，是否重新录入。
        printf("[ WARN]There's already data in the memory. Wipe them and continue?\n");
        printf("[ HINT]Press y for yes and n for no: ");
        //获取用户选择。
        cChoice = getch();
        switch(cChoice)
        {
        case 'n':
        case 'N':
            printf("\n");
            return;
            break;
        default:
            break;
        }
    }
    printf("\n");
    //抹掉原有数据。
    memset(dataList, 0, sizeof(dataList));
    int iIsScanf = 1, i, j;
    printf("[ HINT]Please enter the number of students: ");
    //为避免非法输入，此处使用 iIsScanf 变量判断 scanf() 是否成功获取值。
    //如果未能成功录入，用 fflush() 清空缓冲区，然后提示重录。
    do
    {
        fflush(stdin);
        if (!iIsScanf || iStudentNumber > MAX || iStudentNumber <= 0)
            printf("[ERROR]Not a proper input, please try again: ");
        iIsScanf = scanf("%d", &iStudentNumber);
    } while (!iIsScanf || iStudentNumber > MAX || iStudentNumber <= 0);
    printf("[ HINT]Please enter the number of subjects: ");
    do
    {
        fflush(stdin);
        if (!iIsScanf || iSubjects > CMAX || iSubjects <= 0)
            printf("[ERROR]Not a proper input, please try again: ");
        iIsScanf = scanf("%d", &iSubjects);
    } while (!iIsScanf || iSubjects > CMAX || iSubjects <= 0);
    //逐个录入。
    for (i = 1; i <= iStudentNumber; i++)
    {
        printf("[ HINT]Please enter the ID of student %d: ", i);
        iIsScanf = 1;
        //避免非法输入，提升鲁棒性。
        do
        {
            fflush(stdin);
            if (!iIsScanf)
                printf("[ERROR]Not a proper input, please try again: ");
            iIsScanf = scanf("%d", &dataList[i].iStudentID);
        } while (!iIsScanf);
        printf("[ HINT]Please enter the name of the student %d: ", i);
        fflush(stdin);
        gets(dataList[i].cName);
        for (j = 0; j < iSubjects; j++)
        {
            printf("[ HINT]Please enter the score %d of the student %d: ", j + 1, i);
            do
            {
                fflush(stdin);
                if (!iIsScanf)
                    printf("[ERROR]Not a proper input, please try again: ");
                iIsScanf = scanf("%f", &dataList[i].fScore[j]);
            } while (!iIsScanf);
        }
    }
    printf("[ INFO]Successfully recorded data of %d students!\n\n", iStudentNumber);
    //将“已录入”flag设为 1。
    iIsRecorded = 1;
    return;
}

/***************
** 函数名：ListRecord()
** *m：DATABASE
** 返回：空
** 作用：打印 m 中的学生信息
***************/
void ListRecord(DATABASE *m)
{
    //检查是否已经录入。
    if (!iIsRecorded)
    {
        printf("[ERROR]Please use (1) to input record first!\n\n");
        return;
    }
    int i, j;
    printf(" StudentID             Name          ");
    for (i = 0; i < iSubjects; i++)
        printf("Score%2d   ", i + 1);
    printf("Total     Average    ");
    printf("\n");
    for (i = 0; i < iSubjects; i++)
        printf("=========");
    printf("============================================================\n");
    //逐个打印。
    for (i = 1; i <= iStudentNumber; i++)
    {
        printf(" %-22d%-14s", m[i].iStudentID, m[i].cName);
        for (j = 0; j < iSubjects; j++)
            printf("%-10.2f", m[i].fScore[j]);
        printf("%-10.2f%-10.2f", GetTotal(m[i].fScore, iSubjects), GetAverage(m[i].fScore, iSubjects));
        printf("\n");
    }
    printf("\n[ INFO]Successfully listed data of %d students!\n\n", iStudentNumber);
    return;
}
//计算单科目情况
void CalculateSingleCourseTAndA()
{
    if (!iIsRecorded)
    {
        printf("[ERROR]Please use (1) to input record first!\n\n");
        return;
    }
    int i, j;
    float fTotal = 0;
    printf(" Subject No.     Total        Average\n");
    printf("=======================================================\n");
    for (i = 0; i < iSubjects; i++)
    {
        fTotal = 0;
        for (j = 1; j <= iStudentNumber; j++)
            fTotal += dataList[j].fScore[i];
        printf(" %-16d%-13.2f%-13.2f\n", i + 1, fTotal, fTotal / iStudentNumber);
    }
    printf("\n[ INFO]Successfully listed data of %d subjects!\n", iSubjects);
    return;
}
//计算单个学生分数情况
void CalculateSingleStudentTAndA()
{
    if (!iIsRecorded)
    {
        printf("[ERROR]Please use (1) to input record first!\n\n");
        return;
    }
    int i;
    printf(" Student ID      Name           Total       Average\n");
    printf("===============================================================\n");
    for (i = 1; i <= iStudentNumber; i++)
    {
        printf(" %-16d%-15s%-12.2f%-12.2f\n", dataList[i].iStudentID, dataList[i].cName, GetTotal(dataList[i].fScore, iSubjects), GetAverage(dataList[i].fScore, iSubjects));
    }
    printf("\n[ INFO]Successfully listed data of %d students!\n", iStudentNumber);
    return;
}

void SortByS(_Bool (*comparing)(float a, float b))
{
    if (!iIsRecorded)
    {
        printf("[ERROR]Please use (1) to input record first!\n\n");
        return;
    }
    int i, j;
    //避免破坏源数据库，建立新的排序临时用数据库。
    DATABASE dataTemp;
    DATABASE dataSorted[iStudentNumber + 1];
    //将现有数据库复制到临时数据库。
    memcpy(dataSorted, dataList, sizeof(dataSorted));
    //选择排序。
    for (i = 1; i < iStudentNumber; i++)
    {
        for (j = i + 1; j <= iStudentNumber; j++)
        {
            if ((*comparing)(GetTotal(dataSorted[j].fScore, iSubjects), GetTotal(dataSorted[i].fScore, iSubjects)))
            {
                dataTemp = dataSorted[j];
                dataSorted[j] = dataSorted[i];
                dataSorted[i] = dataTemp;
            }
        }
    }
    //打印排序后的临时数据库。
    ListRecord(dataSorted);
    return;
}
//按 ID 排序。
void SortInAByID()
{
    if (!iIsRecorded)
    {
        printf("[ERROR]Please use (1) to input record first!\n\n");
        return;
    }
    int i, j;
    DATABASE dataTemp;
    DATABASE dataSorted[iStudentNumber + 1];
    memcpy(dataSorted, dataList, sizeof(dataSorted));
    for (i = 1; i < iStudentNumber; i++)
    {
        for (j = i + 1; j <= iStudentNumber; j++)
        {
            if (dataSorted[j].iStudentID < dataSorted[i].iStudentID)
            {
                dataTemp = dataSorted[j];
                dataSorted[j] = dataSorted[i];
                dataSorted[i] = dataTemp;
            }
        }
    }
    ListRecord(dataSorted);
    return;
}
//按姓名排序。
void SortByName()
{
    if (!iIsRecorded)
    {
        printf("[ERROR]Please use (1) to input record first!\n\n");
        return;
    }
    int i, j;
    DATABASE dataSorted[iStudentNumber + 1];
    memcpy(dataSorted, dataList, sizeof(dataSorted));
    for (i = 1; i < iStudentNumber; i++)
    {
        for (j = i + 1; j <= iStudentNumber; j++)
        {
            RecursionSortName(&dataSorted[j], &dataSorted[i], 0);
        }
    }
    ListRecord(dataSorted);
    return;
}


//按学号查找。
void SearchByID()
{
    if (!iIsRecorded)
    {
        printf("[ERROR]Please use (1) to input record first!\n\n");
        return;
    }
    int iInputID, iIsScanf = 1;
    printf("[ HINT]Enter the ID you want to search: ");
    do
    {
        fflush(stdin);
        if (!iIsScanf)
            printf("[ERROR]Not a proper input, please try again: ");
        iIsScanf = scanf("%d", &iInputID);
    } while (!iIsScanf);
    //排序以得到排名值。
    int i, j;
    DATABASE dataTemp;
    DATABASE dataSorted[iStudentNumber + 1];
    memcpy(dataSorted, dataList, sizeof(dataSorted));
    for (i = 1; i < iStudentNumber; i++)
    {
        for (j = i + 1; j <= iStudentNumber; j++)
        {
            if (GetTotal(dataSorted[j].fScore, iSubjects) > GetTotal(dataSorted[i].fScore, iSubjects))
            {
                dataTemp = dataSorted[j];
                dataSorted[j] = dataSorted[i];
                dataSorted[i] = dataTemp;
            }
        }
    }
    /** 获取排名值：如果分数跟前一个人一样，那么 TA 的排名就和前一个人一样。 **/
    dataSorted[1].iRanking = 1;
    for (i = 2; i <= iStudentNumber; i++)
    {
        if (fabs(GetTotal(dataSorted[i].fScore, iSubjects) - GetTotal(dataSorted[i - 1].fScore, iSubjects)) < 1e-3)
        {
            dataSorted[i].iRanking = dataSorted[i - 1].iRanking;
        }
        else
        {
            dataSorted[i].iRanking = i;
        }
    }

    for (i = 1; i <= iStudentNumber; ++i)
    {
        if (iInputID == dataSorted[i].iStudentID)
        {
            printf("[ INFO]Here is the result: \n");
            printf(" StudentID             Name          ");
            for (j = 0; j < iSubjects; j++)
                printf("Score%2d   ", j + 1);
            printf("Total     Average    Ranking");
            printf("\n");
            for (j = 0; j < iSubjects; j++)
                printf("=========");
            printf("======================================================================\n");
            printf(" %-22d%-14s", dataSorted[i].iStudentID, dataSorted[i].cName);
            for (j = 0; j < iSubjects; j++)
                printf("%-10.2f", dataSorted[i].fScore[j]);
            printf("%-10.2f%-11.2f%-3d", GetTotal(dataSorted[i].fScore, iSubjects), GetAverage(dataSorted[i].fScore, iSubjects), dataSorted[i].iRanking);
            printf("\n");
            printf("\n[ INFO]Successfully listed the data of one student.\n\n");
            return;
        }
    }
    printf("[ERROR]Can't find the student with given ID!\n\n");
    return;
}
//按名字查找。
void SearchByName()
{
    if (!iIsRecorded)
    {
        printf("[ERROR]Please use (1) to input record first!\n\n");
        return;
    }
    char cInputName[NMAX];
    printf("[ HINT]Enter the name you want to search: ");
    fflush(stdin);
    gets(cInputName);
    int i, j;
    DATABASE dataTemp;
    DATABASE dataSorted[iStudentNumber + 1];
    memcpy(dataSorted, dataList, sizeof(dataSorted));
    for (i = 1; i < iStudentNumber; i++)
    {
        for (j = i + 1; j <= iStudentNumber; j++)
        {
            if (GetTotal(dataSorted[j].fScore, iSubjects) > GetTotal(dataSorted[i].fScore, iSubjects))
            {
                dataTemp = dataSorted[j];
                dataSorted[j] = dataSorted[i];
                dataSorted[i] = dataTemp;
            }
        }
    }
    dataSorted[1].iRanking = 1;
    for (i = 2; i <= iStudentNumber; i++)
    {
        if (fabs(GetTotal(dataSorted[i].fScore, iSubjects) - GetTotal(dataSorted[i - 1].fScore, iSubjects)) < 1e-3)
        {
            dataSorted[i].iRanking = dataSorted[i - 1].iRanking;
        }
        else
        {
            dataSorted[i].iRanking = i;
        }
    }

    for (i = 1; i <= iStudentNumber; ++i)
    {
        if (!strcmp(cInputName, dataSorted[i].cName))
        {
            printf("[ INFO]Here is the result: \n");
            printf(" StudentID             Name          ");
            for (j = 0; j < iSubjects; j++)
                printf("Score%2d   ", j + 1);
            printf("Total     Average    Ranking");
            printf("\n");
            for (j = 0; j < iSubjects; j++)
                printf("=========");
            printf("======================================================================\n");
            printf(" %-22d%-14s", dataSorted[i].iStudentID, dataSorted[i].cName);
            for (j = 0; j < iSubjects; j++)
                printf("%-10.2f", dataSorted[i].fScore[j]);
            printf("%-10.2f%-11.2f%-3d", GetTotal(dataSorted[i].fScore, iSubjects), GetAverage(dataSorted[i].fScore, iSubjects), dataSorted[i].iRanking);
            printf("\n");
            printf("\n[ INFO]Successfully listed the data of one student.\n\n");
            return;
        }
    }
    printf("[ERROR]Can't find the student with given name.\n\n");
    return;
}
//统计分析。
void StatisticAnalysis()
{
    if (!iIsRecorded)
    {
        printf("[ERROR]Please use (1) to input record first!\n\n");
        return;
    }
    //0 — 5 分别指 优秀、良好、一般、及格、不及格。
    int iSubjectNum[iSubjects][5];
    int i, j;
    memset(iSubjectNum, 0, sizeof(iSubjectNum));
    for (i = 1; i <= iStudentNumber; ++i)
    {
        for (j = 0; j < iSubjects; j++)
        {
            if (dataList[i].fScore[j] >= 90)
                iSubjectNum[j][0]++;
            else if (dataList[i].fScore[j] >= 80)
                iSubjectNum[j][1]++;
            else if (dataList[i].fScore[j] >= 70)
                iSubjectNum[j][2]++;
            else if (dataList[i].fScore[j] >= 60)
                iSubjectNum[j][3]++;
            else
                iSubjectNum[j][4]++;
        }
    }
    printf(" Subject No.      Exce(>=90)        Good[80,90)       So-so[70,80)      Passed[60,70)     Failed(<60)\n");
    printf("================================================================================================================\n");
    for (i = 0; i < iSubjects; i++)
    {
        printf(" %-17d", i + 1);
        for (j = 0; j <= 4; j++)
            printf("%-10d%5.2f%% |", iSubjectNum[i][j], iSubjectNum[i][j] * 100 / (float)iStudentNumber);
        printf("\n");
    }
    printf("\n[ INFO]Successfully listed data of all subjects!\n\n");
    return;
}

int main(void)
{

    int iChoice, iIsScanf = 1;
    do
    {
        printf("1. Input record\n"
               "2. List record\n"
               "3. Calculate total and average score of every course\n"
               "4. Calculate total and average score of every student\n"
               "5. Sort in descending order by total score of every student\n"
               "6. Sort in ascending order by total score of every student\n"
               "7. Sort in ascending order by StudentID\n"
               "8. Sort in dictionary order by name\n"
               "9. Search by StudentID\n"
               "10.Search by name\n"
               "11.Statistic analysis for every course\n"
               "0. Exit\n");
        printf("[ HINT]Please enter your choice: ");
        do
        {
            fflush(stdin);
            if (!iIsScanf)
                printf("[ERROR]Not a proper input, please try again: ");
            iIsScanf = scanf("%d", &iChoice);
        } while (!iIsScanf);
        switch (iChoice)
        {
        case 1:
            printf("\n");
            InputRecord();
            break;
        case 2:
            printf("\n");
            ListRecord(dataList);
            break;
        case 3:
            printf("\n");
            CalculateSingleCourseTAndA();
            break;
        case 4:
            printf("\n");
            CalculateSingleStudentTAndA();
            break;
        case 5:
            printf("\n");
            SortByS(Descending);
            break;
        case 6:
            printf("\n");
            SortByS(Ascending);
            break;
        case 7:
            printf("\n");
            SortInAByID();
            break;
        case 8:
            printf("\n");
            SortByName();
            break;
        case 9:
            printf("\n");
            SearchByID();
            break;
        case 10:
            printf("\n");
            SearchByName();
            break;
        case 11:
            printf("\n");
            StatisticAnalysis();
            break;
        case 0:
            return 0;
            break;
        default:
            printf("\n[ERROR]Not a proper choice!\n\n");
            break;
        }
    } while (1);
    return 0;
}
