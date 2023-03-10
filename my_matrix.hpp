#pragma once
#include <QDebug>
#include <my_struct.hpp>

/***********************************************************************/
/******функция вывода матрицы на экран**********************************/
/******mas - входная матрица********************************************/
/******m  - размер матрицы *********************************************/
/***********************************************************************/
void PrintMatr(double **mas, int m);


/***********************************************************************/
/******функция вывода матрицы-строки на экран***************************/
/******mas - входная матрица********************************************/
/******m  - размер матрицы *********************************************/
/***********************************************************************/
void PrintVect(double *mas, int m);


/***********************************************************************/
/******функция расчеты алгебраического дополнения***********************/
/******mas - входная матрица********************************************/
/******р  - алгебраическое дополнение **********************************/
/******i,j  - координаты текущего элемента *****************************/
/******m - размер исходной матрицы *************************************/
/***********************************************************************/
void GetMatr(double **mas, double **p, int i, int j, int m);

/***********************************************************************/
/******функция расчета определителя матрицы*****************************/
/******mas - входная матрица********************************************/
/******m  - размер матрицы *********************************************/
/***********************************************************************/
double Determinant(double **mas, int m);


/***********************************************************************/
/******функция расчета обратной матрицы*********************************/
/******a - входная матрица**********************************************/
/******m  - размер матрицы *********************************************/
/***********************************************************************/
matrix_correct inverse(double** a, int m);


/***********************************************************************/
/******функция транспонирования матрицы*********************************/
/******a - входная матрица**********************************************/
/******m  - размер матрицы *********************************************/
/***********************************************************************/
double** transpon(double** a, int m);


/***********************************************************************/
/******функция умножения матрицы на вектор *****************************/
/******А - входная матрица**********************************************/
/******b - входной вектор***********************************************/
/******m  - размер матрицы *********************************************/
/***********************************************************************/
double* MV(double **A, double *b, int m);


/***********************************************************************/
/******функция решения СЛАУ ********************************************/
/******А - левая часть СЛАУ ********************************************/
/******b - правая часть СЛАУ *******************************************/
/******m  - размер матрицы *********************************************/
/***********************************************************************/
double* slau_solver(double **A, double *b, int m);

/***********************************************************************/
/******функция умножения двух квадратных матриц ************************/
/******a - первая матрица***********************************************/
/******b - вторая матрица***********************************************/
/******m - размер матрицы **********************************************/
/***********************************************************************/
double** prodMatr(double** a, double** b, int m);


/***********************************************************************/
/******функция расчета ранга матрицы************************************/
/******mas - входная матрица********************************************/
/******m  - размер матрицы *********************************************/
/***********************************************************************/
int rank1(double **a, int n);


/***********************************************************************/
/******функция смены местами двух строк ********************************/
/******mas - входная матрица *******************************************/
/******k,e - номера строк **********************************************/
/******m  - размер матрицы *********************************************/
/***********************************************************************/
void rows_swap(double **mas, int k, int e, int m);

/***********************************************************************/
/******функция смены местами двух столбцов******************************/
/******mas - входная матрица *******************************************/
/******k,e - номера строк **********************************************/
/******m  - размер матрицы *********************************************/
/***********************************************************************/
void colls_swap(double **mas, int k, int e, int m);

/***********************************************************************/
/******функция вычисления определителя методом гаусса*******************/
/******mas - входная матрица *******************************************/
/******m  - размер матрицы *********************************************/
/***********************************************************************/
double gauss_det(double **mas, int n);

/***********************************************************************/
/******функция вычисления определителя методом Гаусса с коррекцией******/
/******mas - входная матрица *******************************************/
/******m  - размер матрицы *********************************************/
/***********************************************************************/
double gauss_det_zero(double **mas, int n);

/***********************************************************************/
/******функция вычисления ранга методом гаусса**************************/
/******mas - входная матрица *******************************************/
/******m  - размер матрицы *********************************************/
/***********************************************************************/
double gauss_rank(double **mas, int n);

/***********************************************************************/
/******функция вычисления ранга методом Гаусса с коррекцией*************/
/******mas - входная матрица *******************************************/
/******m  - размер матрицы *********************************************/
/***********************************************************************/
double gauss_rank_eps_zero(double **mas, int n);

/***********************************************************************/
/******функция вычисления теста Адамара (проверка диагонального)********/
/******преобладания ****************************************************/
/******mas - входная матрица *******************************************/
/******n  - размер матрицы *********************************************/
/***********************************************************************/
int adamar_test(double **mas, int n);

