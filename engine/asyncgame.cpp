#include "asyncgame.h"
#include <boost/asio/io_service.hpp>
#include <boost/asio/strand.hpp>
#include <boost/bind.hpp>
#include <type_traits>

using namespace std;
using namespace boost::asio;

AsyncGame::AsyncGame(shared_ptr<io_service> service, shared_ptr<AsyncPlayer> player1, shared_ptr<AsyncPlayer> player2) :
    service(service), player1(player1), player2(player2)
{
    auto strand = make_shared<boost::asio::io_service::strand>(*service);
    player1->setStrand(strand);
    player2->setStrand(strand);   
}

AsyncGame::EndStatus AsyncGame::getStatus()
{
    int color = board.next_move_color;
    ChessPlayer::Status status = board.getPlayerStatus(color);
    if (status == ChessPlayer::Normal || status == ChessPlayer::InCheck)
    {
        return NONE;
    }
    else if (status == ChessPlayer::Checkmate && color == WHITE )
    {
        return WHITE_LOOSE;
    }
    else if (status == ChessPlayer::Stalemate || status == ChessPlayer::Draw)
    {
        return DRAW;
    }
    else if (status == ChessPlayer::Checkmate && color == BLACK )
    {
        return WHITE_WIN;
    }

    return NONE;
}

void AsyncGame::onMove(const Move& move)
{
    board.move(move);
    moves.push_back(move);
    player2->asyncShowMove(board,  moves.back() , boost::bind(&AsyncGame::onShowMove, this));
}

void AsyncGame::onShowMove()
{
    board.print(moves.back());

    EndStatus st = getStatus();
    if (st == EndStatus::NONE)
    {
        std::swap(player1, player2);
        AsyncPlayer::MoveReadyHandler mrh = boost::bind(&AsyncGame::onMove, this, _1);
        player2->asyncGetNext(board, mrh );
    }
    else
    {
        auto end_game = boost::bind(_end_game_handler, st);
        player1->getStrand()->post(end_game);
    }
}

void AsyncGame::start(function<void(AsyncGame::EndStatus)> end_game_handler)
{
    _end_game_handler = end_game_handler;

    player1->asyncPrepare(board, [](){});
    player2->asyncPrepare(board, [](){});

    board.initDefaultSetup();

    AsyncPlayer::MoveReadyHandler mrh = boost::bind(&AsyncGame::onMove, this, _1);
    player1->asyncGetNext(board, mrh );
}
