#include <iostream>
#include "gen-cpp/Example.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>

int callRPCAdd(const int &_a, const int &_b);

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::std;

int main(){
    try {
        cout << "client received this result from Server: " << callRPCAdd(7, 8) << endl;

    } catch (TException &e) {
        cout << "error calling server with RPC: " << e.what() << endl;
    }
}

int callRPCAdd(const int &_a, const int &_b) {
    shared_ptr<TSocket> socket{new TSocket{"localhost", 9090}};
    shared_ptr<TTransport> transport{new TBufferedTransport{socket}};
    shared_ptr<TProtocol> protocol{new TBinaryProtocol{transport}};
    ExampleClient client{protocol};
    transport->open();

    // this calls the server RPC implementation via socket under the hood
    int result{client.add(_a, _b)};

    transport->close();

    return result;
}
