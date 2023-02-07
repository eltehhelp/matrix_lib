#include <QCoreApplication>
#include <iostream>
#include <my_matrix.hpp>
#include <my_struct.hpp>
using namespace std;
// Основная функция
int main() {
    /*****объявление переменных**********************************/
    int n = 5;                      // размер матрицы
    int i,j;                     // счетчик
    double **mas;               // двумерные матрицы
    double **mas2;
    double *b;                  // одномерные матрицы
    double *v;
    matrix_correct mas3;       //двумерная матрица с признаком достоверности
    double x;                  //вспомогательная переменная



    /**********выделение памяти под массивы**********************************/
    /*выделатся память под массив 1*/
    mas = new double*[n];
    for (i = 0; i < n; i++)
    {
        mas[i] = new double [n];
    }
    /*выделатся память под массив 2*/
    mas2 = new double*[n];
    for (i = 0; i < n; i++)
    {
        mas2[i] = new double [n];
    }
    /*********одномерные массивы***********/
    b = new double [n];
    v = new double [n];



    /**********задаю численные значения массивов****************/
    mas[0][0] = 17;
    mas[0][1] = 24;
    mas[0][2] = 1;
    mas[0][3] = 8;
    mas[0][4] = 15;

    mas[1][0] = 23;
    mas[1][1] = 5;
    mas[1][2] = 7;
    mas[1][3] = 14;
    mas[1][4] = 16;

    mas[2][0] = 4;
    mas[2][1] = 6;
    mas[2][2] = 13;
    mas[2][3] = 20;
    mas[2][4] = 22;

    mas[3][0] = 10;
    mas[3][1] = 12;
    mas[3][2] = 19;
    mas[3][3] = 21;
    mas[3][4] = 3;

    mas[4][0] = 11;
    mas[4][1] = 18;
    mas[4][2] = 25;
    mas[4][3] = 2;
    mas[4][4] = 9;

    b[0] = 1;
    b[1] = 8;
    b[2] = 9;
    b[3] = -6;
    b[4] = 24;
    /********************************************************************/
    cout << "Исходная матрица \n";
    PrintMatr(mas,n);
    cout << " \n";
    cout << " \n";
    /********************************************************************/
    cout << "Определитель матрицы через алгебраические дополнения \n";
    x = Determinant(mas, n);
    cout << "Определитель через алгебраические дополнения \n";
    cout << x << "\n";
    cout << " \n";
    cout << " \n";
    /********************************************************************/
    cout << "Определитель методом Гаусса \n";
    x = gauss_det(mas, n);
    cout << x << "\n";
    cout << " \n";
    cout << " \n";
    /********************************************************************/
    cout << "Определитель методом Гаусса с коррекцией\n";
    x = gauss_det_zero(mas, n);
    cout << x << "\n";
    cout << " \n";
    cout << " \n";
    /*******************************************************************/
    cout << "Ранг методом Гаусса\n";
    x = gauss_rank(mas, n);
    cout << x << "\n";
    cout << " \n";
    cout << " \n";
    /******************************************************************/
    cout << "Ранг методом Гаусса с коррекцией\n";
    x = gauss_rank_eps_zero(mas, n);
    cout << x << "\n";
    cout << " \n";
    cout << " \n";
    /******************************************************************/
    cout << "Тест Адамара\n";
    x = adamar_test(mas, n);
    cout << x << "\n";
    cout << " \n";
    cout << " \n";

    /*****************************************************************/
    cout << "Транспонирование матрицы \n";
    mas2 = transpon(mas, n);
    PrintMatr(mas2,n);
    cout << " \n";
    cout << " \n";
    /*****************************************************************/
    cout << "Обратная матрица \n";
    mas3 = inverse(mas, n);
    PrintMatr(mas3.mas,n);
    cout << " \n";
    cout << " \n";
    /*****************************************************************/
    cout << "Умножение матриц \n";
    mas2 = prodMatr(mas3.mas,mas,n);
    PrintMatr(mas2,n);
    cout << " \n";
    cout << " \n";
    /*****************************************************************/
    cout << "Решение СЛАУ \n";
    cout << "A =  \n";
    PrintMatr(mas,n);
    cout << "b =  \n";
    PrintVect(b,n);
    cout << "X =  \n";
    v = slau_solver(mas,b,n);
    PrintVect(v,n);
    /******************************************************************/
   // cin.get();
    return 0;
}
