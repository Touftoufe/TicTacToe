#include <stdint.h>
#include <iostream>
#include <array>
#include <string>
#include <tuple>

using cells_t = std::array<uint8_t, 9>; 

class TicTacToe_c
{
public:
    using check_list_t = std::array<std::tuple<uint8_t, uint8_t, uint8_t>, 8>;
    
    TicTacToe_c(std::string player1_name, std::string player2_name, uint16_t rounds, bool multiplayer);
    void set_cell(uint8_t player, uint8_t cell);
    void reset();
    bool check() const;
    uint16_t get_score(uint8_t player) const;
    uint16_t get_rounds() const;
    const cells_t& get_cells() const;
    uint8_t get_game_state() const;
    virtual void start();
    int AI_play();
    int examine_board(int value) const;

protected:
    int console_multiplayer(int player);
    int find_cell(int index) const;
    virtual int wait_for_player1(){return console_multiplayer(0);}
    virtual int wait_for_player2(){return console_multiplayer(1);}

    cells_t m_cells;
    std::string m_player1_name;
    std::string m_player2_name;
    uint16_t m_player1_score;
    uint16_t m_player2_score;
    uint8_t m_first_player;
    uint16_t m_rounds;
    bool m_multiplayer;
    uint8_t m_current_game_state;
    bool m_stop_game;
    const check_list_t m_check_list;
};
