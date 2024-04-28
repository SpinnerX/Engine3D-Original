// #pragma once
// #include <Engine3D/Events/Event.h>
// #include <Engine3D/Events/InputPoll.h>

// namespace Engine3D{
//     // KeyEvent Base Class
//     class ENGINE_API KeyEvent : public Event{
//     public:
//         inline virtual KeyCode GetKeyCode() const {
//             return _keyCode;
//         }

//         int GetCategoryFlags() const override{
//             return EventCategoryKeyboard | EventCategoryInput;
//         }

//     protected:
//         // Have this protected constructor
//         // Because you shouldn't be able to create a KeyEvent, essentially
//         KeyEvent(KeyCode keycode) : _keyCode(keycode) {}

//        KeyCode  _keyCode;
//     };

//     // Handling when a key event has been pressed.  (It is a type of KeyEvent)
//     // repeatCount is just a handler if the user decides to press the key for who knows how long
//     // Thinking of hhaving repeatCount.
//     class ENGINE_API KeyPressedEvent : public KeyEvent{
//     public:
//         KeyPressedEvent(KeyCode keycode, int repeatCount) : KeyEvent(keycode), _repeatCount(repeatCount) {}

//         inline int GetRepeatCount() const { return _repeatCount; }

//         std::string toString() const override{
//             std::stringstream ss;
//             ss << fmt::format("KeyPressedEvent: {} ({} repeats)", static_cast<int32_t>(_keyCode), _repeatCount);
//             return ss.str();
//         }

//         // In runtime we want to see what event type this is.
//         static EventType GetStaticType() { return EventType::KeyPressed; }

//         // We need another instance of it, so we know what the actual event type it is.
//         virtual EventType GetEventType() const override { return GetStaticType(); }
//         virtual const char* GetName() const override { return "EventType::KeyPressed"; }

//     private:
//         int _repeatCount;
//     };

//     class  ENGINE_API KeyReleasedEvent : public KeyEvent{
//     public:
//         KeyReleasedEvent(KeyCode keycode) : KeyEvent(keycode){}

//         std::string toString() const override {
//             std::stringstream ss;
//             ss << fmt::format("KeyReleasedEvent: {}", static_cast<int32_t>(_keyCode));
//             return ss.str();
//         }

//         // In runtime we want to see what event type this is.
//         static EventType GetStaticType() { return EventType::KeyReleased; }

//         // We need another instance of it, so we know what the actual event type it is.
//         virtual EventType GetEventType() const override { return GetStaticType(); }
//         virtual const char* GetName() const override { return "EventType::KeyReleased"; }
//     };

//     class ENGINE_API KeyTypedEvent : public KeyEvent{
//     public:
//         KeyTypedEvent(KeyCode keycode) : KeyEvent(keycode) {}

//         std::string toString() const override{
//             std::stringstream ss;
//             ss << fmt::format("KeyTypedEvent: {}", static_cast<int32_t>(_keyCode));
//             return ss.str();
//         }

//         // In runtime we want to see what event type this is.
//         static EventType GetStaticType() { return EventType::KeyTyped; }

//         // We need another instance of it, so we know what the actual event type it is.
//         virtual EventType GetEventType() const override { return GetStaticType(); }
//         virtual const char* GetName() const override { return "EventType::KeyTyped"; }
//     };

// };
pragma once
#include <Engine3D/Core/core.h>
#include <Engine3D/Event/Event.h>
#include <Engine3D/Event/KeyCodes.h>
#include <sstream>

namespace Engine3D{
    
    class ENGINE_API KeyEvent : public Event{
    public:

        // inline KeyCode GetKeyCode() const { return KeyCode(); }

        int GetCategoryFlags() const override{
            return EventCategoryKeyboard | EventCategoryInput;
        }

    private:

    protected:
        KeyEvent(KeyCode code) : keycode(code) {}

        KeyCode keycode;
    };

    class ENGINE_API KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(KeyCode code, int countRepeated) : KeyEvent(code), repeated(countRepeated) {}

        static EventType GetStaticType() { return EventType::KeyPressed; }

    private:
        std::string str() const override{
            std::stringstream ss;
            ss << "KeyPressedEvent(Key) = " << static_cast<int32_t>(keycode);
            ss << "EventType::KeyPressedEvent";
            return ss.str();
        }

        // const char* GetName() const override { return "EventType::KeyPressedEvent"; }

        EventType GetEventType() const override { return GetStaticType(); }

    private:
        int repeated;
    };

    class ENGINE_API KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(KeyCode code) : KeyEvent(code){}

        static EventType GetStaticType() { return EventType::KeyReleased; }

    private:
        std::string str() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent(Key) = " << static_cast<int32_t>(keycode);
            return ss.str();
        }

        EventType GetEventType() const override { return GetStaticType(); }

        // const char* GetName() const override { return "EventType::KeyReleasedEvent"; }
    };

    class ENGINE_API KeyTypedEvent : public KeyEvent {
    public:
        KeyTypedEvent(KeyCode code) : KeyEvent(code) {}

        static EventType GetStaticType() { return EventType::KeyTyped; }

    private:
        std::string str() const override{
            std::stringstream ss;
            ss << "KeyTypedEvent(key) = " << static_cast<int32_t>(keycode);
            return ss.str();
        }

        EventType GetEventType() const override { return GetStaticType(); }
        // const char* GetName() const override { return "EventType::KeyTypedEvent"; }
    };


};