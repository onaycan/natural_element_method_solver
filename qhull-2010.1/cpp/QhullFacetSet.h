/****************************************************************************
**
** Copyright (C) 2008-2010 C.B. Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/QhullFacetSet.h#23 $$Change: 1172 $
** $DateTime: 2010/01/09 21:42:16 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLFACETSET_H
#define QHULLFACETSET_H

#include "QhullSet.h"

#include <ostream>

namespace orgQhull {

#//ClassRef
    class               QhullFacet;

#//Types
    //! QhullFacetSet -- a set of Qhull facets, as a C++ class.  See QhullFacetList.h
    class               QhullFacetSet;
    typedef QhullSetIterator<QhullFacet>
                        QhullFacetSetIterator;

class QhullFacetSet : public QhullSet<QhullFacet> {

private:
#//Fields
    bool                select_all;   //! True if include bad facets.  Default is false.

public:
#//Constructor
                        //Conversion from setT* is not type-safe.  Implicit conversion for void* to T
   explicit             QhullFacetSet(setT *s) : QhullSet<QhullFacet>(s), select_all(false) {}
                        //Copy constructor copies pointer but not contents.  Needed for return by value.
                        QhullFacetSet(const QhullFacetSet &o) : QhullSet<QhullFacet>(o), select_all(o.select_all) {}

private:
                        //!Disable default constructor and copy assignment.  See QhullSetBase
                        QhullFacetSet();
    QhullFacetSet      &operator=(const QhullFacetSet &);
public:

#//Conversion
#ifndef QHULL_NO_STL
    std::vector<QhullFacet> toStdVector() const;
#endif //QHULL_NO_STL
#ifdef QHULL_USES_QT
    QList<QhullFacet>   toQList() const;
#endif //QHULL_USES_QT

#//GetSet
    bool                isSelectAll() const { return select_all; }
    void                selectAll() { select_all= true; }
    void                selectGood() { select_all= false; }

#//Read-only
                        //! Filtered by facet.isGood().  May be 0 when !isEmpty().
    int                 count() const;
    bool                contains(const QhullFacet &f) const;
    int                 count(const QhullFacet &f) const;
                        //! operator==() does not depend on isGood()

#//IO
    // Not same as QhullFacetList#IO.  A QhullFacetSet is a component of a QhullFacetList.

    struct PrintFacetSet{
        const QhullFacetSet *facet_set;
        const char     *message;
        int             run_id;
                        PrintFacetSet(int qhRunId, const char *message, const QhullFacetSet *s) : facet_set(s), message(message), run_id(qhRunId) {}
    };//PrintFacetSet
    const PrintFacetSet       print(int qhRunId, const char *message) const { return PrintFacetSet(qhRunId, message, this); }

    struct PrintIdentifiers{
        const QhullFacetSet *facet_set;
        const char     *message;
                        PrintIdentifiers(const char *message, const QhullFacetSet *s) : facet_set(s), message(message) {}
    };//PrintIdentifiers
    PrintIdentifiers    printIdentifiers(const char *message) const { return PrintIdentifiers(message, this); }

};//class QhullFacetSet

}//namespace orgQhull

#//== Global namespace =========================================

std::ostream &operator<<(std::ostream &os, const orgQhull::QhullFacetSet &fs);
std::ostream &operator<<(std::ostream &os, const orgQhull::QhullFacetSet::PrintFacetSet &pr);
std::ostream &operator<<(std::ostream &os, const orgQhull::QhullFacetSet::PrintIdentifiers &p);

#endif // QHULLFACETSET_H
