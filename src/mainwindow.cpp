#include "../include/mainwindow.h"
#include "../include/Roman.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <regex>

bool red = false;
bool normal = false;

int last_clicked = 0;

int check_correct (const string &text){
    string pattern = "^-?M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})";
    if (text == "") return 0;
    regex roman_fraction(pattern);
    if (regex_match(text, roman_fraction)) return 1;
    return 0;
}

void MainWindow::error(){
    QMessageBox::critical(this, "ВНИМАНИЕ!", "Ошибка при вводе дробей!");
}

int MainWindow::check_correct_input(){
    return (check_correct(ui->textEdit->toPlainText().toStdString()) &&
            check_correct(ui->textEdit_2->toPlainText().toStdString()) &&
            check_correct(ui->textEdit_5->toPlainText().toStdString()) &&
            check_correct(ui->textEdit_6->toPlainText().toStdString()) == 1);
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
        RomanFraction fr1(ui->textEdit->toPlainText().toStdString(),
                          ui->textEdit_2->toPlainText().toStdString());
        RomanFraction fr2(ui->textEdit_5->toPlainText().toStdString(),
                          ui->textEdit_6->toPlainText().toStdString());
        RomanFraction fr3 = fr1 + fr2;
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
        last_clicked = 1;
    } else{
        error();
    }
}

void MainWindow::on_pushButton_2_clicked(){
    if (check_correct_input()){
        RomanFraction fr1(ui->textEdit->toPlainText().toStdString(),
                          ui->textEdit_2->toPlainText().toStdString());
        RomanFraction fr2(ui->textEdit_5->toPlainText().toStdString(),
                          ui->textEdit_6->toPlainText().toStdString());
        RomanFraction fr3 = fr1 - fr2;
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
        last_clicked = 2;
    } else{
        error();
    }
}

void MainWindow::on_pushButton_3_clicked(){
    if (check_correct_input()){
        RomanFraction fr1(ui->textEdit->toPlainText().toStdString(),
                          ui->textEdit_2->toPlainText().toStdString());
        RomanFraction fr2(ui->textEdit_5->toPlainText().toStdString(),
                          ui->textEdit_6->toPlainText().toStdString());
        RomanFraction fr3 = fr1 * fr2;
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
        last_clicked = 3;
    } else{
        error();
    }
}

void MainWindow::on_pushButton_4_clicked(){
    if (check_correct_input()){
        RomanFraction fr1(ui->textEdit->toPlainText().toStdString(),
                          ui->textEdit_2->toPlainText().toStdString());
        RomanFraction fr2(ui->textEdit_5->toPlainText().toStdString(),
                          ui->textEdit_6->toPlainText().toStdString());
        RomanFraction fr3 = fr1 / fr2;
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
        last_clicked = 4;
    } else {
        error();
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1){
    red = arg1;
    checkbox_detect();
}

void MainWindow::on_checkBox_2_stateChanged(int arg1){
    normal = arg1;
    checkbox_detect();
}

void MainWindow::checkbox_detect(){
    switch (last_clicked){
    case 1: on_pushButton_clicked();
        break;
    case 2: on_pushButton_2_clicked();
        break;
    case 3: on_pushButton_3_clicked();
        break;
    case 4: on_pushButton_4_clicked();
        break;
    default: break;
    }
}
