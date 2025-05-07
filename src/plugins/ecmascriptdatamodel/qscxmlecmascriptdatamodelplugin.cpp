// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#include "QtScxml/qscxmldatamodel.h"
#include "qscxmlecmascriptdatamodel_p.h"
#include "qscxmlecmascriptdatamodelplugin_p.h"

QT_BEGIN_NAMESPACE

QScxmlDataModel *QScxmlEcmaScriptDataModelPlugin::createScxmlDataModel() const
{
    return new QScxmlEcmaScriptDataModel;
}

QT_END_NAMESPACE
