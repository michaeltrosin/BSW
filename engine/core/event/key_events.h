//
// Created by Michael on 13.02.2021.
//

#pragma once

#include <core/event/event.h>
#include <core/input/key_codes.h>

namespace bsw {
using namespace key;

class KeyEvent : public Event {
public:
    enum class Modifier : unsigned short {
        NONE = 0,
        SHIFT = BIT(0),
        CONTROL = BIT(1),
        ALT = BIT(2),
        SUPER = BIT(3),
        CAPS_LOCK = BIT(4),
        NUM_LOCK = BIT(5),
    };

    KeyCode get_key_code() const { return m_key_code; }
    Modifier get_modifiers() const { return m_mods; }

    bool has_modifier(Modifier mod) const { return get_modifiers() == mod; }

    EVENT_CATEGORY(EventCategory::KEYBOARD | EventCategory::INPUT)

protected:
    explicit KeyEvent(const KeyCode keycode, const uint32_t mods) : m_key_code(keycode), m_mods((Modifier) mods) {}

    KeyCode m_key_code;
    Modifier m_mods;
};

BITFIELD(KeyEvent::Modifier)

class KeyPressedEvent : public KeyEvent {
public:
    explicit KeyPressedEvent(const KeyCode keycode, const uint32_t mods, const uint32_t repeat_count = 0)
        : KeyEvent(keycode, mods), m_repeat_count(repeat_count) {}

    uint32_t get_repeat_count() const { return m_repeat_count; }

    EVENT_TYPE(KEY_PRESSED)
private:
    uint32_t m_repeat_count;
};

class KeyReleasedEvent : public KeyEvent {
public:
    explicit KeyReleasedEvent(const KeyCode keycode, const uint32_t mods) : KeyEvent(keycode, mods) {}

    EVENT_TYPE(KEY_RELEASED)
};

class KeyTypedEvent : public KeyEvent {
public:
    explicit KeyTypedEvent(const KeyCode keycode) : KeyEvent(keycode, 0) {}

    EVENT_TYPE(KEY_TYPED)
};
}// namespace bsw