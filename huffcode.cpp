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

#include<queue>

#include<vector>


void generateTree( shared_ptr< Node > & head,
                   std::priority_queue< shared_ptr< Node >,
                       std::vector< shared_ptr< Node > >,
                       Compare > pq ) {

    while( pq.size() != 1){
        auto first = pq.top();
        pq.pop();
        auto second = pq.top();
        pq.pop();

        auto newNode = make_shared< Node >( Node( 0,
                                            first->_weight + second->_weight,
                                            first, second ) );

        pq.push( newNode );
    }

    head = pq.top();

}


void HuffCode::setWeights( const unordered_map< char, int > & theweights ) {
    if( theweights.empty() )
        return;

    for( const auto & value: theweights ){
        auto newNode = make_shared< Node >( Node( value.first, value.second ) );
        _pqueue.push( newNode );
    }
}

string HuffCode::traverse_recursive( const shared_ptr< Node > & head,
                                     const char & data, bool & found ) const {

    // BASE CASE
    if ( head->_data == data ){
        found = true;
        return "";
    }

    string ret = "";
    // RECURSIVE CASE
    if ( !found && head->_leftChild != nullptr ){
        ret.append( "0" );
        auto left = traverse_recursive( head->_leftChild, data, found );
        if ( found )
            ret += left;
    }

    if ( !found && head->_rightChild != nullptr ){
        ret.pop_back();
        ret.append( "1" );
        auto right = traverse_recursive( head->_rightChild, data, found );
        if ( found )
            ret += right;
    }

    if ( !found )
        ret.pop_back();

    return ret;
}


string HuffCode::encode( const string & text ) const {
    if( text.empty() )
        return "";

    auto head = make_shared< Node >( Node( 0, 0 ) );

    generateTree( head, _pqueue );

    string total = "";
    bool found = false;
    std::unordered_map< char, string > memo;

    for ( const auto & character : text ) {
        auto tempHead(head);
        auto memoFind = memo.find( character );
        string temp = "";

        if ( head->_data == character)
            temp.append("0");
        else if ( memoFind == memo.end() ){
            temp = traverse_recursive( tempHead, character, found );
            memo[ character ] = temp;
        }
        else
            temp = memo[ character ];

        total += temp;
        found = false;
    }

    return total;
}


string HuffCode::decode( const string & codestr ) const
{
    if( codestr.empty() )
        return "";

    auto head = make_shared< Node >( Node( 0, 0 ) );

    generateTree( head, _pqueue );

    string ret;
    auto tempHead = head;
    for ( const char & character : codestr ){
        if ( character == '0' ) {
            if ( tempHead->_leftChild != nullptr )
                tempHead = tempHead->_leftChild;
            if ( tempHead->_leftChild == nullptr ) {
                ret += tempHead->_data;
                tempHead = head;
            }
        }
        else if ( character == '1' ) {
            if ( tempHead->_rightChild != nullptr )
                tempHead = tempHead->_rightChild;
            if ( tempHead->_rightChild == nullptr ) {
                ret += tempHead->_data;
                tempHead = head;
            }
        }
    }

    return ret;
}
