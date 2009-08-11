/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtXmlPatterns module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the either Technology Preview License Agreement or the
** Beta Release License Agreement.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://qt.nokia.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QABSTRACTXMLFORWARDITERATOR_H
#define QABSTRACTXMLFORWARDITERATOR_H

#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtCore/QSharedData>


QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(XmlPatterns)

template<typename T> class QVector;

/* In this file we in some cases do not use QAbstractXmlForwardIterator's Ptr typedef.
 * This is a compiler workaround for MS VS 6.0. */

template<typename T>
inline bool qIsForwardIteratorEnd(const T &unit)
{
    return !unit;
}

template<typename T> class QAbstractXmlForwardIterator;

class QAbstractXmlForwardIteratorPrivate;

template<typename T>
class QAbstractXmlForwardIterator : public QSharedData
{
public:
    typedef QExplicitlySharedDataPointer<QAbstractXmlForwardIterator<T> > Ptr;
    typedef QList<QExplicitlySharedDataPointer<QAbstractXmlForwardIterator<T> > > List;
    typedef QVector<QExplicitlySharedDataPointer<QAbstractXmlForwardIterator<T> > > Vector;

    inline QAbstractXmlForwardIterator() {}
    virtual ~QAbstractXmlForwardIterator() {}

    virtual T next() = 0;
    virtual T current() const = 0;

    virtual qint64 position() const = 0;

    virtual typename QAbstractXmlForwardIterator<T>::Ptr toReversed();
    virtual QList<T> toList();
    virtual typename QAbstractXmlForwardIterator<T>::Ptr copy() const;
    virtual T last();
    virtual bool isEmpty();
    virtual qint64 count();
    virtual qint64 sizeHint() const;

private:
    Q_DISABLE_COPY(QAbstractXmlForwardIterator<T>)

    QAbstractXmlForwardIteratorPrivate *d_ptr; /* Currently not used. */
};

/* The namespace QPatternist and its members are internal, not part of the public API, and
 * unsupported. Using them leads to undefined behavior. */
namespace QPatternist
{
    class DeduplicateIterator;

    template<typename InputType,
             typename OutputType,
             typename Derived,
             typename ListType = QList<InputType> >
    class ListIteratorPlatform : public QAbstractXmlForwardIterator<OutputType>
    {
        /* This declaration is a workaround for a set of GCC versions on OS X,
         * amongst others powerpc-apple-darwin8-gcc-4.0.1 (GCC) 4.0.1. In
         * DeduplicateIterator, it fails to see the protected inheritance. */
        friend class DeduplicateIterator;

    public:
        virtual OutputType next()
        {
            if(m_position == -1)
                return OutputType();

            if(m_position == m_list.count())
            {
                m_position = -1;
                m_current = OutputType();
                return OutputType();
            }

            m_current = static_cast<const Derived *>(this)->inputToOutputItem(m_list.at(m_position));
            ++m_position;
            return m_current;
        }

        virtual OutputType current() const
        {
            return m_current;
        }

        virtual qint64 position() const
        {
            return m_position;
        }

        virtual qint64 count()
        {
            return m_list.count();
        }

        virtual typename QAbstractXmlForwardIterator<OutputType>::Ptr copy() const
        {
            return QExplicitlySharedDataPointer<QAbstractXmlForwardIterator<OutputType> >(new ListIteratorPlatform<InputType, OutputType, Derived, ListType>(m_list));
        }

    protected:
        inline ListIteratorPlatform(const ListType &list) : m_list(list)
                                                           , m_position(0)
        {
        }

        const ListType  m_list;
        qint64          m_position;
        OutputType      m_current;
    };

    template<typename T,
             typename ListType = QList<T> >
    class ListIterator : public ListIteratorPlatform<T, T, ListIterator<T, ListType>, ListType>
    {
	/*
	 * This declaration is needed for MSVC 2005, 14.00.50727.42 for 80x86.
	 */
	friend class IteratorVector;

        using ListIteratorPlatform<T, T, ListIterator<T, ListType>, ListType>::m_list;

        static inline QVector<T> toVector(const QVector<T> &vector)
        {
            return vector;
        }

        static inline QVector<T> toVector(const QList<T> &list)
        {
            return list.toVector();
        }

        static inline QList<T> toList(const QVector<T> &vector)
        {
            return vector.toList();
        }

        static inline QList<T> toList(const QList<T> &list)
        {
            return list;
        }

    public:
        inline ListIterator(const ListType &list) : ListIteratorPlatform<T, T, ListIterator<T, ListType>, ListType>(list)
        {
        }

        virtual QList<T> toList()
        {
            return toList(m_list);
        }

        virtual QVector<T> toVector()
        {
            return toVector(m_list);
        }

    private:
        inline const T &inputToOutputItem(const T &inputType) const
        {
            return inputType;
        }
        friend class ListIteratorPlatform<T, T, ListIterator<T, ListType>, ListType>;

        // needed for MSVC 2005
        friend class DeduplicateIterator;
    };

    template<typename T>
    inline
    typename QAbstractXmlForwardIterator<T>::Ptr
    makeListIterator(const QList<T> &list)
    {
        return typename ListIterator<T>::Ptr(new ListIterator<T>(list));
    }

    template<typename T>
    inline
    typename QAbstractXmlForwardIterator<T>::Ptr
    makeVectorIterator(const QVector<T> &vector)
    {
        return typename ListIterator<T, QVector<T> >::Ptr(new ListIterator<T, QVector<T> >(vector));
    }
}

template<typename T>
QList<T> QAbstractXmlForwardIterator<T>::toList()
{
    QList<T> result;
    T item(next());

    while(!qIsForwardIteratorEnd(item))
    {
        result.append(item);
        item = next();
    }

    return result;
}

template<typename T>
qint64 QAbstractXmlForwardIterator<T>::count()
{
    qint64 retval = 0;

    while(!qIsForwardIteratorEnd(next()))
        ++retval;

    return retval;
}

template<typename T>
typename QAbstractXmlForwardIterator<T>::Ptr QAbstractXmlForwardIterator<T>::toReversed()
{
    T item(next());
    QList<T> result;

    while(!qIsForwardIteratorEnd(item))
    {
        result.prepend(item);
        item = next();
    }

    return QExplicitlySharedDataPointer<QAbstractXmlForwardIterator<T> >(new QPatternist::ListIterator<T>(result));
}

template<typename T>
T QAbstractXmlForwardIterator<T>::last()
{
    T item(next());

    while(!qIsForwardIteratorEnd(item))
        item = next();

    return item;
}

template<typename T>
typename QAbstractXmlForwardIterator<T>::Ptr QAbstractXmlForwardIterator<T>::copy() const
{
    Q_ASSERT_X(false, Q_FUNC_INFO,
               "This function is internal, unsupported, and should never be called.");
    return typename QAbstractXmlForwardIterator<T>::Ptr();
}

template<typename T>
bool QAbstractXmlForwardIterator<T>::isEmpty()
{
    return qIsForwardIteratorEnd(next());
}

template<typename T>
qint64 QAbstractXmlForwardIterator<T>::sizeHint() const
{
    Q_ASSERT_X(false, Q_FUNC_INFO, "This function is currently not expected to be used.");
    return -1;
}

QT_END_NAMESPACE

QT_END_HEADER

#endif
