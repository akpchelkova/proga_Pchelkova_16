#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), operand1(0), operand2(0) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    display = new QLineEdit(this);
    display->setReadOnly(true);
    layout->addWidget(display);

    QGridLayout *buttonLayout = new QGridLayout();
    layout->addLayout(buttonLayout);

    QStringList buttons = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", "C", "=", "+"
    };

    int pos = 0;
    for (const auto &button : buttons) {
        QPushButton *buttonObj = new QPushButton(button, this);
        buttonLayout->addWidget(buttonObj, pos / 4, pos % 4);
        connect(buttonObj, &QPushButton::clicked, this, [this, button]() {
            if (button == "C") {
                clear();
            } else if (button == "=") {
                calculate();
            } else if (button == "+" || button == "-" || button == "*" || button == "/") {
                handleOperator(button);  // Обработка нажатия оператора
            } else {
                numberPressed(button);
            }
        });
        pos++;
    }
}

MainWindow::~MainWindow() {
}


void MainWindow::numberPressed(const QString &number) {
    // Если оператор уже выбран, перемещаю к новому числу
    display->setText(display->text() + number);
}

void MainWindow::handleOperator(const QString &op) {
    // Устанавливаю operand1 как текущее значение дисплея
    if (!display->text().isEmpty()) {
        operand1 = display->text().toDouble();
    }
    pendingOperator = op;  // Устанавливаю текущий оператор
    display->clear();      // Очищаю дисплей для следующего ввода
}

void MainWindow::calculate() {
    if (pendingOperator.isEmpty()) {
        return;
    }

    // Устанавливаю operand2 значение из дисплея
    operand2 = display->text().toDouble();
    double result = 0;

    if (pendingOperator == "+") {
        result = operand1 + operand2;
    } else if (pendingOperator == "-") {
        result = operand1 - operand2;
    } else if (pendingOperator == "*") {
        result = operand1 * operand2;
    } else if (pendingOperator == "/") {
        if (operand2 != 0) {
            result = operand1 / operand2;
        } else {
            QMessageBox::warning(this, "Ошибка", "Деление на ноль!");
            clear();
            return;
        }
    }

    // Обновляю дисплей результатом и operand1 для следующего вычисления
    display->setText(QString::number(result));
    operand1 = result;  // Устанавливаю результат как новый operand1
    pendingOperator.clear();  // Очищаю оператор
}

void MainWindow::clear() {
    display->clear();
    operand1 = 0;
    operand2 = 0;
    pendingOperator.clear();
}
