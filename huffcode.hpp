// huffcode.hpp  UNFINISHED
// Glenn G. Chappell
// 29 Nov 2015
//
// For CS 411/611 Fall 2015
// Assignment 6, Exercise A
// Header for class HuffCode
//
// Modified 11/22/17
// Chris Hartman
// For CS 411 Fall 2017

#ifndef FILE_HUFFCODE_H_INCLUDED
#define FILE_HUFFCODE_H_INCLUDED

#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <utility>
#include <memory>

// Node Class
// For generating Huffman Codes
// Based on the LLNode2 class by G.G. Chappell
class Node {
    public:
        char                    _data;
        int                     _weight;
        std::shared_ptr< Node > _leftChild;
        std::shared_ptr< Node > _rightChild;

        // 2, 3, or 4 parameter constructor
        // Strong Guarantee
        // Exception neutral
        explicit Node( const char & data, const int & weight,
                       std::shared_ptr< Node > lc = nullptr,
                       std::shared_ptr< Node > rc = nullptr )
            : _data(data), _weight(weight), _leftChild(lc), _rightChild(rc) { }

        ~Node() = default;

        bool operator>( const Node & a ) const {
            if( this->_weight != a._weight)
                return this->_weight > a._weight;
            else
                return this->_data > a._data;
        }

}; // End class Node

// Class Compare
// Provides a comparison function for shared_ptr< Node >
class Compare {
    public:
        bool operator() ( std::shared_ptr<Node> a, std::shared_ptr<Node> b ) {
            if (a != nullptr && b != nullptr)
                return *a > *b;
            return false;
        }
}; // End class Compare

// Class HuffCode
// Encoding & decoding using a Huffman code
class HuffCode {

// ***** HuffCode: ctors, dctor, op= *****
public:

    // Compiler-generated default ctor, copy ctor, copy =, dctor used

// ***** HuffCode: general public functions *****
public:

    void setWeights( const std::unordered_map< char, int > & theweights );

    std::string encode( const std::string & text ) const;

    std::string decode( const std::string & codestr ) const;

// ***** HuffCode: data members *****
private:

    std::string traverse_recursive( const std::shared_ptr< Node > &,
                                    const char &, bool & ) const;

    std::priority_queue< std::shared_ptr< Node >,
                         std::vector< std::shared_ptr< Node > >, Compare > _pqueue;

};  // End class HuffCode


#endif //#ifndef FILE_HUFFCODE_H_INCLUDED
