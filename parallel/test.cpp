//#include <omp.h>
//#include <iostream>
//#include <random>
//#include <chrono>
//
//const int M = 1000; // Количество строк
//const int N = 1000; // Количество столбцов
//int a[M][N];
//
//int main() {
//    int sum[M] = { 0 };
//    setlocale(LC_ALL, "Russian");
//
//    // Инициализация матрицы случайными числами
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> distrib(1, 100);
//    int i, j;
//    for (int i = 0; i < M; i++) {
//        for (int j = 0; j < N; j++) {
//            a[i][j] = distrib(gen);;
//        }
//    }
//
//    double start;
//    double end;
//    start = omp_get_wtime();
//
//    // Расчет суммы единиц для каждой строки в параллельном режиме
//
//    #pragma omp parallel for shared(a, sum) private(j)
//    for (int i = 0; i < M; i++) {
//        for (int j = 0; j < N; j++) {
//            long long product = a[i][j];
//            while (product > 0) {
//                sum[i] += product & 1;
//                product >>= 1;
//            }
//        }
//    }
//
//
//    // Вывод результатов
//    for (int i = 0; i < M; i++) {
//        std::cout << "Сумма единиц в двоичном представлении произведений для строки " << i << ": " << sum[i] << std::endl;
//    }
//
//    end = omp_get_wtime();
//    std::cout<<"Процесс занял:"<<end - start;
//    return 0;
//}