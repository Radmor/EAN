#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void displayException(QString tekst);
    void displayValue(QString intervalElementString);
    void displayMatrixElement(QString intervalElementString);
    void clearMatrixTextBrowser();
    void clearValueTextBrowser();
    void clearTextBrowsers();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

public:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
