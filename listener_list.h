#pragma once

#include <unordered_set>
#include <memory>

template <typename Listener,
          typename Ptr = Listener *,
          typename Collection = std::unordered_set<Ptr>>
class ListenerList {
public:
    virtual ~ListenerList() noexcept = default;

    template <typename Fun>
    inline void call(Fun f) const {
        for (auto &&i : listener)
            (i->*f)();
    }

    template <typename Fun, typename... Values>
    inline void call(Fun f, Values &&... values) const {
        for (auto &&i : listener)
            (i->*f)(std::forward<Values>(values)...);
    }

    inline void add_listener(Ptr ptr) {
        listener.insert(ptr);
    }
    inline void remove_listener(Ptr ptr) {
        listener.erase(ptr);
    }

private:
    Collection listener;
};
