#pragma once
//#include "chessplayer.h"
#include "global.h"
#include "chessboard.h"
#include "asyncaiplayer.h"

#include <memory>
#include <boost/asio/io_service.hpp>
#include <functional>

using namespace std;
using namespace boost::asio;

class AsyncGame
{
private:
    shared_ptr<io_service> service;
    shared_ptr<AsyncAiPlayer> player1;
    shared_ptr<AsyncAiPlayer> player2;
    ChessBoard board;
    function<void(AsyncPlayer::EndStatus)> _end_game_handler;
protected:
    void onWhiteMove(const Move& move);
    void onBlackMove(const Move& move);
public:
    AsyncGame(shared_ptr<io_service> service, shared_ptr<AsyncAiPlayer> player1, shared_ptr<AsyncAiPlayer> player2);
    void start(function<void(AsyncPlayer::EndStatus)> end_game_handler);
};