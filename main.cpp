/*
Copyright 2023 Jankie

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.  
*/

#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "Usage:\n";
        std::cout << "    tcping [target address] [timeout] [packet size]\n";
        std::cout << "\n";
        std::cout << "Options:\n";
        std::cout << "    Target Address: The IP address or domain name you are requesting\n";
        std::cout << "    Timeout: Indicates that the packet is discarded after the timeout period. The default value is 20000 ms\n";
        std::cout << "    Packet size: The size of the packet sent once. The default value is 32 bytes\n";
        std::cout << "\n";
        return 0;
    }

    // Parse command line arguments
    std::string targetAddress = argv[1];
    int timeout = (argc > 2) ? std::stoi(argv[2]) : 20000;
    int packetSize = (argc > 3) ? std::stoi(argv[3]) : 32;

    try {
        io_service ioService;
        ip::tcp::socket socket(ioService);
        ip::tcp::resolver resolver(ioService);
        ip::tcp::resolver::query query(targetAddress, "");

        // Resolve the target address
        ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);

        // Connect to the target address
        boost::asio::connect(socket, endpointIterator);

        // Set the send and receive buffer sizes
        socket.set_option(ip::tcp::socket::send_buffer_size(packetSize));
        socket.set_option(ip::tcp::socket::receive_buffer_size(packetSize));

        // Create the send and receive buffers
        std::vector<char> sendBuffer(packetSize, 'A');
        std::vector<char> receiveBuffer(packetSize);

        int packetsSent = 0;
        int packetsReceived = 0;

        for (int i = 0; i < 4; ++i) {
            ++packetsSent;

            // Start the timer
            boost::asio::steady_timer timer(ioService);
            timer.expires_from_now(std::chrono::milliseconds(timeout));

            // Send the packet
            boost::system::error_code sendError;
            boost::asio::write(socket, boost::asio::buffer(sendBuffer), sendError);

            if (!sendError) {
                // Receive the response packet
                boost::system::error_code receiveError;
                boost::asio::read(socket, boost::asio::buffer(receiveBuffer), receiveError);

                if (!receiveError) {
                    ++packetsReceived;
                    std::cout << "Reply from " << targetAddress << ": bytes=" << packetSize << std::endl;
                } else {
                    std::cout << "Error receiving response." << std::endl;
                }
            } else {
                std::cout << "Error sending packet: " << sendError.message() << std::endl;
            }
        }

        socket.close();

        std::cout << "\nPing statistics for " << targetAddress << ":" << std::endl;
        std::cout << "    Packets: Sent = " << packetsSent << ", Received = " << packetsReceived << ", Lost = " << (packetsSent - packetsReceived) << " (" << ((packetsSent - packetsReceived) * 100 / packetsSent) << "% loss)" << std::endl;

    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}