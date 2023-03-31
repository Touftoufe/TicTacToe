#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRegularExpressionValidator>
#include <QRandomGenerator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_turn(0)
    , m_multiplayer(false)
    , m_game(nullptr)
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
    ui->m_label_player_1_score->setAttribute(Qt::WA_TranslucentBackground);
    ui->m_label_player_2_score->setAttribute(Qt::WA_TranslucentBackground);
    ui->m_label_player_1_score_2->setAttribute(Qt::WA_TranslucentBackground);
    ui->m_label_player_2_score_2->setAttribute(Qt::WA_TranslucentBackground);
    ui->m_label_rounds_left->setAttribute(Qt::WA_TranslucentBackground);
    QValidator *v = new QRegularExpressionValidator(QRegularExpression("[a-zA-Z ]*"), this);
    ui->m_lineEdit_player_1_name->setValidator(v);
    ui->m_lineEdit_player_2_name->setValidator(v);
    QValidator *v2 = new QRegularExpressionValidator(QRegularExpression("[1-9][0-9]*"), this);
    ui->m_lineEdit_rounds->setValidator(v2);
    ui->m_frame_names_menu->setHidden(true);
    ui->m_frame_game->setHidden(true);
    QObject::connect(this, &MainWindow::player_played, this, &MainWindow::update_game);
    QObject::connect(this, &MainWindow::end_of_round, this, &MainWindow::round_ended);

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

    if(m_game)
    {
        m_game->set_cell(m_turn, cell - 1);
    }
    m_turn = !m_turn;
    emit player_played();
}

void MainWindow::reset_game()
{
    for(int i = 0; i < 9; ++i)
    {
        m_cells[i]->setStyleSheet(QString::fromUtf8("background: transparent; border: none; outline: none;"));
        m_cells[i]->setEnabled(true);
    }

    if(m_game)
    {
        m_turn = !m_game->get_first_player();
        m_game->set_first_player(m_turn);
    }
}

void MainWindow::on_m_button_1_player_clicked()
{
    ui->m_lineEdit_player_1_name->setText("");
    ui->m_lineEdit_rounds->setText("1");
    ui->m_label_player_2_name->setText("IA Name");
    ui->m_lineEdit_player_2_name->setText("Why do you care looser");
    ui->m_lineEdit_player_2_name->setReadOnly(true);
    ui->m_frame_names_menu->setHidden(false);
    m_multiplayer = false;
}


void MainWindow::on_m_button_2_players_clicked()
{
    ui->m_lineEdit_player_1_name->setText("");
    ui->m_lineEdit_rounds->setText("1");
    ui->m_label_player_2_name->setText("Player II");
    ui->m_lineEdit_player_2_name->setText("");
    ui->m_lineEdit_player_2_name->setReadOnly(false);
    ui->m_frame_names_menu->setHidden(false);
    m_multiplayer = true;
}


void MainWindow::on_m_button_start_return_clicked()
{
    ui->m_frame_names_menu->setHidden(true);
}

void MainWindow::on_m_button_start_return_2_clicked()
{
    ui->m_frame_game->setHidden(true);
    if(m_game)
    {
        delete m_game;
        m_game = nullptr;
    }
}

void MainWindow::on_m_button_start_game_clicked()
{
    ui->m_frame_game->setHidden(false);
    reset_game();
    if(m_game)
    {
        delete m_game;
        m_game = nullptr;
    }
    ui->m_frame_player_1_winner->setHidden(true);
    ui->m_frame_player_2_winner->setHidden(true);

    QString player1_name = ui->m_lineEdit_player_1_name->text();
    if(player1_name.isEmpty()) player1_name = "Player I";
    QString player2_name = ui->m_lineEdit_player_2_name->text();
    if(player2_name.isEmpty()) player2_name = "Player II";
    ui->m_label_player_1_score->setText(player1_name);
    ui->m_label_player_2_score->setText(player2_name);
    ui->m_label_player_1_score_2->setText("");
    ui->m_label_player_2_score_2->setText("");

    auto f1 = ui->m_label_player_1_score->font();
    if(player1_name.size() > 14)
    {
        f1.setPixelSize(16);
    }
    else
    {
        f1.setPixelSize(19);
    }
    ui->m_label_player_1_score->setFont(f1);

    auto f2 = ui->m_label_player_2_score->font();
    if(player2_name.size() > 14)
    {
        f2.setPixelSize(16);
    }
    else
    {
        f2.setPixelSize(19);
    }
    ui->m_label_player_2_score->setFont(f2);

    bool conversion_ok = false;
    int rounds = ui->m_lineEdit_rounds->text().toInt(&conversion_ok);
    if(!conversion_ok) rounds = 1;
    ui->m_label_rounds_left->setText("Rounds left: " + QString::number(rounds));
    m_game = new TicTacToe_GUI_c(player1_name.toStdString(), player2_name.toStdString(), rounds, m_multiplayer);
    m_turn = m_game->get_first_player();
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

void MainWindow::update_game()
{
    uint16_t rounds_left = m_game->get_rounds();
    if(m_game)
    {
        if(rounds_left)
        {
            if(m_game->check() || !m_game->get_game_state())
            {
                int p1_wins = m_game->examine_board(3);
                int p2_wins = m_game->examine_board(15);

                if(p1_wins != 0xFF)
                {
                    m_game->increment_score(0);
                    ui->m_label_player_1_score_2->setText(ui->m_label_player_1_score_2->text() + "I ");
                    emit end_of_round(p1_wins);
                }
                else if(p2_wins != 0xFF)
                {
                    m_game->increment_score(1);
                    ui->m_label_player_2_score_2->setText(ui->m_label_player_2_score_2->text() + "I ");
                    emit end_of_round(p1_wins);
                }
                else
                {
                    m_game->increment_score(0);
                    m_game->increment_score(1);
                    ui->m_label_player_1_score_2->setText(ui->m_label_player_1_score_2->text() + "I ");
                    ui->m_label_player_2_score_2->setText(ui->m_label_player_2_score_2->text() + "I ");
                    emit end_of_round(0xFF);
                }
                m_game->reset();
                m_game->set_rounds(rounds_left - 1);
                ui->m_label_rounds_left->setText("Rounds left: " + QString::number(rounds_left - 1));
            }

            if(!m_multiplayer && m_turn)
            {
                m_cells[m_game->AI_play()]->click();
            }
        }
    }
}

void MainWindow::round_ended(int winner)
{
    if(m_game)
    {
        if(m_game->get_rounds() > 1)
        {
            reset_game();
        }
        else
        {
            for(int i = 0; i < 9; ++i)
            {
                m_cells[i]->setEnabled(false);
            }
            if(m_game->get_score(0) > m_game->get_score(1))
            {
                ui->m_frame_player_1_winner->setHidden(false);
            }
            else if(m_game->get_score(0) < m_game->get_score(1))
            {
                ui->m_frame_player_2_winner->setHidden(false);
            }

        }
    }
}
