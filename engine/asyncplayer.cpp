#include "asyncplayer.h"

AsyncPlayer::AsyncPlayer()
{

}

AsyncPlayer::~AsyncPlayer()
{

}

std::shared_ptr<boost::asio::io_service::strand> AsyncPlayer::getStrand() const
{
    return strand;
}

void AsyncPlayer::setStrand(const std::shared_ptr<boost::asio::io_service::strand> &value)
{
    strand = value;
}
