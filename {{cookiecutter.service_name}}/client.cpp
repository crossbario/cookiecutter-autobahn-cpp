#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <tuple>
#include <sstream>
#include <cstdlib>

#include <boost/asio.hpp>

#include <autobahn/autobahn.hpp>


typedef std::unordered_map<uint32_t, std::string> IntStringMap;


void log (const std::string& msg) {
    std::cerr << msg << " [thread " << boost::this_thread::get_id() << "]" << std::endl;
}

void on_topic1(const autobahn::wamp_event& event)
{
    std::cerr << "received event: " << event.number_of_arguments() << std::endl;
    IntStringMap m = event.argument<IntStringMap>(0);
    for (const auto& n : m ) {
        std::cout << n.first << ": " << n.second << std::endl;
    }
}


int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cerr << "Usage: callee <RawSocket IP> <RawSocket PORT>" << std::endl;
        return -1;
    }

    try {
        log("starting program ..");

        boost::asio::io_service io;

        bool debug = false;

        boost::future<void> f1, f2, f3;

        auto endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(argv[1]), atoi(argv[2]));

        auto transport = std::make_shared<autobahn::wamp_tcp_transport>(io, endpoint, debug);

        auto session = std::make_shared<autobahn::wamp_session>(io, debug);

        transport->attach(std::static_pointer_cast<autobahn::wamp_transport_handler>(session));

        f1 = transport->connect().then([&](boost::future<void> connected) {

            connected.get();

            log("transport connected");

            f2 = session->start().then(boost::launch::deferred,
                                       [&](boost::future<void> started) {

                started.get();

                log("session started");

                f3 = session->join("realm1").then(boost::launch::deferred,
                                                  [&](boost::future<uint64_t> joined) {

                    joined.get();

                    log("joined realm");

                    boost::future<void> subscribe_future = session->subscribe(
                        "com.examples.subscriptions.topic1",
                        &on_topic1
                    ).then([&] (boost::future<autobahn::wamp_subscription> subscribed)
                        {
                            try {
                                std::cerr << "subscribed to topic: " << subscribed.get().id() << std::endl;
                            }
                            catch (const std::exception& e) {
                                std::cerr << e.what() << std::endl;
                                io.stop();
                                return;
                            }

                            IntStringMap m;
                            m[12] = "foo";
                            m[32] = "bar";
                            m[52] = "baz";
                            std::tuple<IntStringMap> arguments(m);
                            autobahn::wamp_publish_options wpo;
                            wpo.set_exclude_me(false);
                            session->publish("com.examples.subscriptions.topic1", arguments, wpo);
                            std::cerr << "event published" << std::endl;

                            // to exit cleanly, do something like this:
                            if (false) {
                                auto f5 = session->leave().then(
                                    boost::launch::deferred,
                                    [&](boost::future<std::string> reason) {
                                        log("session left");
                                        io.stop();
                                    });
                                f5.get();
                            }
                        }
                    );
                    });
                f3.get();
            });
            f2.get();
        });

        log("starting io service ..");
        io.run();
        log("stopped io service");
    }
    catch (const std::exception& e) {
        log(e.what());
        return -1;
    }

    return 0;
}
