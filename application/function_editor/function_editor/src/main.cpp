//========================================
// main.cpp
//
//  Created on: 2013/12/29
//      Author: you
//========================================

#include <iostream>

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>
#include <list>

class IFunction;
class FunctionManager {
public:
    FunctionManager();
    ~FunctionManager();

private:
    FunctionManager(const FunctionManager&);
    FunctionManager& operator=(const FunctionManager&);

private:
    std::unordered_map<std::string, std::unique_ptr<IFunction> > m_functions;

};

class IFunction {
public:
    virtual ~IFunction() =0;

protected:
    IFunction();

private:
    IFunction(const IFunction&);
    IFunction& operator=(const IFunction&);

};

class EventDispatcher {
public:
    EventDispatcher();
    ~EventDispatcher();

    int dispatch(const std::string& message);

private:
    EventDispatcher(const EventDispatcher&);
    EventDispatcher& operator=(const EventDispatcher&);

private:
    std::unordered_map<std::string, int (*)(const std::string&)> m_eventList;

};

void move(std::list<int>& list_, const std::vector<int>& selected_,
    int moveTo_) {
    std::cout << "move(): ";
    for (auto i : selected_) {
        std::cout << i << ", ";
    }
    std::cout << " -> " << moveTo_ << std::endl;

    auto selIt = std::vector<decltype(list_.begin())>();
    for (auto i : selected_) {
        auto it = list_.begin();
        std::advance(it, i);
        selIt.push_back(it);
    }

    auto movIt = list_.begin();
    std::advance(movIt, moveTo_);
//    std::cout << *selIt << ", " << *movIt << std::endl;
    for (unsigned int i = 0; i < selected_.size(); ++i) {
        std::cout << *selIt[i] << ", ";
    }
    std::cout << " -> " << *movIt << std::endl;

    for (auto it : selIt) {
        list_.splice(movIt, list_, it);
    }

//    std::cout << *selIt << ", " << *movIt << std::endl;

    std::cout << "move(): show" << std::endl;
    for (auto it : list_) {
        std::cout << it << std::endl;
    }
}

class A01 {
public:
    A01(int i)
            : i(i) {
    }
    ~A01() {
    }
    void add(std::vector<std::function<void()> >& list) {
        list.push_back(
                [&]() {std::cout << "A01::lambda(): " << this << ", " << i << std::endl;});
    }
    int i;
};

int main(int argc, char* argv[]) {
    std::cout << "started" << std::endl;

    FunctionManager manager;

    EventDispatcher dispacther;

    std::string input;
    int result = 0;
//    while (result == 0) {
//        std::cout << " > ";
//        std::cin >> input;
//        std::cout << input << std::endl;
//        result = dispacther.dispatch(input);
//    }

    std::list<int> ints { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    for (auto it : ints) {
        std::cout << it << std::endl;
    }

    move(ints, { 0, 2 }, 10);

    std::vector<std::function<void()> > listener;
    auto a01 = new A01(0);
    a01->add(listener);
    std::cout << a01 << std::endl;
//    delete a01;
    for (auto& it : listener) {
        it();
    }

    std::weak_ptr<A01> a01_02;
    {
        std::shared_ptr<A01> a01_01(new A01(3));
        std::shared_ptr<A01> a01_03 = a01_01;

        a01_02 = a01_01;
        if (a01_02.use_count() > 0) {
            std::cout << a01_02.use_count() << ": " << a01_02.lock()->i
                << std::endl;
        }
    }
    if (a01_02.use_count() > 0) {
        std::cout << a01_02.lock()->i << std::endl;
    } else {
        std::cout << "use_count() is 0" << std::endl;
    }

    std::cout << "terminated" << std::endl;
    return 0;
}

FunctionManager::FunctionManager() {
}
FunctionManager::~FunctionManager() {
}

IFunction::~IFunction() {
}

void f() {
    std::cout << "f()" << std::endl;
}
EventDispatcher::EventDispatcher() {
    m_eventList.insert(
            std::make_pair(
                           "quit",
                           [](const std::string& arg) -> int {
                               std::cout << "quit(): " << arg << std::endl;
                               return -1;
                           }));
    m_eventList.insert(
            std::make_pair(
                           "show",
                           [](const std::string& arg) -> int {
                               std::cout << "show(): " << arg << std::endl;
                               return 0;
                           }));

    auto l = []() {std::cout << "l()" << std::endl;};
    void (*AA)()= &f;
    (*AA)();
    AA = l;
    (*AA)();
}
EventDispatcher::~EventDispatcher() {

}

int EventDispatcher::dispatch(const std::string& message) {
    if (m_eventList.count(message) > 0) {
        return m_eventList[message](message);
    } else {
        return 0;
    }
}

