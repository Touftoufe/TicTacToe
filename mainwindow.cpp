#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRegularExpressionValidator>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_turn(0)
{
    ui->setupUi(this);

    m_cells[0] = ui->m_pushButton_1;
    m_cells[1] = ui->m_pushButton_2;
    m_cells[2] = ui->m_pushButton_3;
    m_cells[3] = ui->m_pushButton_4;
    m_cells[4] = ui->m_pushButton_5;
    m_cells[5] = ui->m_pushButton_6;
    m_cells[6] = ui->m_pushButton_7;
    m_cells[7] = ui->m_pushButton_8;
    m_cells[8] = ui->m_pushButton_9;

    ui->m_frame_main_menu->setStyleSheet(QString::fromUtf8(".QFrame {background-image: url(:/img/main_menu.jpg);}"));
    ui->m_button_1_player->setStyleSheet(QString::fromUtf8(".invisible_button_c {background: transparent; border: none; outline: none;}"));
    ui->m_button_2_players->setStyleSheet(QString::fromUtf8(".invisible_button_c {background: transparent; border: none; outline: none;}"));
    ui->m_button_start_game->setStyleSheet(QString::fromUtf8(".invisible_button_c {background: transparent; border: none; outline: none;}"));
    ui->m_label_enter_names->setAttribute(Qt::WA_TranslucentBackground);
    ui->m_label_player_1_name->setAttribute(Qt::WA_TranslucentBackground);
    ui->m_label_player_2_name->setAttribute(Qt::WA_TranslucentBackground);
    ui->m_label_rounds->setAttribute(Qt::WA_TranslucentBackground);
    ui->m_label_start_game->setAttribute(Qt::WA_TranslucentBackground);
    QValidator *v = new QRegularExpressionValidator(QRegularExpression("[a-zA-Z ]*"), this);
    ui->m_lineEdit_player_1_name->setValidator(v);
    ui->m_lineEdit_player_2_name->setValidator(v);
    QValidator *v2 = new QRegularExpressionValidator(QRegularExpression("[1-9][0-9]*"), this);
    ui->m_lineEdit_rounds->setValidator(v2);
    ui->m_frame_names_menu->setHidden(true);
    ui->m_frame_game->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushButton_clicked(int cell)
{
    QString icons[] = {"round", "cross"};
    m_cells[cell - 1]->setStyleSheet((QString::fromUtf8("background: transparent; border: none; outline: none; background-image: url(:/img/%1%2.png); background-repeat: no-repeat;"
                                                        "background-position: center center;")).arg(icons[m_turn], QString::number(QRandomGenerator::global()->bounded(1,5))));
    m_cells[cell - 1]->setEnabled(false);
    m_turn = !m_turn;
}

void MainWindow::reset_game()
{
    for(int i = 0; i < 9; ++i)
    {
        m_cells[i]->setStyleSheet(QString::fromUtf8("background: transparent; border: none; outline: none;"));
        m_cells[i]->setEnabled(true);
    }
    m_turn = 0;
}

void MainWindow::on_m_button_1_player_clicked()
{
    ui->m_lineEdit_player_1_name->setText("");
    ui->m_lineEdit_rounds->setText("");
    ui->m_label_player_2_name->setText("IA Name");
    ui->m_lineEdit_player_2_name->setText("Why do you care looser");
    ui->m_lineEdit_player_2_name->setReadOnly(true);
    ui->m_frame_names_menu->setHidden(false);
}


void MainWindow::on_m_button_2_players_clicked()
{
    ui->m_lineEdit_player_1_name->setText("");
    ui->m_lineEdit_rounds->setText("");
    ui->m_label_player_2_name->setText("Player II");
    ui->m_lineEdit_player_2_name->setText("");
    ui->m_lineEdit_player_2_name->setReadOnly(false);
    ui->m_frame_names_menu->setHidden(false);
}


void MainWindow::on_m_button_start_return_clicked()
{
    ui->m_frame_names_menu->setHidden(true);
}

void MainWindow::on_m_button_start_return_2_clicked()
{
    ui->m_frame_game->setHidden(true);
}

void MainWindow::on_m_button_start_game_clicked()
{
    ui->m_frame_game->setHidden(false);
    reset_game();
}

void MainWindow::on_m_pushButton_1_clicked()
{
    pushButton_clicked(1);
}

void MainWindow::on_m_pushButton_2_clicked()
{
    pushButton_clicked(2);
}

void MainWindow::on_m_pushButton_3_clicked()
{
    pushButton_clicked(3);
}

void MainWindow::on_m_pushButton_4_clicked()
{
    pushButton_clicked(4);
}

void MainWindow::on_m_pushButton_5_clicked()
{
    pushButton_clicked(5);
}

void MainWindow::on_m_pushButton_6_clicked()
{
    pushButton_clicked(6);
}

void MainWindow::on_m_pushButton_7_clicked()
{
    pushButton_clicked(7);
}

void MainWindow::on_m_pushButton_8_clicked()
{
    pushButton_clicked(8);
}

void MainWindow::on_m_pushButton_9_clicked()
{
    pushButton_clicked(9);
}


