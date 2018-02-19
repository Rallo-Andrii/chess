#include "asyncaiplayer.h"   
#include "chessboard.h"   

#include <boost/bind.hpp>
#include <boost/asio/io_service.hpp>
   
   
AsyncAiPlayer::AsyncAiPlayer(int color, int search_depth) : AsyncPlayer(), AIPlayer(color,search_depth)
{

}

AsyncAiPlayer::~AsyncAiPlayer()
{

}

void AsyncAiPlayer::asyncPrepare(const ChessBoard & board, ReadyHandler handler)
{
    handler();
}

void AsyncAiPlayer::asyncGetNext(const ChessBoard & board, MoveReadyHandler handler)
{
    std::function <void()> find_next_move_async = [this, &board, handler]()
    {
        Move found_move;
        getMove(board, found_move);
        strand->post([found_move,handler](){handler(found_move);});
    };

    strand->post(find_next_move_async);
}

void AsyncAiPlayer::asyncShowMove(const ChessBoard & board, Move & move, ReadyHandler handler)
{
    std::function <void()> show_next_move_async = [this, &board, &move, handler]()
    {
        showMove(board, move);
        strand->post([handler](){handler();});
    };

    strand->post(show_next_move_async);
}

void AsyncAiPlayer::asyncShowResult(const ChessBoard & board, EndStatus status, ReadyHandler handler)
{
    handler();
}

/**
 * @brief cancel -- cancels any of the asunc operation
 */
void AsyncAiPlayer::cancel()
{

}