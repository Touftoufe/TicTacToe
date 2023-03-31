#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <functional>
#include <QMainWindow>
#include "invisible_button.h"
#include "TicTacToe.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class TicTacToe_GUI_c: public TicTacToe_c
{
public:
    TicTacToe_GUI_c(std::string player1_name, std::string player2_name, uint16_t rounds, bool multiplayer)
        : TicTacToe_c(player1_name, player2_name, rounds, multiplayer)
    {

    }

    void increment_score(uint8_t player)
    {
        if(player == 0) m_player1_score++;
        else if(player == 1) m_player2_score++;
    }

    void set_first_player(uint8_t player)
    {
        m_first_player = player;
    }

    void set_rounds(uint16_t rounds)
    {
        m_rounds = rounds;
    }

    uint8_t get_first_player() const
    {
        return m_first_player;
    }

    virtual void start() override
    {

    }
protected:
    virtual int wait_for_player1() override
    {
        return 0xFF;
    }

    virtual int wait_for_player2() override
    {
        return 0xFF;
    }
};


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

    void update_game();

    void round_ended(int);

signals:
    void player_played();
    void end_of_round(int);

private:
    void pushButton_clicked(int cell);
    void reset_game();
    Ui::MainWindow *ui;
    QPushButton* m_cells[9];
    uint8_t m_turn;
    bool m_multiplayer;
    TicTacToe_GUI_c *m_game;
};
#endif // MAINWINDOW_H
