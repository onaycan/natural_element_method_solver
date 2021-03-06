/****************************************************************************
**
** Copyright (C) 2009-2010 C.B. Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/PointCoordinates.cpp#23 $$Change: 1164 $
** $DateTime: 2010/01/07 21:52:00 $$Author: bbarber $
**
****************************************************************************/

#include "QhullError.h"
#include "QhullPoint.h"
#include "PointCoordinates.h"

#include <iostream>

using std::istream;
using std::string;
using std::ws;

#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4
#pragma warning( disable : 4996)  // function was declared deprecated(strcpy, localtime, etc.)
#endif

namespace orgQhull {

#//! PointCoordinates -- vector of PointCoordinates

#//Construct
PointCoordinates::
PointCoordinates()
: QhullPoints()
, point_coordinates()
, point_comment()
{
    makeValid();
}

#//Construct
PointCoordinates::
PointCoordinates(int dimension)
: QhullPoints(dimension)
, point_coordinates()
, point_comment()
{
    makeValid();
}

PointCoordinates::
PointCoordinates(const std::string &comment)
: QhullPoints()
, point_coordinates()
, point_comment()
{
    appendComment(comment);
    makeValid();
}

PointCoordinates::
PointCoordinates(int dimension, const std::string &comment)
: QhullPoints(dimension)
, point_coordinates()
, point_comment()
{
    appendComment(comment);
    makeValid();
}

PointCoordinates::
PointCoordinates(int dimension, const std::string &comment, int coordinateCount, const coordT *c)
: QhullPoints(dimension)
, point_coordinates()
, point_comment(comment)
{
    append(coordinateCount, c);
}

PointCoordinates::
PointCoordinates(const PointCoordinates &other)
: QhullPoints(other)
, point_coordinates(other.point_coordinates)
, point_comment(other.point_comment)
{
    makeValid();
}

PointCoordinates & PointCoordinates::
operator=(const PointCoordinates &other)
{
    point_coordinates= other.point_coordinates;
    point_comment= other.point_comment;
    makeValid();
    return *this;
}//operator=

PointCoordinates::
~PointCoordinates()
{ }

#//GetSet

void PointCoordinates::
checkValid() const
{
    if(getCoordinates().data()!=data()
    || getCoordinates().count()!=coordinateCount()){
        throw QhullError(10060, "Qhull error: first point (%x) is not PointCoordinates.data() or count (%d) is not PointCoordinates.count (%d)", coordinateCount(), getCoordinates().count(), 0.0, data());
    }
}//checkValid

void PointCoordinates::
setDimension(int i)
{
    if(i<0){
        throw QhullError(10062, "Qhull error: can not set PointCoordinates dimension to %d", i);
    }
    int currentDimension=QhullPoints::dimension();
    if(currentDimension!=0 && i!=currentDimension){
        throw QhullError(10063, "Qhull error: can not change PointCoordinates dimension (from %d to %d)", currentDimension, i);
    }
    QhullPoints::setDimension(i);
}//setDimension

//#Foreach

Coordinates::ConstIterator PointCoordinates::
beginCoordinates(int pointIndex) const
{
    return point_coordinates.begin()+indexOffset(pointIndex);
}

Coordinates::Iterator PointCoordinates::
beginCoordinates(int pointIndex)
{
    return point_coordinates.begin()+indexOffset(pointIndex);
}

#//Modify

void PointCoordinates::
append(int count, const coordT *c)
{
    if(count<=0){
        return;
    }
    if(includesCoordinates(c)){
        throw QhullError(10065, "Qhull error: can not append a subset of PointCoordinates to itself.  The coordinates for point %d may move.", indexOf(c, QhullError::NOthrow));
    }
    reserveCoordinates(count);
    std::copy(c, c+count, std::back_inserter(point_coordinates));
    makeValid();
}//append coordT

void PointCoordinates::
append(const PointCoordinates &other)
{
    setDimension(other.dimension());
    append(other.coordinateCount(), other.data());
}//append PointCoordinates

void PointCoordinates::
append(const QhullPoint &p)
{
    setDimension(p.dimension());
    append(p.dimension(), p.coordinates());
}//append QhullPoint

void PointCoordinates::
appendComment(const std::string &s){
    if(char c= s[0] && point_comment.empty()){
        if(c=='-' || isdigit(c)){
            throw QhullError(10028, "Qhull argument error: comments can not start with a number or minus, %s", 0, 0, 0.0, s.c_str());
        }
    }
    point_comment += s;
}//appendComment

//! Read PointCoordinates from istream.  First two numbers are dimension and count.  A non-digit starts a rboxCommand.
//! Overwrites point_comment.  See qh_readpoints [io.c]
void PointCoordinates::
appendPoints(istream &in)
{
    int inDimension, inCount;
    in >> ws >> inDimension >> ws;
    if(!in.good()){
        in.clear();
        string remainder;
        getline(in, remainder);
        throw QhullError(10005, "Qhull error: input did not start with dimension or count -- %s", 0, 0, 0, remainder.c_str());
    }
    char c= (char)in.peek();
    if(c!='-' && !isdigit(c)){         // Comments start with a non-digit
        getline(in, point_comment);
        in >> ws;
    }
    in >> inCount >> ws;
    if(!in.good()){
        in.clear();
        string remainder;
        getline(in, remainder);
        throw QhullError(10009, "Qhull error: input did not start with dimension and count -- %d %s", inDimension, 0, 0, remainder.c_str());
    }
    c= (char)in.peek();
    if(c!='-' && !isdigit(c)){         // Comments start with a non-digit
        getline(in, point_comment);
        in >> ws;
    }
    if(inCount<inDimension){           // Count may precede dimension
        std::swap(inCount, inDimension);
    }
    setDimension(inDimension);
    reserveCoordinates(inCount*inDimension);
    int coordinateCount= 0;
    while(!in.eof()){
        realT p;
        in >> p >> ws;
        if(in.fail()){
            in.clear();
            string remainder;
            getline(in, remainder);
            throw QhullError(10008, "Qhull error: failed to read coordinate %d  of point %d\n   %s", coordinateCount % inDimension, coordinateCount/inDimension, 0, remainder.c_str());
        }else{
            point_coordinates.push_back(p);
            coordinateCount++;
        }
    }
    if(coordinateCount != inCount*inDimension){
        if(coordinateCount%inDimension==0){
            throw QhullError(10006, "Qhull error: expected %d %d-d PointCoordinates but read %i PointCoordinates", int(inCount), inDimension, 0.0, int(coordinateCount/inDimension));
        }else{
            throw QhullError(10012, "Qhull error: expected %d %d-d PointCoordinates but read %i PointCoordinates plus %f extra coordinates", inCount, inDimension, float(coordinateCount%inDimension), coordinateCount/inDimension);
        }
    }
    makeValid();
}//appendPoints istream

PointCoordinates PointCoordinates::
operator+(const PointCoordinates &other) const
{
    PointCoordinates pc= *this;
    pc << other;
    return pc;
}//operator+

void PointCoordinates::
reserveCoordinates(int newCoordinates)
{
    // vector::reserve is not const
    point_coordinates.reserve((int)point_coordinates.size()+newCoordinates); // WARN64
    makeValid();
}//reserveCoordinates

#//Helpers

int PointCoordinates::
indexOffset(int i) const {
    int n= i*dimension();
    int coordinateCount= point_coordinates.count();
    if(i<0 || n>coordinateCount){
        throw QhullError(10061, "Qhull error: point_coordinates is too short (%d) for point %d", coordinateCount, i);
    }
    return n;
}

}//namespace orgQhull

#//Global functions

using std::endl;
using std::ostream;

using orgQhull::Coordinates;
using orgQhull::PointCoordinates;

ostream&
operator<<(ostream &os, const PointCoordinates &p)
{
    p.checkValid();
    int count= p.count();
    int dimension= p.dimension();
    string comment= p.comment();
    if(comment.empty()){
        os << dimension << endl;
    }else{
        os << dimension << " " << comment << endl;
    }
    os << count << endl;
    Coordinates::ConstIterator c= p.beginCoordinates();
    for(int i=0; i<count; i++){
        for(int j=0; j<dimension; j++){
            os << *c++ << " ";
        }
        os << endl;
    }
    return os;
}//operator<<

