#pragma once

#include "asyncplayer.h"
#include "aiplayer.h"

class AsyncServerAiPlayer : public AsyncPlayer, /*protected*/ public AIPlayer
{
public:
    AsyncServerAiPlayer(int color, int search_depth);
    virtual ~AsyncServerAiPlayer();

    virtual void asyncPrepare(const ChessBoard & board, ReadyHandler handler) override;
    virtual void asyncGetNext(const ChessBoard & board, MoveReadyHandler handler) override;
    virtual void asyncShowMove(const ChessBoard & board, Move & move, ReadyHandler handler) override;
    //virtual void asyncShowResult(const ChessBoard & board, EndStatus status, ReadyHandler handler) override;

    /**
     * @brief cancel -- cancels any of the async operation
     */
    virtual void cancel() override;

    
};