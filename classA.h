//
// Created by asma- on 13/03/2021.
//

#ifndef CLASS_A
#define CLASS_A
#include <iostream>
#include "ObjectCounters.h"

class A : public ObjectCounters<A> {
private:
    int a{};
public:
    A() { ++count.iCD; }
    A(int x) : a(x) { ++count.iCI; }
    A(const A& other) : a(other.a) { ++count.iCC; }
    A(A&& other) : a(std::move(other.a)) { ++count.iCM; }
    A& operator=(const A&other) {
        a = other.a;
        if (this != &other) ++count.iAC;
        return *this;
    }
    A& operator=(A &&other) {
        a = std::move(other.a);
        ++count.iAM;
        return *this;
    }

    friend bool operator==( const A& lhs, const A& rhs ) {
        return lhs.a==rhs.a;
    }

    friend bool operator!=( const A& lhs, const A& rhs ) {
        return lhs.a!=rhs.a;
    }

    friend bool operator>( const A& lhs, const A& rhs ) {
        return lhs.a>rhs.a;
    }

    friend bool operator<( const A& lhs, const A& rhs ) {
        return lhs.a<rhs.a;
    }

    friend bool operator<=( const A& lhs, const A& rhs ) {
        return lhs.a<=rhs.a;
    }

    friend bool operator>=( const A& lhs, const A& rhs ) {
        return lhs.a>=rhs.a;
    }
    ~A() { ++count.iDD; }
    friend std::ostream& operator<<(std::ostream& os, const A& obj) { return os << obj.a; }
};

#endif // CLASS_A