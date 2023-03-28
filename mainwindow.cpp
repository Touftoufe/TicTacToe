#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->m_main_menu->setStyleSheet(QString::fromUtf8(".QFrame {background-image: url(:/img/main_menu.jpg);}"));
    ui->m_1_player->setStyleSheet(QString::fromUtf8(".invisible_button_c {background-color: transparent; border: none;}"));
    ui->m_2_players->setStyleSheet(QString::fromUtf8(".invisible_button_c {background-color: transparent; border: none;}"));
    ui->m_1_player_sel->setHidden(true);
    ui->m_2_players_sel->setHidden(true);
    ui->m_1_player->set_selector(ui->m_1_player_sel);
    ui->m_2_players->set_selector(ui->m_2_players_sel);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_m_1_player_clicked()
{

}


void MainWindow::on_m_2_players_clicked()
{

}
