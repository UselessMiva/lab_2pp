
#include <fstream>
#include <ctime>
#include <format>
#include <string>
#include <filesystem>
#include <time.h>
#include <nlohmann/json.hpp>
#include <omp.h>
#include <iostream>

void create_dirs()
{
    std::filesystem::path results_folder_path = "C:\\Users\\79171\\Desktop\\lab_2\\lab_2pp\\results";
    std::filesystem::path result_matrix_folder_path = "C:\\Users\\79171\\Desktop\\lab_2\\lab_2pp\\results\\result_matrix";
    std::filesystem::path result_computings_folder_path = "C:\\Users\\79171\\Desktop\\lab_2\\lab_2pp\\results\\result_computing";
    std::filesystem::path data_folder_path = "C:\\Users\\79171\\Desktop\\lab_2\\lab_2pp\\data";

    if (!std::filesystem::exists(results_folder_path) || !std::filesystem::is_directory(results_folder_path))
    {
        std::filesystem::create_directories(results_folder_path);
    }

    if (!std::filesystem::exists(data_folder_path) || !std::filesystem::is_directory(data_folder_path))
    {
        std::filesystem::create_directories(data_folder_path);
    }

    if (!std::filesystem::exists(result_matrix_folder_path) || !std::filesystem::is_directory(result_matrix_folder_path))
    {
        std::filesystem::create_directories(result_matrix_folder_path);
    }

    if (!std::filesystem::exists(result_computings_folder_path) || !std::filesystem::is_directory(result_computings_folder_path))
    {
        std::filesystem::create_directories(result_computings_folder_path);
    }
}

void save_to_json(std::string file_name, double time, int size)
{
    nlohmann::json data;
    data["time"] = time;
    data["size"] = size;

    std::ofstream file(file_name);
    if (file.is_open())
    {
        file << data.dump(4);
        file.close();
    }

    std::cout << "JSON файл успешно создан и заполнен!\n";
}

int **create_matrix(int size)
{
    int **matrix = new int *[size];
    for (int i = 0; i < size; i++)
    {
        matrix[i] = new int[size];
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = rand() % 100;
        }
    }
    return matrix;
}

void write_matrix_to_file(std::string file_name, int **matrix, int size)
{
    std::ofstream file(file_name);
    if (file.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                file << matrix[i][j] << " ";
            }
            file << std::endl;
        }
        file.close();
        std::cout << "Matrix has been written to file." << std::endl;
    }
}

int **matrix_multiplication(int **first_matrix, int **second_matrix, int size, double &time)
{
    int **result_matrix = new int *[size];
    for (int i = 0; i < size; i++)
    {
        result_matrix[i] = new int[size];
    }
    clock_t start = clock();
    int i, j, k;
#pragma omp parallel private(i, j, k)
    {
#pragma omp for
        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                result_matrix[i][j] = 0;
                for (k = 0; k < size; k++)
                {
                    result_matrix[i][j] += first_matrix[i][k] * second_matrix[k][j];
                }
            }
        }
    }
    clock_t end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
    return result_matrix;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    create_dirs();

    int sizes[10] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    for (auto size : sizes)
    {
        for (size_t i = 0; i < 10; i++)
        {
            int **m1 = create_matrix(size);
            int **m2 = create_matrix(size);
            double time;
            int **res = matrix_multiplication(m1, m2, size, time);
            write_matrix_to_file(std::format("C:\\Users\\79171\\Desktop\\lab_2\\lab_2pp\\data\\matrix_1_{}_{}.txt", size, i), m1, size);
            write_matrix_to_file(std::format("C:\\Users\\79171\\Desktop\\lab_2\\lab_2pp\\data\\matrix_2_{}_{}.txt", size, i), m2, size);
            write_matrix_to_file(std::format("C:\\Users\\79171\\Desktop\\lab_2\\lab_2pp\\results\\result_matrix\\result_matrix_{}_{}.txt", size, i), res, size);
            save_to_json(std::format("C:\\Users\\79171\\Desktop\\lab_2\\lab_2pp\\results\\result_computing\\matrix_{}_{}.json", size, i), time, size);
        }
    }
}