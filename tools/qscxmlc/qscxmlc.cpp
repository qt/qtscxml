/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtScxml module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtScxml/private/qscxmlparser_p.h>
#include <QtScxml/qscxmltabledata.h>
#include "scxmlcppdumper.h"

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QFileInfo>

enum {
    NoError = 0,
    CommandLineArgumentsError = -1,
    NoInputFilesError = -2,
    CannotOpenInputFileError = -3,
    ParseError = -4,
    CannotOpenOutputHeaderFileError = -5,
    CannotOpenOutputCppFileError = -6,
    ScxmlVerificationError = -7
};

int write(TranslationUnit *tu)
{
    QTextStream errs(stderr, QIODevice::WriteOnly);

    QFile outH(tu->outHFileName);
    if (!outH.open(QFile::WriteOnly)) {
        errs << QStringLiteral("Error: cannot open '%1': %2").arg(outH.fileName(), outH.errorString()) << endl;
        return CannotOpenOutputHeaderFileError;
    }

    QFile outCpp(tu->outCppFileName);
    if (!outCpp.open(QFile::WriteOnly)) {
        errs << QStringLiteral("Error: cannot open '%1': %2").arg(outCpp.fileName(), outCpp.errorString()) << endl;
        return CannotOpenOutputCppFileError;
    }

    QTextStream h(&outH);
    QTextStream c(&outCpp);
    CppDumper dumper(h, c);
    dumper.dump(tu);
    outH.close();
    outCpp.close();
    return NoError;
}

static void collectAllDocuments(DocumentModel::ScxmlDocument *doc, QMap<DocumentModel::ScxmlDocument *, QString> *docs)
{
    docs->insert(doc, doc->root->name);
    foreach (DocumentModel::ScxmlDocument *subDoc, doc->allSubDocuments) {
        collectAllDocuments(subDoc, docs);
    }
}

int run(QStringList arguments)
{
    QCommandLineParser cmdParser;
    QTextStream errs(stderr, QIODevice::WriteOnly);

    cmdParser.addHelpOption();
    cmdParser.addVersionOption();
    cmdParser.setApplicationDescription(QCoreApplication::translate("main",
                       "Compiles the given input.scxml file to a header and a cpp file."));

    QCommandLineOption optionNoCxx11(QLatin1String("no-c++11"),
                       QCoreApplication::translate("main", "Don't use C++11 in generated code."));
    QCommandLineOption optionNamespace(QLatin1String("namespace"),
                       QCoreApplication::translate("main", "Put generated code into <namespace>."),
                       QCoreApplication::translate("main", "namespace"));
    QCommandLineOption optionOutputBaseName(QStringList() << QLatin1String("o") << QLatin1String("output"),
                       QCoreApplication::translate("main", "Generate <name>.h and <name>.cpp files."),
                       QCoreApplication::translate("main", "name"));
    QCommandLineOption optionOutputHeaderName(QLatin1String("header"),
                       QCoreApplication::translate("main", "Generate <name> for the header file."),
                       QCoreApplication::translate("main", "name"));
    QCommandLineOption optionOutputSourceName(QLatin1String("impl"),
                       QCoreApplication::translate("main", "Generate <name> for the source file."),
                       QCoreApplication::translate("main", "name"));
    QCommandLineOption optionClassName(QLatin1String("classname"),
                       QCoreApplication::translate("main", "Generate <name> for state machine class name."),
                       QCoreApplication::translate("main", "name"));
    QCommandLineOption optionQtMode(QLatin1String("qt-mode"),
                       QCoreApplication::translate("main", "Enables or disables Qt mode. "
                                                           "In order to unconditionally enable qt-mode, specify \"yes\". "
                                                           "To unconditionally disable qt-mode, specify \"no\". "
                                                           "To read the setting from the input file, specify \"from-input\". "
                                                           "The default is \"from-input\"."),
                       QCoreApplication::translate("main", "mode"), QLatin1String("from-input"));

    cmdParser.addPositionalArgument(QLatin1String("input"),
                       QCoreApplication::translate("main", "Input SCXML file."));
    cmdParser.addOption(optionNoCxx11);
    cmdParser.addOption(optionNamespace);
    cmdParser.addOption(optionOutputBaseName);
    cmdParser.addOption(optionOutputHeaderName);
    cmdParser.addOption(optionOutputSourceName);
    cmdParser.addOption(optionClassName);
    cmdParser.addOption(optionQtMode);

    cmdParser.process(arguments);

    const QStringList inputFiles = cmdParser.positionalArguments();

    if (inputFiles.count() < 1) {
        errs << QCoreApplication::translate("main", "Error: no input file.") << endl;
        cmdParser.showHelp(NoInputFilesError);
    }

    if (inputFiles.count() > 1) {
        errs << QCoreApplication::translate("main", "Error: unexpected argument(s): %1")
                .arg(inputFiles.mid(1).join(QLatin1Char(' '))) << endl;
        cmdParser.showHelp(NoInputFilesError);
    }

    const QString scxmlFileName = inputFiles.at(0);

    TranslationUnit options;
    options.useCxx11 = !cmdParser.isSet(optionNoCxx11);
    if (cmdParser.isSet(optionNamespace))
        options.namespaceName = cmdParser.value(optionNamespace);
    QString outFileName = cmdParser.value(optionOutputBaseName);
    QString outHFileName = cmdParser.value(optionOutputHeaderName);
    QString outCppFileName = cmdParser.value(optionOutputSourceName);
    QString mainClassName = cmdParser.value(optionClassName);
    QString qtModeName = cmdParser.value(optionQtMode);

    QScxmlParser::QtMode qtMode = QScxmlParser::QtModeFromInputFile;

    if (qtModeName == QLatin1String("yes")) {
        qtMode = QScxmlParser::QtModeEnabled;
    } else if (qtModeName == QLatin1String("no")) {
        qtMode = QScxmlParser::QtModeDisabled;
    } else if (qtModeName == QLatin1String("from-input")) {
        qtMode = QScxmlParser::QtModeFromInputFile;
    } else {
        errs << QCoreApplication::translate("main", "Error: unexpected value for qt-mode option: %1")
                .arg(qtModeName) << endl;
        cmdParser.showHelp(CommandLineArgumentsError);
    }

    if (outFileName.isEmpty())
        outFileName = QFileInfo(scxmlFileName).baseName();
    if (outHFileName.isEmpty())
        outHFileName = outFileName + QLatin1String(".h");
    if (outCppFileName.isEmpty())
        outCppFileName = outFileName + QLatin1String(".cpp");

    QFile file(scxmlFileName);
    if (!file.open(QFile::ReadOnly)) {
        errs << QStringLiteral("Error: cannot open input file %1").arg(scxmlFileName);
        return CannotOpenInputFileError;
    }

    QXmlStreamReader reader(&file);
    QScxmlParser parser(&reader);
    parser.setFileName(file.fileName());
    parser.setQtMode(qtMode);
    parser.parse();
    if (!parser.errors().isEmpty()) {
        foreach (const QScxmlError &error, parser.errors()) {
            errs << error.toString() << endl;
        }
        return ParseError;
    }

    auto mainDoc = QScxmlParserPrivate::get(&parser)->scxmlDocument();
    if (mainDoc == nullptr) {
        Q_ASSERT(!parser.errors().isEmpty());
        foreach (const QScxmlError &error, parser.errors()) {
            errs << error.toString() << endl;
        }
        return ScxmlVerificationError;
    }

    QMap<DocumentModel::ScxmlDocument *, QString> docs;
    collectAllDocuments(mainDoc, &docs);
    if (mainClassName.isEmpty())
        mainClassName = mainDoc->root->name;
    if (mainClassName.isEmpty()) {
        mainClassName = QFileInfo(scxmlFileName).fileName();
        int dot = mainClassName.indexOf(QLatin1Char('.'));
        if (dot != -1)
            mainClassName = mainClassName.left(dot);
    }
    docs.insert(mainDoc, mainClassName);

    TranslationUnit tu = options;
    tu.scxmlFileName = QFileInfo(file).fileName();
    tu.mainDocument = mainDoc;
    tu.outHFileName = outHFileName;
    tu.outCppFileName = outCppFileName;
    for (QMap<DocumentModel::ScxmlDocument *, QString>::const_iterator i = docs.begin(), ei = docs.end(); i != ei; ++i) {
        auto name = i.value();
        if (name.isEmpty()) {
            name = QStringLiteral("%1_StateMachine_%2").arg(mainClassName).arg(tu.classnameForDocument.size() + 1);
        }
        tu.classnameForDocument.insert(i.key(), name);
    }

    return write(&tu);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationVersion(QString::fromLatin1("%1 (Qt %2)").arg(
                            QString::number(Q_QSCXMLC_OUTPUT_REVISION),
                            QString::fromLatin1(QT_VERSION_STR)));
    return run(QCoreApplication::arguments());
}
