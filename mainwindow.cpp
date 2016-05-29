#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include "logicmain.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Wyznaczanie wartości i współczynników okresowej funkcji sklejanej trzeciego stopnia");
    QPixmap folderPixmap("/home/ph/Dokumenty/EAN/icons/folder.ico");
    QIcon folderIcon(folderPixmap);
    //this->pushButton->setIcon(folderIcon);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filepath=QFileDialog::getOpenFileName(
                this,
                tr("Choose data file"),
                "/home/ph/Dokumenty/EAN/data",
                "Text files(*.txt);;All files(*.*)"
                );
    //QMessageBox::critical(this,tr("File chosen:"),filepath);
    ui->textBrowser->setText(filepath);

}

void MainWindow::displayException(QString exceptionText){
    this->clearTextBrowsers();
    QMessageBox::critical(this,tr("Exception!"),exceptionText);
}

void MainWindow::displayValue(QString valueString){
    ui->textBrowser_2->setText(valueString);
}

void MainWindow::displayMatrixElement(QString matrixElementString){
    //ui->textBrowser_3->append(matrixElementString);
    ui->textBrowser_3->moveCursor (QTextCursor::End);
    ui->textBrowser_3->insertPlainText (matrixElementString);
    ui->textBrowser_3->moveCursor (QTextCursor::End);
}

void MainWindow::clearValueTextBrowser(){
    ui->textBrowser_2->clear();
}

void MainWindow::clearTextBrowsers(){
    this->clearValueTextBrowser();
    this->clearMatrixTextBrowser();
}

void MainWindow::clearMatrixTextBrowser(){
    ui->textBrowser_3->clear();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString filepath=ui->textBrowser->toPlainText();

    bool ifNumeric;

    if(ui->radioButton->isChecked()){
        ifNumeric=true;
    }
    else{
        ifNumeric=false;

    }

    logicfunction(this,filepath.toStdString(),ifNumeric);
}
