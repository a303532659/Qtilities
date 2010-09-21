/****************************************************************************
**
** Copyright (c) 2009-2010, Jaco Naude
**
** This file is part of Qtilities which is released under the following
** licensing options.
**
** Option 1: Open Source
** Under this license Qtilities is free software: you can
** redistribute it and/or modify it under the terms of the GNU General
** Public License as published by the Free Software Foundation, either
** version 3 of the License, or (at your option) any later version.
**
** Qtilities is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Qtilities. If not, see http://www.gnu.org/licenses/.
**
** Option 2: Commercial
** Alternatively, this library is also released under a commercial license
** that allows the development of closed source proprietary applications
** without restrictions on licensing. For more information on this option,
** please see the project website's licensing page:
** http://www.qtilities.org/licensing.html
**
** If you are unsure which license is appropriate for your use, please
** contact support@qtilities.org.
**
****************************************************************************/

#include <QApplication>

#include <QtilitiesCoreGui>
using namespace Qtilities::Core;
using namespace Qtilities::CoreGui;
using namespace Qtilities::CoreGui::Icons;

int main(int argc, char *argv[])
{
    QtilitiesApplication a(argc, argv);
    QtilitiesApplication::setOrganizationName("Jaco Naude");
    QtilitiesApplication::setOrganizationDomain("Qtilities");
    QtilitiesApplication::setApplicationName("Building Tree Structures Example");
    QtilitiesApplication::setApplicationVersion(QtilitiesApplication::qtilitiesVersion());

    // Create the tree nodes:
    TreeNode* nodeA = new TreeNode("Node A");
    nodeA->enableActivityControl(ObserverHints::CheckboxActivityDisplay,ObserverHints::FollowSelection);
    TreeNode* nodeB = nodeA->addNode("Node B");
    TreeNode* nodeC = nodeA->addNode("Node C");
    nodeB->enableActivityControl(ObserverHints::CheckboxActivityDisplay,ObserverHints::FollowSelection);
    /*ObserverHints::DisplayFlags display_flags = 0;
    display_flags |= ObserverHints::ItemView;
    display_flags |= ObserverHints::NavigationBar;
    display_flags |= ObserverHints::ActionToolBar;
    nodeA->displayHints()->setDisplayFlagsHint(display_flags);
    nodeB->displayHints()->setDisplayFlagsHint(display_flags);
    nodeC->displayHints()->setDisplayFlagsHint(display_flags);*/
    nodeB->enableNamingControl(ObserverHints::EditableNames,NamingPolicyFilter::ProhibitDuplicateNames);
    nodeB->setCategorizedDisplayEnabled(true);

    // Create the tree items:
    nodeA->addItem("Item 1")->setToolTip("Hello, I'm a ToolTip.");
    nodeB->addItem("Item 2",QtilitiesCategory("Test Category::Sub Category","::"));
    nodeB->addItem("Item 3");
    nodeB->addItem("Item 4");
    nodeB->addItem("Item 5");
    TreeItem* active_item = nodeB->addItem("Item 6");
    nodeB->addItem("Item 7");

    // Add some formatting to the nodes:
    /*nodeA->setForegroundRole(QBrush(Qt::darkRed));
    nodeA->setFont(QFont("Helvetica [Cronyx]",20));
    nodeA->setAlignment(Qt::AlignCenter);
    nodeA->setBackgroundRole(QBrush(Qt::gray));
    nodeB->setForegroundRole(QBrush(Qt::darkGreen));
    nodeB->setFont(QFont("Helvetica [Cronyx]",20));
    nodeB->setAlignment(Qt::AlignCenter);
    nodeB->setBackgroundRole(QBrush(Qt::gray));
    nodeC->setForegroundRole(QBrush(Qt::darkYellow));
    nodeC->setFont(QFont("Helvetica [Cronyx]",20));
    nodeC->setAlignment(Qt::AlignCenter);
    nodeC->setBackgroundRole(QBrush(Qt::gray));*/

    /*nodeC->startProcessingCycle();
    for (int i = 0; i < 100; i++) {
        nodeC->addItem(QString("Batch Item").arg(i));
    }
    nodeC->endProcessingCycle();*/

    // Test activity:
    QList<QObject*> active_subjects;
    active_subjects << active_item;
    nodeB->activityPolicyFilter()->setActiveSubjects(active_subjects);

    // Test XML tree streaming:
    QString path_formatted = QString("%1/test_formatted.xml").arg(QApplication::applicationDirPath());
    nodeA->saveToFile(path_formatted);
    nodeA->loadFromFile(path_formatted);

    // Create an observer widget wih the items:
    ObserverWidget* tree_widget = new ObserverWidget();
    QtilitiesApplication::setMainWindow(tree_widget);
    tree_widget->setObserverContext(nodeA);
    tree_widget->initialize();
    tree_widget->show();

    return a.exec();
}
