#include <iostream>
#include <thread>
#include <vector>

class MergeSort {
public:
    // Функция для сортировки массива вызовом метода слияния
    void Sort(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            // Рекурсивно сортируем левую и правую половины массива
            Sort(arr, left, mid);
            Sort(arr, mid + 1, right);

            // Вызываем функцию слияния
            Merge(arr, left, mid, right);
        }
    }

private:
    // Функция для слияния двух половин массива
    void Merge(std::vector<int>& arr, int left, int mid, int right) {
        int i, j, k;
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<int> L(n1), R(n2);

        // Заполняем временные массивы L и R
        for (i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        i = 0;
        j = 0;
        k = left;

        // Слияние временных массивов обратно в arr
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        // Добавление оставшихся элементов в основной массив
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
};

int main() {
    std::vector<int> arr(10);

    // Ввод значений в массив от пользователя
    std::cout << "Vvedite 10 chisel: ";
    for (int i = 0; i < 10; i++) {
        std::cin >> arr[i];
    }

    MergeSort mergeSort;

    // Создание отдельного потока для сортировки массива
    std::thread mergeSortThread([&mergeSort, &arr]() {
        mergeSort.Sort(arr, 0, arr.size() - 1);
        });

    mergeSortThread.join(); // Ожидание завершения потока

    // Вывод отсортированного массива
    std::cout << "Otsortirovat massiv: ";
    for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}