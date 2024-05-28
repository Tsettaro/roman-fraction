#include "../include/mainwindow.h"
#include "../include/Roman.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <regex>

bool is_reduced = false;
bool normal = false;

int last_clicked = 0;

int check_correct (const string &text){
    // Regular expression pattern to match valid Roman numerals
    const string pattern = "-?M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})";

    if (text.empty()) return 0;
    regex roman_fraction("^" + pattern + "/" + pattern + "$");
    if (regex_match(text, roman_fraction)) return 1;
    return 0;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::error(){
    QMessageBox::critical(this, "ВНИМАНИЕ!", "Ошибка при вводе дробей!");
}

int MainWindow::check_correct_input(){
    return (check_correct(ui->lineEdit->text().toStdString()) &&
            check_correct(ui->lineEdit_2->text().toStdString()) == 1);
}

void MainWindow::on_plus_clicked(){
    if (check_correct_input()){
        RomanFraction fr1(ui->lineEdit->text().toStdString());
        RomanFraction fr2(ui->lineEdit_2->text().toStdString());

        RomanFraction fr3 = fr1 + fr2;
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
        last_clicked = 1;
    } else{
        error();
    }
}

void MainWindow::on_minus_clicked(){
    if (check_correct_input()){
        RomanFraction fr1(ui->lineEdit->text().toStdString());
        RomanFraction fr2(ui->lineEdit_2->text().toStdString());

        RomanFraction fr3 = fr1 - fr2;
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
        last_clicked = 2;
    } else{
        error();
    }
}

void MainWindow::on_multi_clicked(){
    if (check_correct_input()){
        RomanFraction fr1(ui->lineEdit->text().toStdString());
        RomanFraction fr2(ui->lineEdit_2->text().toStdString());

        RomanFraction fr3 = fr1 * fr2;
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
        last_clicked = 3;
    } else{
        error();
    }
}

void MainWindow::on_divide_clicked(){
    if (check_correct_input()){
        RomanFraction fr1(ui->lineEdit->text().toStdString());
        RomanFraction fr2(ui->lineEdit_2->text().toStdString());

        RomanFraction fr3 = fr1 / fr2;
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
        last_clicked = 4;
    } else {
        error();
    }
}

void MainWindow::on_difference_clicked(){
    if (check_correct_input()){
        RomanFraction fr1(ui->lineEdit->text().toStdString());
        RomanFraction fr2(ui->lineEdit_2->text().toStdString());

        if (fr1 > fr2){
            ui->label_3->setText("First fr > second");
        } else if (fr1 < fr2){
            ui->label_3->setText("First fr < second");
        } else {
            ui->label_3->setText("Both");
        }
        last_clicked = 0;
    } else {
        error();
    }
}
void MainWindow::on_standart_form_stateChanged(int arg1){
    normal = arg1;
    checkbox_detect();
}

void MainWindow::on_checkBox_divide_stateChanged(int arg1){
    is_reduced = arg1;
    checkbox_detect();
}

void MainWindow::checkbox_detect(){
    switch (last_clicked){
    case 1: on_plus_clicked();
        break;
    case 2: on_minus_clicked();
        break;
    case 3: on_multi_clicked();
        break;
    case 4: on_divide_clicked();
        break;
    default: break;
    }
}
