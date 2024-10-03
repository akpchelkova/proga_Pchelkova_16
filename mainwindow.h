#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

class QLineEdit;
class QPushButton;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void numberPressed(const QString &number);
    void handleOperator(const QString &op); 
    void calculate();
    void clear();

private:
    QLineEdit *display;
    double operand1;
    double operand2;
    QString pendingOperator;
};

#endif // MAINWINDOW_H
