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
        throw invalid_argument("Невірний номер функції");
    }
}

int main() {
    // Коректне відображення українських символів у Windows-консолі
    setlocale(LC_ALL, "");
    system("chcp 65001 > nul");

    int choice;
    double a, b, h;

    try {
        cout << "=== ТАБУЛЮВАННЯ ФУНКЦІЙ ===" << endl;
        cout << "Оберіть функцію:" << endl;
        cout << "1) y = sin(x)" << endl;
        cout << "2) y = cos(x)" << endl;
        cout << "3) y = e^x" << endl;
        cout << "4) y = ln(x)" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        if (!cin)
            throw invalid_argument("Помилка: потрібно вводити число.");

        cout << "\nВведіть початок відрізка a: ";
        cin >> a;
        cout << "Введіть кінець відрізка b: ";
        cin >> b;
        cout << "Введіть крок h: ";
        cin >> h;

        if (!cin)
            throw invalid_argument("Помилка: введено нечислове значення.");
        if (h <= 0)
            throw invalid_argument("Крок h повинен бути більшим за 0.");
        if (a > b)
            throw invalid_argument("Початок відрізка не може бути більшим за кінець.");

        cout << "\nРезультат табулювання:\n";
        cout << setw(10) << "x" << setw(20) << "y" << endl;
        cout << "---------------------------------\n";

        for (double x = a; x <= b + 1e-12; x += h) {
            try {
                double y = f(choice, x);
                cout << setw(10) << fixed << setprecision(4) << x
                    << setw(20) << y << endl;
            }
            catch (domain_error&) {
                cout << setw(10) << fixed << setprecision(4) << x
                    << setw(20) << "немає значення" << endl;
            }
        }
    }
    catch (exception& e) {
        cout << "\nСталася помилка: " << e.what() << endl;
    }

    return 0;
}