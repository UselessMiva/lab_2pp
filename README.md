Лабораторная работа №2
Выполнил Абанин Иван 6312-100503D
Характеристики процессора
 AMD Ryzen 5 5600H 
 Базовая частота:	3.3 ГГц
 Ядра: 6
 Логических процессоров: 12
Описание файлов:
data - папка со значениями матриц для параллельных вычислений
results - папка с результатами вычислений, сделанных с помощью OpenMP
result_computing - папка с временем вычислений и размером для каждой матрицы
result-matrix - папка с результирующей матрицей (результат перемножения двух матриц)
data_np - папка со значениями матриц(not parallel)
results - папка с результатами вычислений(not parallel)
result_computing - папка с временем вычислений и размером для каждой матрицы
result-matrix - папка с результирующей матрицей (результат перемножения двух матриц)
lab_2mth.cpp - С++ скрипт, который создает, перемножает и записывает матрицы и результаты в файл, используя для этого библиотеку omp
lab_2sth.cpp - С++ скрипт, который создает, перемножает и записывает матрицы и результаты в файл, без использования библиотеки omp
calc_checking.py - Python утилита для проверки перемножения матриц на C++
main.py - Python скрипт для проверки результатов C++ программы, использует calc_cheking.py (Для этого используется библиотека Numpy)
graph.png - График зависимости времени перемножения матриц от их размера для параллельных и обычных вычислений

График:
!(https://github.com/UselessMiva/lab_2pp/blob/main/graph.png)
