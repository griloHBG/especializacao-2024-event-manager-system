//
// Created by grilo on 02/11/24.
//

#ifndef ESPECIALIZACAO_2024_EVENT_MANAGER_SYSTEM_EVENTMANAGERSYSTEM_H
#define ESPECIALIZACAO_2024_EVENT_MANAGER_SYSTEM_EVENTMANAGERSYSTEM_H

#include <forward_list>
#include <string>
#include <iomanip>
#include <iostream>
#include <optional>

namespace EMS {

    enum class Priority {
        HIGH,
        LOW,
    };


    struct Event {
        std::string description;
        Priority priority;
        unsigned long long int time_ms;
    };

    class EventManagerSystem {

        using EventList = std::forward_list<Event>;
        using EventListIterator = std::forward_list<Event>::iterator;

    public:
        void add_event(Event&& e);

        std::optional<Event> handover(bool success);

        friend std::ostream& operator<<(std::ostream& os, const EventManagerSystem& ems);

    private:
        EventList event_list{};
        EventListIterator last_high_prio_event{nullptr};
        EventListIterator first_low_prio_event{nullptr};
        EventListIterator last_low_prio_event{nullptr};
/*
    static bool time_compare(const Event& e1, const Event& e2) {
        return e1.time_ms < e2.time_ms;
    }
*/
    };

    std::ostream& operator<<(std::ostream& os, Priority p);

    std::ostream& operator<<(std::ostream& os, const Event& e);

    std::ostream& operator<<(std::ostream& os, const std::forward_list<Event>& list);

    std::ostream& operator<<(std::ostream& os, const EventManagerSystem& ems);

} // EMS
#endif //ESPECIALIZACAO_2024_EVENT_MANAGER_SYSTEM_EVENTMANAGERSYSTEM_H
