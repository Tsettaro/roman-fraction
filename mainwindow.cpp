#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "Roman.h"
#include <regex>

string pattern = "^-?M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})";

int check_correct (const string &text){
    if (text == "") return 0;
    regex roman_fraction(pattern);
    if (regex_match(text, roman_fraction)) return 1;
    return 0;
}

int is_real(int a, int b){
    return a < 4000 && b < 4000;
}

int MainWindow::check_correct_input(){
    return (check_correct(ui->textEdit->toPlainText().toUtf8().constData()) &&
            check_correct(ui->textEdit_2->toPlainText().toUtf8().constData()) &&
            check_correct(ui->textEdit_5->toPlainText().toUtf8().constData()) &&
            check_correct(ui->textEdit_6->toPlainText().toUtf8().constData()) == 1);
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    if (check_correct_input()){
        RomanFraction *fr1 = new RomanFraction(ui->textEdit->toPlainText().toUtf8().constData(),
                          ui->textEdit_2->toPlainText().toUtf8().constData());
        RomanFraction *fr2 = new RomanFraction(ui->textEdit_5->toPlainText().toUtf8().constData(),
                          ui->textEdit_6->toPlainText().toUtf8().constData());
        RomanFraction fr3 = *(fr1) + *(fr2);
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
        delete fr1;
        delete fr2;
    } else{
        QMessageBox::critical(this, "ВНИМАНИЕ!", "Ошибка при вводе дробей!");
    }
}

void MainWindow::on_pushButton_2_clicked(){
    if (check_correct_input()){
        RomanFraction *fr1 = new RomanFraction(ui->textEdit->toPlainText().toUtf8().constData(),
                                               ui->textEdit_2->toPlainText().toUtf8().constData());
        RomanFraction *fr2 = new RomanFraction(ui->textEdit_5->toPlainText().toUtf8().constData(),
                                               ui->textEdit_6->toPlainText().toUtf8().constData());
        RomanFraction fr3 = *(fr1) - *(fr2);
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
        delete fr1;
        delete fr2;
    } else{
        QMessageBox::critical(this, "ВНИМАНИЕ!", "Ошибка при вводе дробей!");
    }
}


void MainWindow::on_pushButton_3_clicked(){
    if (check_correct_input()){
        RomanFraction *fr1 = new RomanFraction(ui->textEdit->toPlainText().toUtf8().constData(),
                                               ui->textEdit_2->toPlainText().toUtf8().constData());
        RomanFraction *fr2 = new RomanFraction(ui->textEdit_5->toPlainText().toUtf8().constData(),
                                               ui->textEdit_6->toPlainText().toUtf8().constData());
        RomanFraction fr3 = *(fr1) * *(fr2);
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
        delete fr1;
        delete fr2;
    } else {
        QMessageBox::critical(this, "ВНИМАНИЕ!", "Ошибка при вводе дробей!");
    }
}


void MainWindow::on_pushButton_4_clicked(){
    if (check_correct_input()){
        RomanFraction *fr1 = new RomanFraction(ui->textEdit->toPlainText().toUtf8().constData(),
                                               ui->textEdit_2->toPlainText().toUtf8().constData());
        RomanFraction *fr2 = new RomanFraction(ui->textEdit_5->toPlainText().toUtf8().constData(),
                                               ui->textEdit_6->toPlainText().toUtf8().constData());
        RomanFraction fr3 = *(fr1) / *(fr2);
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
        delete fr1;
        delete fr2;
    } else {
        QMessageBox::critical(this, "ВНИМАНИЕ!", "Ошибка при вводе дробей!");
    }
}
