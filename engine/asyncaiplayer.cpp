#include "asyncaiplayer.h"   
   
   
   
AsyncAiPlayer::AsyncAiPlayer(int color, int search_depth) : AsyncPlayer(), AIPlayer(color,search_depth)
{

}

AsyncAiPlayer::~AsyncAiPlayer()
{

}

void AsyncAiPlayer::asyncPrepare(const ChessBoard & board, ReadyHandler handler)
{

}

void AsyncAiPlayer::asyncGetNext(const ChessBoard & board, MoveReadyHandler handler)
{

}

void AsyncAiPlayer::asyncShowMove(const ChessBoard & board, const Move & move, ReadyHandler handler)
{

}

void AsyncAiPlayer::asyncShowResult(const ChessBoard & board, EndStatus status, ReadyHandler handler)
{

}

/**
 * @brief cancel -- cancels any of the asunc operation
 */
void AsyncAiPlayer::cancel()
{

}