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