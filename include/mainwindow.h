#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_plus_clicked();
    void on_minus_clicked();
    void on_multi_clicked();
    void on_divide_clicked();

    void on_standart_form_stateChanged(int arg1);
    void on_checkBox_divide_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    int check_correct_input();
    void checkbox_detect();
    void error();
};
#endif // MAINWINDOW_H
