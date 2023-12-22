
#include <iostream>
#include <functional>
#include <vector>
#include <any>

enum class Event : int {
    TEST
};

template <typename... Args>
class CallbackPair {
public:
    CallbackPair(Event type):
        type(type)
    {
    }

    Event type;
    std::vector<std::function<void(Args...)>> callbacks;
};

class EventManager {
public:
    template <typename Event, typename... Args>
    void trigger(Event type, Args&&... args)
    {
        for (auto &callback : _callbacks) {
            if (callback.type == type)
                callback.callback(std::forward<Args>(args)...);
        }
    }

    template <typename Event, typename... Args>
    void connect(Event type, std::function<void(Args...)> callback)
    {
        _callbacks.emplace_back(type, callback);
    }

private:
    std::vector<CallbackPair<Event, std::any>> _callbacks;
};
