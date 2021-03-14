//
// Created by Michael on 13.02.2021.
//

#pragma once

#include <core/event/event.h>

#include <functional>
#include <vector>

namespace bsw {

template<typename T>
class EventHandler {
    using CallbackFunction = std::function<void(T &)>;

public:
    /**
     * Using this operator, a callback function will be appended to this handler
     *
     * @param callback_function
     * @return
     */
    EventHandler &operator+=(const CallbackFunction &callback_function);

    /**
     * Calls the event
     * @param event
     */
    void operator()(T &event);

private:
    std::vector<CallbackFunction> m_attached_callbacks;
};

}// namespace bsw