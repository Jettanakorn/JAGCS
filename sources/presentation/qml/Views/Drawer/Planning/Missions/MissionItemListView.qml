import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Views/Common"

Row {
    id: missionItemList

    property int missionId: 0
    property int selectedItemId: 0
    width: sizings.controlBaseSize * repeater.count

    property alias items: repeater.model

    signal selectionRequest(int itemId)
    signal checkItemX(real x)

    onMissionIdChanged: presenter.setMission(missionId)

    MissionItemListPresenter {
        id: presenter
        view: missionItemList
    }

    Controls.Label {
        id: label
        visible: repeater.count == 0
        text: qsTr("No waypoints")
        horizontalAlignment: Qt.AlignHCenter
        width: parent.width
    }

    Repeater {
        id: repeater

        Item {
            width: Math.min(itemView.implicitWidth, missionItemList.width / repeater.count)
            height: itemView.implicitHeight

            PointView {
                id: itemView
                anchors.centerIn: parent
                selected: selectedItemId === model.itemId
                sequence: model.sequence
                command: model.command
                reached: model.reached
                status: model.status
                onSelectedChanged: if (visible && selected) checkItemX(parent.x)
                onVisibleChanged: if (visible && selected) checkItemX(parent.x)

                MouseArea {
                    anchors.fill: parent
                    onClicked: missionItemList.selectionRequest(model.itemId)
                }
            }
        }
    }
}
