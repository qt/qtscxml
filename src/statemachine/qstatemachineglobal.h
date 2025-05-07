// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef QSTATEMACHINEGLOBAL_H
#define QSTATEMACHINEGLOBAL_H

#include <QtCore/qglobal.h>
#include <QtStateMachine/qtstatemachine-config.h>

#if defined(BUILD_QSTATEMACHINE)
#  define Q_STATEMACHINE_EXPORT
#else
#  include <QtStateMachine/qtstatemachineexports.h>
#endif

#endif // QSTATEMACHINEGLOBAL_H
