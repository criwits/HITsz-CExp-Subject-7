/***************
** 函数名：SortByS()
** *comparing()：布尔函数指针
** 返回：空
** 作用：进行“分数”的选择排序。
***************/
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
            if ((*comparing)(dataSorted[j].fScore, dataSorted[i].fScore))
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

/***************
** 函数名：SortInAByID()
** 返回：空
** 作用：进行“学号”的选择排序。
***************/
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

/***************
** 函数名：SortInD()
** 返回：空
** 作用：对姓名逐字符按字典序排序。
***************/
void SortInD()
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

/***************
** 函数名：SearchByID()、Search()
** 返回：空
** 作用：二分法递归查找学号对应的分数。
***************/
float Search(DATABASE *data, int search, int start, int end, int *index)
{
    if (data[(start + end) / 2].iStudentID == search)
    {
        *index = (start + end) / 2;
        return data[(start + end) / 2].fScore;
    }
    if (start != end)
    {
        if (data[(start + end) / 2].iStudentID < search)
            Search(data, search, (start + end) / 2 + 1, end, index);
        if (data[(start + end) / 2].iStudentID > search)
            Search(data, search, start, (start + end) / 2, index);
    }
    else return -1.0;
}

void SearchByID()
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
    //先按成绩排一次序。
    for (i = 1; i < iStudentNumber; i++)
    {
        for (j = i + 1; j <= iStudentNumber; j++)
        {
            if (dataSorted[j].fScore > dataSorted[i].fScore)
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
        if (fabs(dataSorted[i].fScore - dataSorted[i - 1].fScore) < 1e-3)
        {
            dataSorted[i].iRanking = dataSorted[i - 1].iRanking;
        }
        else
        {
            dataSorted[i].iRanking = i;
        }
    }

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

    int iInputID, iIsScanf = 1;
    printf("[ HINT]Please enter the ID you want to search: ");
    do
    {
        fflush(stdin);
        if (!iIsScanf)
            printf("[ERROR]Not a proper input, please try again: ");
        iIsScanf = scanf("%d", &iInputID);
    } while (!iIsScanf);

    int iIndex = 0;
    float fSearched = 0;
    fSearched = Search(dataSorted, iInputID, 1, iStudentNumber, &iIndex);
    if (fSearched == -1)
    {
        printf("[ERROR]Can't find the student with id %d!\n\n", iInputID);
        return;
    }
    else
    {
        printf("[RESLT]The score of %d is %.2f, the ranking is %d.\n\n", iInputID, fSearched, dataSorted[iIndex].iRanking);
        return;
    }

}

/***************
** 函数名：SearchByName()
** 返回：空
** 作用：查找名字对应的分数。
***************/
void SearchByName()
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
    //先按成绩排一次序。
    for (i = 1; i < iStudentNumber; i++)
    {
        for (j = i + 1; j <= iStudentNumber; j++)
        {
            if (dataSorted[j].fScore > dataSorted[i].fScore)
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
        if (fabs(dataSorted[i].fScore - dataSorted[i - 1].fScore) < 1e-3)
        {
            dataSorted[i].iRanking = dataSorted[i - 1].iRanking;
        }
        else
        {
            dataSorted[i].iRanking = i;
        }
    }
    char cInputName[NMAX];
    printf("[ HINT]Please enter the name you want to search: ");
    fflush(stdin);
    gets(cInputName);
    //遍历现有的成绩表。
    for (i = 1; i <= iStudentNumber; i++)
    {
        if (!strcmp(cInputName, dataSorted[i].cName))
        {
            printf("[RESLT]The score of %s is %.2f, the ranking is %d.\n\n", dataSorted[i].cName, dataSorted[i].fScore, dataSorted[i].iRanking);
            return;
        }
    }
    //若未发现，则提示错误。
    printf("[ERROR]Can't find the student with the name %s!\n\n", cInputName);
    return;
}
/***************
** 函数名：StatisticAnalysis()
** 返回：空
** 作用：对成绩进行统计分析。
***************/
void StatisticAnalysis()
{
    if (!iIsRecorded)
    {
        printf("[ERROR]Please use (1) to input record first!\n\n");
        return;
    }
    //iAnalysis[] 中，0 代表优秀，4 代表不及格。
    int i, iAnalysis[5] = { 0 };
    //逐个判断成绩段。
    for (i = 1; i <= iStudentNumber; i++)
    {
        if (dataList[i].fScore >= 90)//优秀
            iAnalysis[0]++;
        else if (dataList[i].fScore >= 80)//良好
            iAnalysis[1]++;
        else if (dataList[i].fScore >= 70)//一般
            iAnalysis[2]++;
        else if (dataList[i].fScore >= 60)//及格
            iAnalysis[3]++;
        else//不及格
            iAnalysis[4]++;
    }
    printf(" Level        Number         Ratio(%%)\n");
    printf("=====================================\n");
    printf(" Excellent    %-14d %.1f\n", iAnalysis[0], iAnalysis[0] / (float)iStudentNumber * 100);
    printf(" Good         %-14d %.1f\n", iAnalysis[1], iAnalysis[1] / (float)iStudentNumber * 100);
    printf(" So-so        %-14d %.1f\n", iAnalysis[2], iAnalysis[2] / (float)iStudentNumber * 100);
    printf(" Only-passed  %-14d %.1f\n", iAnalysis[3], iAnalysis[3] / (float)iStudentNumber * 100);
    printf(" Failed       %-14d %.1f\n", iAnalysis[4], iAnalysis[4] / (float)iStudentNumber * 100);
    printf("\n[ INFO]Successfully listed data of all five levels.\n\n");
    return;
}


int main(void)
{
    int iChoice, iIsScanf = 1;
    do
    {
        printf("1. Input record\n"
               "2. List record\n"
               "3. Calculate total and average score of course\n"
               "4. Sort in descending order by score\n"
               "5. Sort in ascending order by score\n"
               "6. Sort in ascending order by Student ID\n"
               "7. Sort in dictionary order by name\n"
               "8. Search by Student ID\n"
               "9. Search by name\n"
               "10.Statistic analysis\n"
               "0. Exit\n"
               "[ HINT]Please enter your choice: ");
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
            CalculateTAndA();
            break;
        case 4:
            printf("\n");
            SortByS(Descending);
            break;
        case 5:
            printf("\n");
            SortByS(Ascending);
            break;
        case 6:
            printf("\n");
            SortInAByID();
            break;
        case 7:
            printf("\n");
            SortInD();
            break;
        case 8:
            printf("\n");
            SearchByID();
            break;
        case 9:
            printf("\n");
            SearchByName();
            break;
        case 10:
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
