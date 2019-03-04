#ifndef DEMO_H_
#define DEMO_H_

#include <iomanip>
#include <iostream>
#include <set>

template <typename T>
class Demo {
  public:
    Demo() = default;
    explicit Demo(T value)
        : inserted_{true}
        , value_{value}
    {
    }

    bool m(T t)
    {
        const auto [r, inserted] = set_.insert(t);
        return inserted;
    }

    bool inserted() const { return inserted_; }

  private:
    std::set<T> set_{};
    bool inserted_{false};
    T value_{0};
};

#endif // DEMO_H
