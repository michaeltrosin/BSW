//
// Created by Michael on 13.02.2021.
//

#include "event_handler.h"

template<typename T>
void bsw::EventHandler<T>::operator()(T &event) {
    for (auto &cb : m_attached_callbacks) { cb(event); }
}
template<typename T>
bsw::EventHandler<T> &bsw::EventHandler<T>::operator+=(const bsw::EventHandler<T>::CallbackFunction &callback_function) {
    m_attached_callbacks.push_back(callback_function);
    return *this;
}
