#pragma once
#include <Engine3D/Events/Event.h>
#include <Engine3D/Events/InputPoll.h>

namespace Engine3D{
    // KeyEvent Base Class
    class ENGINE_API KeyEvent : public Event{
    public:
        inline virtual KeyCode GetKeyCode() const {
            return _keyCode;
        }

        int GetCategoryFlags() const override{
            return EventCategoryKeyboard | EventCategoryInput;
        }

    protected:
        // Have this protected constructor
        // Because you shouldn't be able to create a KeyEvent, essentially
        KeyEvent(KeyCode keycode) : _keyCode(keycode) {}

       KeyCode  _keyCode;
    };

    // Handling when a key event has been pressed.  (It is a type of KeyEvent)
    // repeatCount is just a handler if the user decides to press the key for who knows how long
    // Thinking of hhaving repeatCount.
    class ENGINE_API KeyPressedEvent : public KeyEvent{
    public:
        KeyPressedEvent(KeyCode keycode, int repeatCount) : KeyEvent(keycode), _repeatCount(repeatCount) {}

        inline int GetRepeatCount() const { return _repeatCount; }

        std::string toString() const override{
            std::stringstream ss;
            ss << fmt::format("KeyPressedEvent: {} ({} repeats)", static_cast<int32_t>(_keyCode), _repeatCount);
            return ss.str();
        }

        // In runtime we want to see what event type this is.
        static EventType GetStaticType() { return EventType::KeyPressed; }

        // We need another instance of it, so we know what the actual event type it is.
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char* GetName() const override { return "EventType::KeyPressed"; }

    private:
        int _repeatCount;
    };

    class  ENGINE_API KeyReleasedEvent : public KeyEvent{
    public:
        KeyReleasedEvent(KeyCode keycode) : KeyEvent(keycode){}

        std::string toString() const override {
            std::stringstream ss;
            ss << fmt::format("KeyReleasedEvent: {}", static_cast<int32_t>(_keyCode));
            return ss.str();
        }

        // In runtime we want to see what event type this is.
        static EventType GetStaticType() { return EventType::KeyReleased; }

        // We need another instance of it, so we know what the actual event type it is.
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char* GetName() const override { return "EventType::KeyReleased"; }
    };

    class ENGINE_API KeyTypedEvent : public KeyEvent{
    public:
        KeyTypedEvent(KeyCode keycode) : KeyEvent(keycode) {}

        std::string toString() const override{
            std::stringstream ss;
            ss << fmt::format("KeyTypedEvent: {}", static_cast<int32_t>(_keyCode));
            return ss.str();
        }

        // In runtime we want to see what event type this is.
        static EventType GetStaticType() { return EventType::KeyTyped; }

        // We need another instance of it, so we know what the actual event type it is.
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual const char* GetName() const override { return "EventType::KeyTyped"; }
    };

};
