
#include "gen-cpp/Example.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <iostream>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class ExampleHandler : virtual public ExampleIf {
public:
    ExampleHandler() {
        // Your initialization goes here
    }

    void ping() {
        // Your implementation goes here
        printf("ping was called by client\n");
    }

    int32_t add(const int32_t a, const int32_t b) {
        // Your implementation goes here
        printf("\"add\" was called by client\n");
        return a + b;
    }

};

int main(int argc, char **argv) {
    const int port = 9090;
    ::std::shared_ptr<ExampleHandler> handler(new ExampleHandler());
    ::std::shared_ptr<TProcessor> processor(new ExampleProcessor(handler));
    ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();
    return 0;
}

