#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "Roman.h"
#include <regex>

bool is_checked = false;
bool is_checked2 = false;

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
        ui->label_3->setText(QString::fromStdString(fr3.fraction()));
    } else{
        QMessageBox::critical(this, "ВНИМАНИЕ!", "Ошибка при вводе дробей!");
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1){
    is_checked = arg1;
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    is_checked2 = arg1;
}

