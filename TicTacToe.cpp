#include <algorithm>
#include <iterator>
#include "TicTacToe.h"

using namespace std;

TicTacToe_c::TicTacToe_c(string player1_name, string player2_name, uint16_t rounds, bool multiplayer)
    : m_player1_name(player1_name), 
      m_player2_name(player2_name),
      m_player1_score(0),
      m_player2_score(0),
      m_first_player(0),
      m_rounds(rounds),
      m_multiplayer(multiplayer),
      m_current_game_state(9),
      m_stop_game(false),
      m_check_list({{
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {0, 3, 6},
            {1, 4, 7},
            {2, 5, 8},
            {0, 4, 8},
            {2, 4, 6}
        }})
{
    m_cells.fill(0);
}

void TicTacToe_c::set_cell(uint8_t player, uint8_t cell)
{
    m_cells[cell] = 1 + player * 4;
    m_current_game_state--;
}

void TicTacToe_c::reset()
{
    m_cells.fill(0);
    m_current_game_state = 9;
}

bool TicTacToe_c::check() const
{
    return ((m_cells[0] != 0) && (m_cells[0] == m_cells[1]) && (m_cells[0] == m_cells[2]))
        || ((m_cells[3] != 0) && (m_cells[3] == m_cells[4]) && (m_cells[3] == m_cells[5]))
        || ((m_cells[6] != 0) && (m_cells[6] == m_cells[7]) && (m_cells[6] == m_cells[8]))
        || ((m_cells[0] != 0) && (m_cells[0] == m_cells[3]) && (m_cells[0] == m_cells[6]))
        || ((m_cells[1] != 0) && (m_cells[1] == m_cells[4]) && (m_cells[1] == m_cells[7]))
        || ((m_cells[2] != 0) && (m_cells[2] == m_cells[5]) && (m_cells[2] == m_cells[8]))
        || ((m_cells[0] != 0) && (m_cells[0] == m_cells[4]) && (m_cells[0] == m_cells[8]))
        || ((m_cells[2] != 0) && (m_cells[2] == m_cells[4]) && (m_cells[2] == m_cells[6]));
}

uint16_t TicTacToe_c::get_score(uint8_t player) const
{
    if(player == 0) return m_player1_score;
    else if(player == 1) return m_player2_score;
    else return 0;
}

uint16_t TicTacToe_c::get_rounds() const
{
    return m_rounds;
}

const cells_t& TicTacToe_c::get_cells() const
{
    return m_cells;
}

uint8_t TicTacToe_c::get_game_state() const
{
    return m_current_game_state;
}

int TicTacToe_c::find_cell(int index) const
{
    const cells_t &cells = get_cells();
    uint8_t e0 = std::get<0>(m_check_list[index]);
    uint8_t e1 = std::get<1>(m_check_list[index]);
    uint8_t e2 = std::get<2>(m_check_list[index]);
    if(!cells[e0]) return e0;
    else if(!cells[e1]) return e1;
    else return e2;
}

int TicTacToe_c::examine_board(int value) const
{
    const cells_t &cells = get_cells();
    array<int, 8> result;
    for(int i = 0; i < 8; ++i)
    {
        uint8_t e0 = std::get<0>(m_check_list[i]);
        uint8_t e1 = std::get<1>(m_check_list[i]);
        uint8_t e2 = std::get<2>(m_check_list[i]);
        result[i] = cells[e0] + cells[e1] + cells[e2];
    }

    auto *found = std::find(std::begin(result), std::end(result), value);
    if(found != std::end(result))
    {
        return find_cell(std::distance(begin(result), found));
    }
    else return 0xFF;
}

int TicTacToe_c::AI_play()
{
    int cell = 0xFF;
    const cells_t &cells = get_cells();
    if(get_game_state() == 9 || (get_game_state() == 8 && !cells[4]))
    {
        cell = 4;
    }
    else if(get_game_state() == 8 && cells[4])
    {
        cell = 0;
    }
    else
    {
        cell = examine_board(10);
        if(cell == 0xFF)
        {
            cell = examine_board(2);
            if(cell == 0xFF)
            {
                cell = examine_board(5);
                if(cell == 0xFF)
                {
                    for(int i = 0; i < 9; i++)
                    {
                        if(cells[i] == 0)
                        {
                            cell = i;
                            break;
                        }
                    }
                }
            }
        }
    }
    return cell;
    // std::cout << "X " << cell << endl;
}

void TicTacToe_c::start()
{
    while(m_rounds && !m_stop_game)
    {
        bool win = false;
        uint8_t player = m_first_player;
        while(get_game_state() && !m_stop_game && !win)
        {
            int cell = 0xFF;
            if(player == 0)
            {
                cell = wait_for_player1();
            }
            else
            {
                if(m_multiplayer)
                {
                    cell = wait_for_player2();
                }
                else
                {
                    cell = AI_play();
                }
            }
            set_cell(player, cell);
            player = !player;
            win = check();
        }
        if(win)
        {
            if(examine_board(15) != 0xFF)
            {
                m_player2_score++;
            }
            else if(examine_board(3) != 0xFF)
            {
                m_player1_score++;
            }
        }
        else if(get_game_state() == 0)
        {
                m_player1_score++;
                m_player2_score++;
        }
        m_first_player = !m_first_player;
        reset();
        m_rounds--;
        // std::cout << "SCORE:\nPlayer 1: " << m_player1_score << "\nPlayer 2: " << m_player2_score << endl;
        // std::cout << "Rounds left:" << m_rounds << endl;
    }
}

int TicTacToe_c::console_multiplayer(int player)
{
    int cell = 0xFF;
    cin >> cell;
    return cell;
}
