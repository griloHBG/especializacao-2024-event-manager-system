#include <iostream>
#include <forward_list>
#include <string>
#include <map>
#include <iomanip>
#include <random>
#include <optional>
#include "EventManagerSystem.h"

std::random_device rd;
std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<unsigned long long int> dist(0, 49);

auto getRandomNumber() {
    return dist(gen);
}

enum CommandLetter {
    ADD_EVENT='a',
    HANDOVER_EVENT='h',
    PRINT_EVENTS='p',
    QUIT='q',
};

std::string random_name[]= {
"00area",      "01book",          "02business",  "03case",  "04child",     "05company",   "06country",   "07day",       "08eye",   "09fact",
"10family",    "11government",    "12group",     "13hand",  "14home",      "15job",       "16life",      "17lot",       "18man",   "19money",
"20month",     "21mother",        "22Mr",        "23night", "24number",    "25part",      "26people",    "27place",     "28point", "29problem",
"30program",   "31question",      "32right",     "33room",  "34school",    "35state",     "36story",     "37student",   "38study", "39system",
"40thing",     "41time",          "42water",     "43way",   "44week",      "45woman",     "46word",      "47work",      "48world", "49year"
};

int main() {
/*
    std::forward_list<std::string> xablau {"123456789 123456789 123456789 123456789 ","bnmghjtyu bnmghjtyu bnmghjtyu bnmghjtyu ",";.,~çl['p ;.,~çl['p ;.,~çl['p ;.,~çl['p "};

    auto a = xablau.front();
    xablau.pop_front();
    std::cout << a << std::endl;

    a = xablau.front();
    xablau.pop_front();
    std::cout << a << std::endl;

    a = xablau.front();
    xablau.pop_front();
    std::cout << a << std::endl;

    std::exit(0);
*/
    EMS::EventManagerSystem ems{};

    std::map<char, std::string> commands {
        {CommandLetter::ADD_EVENT, "Add event"},
        {CommandLetter::HANDOVER_EVENT, "Handover event"},
        {CommandLetter::PRINT_EVENTS, "Print events"},
        {CommandLetter::QUIT, "Quit"},
    };

    char command_letter = 'p';

    auto random_number = getRandomNumber();

    unsigned long long int time = 0;

    std::optional<EMS::Event> handedover_event{};
    EMS::Event new_event{};

#ifdef NO_USER_INPUT
    std::stringstream ss{"aaaaaaaaaahhhhhq"};
#endif

    while(command_letter != CommandLetter::QUIT) {
        std::cout   << "Choose one option:" << std::endl;
        for (const auto &[letter, description]:commands) {
            std::cout << "\t" << std::setw(15) << description << " (" << letter << ")" << std::endl;
        }
        std::cout << "> ";
#ifdef NO_USER_INPUT
        ss >> command_letter;
#else
        std::cin >> command_letter;
#endif
        std::cout << std::endl;

        switch(command_letter) {
            case CommandLetter::ADD_EVENT:
                std::cout << "add event" << std::endl;
                new_event = EMS::Event{random_name[random_number], random_number > 24 ? EMS::Priority::HIGH : EMS::Priority::LOW, time};
                std::cout << "New Event: " << new_event << std::endl;
                ems.add_event(std::move(new_event));
                std::cout << "Event List: \n" << ems << std::endl;
                //add_event(list);
                break;
            case CommandLetter::HANDOVER_EVENT:
                std::cout << "handover event" << std::endl;
                if ((handedover_event = ems.handover(random_number > 24)))
                {
                    std::cout << "Event handedover: " << *handedover_event << std::endl;
                    std::cout << ems << std::endl;
                } else {
                    std::cout << "Event list is empty already! No handover!" << std::endl;
                }
                break;
            case CommandLetter::PRINT_EVENTS:
                std::cout << "print events" << std::endl;
                std::cout << ems << std::endl;
                break;
            case CommandLetter::QUIT:
                std::cout << "quit" << std::endl;
                std::exit(1);
                break;
            default:
                std::cerr << "fail!";
                std::exit(1);
        }

        random_number = getRandomNumber();
        time++;
    }
}