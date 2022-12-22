
#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

// Генерація значень елементів масиву
void CreateArray(double* a, const int size, const int Low, const int High, int i)
{
    // генерація випадковогозначення елементу
    a[i] = 0.01 * (10 * Low + rand() % (10 * (High - Low + 1)));
    if (i < size - 1) // перевірка щоб не вийти за межі масиву
        // рекурсивний виклик функції
        CreateArray(a, size, Low, High, i + 1);
}



// Вивід елементів масиву
void PrintArray(double* a, const int size, int i)
{
    // форматований вивід елемента масиву
    cout << setw(10) << fixed << setprecision(3) << a[i];
    if (i < size - 1)                // перевірка щоб не вийти за межі масиву
        PrintArray(a, size, i + 1);  // рекурсивний виклик функції
    else
        cout << endl;
}


// Обчислення суми елементів з непарними номерами i=0
double SumOddNumbers(double* a, const int size, int i, double sum)
{
    if (i % 2)
        sum += a[i]; // 
    if (i < size - 1)    // перевірка щоб не вийти за межі масиву				
        return SumOddNumbers(a, size, i + 1, sum);
    else
        return sum;        // повернення суми елементів
}


// Обчислює суму елементів масиву, розташованих між першим і останнім від’ємними елементами
double SumBetweenNegatives(double* a, const int size, int i, double& sum, double& acc, bool& started)
{
    if (a[i] < 0) // перевірили чи від'ємний
    {
        if (!started)   // якщо ще не стартували раніше
        {               // стартуємо 
            acc = 0;    // обнуляємо проміжну суму
            started = true;
        }
        else
        {
            sum += acc;   // додаємо проміжну суму до основної
            acc = a[i];   // проміжній сумі присвоюємо значення елемента
        }
    }
    else
        acc += a[i]; // збільшуємо проміжну суму


    if (i < size - 1)    // перевірка щоб не вийти за межі масиву	
        return SumBetweenNegatives(a, size, i + 1, sum, acc, started);
    else
        return sum;        // повернення суми елементів
}

// стиснення масиву
void compress_array(double* a, const int size, int i, int& k)
{
    // i - лічильник опрацьованих елементів
    // k - лічильник викинутих елементів

    // порівнюємо значення елемента масиву з 1,0
    if (fabs(a[i]) <= 1.0)
    {   // якщо не більше 1
        // в циклі зміщуємо елементи 
        for (int j = i; j < size - k - 1; j++)
            a[j] = a[j + 1];

        ++k; // збільшили лічильник викинутих елементів  
        i--;
    }

    if (i < size - k)    // перевірка щоб не вийти за межі масиву	
    {
        if (k > 0) a[size - k] = 0;          // Заповнюємо нулями кінець масиву  
        compress_array(a, size, i + 1, k);
    }
}


int main()
{
    srand((unsigned)time(NULL)); // ініціалізація генератора випадкових чисел
    int n;            // розмір масиву
    int k = 0;
    int Low = -40;
    int High = 20;
    double sum = 0.0, acc = 0.0;
    bool started = false;

    // ввід розмірності динамічного масиву
    cout << "n = "; cin >> n;

    // cтворення динамічного масиву
    double* a = new double[n];

    CreateArray(a, n, Low, High, 0);  // заповненння масиву випадковими числами
    PrintArray(a, n, 0);              // вивід масиву   
    cout << " The sum odd number elements: " << SumOddNumbers(a, n, 0, 0.0) << endl;
    cout << " The sum between the first and last negatives: " << SumBetweenNegatives(a, n, 0, sum, acc, started) << endl;

    compress_array(a, n, 0, k);
    cout << " Compressed array: " << endl;
    PrintArray(a, n, 0);              // Вивід зміненого масиву

    delete[] a; // знищили динамічнийі масив
    return 0;
}
