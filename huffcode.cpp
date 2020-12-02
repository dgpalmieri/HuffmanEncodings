// huffcode.cpp  UNFINISHED
// Glenn G. Chappell
// 29 Nov 2015
//
// For CS 411/611 Fall 2015
// Assignment 6, Exercise A
// Source for class HuffCode
//
// Modified 11/22/17
// Chris Hartman
// For CS 411 Fall 2017

#include "huffcode.hpp"  // for class HuffCode declaration
#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;
#include<memory>
using std::shared_ptr;
using std::make_shared;
#include<utility>
using std::pair;
using std::make_pair;

// Node Class
// For generating Huffman Codes
// Based on the LLNode2 class by G.G. Chappell
template< typename ValType >
class Node {
    public:
        ValType            _data;
        int                _weight;
        shared_ptr< Node > _leftChild;
        shared_ptr< Node > _rightChild;

        // 1, 2, or 3 parameter constructor
        // Strong Guarantee
        // Exception neutral
        explicit Node( const ValType & data, shared_ptr< Node > lc = nullptr,
                                             shared_ptr< Node > rc = nullptr )
            : _data(data), _leftChild(lc), _rightChild(rc) {}

        ~Node() = default;
};


void HuffCode::setWeights( const unordered_map< char, int > & theweights )
{
    if( theweights.empty() )
        return;

    for( const auto & value: theweights )
        _pqueue.push( make_pair( value.second, value.first ) );
}


string HuffCode::encode( const string & text ) const
{
    if( text.empty() )
        return "";

    return "";  // DUMMY RETURN
}


string HuffCode::decode( const string & codestr ) const
{
    if( codestr.empty() )
        return "";

    return "";  // DUMMY RETURN
}

