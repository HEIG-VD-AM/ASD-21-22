/*
 ----------------------------------------------------------------------------------
 Nom du fichier : some_bits.hpp

 Auteur(s)      : Olivier Cuisenaire

 Date creation  : 22.03.2021

 Compilateur    : Mingw-w64 g++ 11.2.0
 ----------------------------------------------------------------------------------
*/
#ifndef SOME_BITS_HPP
#define SOME_BITS_HPP

template<typename T>
class SomeBits {
    size_t shift;
    T mask;
public:
    SomeBits(size_t nombreDeBits, size_t part)
            : shift(part * nombreDeBits),
              mask(T(T(1u) << nombreDeBits) - T(1u)) {

    }
    T operator()(T const& t) {
        return T(mask & (t >> shift));
    }
};

#endif // SOME_BITS_HPP