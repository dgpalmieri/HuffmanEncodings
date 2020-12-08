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
using std::to_string;
#include <unordered_map>
using std::unordered_map;
#include<memory>
using std::shared_ptr;
using std::make_shared;
#include<utility>
using std::pair;
using std::make_pair;
#include<algorithm>

#include<iostream> // TODO remove these
using std::cout;
using std::endl;


// TODO remove this
void printBT(const std::string& prefix, const shared_ptr<Node> & node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->_data << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->_leftChild, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->_rightChild, false);
    }
}

// TODO remove this
void printBT(const shared_ptr<Node> node)
{
    printBT("", node, false);
}


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
        //cout << "data: " << value.first << " weight: " << value.second << endl;
        auto newNode = make_shared< Node >( Node( value.first, value.second ) );
        _pqueue.push( newNode );
    }
}

string HuffCode::traverse_recursive( const shared_ptr< Node > & head,
                                     const char & data, bool & found ) const {

    // BASE CASE
    if ( head->_data == data ){
        //cout << "found " << data << endl;
        found = true;
        return "";
    }

    string ret = "";
    // RECURSIVE CASE
    if ( !found && head->_leftChild != nullptr ){
        //cout << "left" << endl;
        ret.append( "0" );
        auto left = traverse_recursive( head->_leftChild, data, found );
        if ( found )
            ret += left;
    }

    if ( !found && head->_rightChild != nullptr ){
        //cout << "right" << endl;
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
    printBT(head);

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

        //cout << character << ": " << temp << endl;
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

