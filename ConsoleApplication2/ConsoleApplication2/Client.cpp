#include <stdlib.h>
#include "connectionHandler.h"
#include "InputReader.h"
#include "EncoderDecoder.h"
#include "Listener.h"
#include <thread>
using namespace std;

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
int main(int argc, char* argv[]) {
         
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1]; // int port = 7777;
    short port = atoi(argv[2]); // std::string host = "127.0.0.1";

    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

    std::vector<string>* sendList = new vector<string>;
    std::mutex mutex;
    InputReader inputReader(sendList, mutex);
    std::thread th1(&InputReader::run, &inputReader);
    EncoderDecoder encdec;

    Listener listener(&connectionHandler);
    std::thread th2(&Listener::run, &listener);

    while (1) {
        string line = "";
        stringstream msg;
        mutex.lock();
        if (sendList->size() != 0) {
            line = sendList->at(0);
            sendList->erase(sendList->begin());
        }
        mutex.unlock();

        if (line != "") {
            char encodedLine[1024];
            int len = encdec.encode(line, encodedLine);

            if (!connectionHandler.sendBytes(encodedLine, len)) {
                msg << "Disconnected. Exiting...\n" << std::endl;
                cout << msg.str();
                break;
            }
            cout << msg.str();
        }

        if (listener.isTerminate()) {
            break;
        }
        if (connectionHandler.checkIfError) {
            inputReader.checkIfError = true;
        }
    }    
    inputReader.Terminate();
    delete sendList;
    th1.join();    
    th2.join();

    return 0;
}

