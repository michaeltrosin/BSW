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
    EventHandler &operator+=(const CallbackFunction &callback_function);

    void operator()(T &event);

private:
    std::vector<CallbackFunction> m_attached_callbacks;
};

}// namespace bsw