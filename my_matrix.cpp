#include <iostream>
#include <math.h>
#include <my_matrix.hpp>
#include <my_struct.hpp>
#include <QDebug>
#include <QVector>
using namespace std;


/**************Функция вывода матрицы**************************/
void PrintMatr(double **mas, int m) {
    int i, j; // переменные - счетчики
    for (i = 0; i<m; i++) {
        for (j = 0; j<m; j++)
            cout << mas[i][j] << " "; // вывод одной строки матрицы
        cout << endl;  // переход на новую строку
    }
}

/********************функция вывода вектора****************************/
void PrintVect(double *mas,int m) {
    int i; // переменная счетчик

    for (i = 0; i<m; i++) {
        cout << mas[i] << " ";// вывод одного элемента с пробелами
    }
    cout << endl;//переход на новую строку
}


/***********Получение матрицы без i-й строки и j-го столбца*************/
void GetMatr(double **mas, double **p, int i, int j, int m) {
    int ki, kj, di, dj; // переменные-счетчики
    di = 0;
    for (ki = 0; ki<(m - 1); ki++) { // проверка индекса строки
        if (ki == i) di = 1;
        dj = 0;
        for (kj = 0; kj<(m -1); kj++) { // проверка индекса столбца
            if (kj == j) dj = 1;
            p[ki][kj] = mas[ki + di][kj + dj];//выборка одного элемента алгебраического дополнения
        }}}


/**************** Рекурсивное вычисление определителя******************/
double Determinant(double **mas, int m) {
    int i, n; // переменные-счетчики
    double d, k; // вспомогательные переменные
    double **p;  //переменная содержащая алгебраическое дополнение
    p = new double*[m]; // выделение памяти под алгебраическое дополнение
    for (i = 0; i<m; i++)
        p[i] = new double[m]; //вспомогательный массив в котором хранится алгебраическое дополнение
    d = 0;
    k = 1; //(-1) в степени i
    n = m - 1;
    if (m<1) {;
        return(0); // при нулевом размере матрицы функция будет выдавать 0
    };
    if (m == 1) {
        d = mas[0][0];// определитель матрицы 1*1
        return(d);}
    if (m == 2) {
        d = mas[0][0] * mas[1][1] - (mas[1][0] * mas[0][1]); //определитель матрицы 2*2
        return(d);}
    if (m>2) {   //определитель матрицы 3*3 либо больше
        for (i = 0; i<m; i++) {
            GetMatr(mas, p, i, 0, m);
            d = d + k * mas[i][0] * Determinant(p, n); //рекурсивный вызов функции
            k = -k; //смена знака алгебраических дополнений
        }}
    return(d);}

/*****************функция расчета обратной матрицы***************************/
matrix_correct inverse(double** a, int m)
{
    matrix_correct res;
    double k=1; // переменная для смены знака
    double d; // переменная для хранения определителя
    int i, j; // счетчики для перебора элементов
    res.mas = new double* [m]; // выделяю памяьб для выходного массива
    for (i = 0; i < m; i++)
    {   res.mas[i] = new double[m]; // создание выходного массива
    }
    double **p; //объявляю маттрицу алгебраического дополнения
    p = new double*[m];// выделаю память для алгебраического дополнения
    for (i = 0; i<m; i++)
        p[i] = new double[m]; //создание вспомогательного массива для расчета алгебраических дополнений

    res.correct=1; //по умолчанию призннак корректности расчета выставляется 1 (расчет корректен)

    d = Determinant(a,m); // расчет определителя

    if (d*d<0.0000001) /* сравниваю значения определителя, если оно близко к нулю то выдаю признак того что расчет недостоверен*/
    {
        res.correct=0; // если определитель близок к нулю то признак корректности расчета ставим 0 (расчету нельзя доверять)

    };
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {
            GetMatr(a, p, j, i, m); //выбираю алгебраическое дополнение
            res.mas[i][j] = Determinant(p,m-1)/d*k; //расчет одного элемента обратной матрицы
            k=-k; //смена знака по элементам
        }
    }

    return res; //возрат вычисленных данных
}

/**************функция транспонирования квадратной матрицы*********************/
double** transpon(double** a, int m)
{
    double** res; // объявляю переменную для выходного массива
    int i, j;     // счетчики для перебора маассива
    res = new double* [m]; //выделаю память для выходного массива
    for (i = 0; i < m; i++)
    {
        res[i] = new double[m]; //создание выходного массива
    }
    for (i = 0; i < m; i++)
    { for (j = 0; j < m; j++)
        { res[i][j] = a[j][i]; //поворот одного элемента
        }}
    return res; //вывод результата
}

/********* умножение матрицы на вектор (по правилам умножения матриц)***********/
double* MV(double **A, double *b, int m)
{

    double* v; // объявляю вектор для выходных значений
    v = new double [m]; // выделение памяти для выходных значений
    for (int i = 0; i < m; i++)
    {
        v[i] = 0; //обнуление суммы для одного элемента
        for (int j = 0; j < m; j++)
            v[i] += A[i][j] * b[j];//расчет одного элемента
    }
    return v;
}


/********* решение слау матричным методом ***********/
double* slau_solver(double **A, double *b, int m)
{

    double* v; // объявляю вектор для выходных значений
    matrix_correct mas2;
    v = new double [m]; // выделение памяти для выходных значений

    mas2 = inverse(A,m);

    for (int i = 0; i < m; i++)
    {
        v[i] = 0; //обнуление суммы для одного элемента
        for (int j = 0; j < m; j++)
            v[i] += mas2.mas[i][j] * b[j];//расчет одного элемента
    }
    return v;
}

/***********Умножение двух квадратных матриц******************/
double** prodMatr(double** a, double** b, int m)
{
    double** res; // объявление выходного массива
    int i, j;
    res = new double* [m]; // выделение памяти для выходного массива
    for (i = 0; i < m; i++)
    {  res[i] = new double[m];//создание выходной матрицы
    }
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {   res[i][j] = 0; //обнуление суммы для одного элемента
            for (int k = 0; k < m; k++)
                res[i][j] += a[i][k] * b[k][j]; //расчет одного элемента матрицы
        }}
    return res; //вывод результата
}

/*********функция смены местами двух строк матрицы*************/
void rows_swap(double **mas, int k, int e, int m)
{
    double temp;               // временная переменная
    int i;                     // счетчик
    for (i = 0; i < m; i++)    // перебор столбцов
    {
        temp = mas[k][i];      // сохранение строки во временную переменную
        mas[k][i] = mas[e][i]; // смена местами двух строк
        mas[e][i] = temp;
    }
    return; //вывод результата
}

/*********функция смены местами двух столбцов матрицы*************/
void colls_swap(double **mas, int k, int e, int m)
{
    double temp;               // временная переменная
    int i;                     // счетчик
    for (i = 0; i < m; i++)    //перебор строк
    {
        temp = mas[k][i];      //временная переменная
        mas[i][k] = mas[e][i]; // смена местами строк
        mas[i][e] = temp;
    }
    return; //вывод результата
}



/********определитель методом Гаусса (с перестановкой строк)******************************/
double gauss_det(double **mas, int n) // определитель методом Гаусса
{
    int i,j,k,r;        // переменные счетчики
    double c,M,max;     // вспомогательные переменные для расчета
    double     det=1;   // начальное значение определителя (на него будут умножаться значения диагонали)
    double       **a;   // матрица к которой будут применяться преобразования Гаусса
    a=new double *[n];  // выделение памяти под временную матрицу
    for(i=0;i<n;i++)
    {
        a[i]=new double[n];
    }

    for(i=0;i<n;i++)    // заполнение временной матрицы
    {
        for(j=0;j<n;j++)
        {
            a[i][j]=mas[i][j];
        }
    }
    for(k=0;k<n;k++) // преобразование матрицы к верхнетреугольной
    {
        max=fabs(a[k][k]); // начальное значение для поиска
        r=k;
        for(i=k+1;i<n;i++)
        {
            if (fabs(a[i][k])>max)
            {
                max=fabs(a[i][k]); // поиск максимального элемента
                r=i;
            }
        }
        if (r!=k)
        {
            det=-det; // смена знака определителя при перестановке строк
        }
        for(j=0;j<n;j++) // перестановка строк
        {
            c=a[k][j];
            a[k][j]=a[r][j];
            a[r][j]=c;
        }
        for(i=k+1;i<n;i++)
        {
            for(M=a[i][k]/a[k][k],j=k;j<n;j++) // перебор строк
            {
                a[i][j]-=M*a[k][j]; // домножение сроки на число
            }
        }
    }
    for(i=0;i<n;i++)
        det*=a[i][i]; // определитель как произведение элементов главной диагонали
    return det;
}

/********расчет определителя модифицированным методом Гаусса**************/
double gauss_det_zero(double **mas, int n)
{
    int i,j,k;               // переменные счетчики
    double M;                // коэффициент на который домножаютс элементы для обнуления
    double     det=1;        // начальное значения определителя
    double eps  = 0.0000001; // погрешность расчета, если диагональный элемент меньше eps то данный элемент считаем нулём
    double       **a;        // вспомогательный массив для хранения матрицы
    a=new double *[n];       // выделение памяти под вспомогательный массив
    for(i=0;i<n;i++)
    {
        a[i]=new double[n];
    }

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            a[i][j]=mas[i][j];  // заполнение вспомогательной матрицы
        }
    }
    for(k=0;k<n;k++) // преобразование матрицы к верхнетреугольной
    {

        for(i=k+1;i<n;i++)
        {
            for(M=a[i][k]/a[k][k],j=k;j<n;j++) // расчет значения коэффициента для обнуления элементов
            {
                a[i][j]-=M*a[k][j];               // домножение сроки на число
                if((i>j) & (fabs(a[i][j])<eps))
                {
                    a[i][j]=0;    // обнуление элемента под главной диагональю
                }

            }
        }
    }
    if((fabs(a[n-1][n-1])<eps)) // сравнение последнего диагонального элемента с нулём
    {
        a[n-1][n-1]=0;          // коррекция последнего диагонального элемента если он близок к нулю
    }
    for(i=0;i<n;i++)
        det*=a[i][i];           // определитель как произведение элементов главной диагонали
    return det;                 // возвращение значения функции
}

/******************************************************************/
/********ранг матрицы методом Гаусса ******************************/
/*************************************************************/
double gauss_rank(double **mas, int n) // определитель методом Гаусса
{
    int i,j,k,r;              // переменные счетчики
    double M;                 // вспомогательная переменная
    double eps  = 0.0000001;  // задаю погрешность, если значение элемента меньше значения eps то считаю что данный элемент равен нулю
    double  **a;              // перременная для хранения матрицы
    a=new double *[n];        // выделение памяти под матрицу
       for(i=0;i<n;i++)
    {
        a[i]=new double[n];
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            a[i][j]=mas[i][j];  // заполнение элементов вспомогательной матрицы
        }
    }
    for(k=0;k<n;k++)
    {

        for(i=k+1;i<n;i++)
        {
            for((M=a[i][k]/a[k][k]),j=k;j<n;j++)
            {
                a[i][j]-=M*a[k][j]; //обнулеение элементов

            }

        }
    }
    r = 0; // теперь в этой переменной считаю ранг
    for(i=0;i<n;i++)
    {
        if((a[i][i]*a[i][i])>eps)//считаю ненулевые элементы главной диагонали
        {
            r++;
        }
    }
    return r;
}

/********модифицированный метод Гаусса расчета ранга*********************/
double gauss_rank_eps_zero(double **mas, int n) // определитель методом Гаусса
{
    int i,j,k,r;              // переменные счетчики
    double M;                 // вспомогательная переменная
    double eps  = 0.0000001;  // задаю погрешность, если значение элемента меньше значения eps то считаю что данный элемент равен нулю
    double  **a;              // перременная для хранения матрицы
    a=new double *[n];        // выделение памяти под матрицу
    for(i=0;i<n;i++)
    {
        a[i]=new double[n];
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            a[i][j]=mas[i][j]; // создание матрицы для которой реализуется метод Гаусса
        }
    }
    for(k=0;k<n;k++)
    {
        for(i=k+1;i<n;i++)
        {
            for((M=a[i][k]/a[k][k]),j=k;j<n;j++) // расчет коэффициента для обнуления элемента
            {
                a[i][j]-=M*a[k][j]; // домножение строки на число
                if((i>j) & (fabs(a[i][j])<eps))
                {
                    a[i][j]=0;  // обнуление элемента
                }
            }
        }
    }

    if((fabs(a[n-1][n-1])<eps)) // проверяем последний диагональный элемент, остальные тоже можно проверять на на практике проверено что ранг может падать только на 1
    {
        a[n-1][n-1]=0;
    }
    r = 0; // теперь в этой переменной считаю ранг
    for(i=0;i<n;i++)
    {
        if((a[i][i]*a[i][i])>eps)//считаю ненулевые элементы главной диагонали
        {
            r++;
        }
    }
    return r;
}

/********тест Адамара для проверки диагонального преобладания*********************/
int adamar_test(double **mas, int n)
{
    int i,j,k,j0;            // счетчики
    double  **a;             // матрица абсолютных значений
    double  *Mj;             // вспомогательный одномерный массив
    double S;                // частичная сумма элементов массива
    int param = 1;           // выходная переменная (результат теста Адамара)
    double M;                // переменная в которой хранится максимальный элемент строки
    Mj = new double [n];     // выделение памяти под одномерный массив
    a=new double *[n];       // выделение памяти под двумерный массив
    for(i=0;i<n;i++)
    {
        a[i]=new double[n];
    }
    //расчет абсолютных значений элементов матрицы
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            a[i][j]=fabs(mas[i][j]);
        }
    }

    for(i=0;i<n;i++) // перебор строк матрицы
    {
        M = a[i][0];
        j0  = 0;
        // создание временнго массива
        for(k=0;k<n;k++)
        {
            Mj[k]  = a[i][k]; // временный массив содержащий элементы строки
        }
        // поиск максимального элемента
        for(j=1;j<n;j++)
        {
            if (a[i][j]>M)
            {
                M  = a[i][j];
                j0 = j; // номер столбца с максимальным элементам
            }
        }
        Mj[j0] = 0;     //  обнудение максимального элемента массива
        S = 0;          //  сумма всех элементов массива кроме максимального (начальное значение)
        for(k=0;k<n;k++)
        {
            S  = S + Mj[k];   // суммирование элементов массива
        }
        if (M<S)              // тест Адамара
        {param = 0;    // обновление параметра по результатам теста
        }


    }


    return param;
}

