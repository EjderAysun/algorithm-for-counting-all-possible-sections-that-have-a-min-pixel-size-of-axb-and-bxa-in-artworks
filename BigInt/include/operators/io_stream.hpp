/*
    ===========================================================================
    I/O stream operators
    ===========================================================================
*/

#ifndef BIG_INT_IO_STREAM_OPERATORS_HPP
#define BIG_INT_IO_STREAM_OPERATORS_HPP

// #include "BigInt.hpp"
#include "../BigInt.hpp"  // file-path fixed
// #include "constructors/constructors.hpp"
#include "../constructors/constructors.hpp"  // file-path fixed
// #include "operators/assignment.hpp"
#include "../operators/assignment.hpp"  // file-path fixed


/*
    BigInt from input stream
    ------------------------
*/

// std::istream& operator>>(std::istream& in, BigInt& num) {
//     std::string input;
//     in >> input;
//     num = BigInt(input);  // remove sign from value and set sign, if exists

//     return in;
// }

std::istream& operator>>(std::istream& in, BigInt& num) {
    std::string input;
    if (in >> input) {
        try {
            num = BigInt(input);  // remove sign from value and set sign, if exists
            return in;
        } catch (const std::invalid_argument& e) {
            in.setstate(std::ios::failbit);
        }

    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}



/*
    BigInt to output stream
    -----------------------
*/

std::ostream& operator<<(std::ostream& out, const BigInt& num) {
    if (num.sign == '-')
        out << num.sign;
    out << num.value;

    return out;
}

#endif  // BIG_INT_IO_STREAM_OPERATORS_HPP
