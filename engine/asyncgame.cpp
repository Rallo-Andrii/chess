#include "asyncgame.h"

AsyncGame::AsyncGame(shared_ptr<io_service> io_ptr, shared_ptr<AsyncAiPlayer> player1, shared_ptr<AsyncAiPlayer> player2) :
    io_ptr(io_ptr), player1(player1), player2(player2)
{

}