#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "invisible_button.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_m_button_1_player_clicked();

    void on_m_button_2_players_clicked();

    void on_m_button_start_return_clicked();

    void on_m_button_start_game_clicked();

    void on_m_pushButton_1_clicked();

    void on_m_pushButton_2_clicked();

    void on_m_pushButton_3_clicked();

    void on_m_pushButton_4_clicked();

    void on_m_pushButton_5_clicked();

    void on_m_pushButton_6_clicked();

    void on_m_pushButton_7_clicked();

    void on_m_pushButton_8_clicked();

    void on_m_pushButton_9_clicked();


    void on_m_button_start_return_2_clicked();

private:
    void pushButton_clicked(int cell);
    void reset_game();
    Ui::MainWindow *ui;
    QPushButton* m_cells[9];
    uint8_t m_turn;
};
#endif // MAINWINDOW_H
