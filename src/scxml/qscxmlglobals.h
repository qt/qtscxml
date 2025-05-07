// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef QSCXMLGLOBALS_H
#define QSCXMLGLOBALS_H
#include <QtCore/qglobal.h>
#include <QtScxml/qtscxml-config.h>

#if defined(BUILD_QSCXMLC)
#  define Q_SCXML_EXPORT
#else
#  include <QtScxml/qtscxmlexports.h>
#endif

// Silence syncqt
QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

#endif // QSCXMLGLOBALS_H

