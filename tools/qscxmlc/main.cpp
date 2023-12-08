// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#include <QtScxml/qscxmltabledata.h>
#include "qscxmlc.h"

#include <QCoreApplication>
#include <QStringList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationVersion(QString::fromLatin1("%1 (Qt %2)").arg(
                            QString::number(Q_QSCXMLC_OUTPUT_REVISION),
                            QString::fromLatin1(QT_VERSION_STR)));
    return run(QCoreApplication::arguments());
}
