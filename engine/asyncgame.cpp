#include "asyncgame.h"
#include <boost/asio/io_service.hpp>
#include <boost/asio/strand.hpp>
#include <boost/bind.hpp>
#include <type_traits>

using namespace std;
using namespace boost::asio;

AsyncGame::AsyncGame(shared_ptr<io_service> service, shared_ptr<AsyncAiPlayer> player1, shared_ptr<AsyncAiPlayer> player2) :
    service(service), player1(player1), player2(player2)
{
    auto strand = make_shared<boost::asio::io_service::strand>(*service);
    player1->setStrand(strand);
    player2->setStrand(strand);   
    AsyncPlayer::EndStatus endStatus; 
}

void AsyncGame::onWhiteMove(const Move& move)
{
    board.move(move);
    Move move1 = move;
    player2->showMove(board, move1);
    board.print(move1);

    ChessPlayer::Status status = board.getPlayerStatus(player2->getColor());

    if (status == ChessPlayer::Normal || status == ChessPlayer::InCheck)
    {
        AsyncPlayer::MoveReadyHandler mrh = boost::bind(&AsyncGame::onBlackMove, this, _1);
        player2->asyncGetNext(board, mrh );
    }
    else
    {
        AsyncPlayer::EndStatus st;
        switch(status)
        {
            case ChessPlayer::Checkmate:
                st = AsyncPlayer::EndStatus::WHITE_WIN;
            case ChessPlayer::Stalemate:
            case ChessPlayer::Draw:
                st = AsyncPlayer::EndStatus::DRAW;
            default:
                break;
        }
        auto end_game = boost::bind(_end_game_handler, st);
        player1->getStrand()->post(end_game);
    }
}
void AsyncGame::onBlackMove(const Move& move)
{
    board.move(move);
    Move move1 = move;
    player1->showMove(board, move1);
    board.print(move1);

    ChessPlayer::Status status = board.getPlayerStatus(player1->getColor());

    if (status == ChessPlayer::Normal || status == ChessPlayer::InCheck)
    {
        AsyncPlayer::MoveReadyHandler mrh = boost::bind(&AsyncGame::onWhiteMove, this, _1);
        player1->asyncGetNext(board, mrh);
    }
    else
    {
        AsyncPlayer::EndStatus st;
        switch(status)
        {
            case ChessPlayer::Checkmate:
                st = AsyncPlayer::EndStatus::WHITE_LOOSE;
                break;
            case ChessPlayer::Stalemate:
            case ChessPlayer::Draw:
                st = AsyncPlayer::EndStatus::DRAW;
            default:
                break;
        }
        auto end_game = boost::bind(_end_game_handler, st);
        player1->getStrand()->post(end_game);
    }
}

void AsyncGame::start(function<void(AsyncPlayer::EndStatus)> end_game_handler)
{
    _end_game_handler = end_game_handler;
    board.initDefaultSetup();
    AsyncPlayer::MoveReadyHandler mrh = boost::bind(&AsyncGame::onWhiteMove, this, _1);
    player1->asyncGetNext(board, mrh );
}
