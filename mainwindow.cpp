#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "Roman.h"
#include <regex>

bool is_checked = false;
bool is_checked2 = false;

int last_clicked = 0;

int check_correct (const string &text){
    string pattern = "^-?M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})";
    if (text == "") return 0;
    regex roman_fraction(pattern);
    if (regex_match(text, roman_fraction)) return 1;
    return 0;
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
        unique_ptr <RomanFraction> fr1(new RomanFraction(ui->textEdit->toPlainText().toStdString(),
                          ui->textEdit_2->toPlainText().toStdString()));
        unique_ptr <RomanFraction> fr2(new RomanFraction(ui->textEdit_5->toPlainText().toStdString(),
                          ui->textEdit_6->toPlainText().toStdString()));
        last_clicked = 1;
        RomanFraction fr3 = *fr1 + *fr2;
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
    } else{
        QMessageBox::critical(this, "ВНИМАНИЕ!", "Ошибка при вводе дробей!");
    }
}

void MainWindow::on_pushButton_2_clicked(){
    if (check_correct_input()){
        unique_ptr <RomanFraction> fr1(new RomanFraction(ui->textEdit->toPlainText().toStdString(),
                                                             ui->textEdit_2->toPlainText().toStdString()));
        unique_ptr <RomanFraction> fr2(new RomanFraction(ui->textEdit_5->toPlainText().toStdString(),
                                                             ui->textEdit_6->toPlainText().toStdString()));
        RomanFraction fr3 = *fr1 - *fr2;
        last_clicked = 2;
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
    } else{
        QMessageBox::critical(this, "ВНИМАНИЕ!", "Ошибка при вводе дробей!");
    }
}

void MainWindow::on_pushButton_3_clicked(){
    if (check_correct_input()){
        unique_ptr <RomanFraction> fr1(new RomanFraction(ui->textEdit->toPlainText().toStdString(),
                                                        ui->textEdit_2->toPlainText().toStdString()));
        unique_ptr <RomanFraction> fr2(new RomanFraction(ui->textEdit_5->toPlainText().toStdString(),
                                                        ui->textEdit_6->toPlainText().toStdString()));
        RomanFraction fr3 = *fr1 * *fr2;
        last_clicked = 3;
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
    } else{
        QMessageBox::critical(this, "ВНИМАНИЕ!", "Ошибка при вводе дробей!");
    }
}

void MainWindow::on_pushButton_4_clicked(){
    if (check_correct_input()){
        unique_ptr <RomanFraction> fr1(new RomanFraction(ui->textEdit->toPlainText().toStdString(),
                                                        ui->textEdit_2->toPlainText().toStdString()));
        unique_ptr <RomanFraction> fr2(new RomanFraction(ui->textEdit_5->toPlainText().toStdString(),
                                                        ui->textEdit_6->toPlainText().toStdString()));
        RomanFraction fr3 = *fr1 / *fr2;
        last_clicked = 4;
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
    } else{
        QMessageBox::critical(this, "ВНИМАНИЕ!", "Ошибка при вводе дробей!");
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1){
    is_checked = arg1;
    checkbox_detect();
}

void MainWindow::on_checkBox_2_stateChanged(int arg1){
    is_checked2 = arg1;
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
    }
}
