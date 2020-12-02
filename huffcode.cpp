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
        explicit Node( const ValType & data, const int & weight,
                                             shared_ptr< Node > lc = nullptr,
                                             shared_ptr< Node > rc = nullptr )
            : _data(data), _leftChild(lc), _rightChild(rc) { }

        ~Node() = default;
};

// TODO remove this
void printBT(const std::string& prefix, const shared_ptr<Node< char >> & node, bool isLeft)
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
void printBT(const shared_ptr<Node<char>> node)
{
    printBT("", node, false);
}


void generateTree( shared_ptr< Node< char > > & head,
                   std::priority_queue< std::pair<int, char>,
                       std::vector< std::pair< int, char > >,
                       std::greater< std::pair< int, char > > > pq ) {

    while( !pq.empty() ){
        auto top = pq.top();

        if( head->_leftChild == nullptr ){
            head->_leftChild = make_shared< Node< char > >
                              ( Node< char >(top.second, top.first) );
            pq.pop();
            continue;
        }

        if ( head->_rightChild == nullptr ){
            head->_rightChild = make_shared< Node< char > >
                               ( Node< char >(top.second, top.first) );
            pq.pop();
            continue;
        }

        int leftWeight = head->_leftChild ?
                         head->_leftChild->_weight : 0;

        int rightWeight = head->_rightChild ?
                          head->_rightChild->_weight : 0;

        head = make_shared< Node< char > >( Node< char >
                        ( 0, leftWeight + rightWeight, head ) );

    }
}


void HuffCode::setWeights( const unordered_map< char, int > & theweights ) {
    if( theweights.empty() )
        return;

    for( const auto & value: theweights )
        _pqueue.push( make_pair( value.second, value.first ) );
}


string HuffCode::encode( const string & text ) const {
    if( text.empty() )
        return "";

    auto head = make_shared< Node< char > >( Node< char >( 0, 0 ) );

    generateTree( head, _pqueue );

    string total = "";
    for ( const auto & character : text ) {
        auto tempHead(head);

        while( true ){
            if ( tempHead->_rightChild &&
                 tempHead->_rightChild->_data == character ) {
                total += "1";
                break;
            }
            else if ( tempHead->_leftChild &&
                      tempHead->_leftChild->_data == character ) {
                total += "0";
                break;
            }
            else {
                total += "0";
                if ( tempHead->_leftChild ){
                    tempHead = tempHead->_leftChild ;
                }
                else {
                    break; }
            }
        }
    }

    return total;
}


string HuffCode::decode( const string & codestr ) const
{
    if( codestr.empty() )
        return "";

    auto head = make_shared< Node< char > >( Node< char >( 0, 0 ) );

    generateTree( head, _pqueue );

    string ret;
    auto tempHead = head;
    for ( const char & character : codestr ){
        if ( character == '0' ) {
            if ( tempHead->_leftChild != nullptr ){
                tempHead = tempHead->_leftChild;
                if ( tempHead->_leftChild == nullptr ) {
                    ret += tempHead->_data;
                    tempHead = head;
                }
            }
        }
        else if ( character == '1' ) {
            ret += tempHead->_rightChild->_data;
            tempHead = head;
        }
    }

    return ret;  // DUMMY RETURN
}

