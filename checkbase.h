/**********************************************************************
**  Copyright (C) 2015 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
**  Author: Sérgio Martins <sergio.martins@kdab.com>
**
** This file may be distributed and/or modified under the terms of the
** GNU Lesser General Public License version 2.1 and version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE.LGPL.txt included.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**********************************************************************/

#ifndef CHECK_BASE_H
#define CHECK_BASE_H

#include <clang/Frontend/CompilerInstance.h>
#include <string>

namespace clang {
class CXXMethodDecl;
class Stmt;
class Decl;
class ParentMap;
class TranslationUnitDecl;
class FixItHint;
}

class CheckBase
{
public:
    typedef std::vector<std::unique_ptr<CheckBase> > List;
    explicit CheckBase(const std::string &name);
    ~CheckBase();

    void VisitStatement(clang::Stmt *stm);
    void VisitDeclaration(clang::Decl *stm);

    std::string name() const;

    void setParentMap(clang::ParentMap *parentMap);

protected:
    virtual void VisitStmt(clang::Stmt *stm);
    virtual void VisitDecl(clang::Decl *decl);
    bool shouldIgnoreFile(const std::string &filename) const;
    virtual std::vector<std::string> filesToIgnore() const;
    void emitWarning(clang::SourceLocation loc, std::string error, bool printWarningTag = true) const;
    void emitWarning(clang::SourceLocation loc, std::string error, const std::vector<clang::FixItHint> &fixits, bool printWarningTag = true) const;

    void emitManualFixitWarning(clang::SourceLocation loc);

    clang::CompilerInstance &m_ci;
    clang::TranslationUnitDecl *m_tu;
    clang::ParentMap *m_parentMap;
    clang::CXXMethodDecl *m_lastMethodDecl;
    std::string m_name;
};

#endif
