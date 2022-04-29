/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWidgets module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
******************************************************************************/

#include "qkeyeventtransition.h"
#include "qbasickeyeventtransition_p.h"
#include "qstatemachine.h"

#include <private/qeventtransition_p.h>

QT_BEGIN_NAMESPACE

/*!
  \class QKeyEventTransition

  \brief The QKeyEventTransition class provides a transition for key events.

  \since 4.6
  \ingroup statemachine
  \inmodule QtStateMachine

  QKeyEventTransition is part of \l{Qt State Machine Overview}{Qt State Machine Framework}.

  \sa QState::addTransition()
*/

/*!
    \property QKeyEventTransition::key

    \brief the key that this key event transition is associated with
*/

/*!
    \property QKeyEventTransition::modifierMask

    \brief the keyboard modifier mask that this key event transition checks for
*/

class QKeyEventTransitionPrivate : public QEventTransitionPrivate
{
    Q_DECLARE_PUBLIC(QKeyEventTransition)
public:
    QKeyEventTransitionPrivate() {}

    QBasicKeyEventTransition *transition;
};

/*!
  Constructs a new key event transition with the given \a sourceState.
*/
QKeyEventTransition::QKeyEventTransition(QState *sourceState)
    : QEventTransition(*new QKeyEventTransitionPrivate, sourceState)
{
    Q_D(QKeyEventTransition);
    d->transition = new QBasicKeyEventTransition();
}

/*!
  Constructs a new key event transition for events of the given \a type for
  the given \a object, with the given \a key and \a sourceState.
*/
QKeyEventTransition::QKeyEventTransition(QObject *object, QEvent::Type type,
                                         int key, QState *sourceState)
    : QEventTransition(*new QKeyEventTransitionPrivate, object, type, sourceState)
{
    Q_D(QKeyEventTransition);
    d->transition = new QBasicKeyEventTransition(type, key);
}

/*!
  Destroys this key event transition.
*/
QKeyEventTransition::~QKeyEventTransition()
{
    Q_D(QKeyEventTransition);
    delete d->transition;
}

/*!
  Returns the key that this key event transition checks for.
*/
int QKeyEventTransition::key() const
{
    Q_D(const QKeyEventTransition);
    return d->transition->key();
}

/*!
  Sets the \a key that this key event transition will check for.
*/
void QKeyEventTransition::setKey(int key)
{
    Q_D(QKeyEventTransition);
    d->transition->setKey(key);
}

QBindable<int> QKeyEventTransition::bindableKey()
{
    Q_D(QKeyEventTransition);
    return d->transition->bindableKey();
}

/*!
  Returns the keyboard modifier mask that this key event transition checks
  for.
*/
Qt::KeyboardModifiers QKeyEventTransition::modifierMask() const
{
    Q_D(const QKeyEventTransition);
    return d->transition->modifierMask();
}

/*!
  Sets the keyboard modifier mask that this key event transition will
  check for to \a modifierMask.
*/
void QKeyEventTransition::setModifierMask(Qt::KeyboardModifiers modifierMask)
{
    Q_D(QKeyEventTransition);
    d->transition->setModifierMask(modifierMask);
}

QBindable<Qt::KeyboardModifiers> QKeyEventTransition::bindableModifierMask()
{
    Q_D(QKeyEventTransition);
    return d->transition->bindableModifierMask();
}

/*!
  \reimp
*/
bool QKeyEventTransition::eventTest(QEvent *event)
{
    Q_D(const QKeyEventTransition);
    if (!QEventTransition::eventTest(event))
        return false;
    QStateMachine::WrappedEvent *we = static_cast<QStateMachine::WrappedEvent*>(event);
    d->transition->setEventType(we->event()->type());
    return QAbstractTransitionPrivate::get(d->transition)->callEventTest(we->event());
}

/*!
  \reimp
*/
void QKeyEventTransition::onTransition(QEvent *event)
{
    QEventTransition::onTransition(event);
}

QT_END_NAMESPACE

#include "moc_qkeyeventtransition.cpp"
