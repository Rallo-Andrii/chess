#pragma once
//#include "chessplayer.h"
#include "global.h"
#include "chessboard.h"
#include "asyncaiplayer.h"

#include <memory>
#include <boost/asio/io_service.hpp>
#include <functional>
#include <list>

using namespace std;
using namespace boost::asio;

class AsyncGame
{
public:
    enum EndStatus {
        NONE = 0,
        WHITE_WIN,
        DRAW,
        WHITE_LOOSE
    };
private:
    shared_ptr<io_service> service;
    shared_ptr<AsyncPlayer> player1;
    shared_ptr<AsyncPlayer> player2;
    ChessBoard board;
    function<void(EndStatus)> _end_game_handler;
    list<Move> moves;
protected:
    //void onWhiteMove(const Move& move);
    //void onBlackMove(const Move& move);
    void onMove(const Move& move);
    void onShowMove();
public:
    AsyncGame(shared_ptr<io_service> service, shared_ptr<AsyncPlayer> player1, shared_ptr<AsyncPlayer> player2);
    void start(function<void(EndStatus)> end_game_handler);
    EndStatus getStatus();
};