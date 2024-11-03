//
// Created by grilo on 02/11/24.
//

#include "EventManagerSystem.h"

namespace EMS {

    void EventManagerSystem::add_event(EMS::Event &&e) {
        switch(e.priority){
            case Priority::HIGH:
                if (last_high_prio_event == event_list.end()) {
                    event_list.push_front(e);
                    last_high_prio_event = event_list.begin();
                } else {
                    last_high_prio_event = event_list.insert_after(last_high_prio_event, e);
                }
                break;
            case Priority::LOW:
                if (first_low_prio_event == event_list.end()) {
                    if (last_high_prio_event == event_list.end()) {
                        //high priority EMPTY and low priority EMPTY : add to the begin
                        event_list.push_front(e);
                        first_low_prio_event = event_list.begin();
                        last_low_prio_event = event_list.begin();
                    } else {
                        //high priority NOT EMPTY and low priority EMPTY : add after the last high priority
                        first_low_prio_event = event_list.insert_after(last_high_prio_event, e);
                        last_low_prio_event = first_low_prio_event;
                    }
                } else {
                    //low priority NOT EMPTY : add after the last low priority
                    last_low_prio_event = event_list.insert_after(last_low_prio_event, e);
                }

                break;
            default:
                std::cerr << "erro!" << std::endl;
                std::exit(1);
        }
    }

    std::optional<Event> EventManagerSystem::handover(bool success) {
        if(success) {
            if (event_list.empty()) {
                return {};
            }
            Event e = event_list.front();
            event_list.pop_front();
            return e;
        } else {
            std::cout << "HANDOVER FAILED!" << std::endl;
            return {};
        }
    }


    std::ostream& operator<<(std::ostream& os, const Priority p){
        switch(p) {
            case Priority::HIGH:
                os << "high";
                break;
            case Priority::LOW:
                os << "low";
                break;
            default:
                std::cerr << "should not happen!";
                std::exit(1);
                break;
        }
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Event& e){
        os << std::setw(12) << e.description << " | " << std::setw(6) << e.priority << " | " <<  std::setw(8) << e.time_ms;

        return os;
    }

    std::ostream& operator<<(std::ostream& os, const std::forward_list<Event>& list){
        for(auto& e:list) {
            os << e << '\n';
        }

        return os;
    }

    std::ostream& operator<<(std::ostream& os, const EventManagerSystem& ems){
        os << ems.event_list;

        return os;
    }
} // EMS