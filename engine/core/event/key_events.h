//
// Created by Michael on 13.02.2021.
//

#pragma once

#include <core/event/event.h>
#include <core/input/key_codes.h>

namespace bsw {
using namespace keycodes;

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

  KeyCode GetKeyCode() const { return key_code_; }
  Modifier GetModifiers() const { return mods_; }

  bool HasModifier(Modifier mod) const { return GetModifiers() == mod; }

  EVENT_CATEGORY(EventCategory::KEYBOARD | EventCategory::INPUT)

protected:
  explicit KeyEvent(const KeyCode keycode, const uint32_t mods)
      : key_code_(keycode), mods_((Modifier)mods) {}

  KeyCode key_code_;
  Modifier mods_;
};

BITFIELD(KeyEvent::Modifier)

class KeyPressedEvent : public KeyEvent {
public:
  explicit KeyPressedEvent(const KeyCode keycode, const uint32_t mods,
                           const uint32_t repeat_count = 0)
      : KeyEvent(keycode, mods), repeat_count_(repeat_count) {}

  unsigned int GetRepeatCount() const { return repeat_count_; }

  EVENT_TYPE(KEY_PRESSED)
private:
  unsigned int repeat_count_;
};

class KeyReleasedEvent : public KeyEvent {
public:
  explicit KeyReleasedEvent(const KeyCode keycode, const uint32_t mods)
      : KeyEvent(keycode, mods) {}

  EVENT_TYPE(KEY_RELEASED)
};

class KeyTypedEvent : public KeyEvent {
public:
  explicit KeyTypedEvent(const KeyCode keycode) : KeyEvent(keycode, 0) {}

  EVENT_TYPE(KEY_TYPED)
};
} // namespace bsw