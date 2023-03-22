#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

struct BaseInternal {
    BaseInternal() {
        std::cout << "BaseInternal::ctor" << std::endl;
    }

    virtual ~BaseInternal() {
        std::cout << "BaseInternal::dtor" << std::endl;
    }
};

struct DerivedInternal : BaseInternal {
    DerivedInternal() : BaseInternal() {
        std::cout << "DerivedInternal::ctor" << std::endl;
    }

    ~DerivedInternal() override {
        std::cout << "DerivedInternal::dtor" << std::endl;
    }
};

struct Base {
    BaseInternal b;

    //virtual ~Base() = default;
    //
    //virtual void print() const {
    //    std::cout << "Base::print" << std::endl;
    //}
};

struct Derived : Base {
    DerivedInternal d;

    //~Derived() override = default;
    //
    //void print() const override {
    //    std::cout << "Derived::print" << std::endl;
    //}
};

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Derived d;
    //d.print();
    std::cout << std::endl;

    Base* b = new Derived;
    //b->print();
    std::cout << std::endl;
    delete b;
    std::cout << std::endl;

    int* ptr = new int;
    return 0;
}

/*
--------------------------------------------------------------------------------
 BaseInternal::ctor
 BaseInternal::ctor
 DerivedInternal::ctro
 Derived::print
 BaseInternal::ctor
 BaseInternal::ctor
 DerivedInternal::ctro
 Derived::print
 BaseInternal::dtor
 DerivedInternal::dtor
 BaseInternal::dtor
 BaseInternal::dtor
--------------------------------------------------------------------------------
BaseInternal::ctor - 4 calls
BaseInternal::dtor - 3 calls
--------------------------------------------------------------------------------
BaseInternal::ctor
BaseInternal::ctor
DerivedInternal::ctro
Derived::print
BaseInternal::ctor
BaseInternal::ctor
DerivedInternal::ctro
Derived::print
DerivedInternal::dtor
BaseInternal::dtor
BaseInternal::dtor
DerivedInternal::dtor
BaseInternal::dtor
BaseInternal::dtor
--------------------------------------------------------------------------------
BaseInternal::ctor - 4 calls
BaseInternal::dtor - 4 calls
--------------------------------------------------------------------------------
*/
