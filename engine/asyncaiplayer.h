#pragma once

#include "asyncplayer.h"
#include "aiplayer.h"

class AsyncAiPlayer : public AsyncPlayer, protected AIPlayer
{
public:
    AsyncAiPlayer(int color, int search_depth);
    virtual ~AsyncAiPlayer();

    virtual void asyncPrepare(const ChessBoard & board, ReadyHandler handler) override;
    virtual void asyncGetNext(const ChessBoard & board, MoveReadyHandler handler) override;
    virtual void asyncShowMove(const ChessBoard & board, const Move & move, ReadyHandler handler) override;
    virtual void asyncShowResult(const ChessBoard & board, EndStatus status, ReadyHandler handler) override;

    /**
     * @brief cancel -- cancels any of the async operation
     */
    virtual void cancel() override;

    
};

