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

#include "qmljsoutlinetreeview.h"
#include "qmloutlinemodel.h"

#include <utils/annotateditemdelegate.h>
#include <QMenu>

namespace QmlJSEditor {
namespace Internal {

QmlJSOutlineTreeView::QmlJSOutlineTreeView(QWidget *parent) :
    Utils::NavigationTreeView(parent)
{
    setExpandsOnDoubleClick(false);

    setDragEnabled(true);
    viewport()->setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(InternalMove);

    setRootIsDecorated(false);

    Utils::AnnotatedItemDelegate *itemDelegate = new Utils::AnnotatedItemDelegate(this);
    itemDelegate->setDelimiter(QLatin1String(" "));
    itemDelegate->setAnnotationRole(QmlOutlineModel::AnnotationRole);
    setItemDelegateForColumn(0, itemDelegate);
}

void QmlJSOutlineTreeView::contextMenuEvent(QContextMenuEvent *event)
{
    if (!event)
        return;

    QMenu contextMenu;

    QAction *action = contextMenu.addAction(tr("Expand All"));
    connect(action, &QAction::triggered, this, [this] () { expandAll(); });
    action = contextMenu.addAction(tr("Collapse All"));
    connect(action, &QAction::triggered, this, [this] () { collapseAllExceptRoot(); });

    contextMenu.exec(event->globalPos());

    event->accept();
}

void QmlJSOutlineTreeView::collapseAllExceptRoot()
{
    if (!model())
        return;
    const QModelIndex rootElementIndex = model()->index(0, 0, rootIndex());
    int rowCount = model()->rowCount(rootElementIndex);
    for (int i = 0; i < rowCount; ++i) {
        collapse(model()->index(i, 0, rootElementIndex));
    }
}

} // namespace Internal
} // namespace QmlJSEditor
