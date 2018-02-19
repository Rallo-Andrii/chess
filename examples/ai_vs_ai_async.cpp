#include "asyncgame.h"
#include "asyncaiplayer.h"
#include <thread>
#include <memory>

using namespace std;
using namespace boost::asio;
int main()
{
    auto service = std::make_shared<io_service>();
    thread threads[5];


    shared_ptr<AsyncAiPlayer> players[2] = {make_shared<AsyncAiPlayer>(WHITE, 1), make_shared<AsyncAiPlayer>(BLACK, 1)};
    AsyncGame game(service, players[0], players[1]);

    game.start([service](AsyncPlayer::EndStatus end_status) {
        switch (end_status) {
        case AsyncPlayer::WHITE_WIN:
            cout << "White win" << endl;
            break;
        case AsyncPlayer::DRAW:
            cout << "A draw" << endl;
            break;
        case AsyncPlayer::WHITE_LOOSE:
            cout << "White loose" << endl;
            break;
        }
        service->stop();
    });
  
    for (thread & thrd : threads) {
        thrd = thread([service]() {
            service->run();
        });
    }

    for (thread & thrd : threads) {
        thrd.join();
    }

    getchar();
    return 0;
}
