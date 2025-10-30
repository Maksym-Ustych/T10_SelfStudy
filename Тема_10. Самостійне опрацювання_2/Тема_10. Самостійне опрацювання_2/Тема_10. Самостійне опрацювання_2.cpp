#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>
using namespace std;

double f(int choice, double x) {
    switch (choice) {
    case 1: return sin(x);
    case 2: return cos(x);
    case 3: return exp(x);
    case 4:
        if (x <= 0)
            throw domain_error("ln(x) визначено лише для x > 0");
        return log(x);
    default:
        throw invalid_argument("Невірний номер функції.");
    }
}

double simpsonIntegral(int choice, double a, double b, int n) {
    if (n % 2 != 0) n++; // n має бути парним

    double h = (b - a) / n;
    double sum = f(choice, a) + f(choice, b);

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0)
            sum += 2 * f(choice, x);
        else
            sum += 4 * f(choice, x);
    }

    return (h / 3) * sum;
}

int main() {
    // Коректне відображення української в консолі Windows
    setlocale(LC_ALL, "");
    system("chcp 65001 > nul");

    int choice, n;
    double a, b;

    try {
        cout << "=== ОБЧИСЛЕННЯ ІНТЕГРАЛУ МЕТОДОМ СІМПСОНА ===" << endl;
        cout << "Оберіть функцію:" << endl;
        cout << "1) y = sin(x)" << endl;
        cout << "2) y = cos(x)" << endl;
        cout << "3) y = e^x" << endl;
        cout << "4) y = ln(x)" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        if (!cin)
            throw invalid_argument("Помилка: введено не число.");

        cout << "\nВведіть межу a: ";
        cin >> a;
        cout << "Введіть межу b: ";
        cin >> b;
        cout << "Введіть кількість підрозділів (n): ";
        cin >> n;

        if (!cin)
            throw invalid_argument("Помилка: введено не числове значення.");
        if (n <= 0)
            throw invalid_argument("n повинно бути > 0");
        if (a > b)
            throw invalid_argument("a не може бути більшим за b");

        double result = simpsonIntegral(choice, a, b, n);
        cout << fixed << setprecision(6);
        cout << "\nІнтеграл на відрізку [" << a << "; " << b << "] ≈ " << result << endl;

    }
    catch (exception& e) {
        cout << "\nСталася помилка: " << e.what() << endl;
    }

    return 0;
}