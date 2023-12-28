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
#include "boost/asio.hpp"
using namespace boost::asio;

int main(int argc, char* argv[]){
    if(argc == 1){
        printf("TCPing 0.1.0\n");
        printf("Usage:\n");
        printf("tcping [target address] [timeout] [packet size]\n");
        printf("\n")
        printf("Target Address: The ip address or domain name you are requesting");
        printf("Timeout: indicates that the packet is discarded after the timeout period. The default value is 20000 ms")
        printf("Packet size: The size of the packet sent once. The default value is 32 bytes")
        printf("\n")
    }
    return 0;
}