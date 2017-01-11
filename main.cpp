#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <pthread.h>

// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>

#include "AgentClass.h"
#include "defines.h"
#include "externs.h"

void printMenu(std::vector<std::string> commands);

AgentClass agentInst;

void *interactivePrint(void*) {
    while(1) {
        std::string command;
        std::cout << "\n>> ";
        std::getline(std::cin, command);

        boost::trim(command);
        std::vector<std::string> commands;
        boost::split_regex(commands, command, boost::regex( "[\\s]+" ));
        printMenu(commands);
    }
    pthread_exit(NULL);
}


int main(int argc, char **argv) {
    if (argc == 2) {
        if ((!strcmp(argv[1], "--help")) || (!strcmp(argv[1], "-h"))) {
            printf("Agent SNMP\n\thelp\n");
            return 0;
        }
    }

    pthread_t interactiveThread;
    agentInst.init();

    if (argc == 2) {
        if ((!strcmp(argv[1], "--print_tree")) || (!strcmp(argv[1], "-t"))) {
            agentInst.parserInst.tree.print_tree();
        }
        if ((!strcmp(argv[1], "--interactive")) || (!strcmp(argv[1], "-i"))) {
            int rc = pthread_create(&interactiveThread, NULL, interactivePrint, NULL);
            if (rc) {
                printf("Error: unable to enter interactive mode :(\n");
                exit(-1);
            }
        }
    } else if (argc == 3) {
        if ((!strcmp(argv[1], "--print_node_name")) || (!strcmp(argv[1], "-n"))) {
            std::string name(argv[2]);
            agentInst.parserInst.tree.print_node(name);
        }
        if ((!strcmp(argv[1], "--print_node_oid")) || (!strcmp(argv[1], "-o"))) {
            std::string name(argv[2]);
            std::vector<std::string> v;
            std::vector<int> v_int;
            boost::split_regex(v, name, boost::regex( "\\." ));
            for (auto &p : v) {
                v_int.push_back(std::stoi(p));
            }
            agentInst.parserInst.tree.print_node(v_int);
        }
    }


    // printf("seze of long: %d, int %d\n", sizeof(long), sizeof(int));
    // std::list<char> testList;
    // testList = agentInst.serializerInst.getIntBer((long)1<<32-1);
    // for (auto &p : testList) {
    //     printf("%02X ", (unsigned char) p);
    // }
    // printf("\n");
    // testList = agentInst.serializerInst.getIntBer(-(long)(1<<32)+1);
    // for (auto &p : testList) {
    //     printf("%02X ", (unsigned char) p);
    // }
    // printf("\n");

    agentInst.flow();

    return 0;
}

void printMenu(std::vector<std::string> commands) {
    if (commands.size() == 1) {
        if ((commands.at(0) == "help") || (commands.at(0) == "h")) {
            printf("Agent SNMP\n\thelp\n");
        }
        if ((commands.at(0) == "print_tree") || (commands.at(0) == "t")) {
            agentInst.parserInst.tree.print_tree();
        }
    } else if (commands.size() == 2) {
        if ((commands.at(0) == "print_node_name") || (commands.at(0) == "n")) {
            std::string name = commands.at(1);
            agentInst.parserInst.tree.print_node(name);
        }
        if ((commands.at(0) == "print_node_oid") || (commands.at(0) == "o")) {
            std::string name = commands.at(1);
            std::vector<std::string> v;
            std::vector<int> v_int;
            boost::split_regex(v, name, boost::regex( "\\." ));
            for (auto &p : v) {
                v_int.push_back(std::stoi(p));
            }
            agentInst.parserInst.tree.print_node(v_int);
        }
    }

}
