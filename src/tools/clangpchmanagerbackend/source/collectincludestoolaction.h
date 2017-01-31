/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
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
****************************************************************************/

#pragma once

#include "stringcache.h"

#include "collectincludesaction.h"

#include <clang/Tooling/Tooling.h>

namespace ClangBackEnd {

class CollectIncludesToolAction final : public clang::tooling::FrontendActionFactory
{
public:
    CollectIncludesToolAction(std::vector<uint> &includeIds,
                              StringCache<Utils::SmallString> &filePathCache,
                              const std::vector<uint> &excludedIncludeUIDs)
        : m_includeIds(includeIds),
          m_filePathCache(filePathCache),
          m_excludedIncludeUIDs(excludedIncludeUIDs)
    {}

    clang::FrontendAction *create()
    {
        return new CollectIncludesAction(m_includeIds,
                                         m_filePathCache,
                                         m_excludedIncludeUIDs,
                                         m_alreadyIncludedFileUIDs);
    }

private:
    std::vector<uint> m_alreadyIncludedFileUIDs;
    std::vector<uint> &m_includeIds;
    StringCache<Utils::SmallString> &m_filePathCache;
    const std::vector<uint> &m_excludedIncludeUIDs;
};

} // namespace ClangBackEnd