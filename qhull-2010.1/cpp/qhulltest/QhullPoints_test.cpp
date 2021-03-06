/****************************************************************************
**
** Copyright (p) 2009-2010 C.B. Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/qhulltest/QhullPoints_test.cpp#19 $$Change: 1176 $
** $DateTime: 2010/01/11 19:40:05 $$Author: bbarber $
**
****************************************************************************/

//pre-compiled header
#include <iostream>
#include "../road/RoadTest.h" // QT_VERSION

#include "QhullPoints.h"
#include "RboxPoints.h"
#include "Qhull.h"

using std::cout;
using std::endl;
using std::ostringstream;

namespace orgQhull {

class QhullPoints_test : public RoadTest
{
    Q_OBJECT

#//Test slots
private slots:
    void cleanup();
    void t_construct();
    void t_convert();
    void t_getset();
    void t_element();
    void t_iterator();
    void t_const_iterator();
    void t_search();
    void t_points_iterator();
    void t_io();
};//QhullPoints_test

void
add_QhullPoints_test()
{
    new QhullPoints_test();
}

//Executed after each testcase
void QhullPoints_test::
cleanup()
{
    UsingLibQhull::checkQhullMemoryEmpty();
    RoadTest::cleanup();
}

void QhullPoints_test::
t_construct()
{
    QhullPoints ps;
    QCOMPARE(ps.dimension(), 0);
    QVERIFY(ps.isEmpty());
    QVERIFY(ps.empty());
    QCOMPARE(ps.count(), 0);
    QCOMPARE(ps.size(), 0u);
    QCOMPARE(ps.coordinateCount(), 0);
    coordT c[]= {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    QhullPoints ps2;
    ps2.defineAs(2, 6, c);
    QCOMPARE(ps2.dimension(), 2);
    QVERIFY(!ps2.isEmpty());
    QVERIFY(!ps2.empty());
    QCOMPARE(ps2.count(), 3);
    QCOMPARE(ps2.size(), 3u);
    QCOMPARE(ps2.coordinates(), c);
    QhullPoints ps7(3);
    QCOMPARE(ps7.dimension(), 3);
    QVERIFY(ps7.isEmpty());
    QhullPoints ps3(2, 6, c);
    QCOMPARE(ps3.dimension(), 2);
    QVERIFY(!ps3.isEmpty());
    QCOMPARE(ps3.coordinates(), ps2.coordinates());
    QVERIFY(ps3==ps2);
    QVERIFY(ps3!=ps);
    QhullPoints ps4= ps3;
    QVERIFY(ps4==ps3);
    // ps4= ps3; //compiler error
    QhullPoints ps5(ps4);
    QVERIFY(ps5==ps4);
    QVERIFY(!(ps5!=ps4));
    coordT c2[]= {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    QhullPoints ps6(2, 6, c2);
    QVERIFY(ps6==ps2);
}//t_construct

void QhullPoints_test::
t_convert()
{
    //defineAs tested above
    coordT c[]= {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    QhullPoints ps(3, 6, c);
    QCOMPARE(ps.dimension(), 3);
    QCOMPARE(ps.size(), 2u);
    const coordT *c2= ps.constData();
    QCOMPARE(c, c2);
    const coordT *c3= ps.data();
    QCOMPARE(c, c3);
    coordT *c4= ps.data();
    QCOMPARE(c, c4);
    std::vector<QhullPoint> vs= ps.toStdVector();
    QCOMPARE(vs.size(), 2u);
    QhullPoint p= vs[1];
    QCOMPARE(p[2], 5.0);
    QList<QhullPoint> qs= ps.toQList();
    QCOMPARE(qs.size(), 2);
    QhullPoint p2= qs[1];
    QCOMPARE(p2[2], 5.0);
}//t_convert

void QhullPoints_test::
t_getset()
{
    //See t_construct for coordinates, count, defineAs, dimension, empty, isempty, ==, !=, size
    coordT c[]= {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    QhullPoints ps(3, 6, c);
    QhullPoints ps2(3, 6, c);
    QCOMPARE(ps2.dimension(), 3);
    QCOMPARE(ps2.coordinates(), c);
    QCOMPARE(ps2.count(), 2);
    QCOMPARE(ps2.coordinateCount(), 6);
    coordT c2[]= {-1.0, -2.0, -3.0, -4.0, -5.0, -6.0};
    ps2.defineAs(6, c2);
    QCOMPARE(ps2.coordinates(), c2);
    QCOMPARE(ps2.count(), 2);
    QCOMPARE(ps2.size(), 2u);
    QCOMPARE(ps2.dimension(), 3);
    QVERIFY(!ps2.isEmpty());
    QVERIFY(ps!=ps2);
    // ps2= ps; // assignment not available, compiler error
    ps2.defineAs(ps);
    QVERIFY(ps==ps2);
    ps2.setDimension(2);
    QCOMPARE(ps2.dimension(), 2);
    QCOMPARE(ps2.coordinates(), c);
    QVERIFY(!ps2.isEmpty());
    QCOMPARE(ps2.count(), 3);
    QCOMPARE(ps2.size(), 3u);
    QVERIFY(ps!=ps2);
    QhullPoints ps3(3);
    ps3.defineAs(5, c2);
    QCOMPARE(ps3.count(), 1);
    QCOMPARE(ps3.extraCoordinatesCount(), 2);
    QCOMPARE(ps3.extraCoordinates()[0], -4.0);
    QVERIFY(ps3.includesCoordinates(ps3.data()));
    QVERIFY(ps3.includesCoordinates(ps3.data()+ps3.count()-1));
    QVERIFY(!ps3.includesCoordinates(ps3.data()-1));
    QVERIFY(!ps3.includesCoordinates(ps3.data()+ps3.coordinateCount()));
}//t_getset


void QhullPoints_test::
t_element()
{
    coordT c[]= {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    QhullPoints ps(2, 6, c);
    QhullPoint p(2, c);
    QCOMPARE(ps[0], p);
    QCOMPARE(ps.at(1), ps[1]);
    QCOMPARE(ps.first(), p);
    QCOMPARE(ps.front(), ps.first());
    QCOMPARE(ps.last(), ps.at(2));
    QCOMPARE(ps.back(), ps.last());
    QhullPoints ps2= ps.mid(2);
    QCOMPARE(ps2.count(), 1);
    QhullPoints ps3= ps.mid(3);
    QVERIFY(ps3.isEmpty());
    QVERIFY(ps3.empty());
    QhullPoints ps4= ps.mid(10);
    QVERIFY(ps4.isEmpty());
    QhullPoints ps5= ps.mid(-1);
    QVERIFY(ps5.isEmpty());
    QhullPoints ps6= ps.mid(1, 1);
    QCOMPARE(ps6.count(), 1);
    QCOMPARE(ps6[0], ps[1]);
    QhullPoints ps7= ps.mid(1, 10);
    QCOMPARE(ps7.count(), 2);
    QCOMPARE(ps7[1], ps[2]);
    QhullPoint p8;
    QCOMPARE(ps.value(2), ps[2]);
    QCOMPARE(ps.value(-1), p8);
    QCOMPARE(ps.value(3), p8);
    QCOMPARE(ps.value(3, p), p);
    QVERIFY(ps.value(1, p)!=p);
    foreach(QhullPoint p, ps){  // Qt only
        QCOMPARE(p.dimension(), 2);
        QVERIFY(p[0]==0.0 || p[0]==2.0 || p[0]==4.0);
    }
}//t_element

void QhullPoints_test::
t_iterator()
{
    coordT c[]= {0.0, 1.0, 2.0};
    QhullPoints ps(1, 3, c);
    QhullPoints::Iterator i(ps);
    QhullPoints::iterator i2= ps.begin();
    QVERIFY(i==i2);
    QVERIFY(i>=i2);
    QVERIFY(i<=i2);
    i= ps.begin();
    QVERIFY(i==i2);
    i2= ps.end();
    QVERIFY(i!=i2);
    QhullPoint p(i); // QhullPoint is the base class for QhullPoints::iterator
    QCOMPARE(p.dimension(), ps.dimension());
    QCOMPARE(p.coordinates(), ps.coordinates());
    i2--;
    QhullPoint p2= *i2;
    QCOMPARE(p[0], 0.0);
    QCOMPARE(p2[0], 2.0);
    QhullPoints::Iterator i5(i2);
    QCOMPARE(*i2, *i5);
    coordT c3[]= {0.0, -1.0, -2.0};
    QhullPoints::Iterator i3(1, c3);
    QVERIFY(i!=i3);
    QCOMPARE(*i, *i3);

    (i3= i)++;
    QCOMPARE((*i3)[0], 1.0);
    QCOMPARE(i3->dimension(), 1);
    QCOMPARE(i3[0][0], 1.0);
    QCOMPARE(i3[0], ps[1]);

    QVERIFY(i==i);
    QVERIFY(i!=i2);
    QVERIFY(i<i2);
    QVERIFY(i<=i2);
    QVERIFY(i2>i);
    QVERIFY(i2>=i);

    QhullPoints::ConstIterator i4(1, c);
    QVERIFY(i==i4); // iterator COMP const_iterator
    QVERIFY(i<=i4);
    QVERIFY(i>=i4);
    QVERIFY(i4==i); // const_iterator COMP iterator
    QVERIFY(i4<=i);
    QVERIFY(i4>=i);
    QVERIFY(i>=i4);
    QVERIFY(i4<=i);
    QVERIFY(i2!=i4);
    QVERIFY(i2>i4);
    QVERIFY(i2>=i4);
    QVERIFY(i4!=i2);
    QVERIFY(i4<i2);
    QVERIFY(i4<=i2);
    ++i4;
    QVERIFY(i<i4);
    QVERIFY(i<=i4);
    QVERIFY(i4>i);
    QVERIFY(i4>=i);

    i= ps.begin();
    i2= ps.begin();
    QCOMPARE(i, i2++);
    QCOMPARE(*i2, ps[1]);
    QCOMPARE(++i, i2);
    QCOMPARE(i, i2--);
    QCOMPARE(i2, ps.begin());
    QCOMPARE(--i, i2);
    QCOMPARE(i2+=3, ps.end());
    QCOMPARE(i2-=3, ps.begin());
    QCOMPARE(i2+0, ps.begin());
    QCOMPARE(i2+3, ps.end());
    i2 += 3;
    i= i2-0;
    QCOMPARE(i, i2);
    i= i2-3;
    QCOMPARE(i, ps.begin());
    QCOMPARE(i2-i, 3);

    //ps.begin end tested above

    // QhullPoints is const-only
}//t_iterator

void QhullPoints_test::
t_const_iterator()
{
    coordT c[]= {0.0, 1.0, 2.0};
    const QhullPoints ps(1, 3, c);
    QhullPoints::ConstIterator i(ps);
    QhullPoints::const_iterator i2= ps.begin();
    QVERIFY(i==i2);
    QVERIFY(i>=i2);
    QVERIFY(i<=i2);
    i= ps.begin();
    QVERIFY(i==i2);
    i2= ps.end();
    QVERIFY(i!=i2);
    QhullPoint p(i);
    QCOMPARE(p.dimension(), ps.dimension());
    QCOMPARE(p.coordinates(), ps.coordinates());
    i2--;
    QhullPoint p2= *i2;
    QCOMPARE(p[0], 0.0);
    QCOMPARE(p2[0], 2.0);
    QhullPoints::ConstIterator i5(i2);
    QCOMPARE(*i2, *i5);
    coordT c3[]= {0.0, -1.0, -2.0};
    QhullPoints::ConstIterator i3(1, c3);
    QVERIFY(i!=i3);
    QCOMPARE(*i, *i3);

    (i3= i)++;
    QCOMPARE((*i3)[0], 1.0);
    QCOMPARE(i3->dimension(), 1);
    QCOMPARE(i3[0][0], 1.0);
    QCOMPARE(i3[0][0], 1.0);
    QCOMPARE(i3[0], ps[1]);

    QVERIFY(i==i);
    QVERIFY(i!=i2);
    QVERIFY(i<i2);
    QVERIFY(i<=i2);
    QVERIFY(i2>i);
    QVERIFY(i2>=i);

    // See t_iterator for const_iterator COMP iterator

    i= ps.begin();
    i2= ps.constBegin();
    QCOMPARE(i, i2++);
    QCOMPARE(*i2, ps[1]);
    QCOMPARE(++i, i2);
    QCOMPARE(i, i2--);
    QCOMPARE(i2, ps.constBegin());
    QCOMPARE(--i, i2);
    QCOMPARE(i2+=3, ps.constEnd());
    QCOMPARE(i2-=3, ps.constBegin());
    QCOMPARE(i2+0, ps.constBegin());
    QCOMPARE(i2+3, ps.constEnd());
    i2 += 3;
    i= i2-0;
    QCOMPARE(i, i2);
    i= i2-3;
    QCOMPARE(i, ps.constBegin());
    QCOMPARE(i2-i, 3);

    // QhullPoints is const-only
}//t_const_iterator


void QhullPoints_test::
t_search()
{
    coordT c[]= {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 0, 1};
    QhullPoints ps(2, 8, c); //2-d array of 4 points
    QhullPoint p= ps.first();
    QhullPoint p2= ps.last();
    QVERIFY(ps.contains(p));
    QVERIFY(ps.contains(p2));
    QVERIFY(p==p2);
    QhullPoint p5= ps[2];
    QVERIFY(p!=p5);
    QVERIFY(ps.contains(p5));
    coordT c2[]= {0.0, 1.0, 2.0, 3.0};
    QhullPoint p3(2, c2); //2-d point
    QVERIFY(ps.contains(p3));
    QhullPoint p4(3, c2); //3-d point
    QVERIFY(!ps.contains(p4));
    p4.defineAs(2, c); //2-d point
    QVERIFY(ps.contains(p4));
    p4.defineAs(2, c+1); //2-d point
    QVERIFY(!ps.contains(p4));
    QhullPoint p6(2, c2+2); //2-d point
    QCOMPARE(ps.count(p), 2);
    QCOMPARE(ps.count(p2), 2);
    QCOMPARE(ps.count(p3), 2);
    QCOMPARE(ps.count(p4), 0);
    QCOMPARE(ps.count(p6), 1);
    QCOMPARE(ps.indexOf(&ps[0][0]), 0);
    //QCOMPARE(ps.indexOf(ps.end()), -1); //ps.end() is a QhullPoint which may match
    QCOMPARE(ps.indexOf(0), -1);
    QCOMPARE(ps.indexOf(&ps[3][0]), 3);
    QCOMPARE(ps.indexOf(&ps[3][1], QhullError::NOthrow), 3);
    QCOMPARE(ps.indexOf(ps.data()+ps.coordinateCount(), QhullError::NOthrow), -1);
    QCOMPARE(ps.indexOf(p), 0);
    QCOMPARE(ps.indexOf(p2), 0);
    QCOMPARE(ps.indexOf(p3), 0);
    QCOMPARE(ps.indexOf(p4), -1);
    QCOMPARE(ps.indexOf(p5), 2);
    QCOMPARE(ps.indexOf(p6), 1);
    QCOMPARE(ps.lastIndexOf(p), 3);
    QCOMPARE(ps.lastIndexOf(p4), -1);
    QCOMPARE(ps.lastIndexOf(p6), 1);
    QhullPoints ps2(3);
    QCOMPARE(ps2.indexOf(ps2.data()), -1);
    QCOMPARE(ps2.indexOf(ps2.data()+1, QhullError::NOthrow), -1);
    QCOMPARE(ps2.indexOf(p), -1);
    QCOMPARE(ps2.lastIndexOf(p), -1);
    QhullPoints ps3;
    QCOMPARE(ps3.indexOf(ps3.data()), -1);
    QCOMPARE(ps3.indexOf(ps3.data()+1, QhullError::NOthrow), -1);
    QCOMPARE(ps3.indexOf(p), -1);
    QCOMPARE(ps3.lastIndexOf(p), -1);
    QhullPoints ps4(2, 0, c);
    QCOMPARE(ps4.indexOf(p), -1);
    QCOMPARE(ps4.lastIndexOf(p), -1);
}//t_search

void QhullPoints_test::
t_points_iterator()
{
    coordT c2[]= {0.0};
    QhullPoints ps2(0, 0, c2); // 0-dimensional
    QhullPointsIterator i2= ps2;
    QVERIFY(!i2.hasNext());
    QVERIFY(!i2.hasPrevious());
    i2.toBack();
    QVERIFY(!i2.hasNext());
    QVERIFY(!i2.hasPrevious());

    coordT c[]= {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    QhullPoints ps(3, 6, c); // 3-dimensional
    QhullPointsIterator i(ps);
    i2= ps;
    QVERIFY(i2.hasNext());
    QVERIFY(!i2.hasPrevious());
    QVERIFY(i.hasNext());
    QVERIFY(!i.hasPrevious());
    i2.toBack();
    i.toFront();
    QVERIFY(!i2.hasNext());
    QVERIFY(i2.hasPrevious());
    QVERIFY(i.hasNext());
    QVERIFY(!i.hasPrevious());

    QhullPoint p= ps[0];
    QhullPoint p2(ps[0]);
    QCOMPARE(p, p2);
    QVERIFY(p==p2);
    QhullPoint p3(ps[1]);
 // p2[0]= 0.0;
    QVERIFY(p==p2);
    QCOMPARE(i2.peekPrevious(), p3);
    QCOMPARE(i2.previous(), p3);
    QCOMPARE(i2.previous(), p);
    QVERIFY(!i2.hasPrevious());
    QCOMPARE(i.peekNext(), p);
    // i.peekNext()= 1.0; // compiler error
    QCOMPARE(i.next(), p);
    QCOMPARE(i.peekNext(), p3);
    QCOMPARE(i.next(), p3);
    QVERIFY(!i.hasNext());
    i.toFront();
    QCOMPARE(i.next(), p);
}//t_points_iterator

void QhullPoints_test::
t_io()
{
    QhullPoints ps;
    ostringstream os;
    os << "Empty QhullPoints\n" << ps << endl;
    coordT c[]= {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    QhullPoints ps2(3, 6, c); // 3-dimensional explicit
    os << "QhullPoints from c[]\n" << ps2 << endl;
    RboxPoints rcube("c");
    Qhull q(rcube,"Qt QR0");  // triangulation of rotated unit cube
    QhullPoints ps3= q.points();
    os << "QhullPoints\n" << ps3;
    os << "RunId\n" << ps3.print(q.runId());
    os << ps3.print(q.runId(), "RunId w/ message\n");
    os << ps3.printWithIdentifier(q.runId(), "RunId w/ identifiers\n");
    cout << os.str();
    QString s= QString::fromStdString(os.str());
    QCOMPARE(s.count("p"), 3*8+3);
    // QCOMPARE(s.count(QRegExp("f\\d")), 3*7 + 13*3*2);
}//t_io

}//orgQhull

#include "moc/QhullPoints_test.moc"
