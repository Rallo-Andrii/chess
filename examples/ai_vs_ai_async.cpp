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


    shared_ptr<AsyncPlayer> players[2] = {make_shared<AsyncAiPlayer>(WHITE, 1), make_shared<AsyncAiPlayer>(BLACK, 1)};
    AsyncGame game(service, players[0], players[1]);

    game.start([service](AsyncGame::EndStatus end_status) {
        switch (end_status) {
        case AsyncGame::WHITE_WIN:
            cout << "White win" << endl;
            break;
        case AsyncGame::DRAW:
            cout << "A draw" << endl;
            break;
        case AsyncGame::WHITE_LOOSE:
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
