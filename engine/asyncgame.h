#pragma once
//#include "chessplayer.h"
#include <global.h>
#include "asyncaiplayer.h"

#include <memory>
#include <boost/asio/io_service.hpp>
#include <functional>

using namespace std;
using namespace boost::asio;

class AsyncGame
{
private:
    shared_ptr<io_service> io_ptr;
    shared_ptr<AsyncAiPlayer> player1;
    shared_ptr<AsyncAiPlayer> player2;
public:
    AsyncGame(shared_ptr<io_service> io_ptr, shared_ptr<AsyncAiPlayer> player1, shared_ptr<AsyncAiPlayer> player2);
};