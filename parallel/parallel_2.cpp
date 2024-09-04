#include <omp.h>
#include <chrono>
#include <iostream>

const int NMAX = 100; // Размер массива - константа
const int NMAX_MAX = 1000; // Максимальное значение для LIMIT
float a[NMAX][NMAX];
int main() 
{
    setlocale(LC_ALL, "Russian");
    int i, j;
    float sum = 0;
    for (int LIMIT = 1; LIMIT <= NMAX_MAX; LIMIT += 5) {
        // Инициализация массива
        for (int i = 0; i < NMAX; i++) {
            for (int j = 0; j < NMAX; j++) {
                a[i][j] = i + j;
            }
        }



        // Однопоточная версия///////////////////////////////////////////////////////////////////
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < NMAX; i++) {
            float sum = 0;
            for (int j = 0; j < NMAX; j++) {
                sum += a[i][j];
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_single = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();



        // Многопоточная версия/////////////////////////////////////////////////////////////
        start = std::chrono::high_resolution_clock::now();
        #pragma omp parallel shared(a) if (NMAX > LIMIT)
        {
        #pragma omp for private(i, j, sum)
            for (int i = 0; i < NMAX; i++) {
                float sum = 0;
                for (int j = 0; j < NMAX; j++) {
                    sum += a[i][j];
                }
            }
        }
        end = std::chrono::high_resolution_clock::now();
        auto duration_parallel = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        /////////////////////////////////////////////////////////////////////////////////////


        // Вывод результатов
        std::cout << "LIMIT: " << LIMIT << std::endl;
        std::cout << "Однопоточная версия: " << duration_single << " мкс" << std::endl;
        std::cout << "Многопоточная версия: " << duration_parallel << " мкс" << std::endl;
        if (duration_single%10 == duration_parallel%10) {
            std::cout << "-------------------------Времена выполнения совпадают!---------------------" << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}