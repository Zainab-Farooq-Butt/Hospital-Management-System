import QtQuick
import QtQuick.Controls

Window {
    width: 680
    height: 500
    visible: true
    title: "Hospital Management System"

    Rectangle {
        anchors.fill: parent
        color: "#EAF6FB"

        StackView {
            id: stack
            anchors.fill: parent
            initialItem: menuPage
        }

        Component {
            id: menuPage
            Rectangle {
                anchors.fill: parent
                color: "#EAF6FB"

                Rectangle {
                    width: parent.width
                    height: 80
                    color: "#005F6B"
                    Text {
                        anchors.centerIn: parent
                        text: "🏥  Hospital Management System"
                        font.pixelSize: 24
                        font.bold: true
                        color: "white"
                        font.letterSpacing: 1.2
                    }
                }

                Column {
                    anchors.centerIn: parent
                    anchors.verticalCenterOffset: 40
                    spacing: 20

                    Text {
                        text: "Select a module to continue"
                        font.pixelSize: 14
                        color: "#007B8A"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Rectangle {
                        width: 280; height: 60; radius: 12; color: "#3A9AD9"
                        Row {
                            anchors.centerIn: parent
                            spacing: 12
                            Text { text: "👨‍⚕️"; font.pixelSize: 22; anchors.verticalCenter: parent.verticalCenter }
                            Text { text: "Doctor Form"; font.pixelSize: 17; font.bold: true; color: "white"; anchors.verticalCenter: parent.verticalCenter }
                        }
                        MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: stack.push(doctorPage) }
                    }

                    Rectangle {
                        width: 280; height: 60; radius: 12; color: "#007B8A"
                        Row {
                            anchors.centerIn: parent
                            spacing: 12
                            Text { text: "📅"; font.pixelSize: 22; anchors.verticalCenter: parent.verticalCenter }
                            Text { text: "Appointment Form"; font.pixelSize: 17; font.bold: true; color: "white"; anchors.verticalCenter: parent.verticalCenter }
                        }
                        MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: stack.push(appointmentPage) }
                    }
                }

                Rectangle {
                    width: parent.width; height: 36; anchors.bottom: parent.bottom; color: "#005F6B"
                    Text { anchors.centerIn: parent; text: "Hospital Management System  •  v1.0"; color: "#B2DFF7"; font.pixelSize: 11 }
                }
            }
        }

        Component {
            id: doctorPage
            Rectangle {
                id: doctorRoot
                anchors.fill: parent
                color: "#EAF6FB"

                property string msgText: ""
                property string msgColor: "#005F6B"
                property bool showMsg: false

                Rectangle {
                    width: parent.width; height: 80; color: "#005F6B"
                    Text {
                        anchors.centerIn: parent
                        text: "👨‍⚕️  Doctor Form"
                        font.pixelSize: 22; font.bold: true; color: "white"; font.letterSpacing: 1.2
                    }
                }

                Column {
                    anchors.centerIn: parent
                    anchors.verticalCenterOffset: 30
                    spacing: 14

                    Column {
                        spacing: 4
                        Text { text: "Doctor Name"; font.pixelSize: 12; color: "#005F6B"; font.bold: true }
                        Rectangle {
                            width: 300; height: 42; radius: 8; color: "white"
                            border.color: "#6BCBEB"; border.width: 1
                            TextField {
                                id: nameField
                                anchors.fill: parent; anchors.margins: 4
                                placeholderText: "Enter doctor name"
                                background: Rectangle { color: "transparent" }
                                font.pixelSize: 13
                            }
                        }
                    }

                    Column {
                        spacing: 4
                        Text { text: "Specialty"; font.pixelSize: 12; color: "#005F6B"; font.bold: true }
                        Rectangle {
                            width: 300; height: 42; radius: 8; color: "white"
                            border.color: "#6BCBEB"; border.width: 1
                            TextField {
                                id: specField
                                anchors.fill: parent; anchors.margins: 4
                                placeholderText: "e.g. Cardiologist"
                                background: Rectangle { color: "transparent" }
                                font.pixelSize: 13
                            }
                        }
                    }

                    Column {
                        spacing: 4
                        Text { text: "Availability"; font.pixelSize: 12; color: "#005F6B"; font.bold: true }
                        Rectangle {
                            width: 300; height: 42; radius: 8; color: "white"
                            border.color: "#6BCBEB"; border.width: 1
                            TextField {
                                id: availField
                                anchors.fill: parent; anchors.margins: 4
                                placeholderText: "e.g. Mon - Fri, 9am - 5pm"
                                background: Rectangle { color: "transparent" }
                                font.pixelSize: 13
                            }
                        }
                    }

                    Rectangle {
                        width: 300; height: 36; radius: 8
                        visible: doctorRoot.showMsg
                        color: doctorRoot.msgColor === "#005F6B" ? "#d4f5e9" : "#fde8e8"
                        Text {
                            anchors.centerIn: parent
                            text: doctorRoot.msgText
                            color: doctorRoot.msgColor
                            font.pixelSize: 13
                            font.bold: true
                        }
                    }

                    Row {
                        spacing: 14

                        Rectangle {
                            width: 143; height: 44; radius: 10; color: "#3A9AD9"
                            Text { anchors.centerIn: parent; text: "Add Doctor"; font.pixelSize: 14; font.bold: true; color: "white" }
                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    if (nameField.text === "" || specField.text === "" || availField.text === "") {
                                        doctorRoot.msgText = "⚠️ Please fill all fields!"
                                        doctorRoot.msgColor = "#c0392b"
                                    } else {
                                        doctorRoot.msgText = "✅ Doctor added successfully!"
                                        doctorRoot.msgColor = "#005F6B"
                                    }
                                    doctorRoot.showMsg = true
                                }
                            }
                        }

                        Rectangle {
                            width: 143; height: 44; radius: 10; color: "#005F6B"
                            Text { anchors.centerIn: parent; text: "⬅  Back"; font.pixelSize: 14; font.bold: true; color: "white" }
                            MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: stack.pop() }
                        }
                    }
                }

                Rectangle {
                    width: parent.width; height: 36; anchors.bottom: parent.bottom; color: "#005F6B"
                    Text { anchors.centerIn: parent; text: "Hospital Management System  •  v1.0"; color: "#B2DFF7"; font.pixelSize: 11 }
                }
            }
        }

        Component {
            id: appointmentPage
            Rectangle {
                id: apptRoot
                anchors.fill: parent
                color: "#EAF6FB"

                property string msgText: ""
                property string msgColor: "#005F6B"
                property bool showMsg: false

                Rectangle {
                    width: parent.width; height: 80; color: "#005F6B"
                    Text {
                        anchors.centerIn: parent
                        text: "📅  Appointment Form"
                        font.pixelSize: 22; font.bold: true; color: "white"; font.letterSpacing: 1.2
                    }
                }

                Column {
                    anchors.centerIn: parent
                    anchors.verticalCenterOffset: 30
                    spacing: 14

                    Column {
                        spacing: 4
                        Text { text: "Patient Name"; font.pixelSize: 12; color: "#005F6B"; font.bold: true }
                        Rectangle {
                            width: 300; height: 42; radius: 8; color: "white"
                            border.color: "#6BCBEB"; border.width: 1
                            TextField {
                                id: patientField
                                anchors.fill: parent; anchors.margins: 4
                                placeholderText: "Enter patient name"
                                background: Rectangle { color: "transparent" }
                                font.pixelSize: 13
                            }
                        }
                    }

                    Column {
                        spacing: 4
                        Text { text: "Doctor Name"; font.pixelSize: 12; color: "#005F6B"; font.bold: true }
                        Rectangle {
                            width: 300; height: 42; radius: 8; color: "white"
                            border.color: "#6BCBEB"; border.width: 1
                            TextField {
                                id: apptDoctorField
                                anchors.fill: parent; anchors.margins: 4
                                placeholderText: "Enter doctor name"
                                background: Rectangle { color: "transparent" }
                                font.pixelSize: 13
                            }
                        }
                    }

                    Column {
                        spacing: 4
                        Text { text: "Appointment Date"; font.pixelSize: 12; color: "#005F6B"; font.bold: true }
                        Rectangle {
                            width: 300; height: 42; radius: 8; color: "white"
                            border.color: "#6BCBEB"; border.width: 1
                            TextField {
                                id: dateField
                                anchors.fill: parent; anchors.margins: 4
                                placeholderText: "e.g. 2025-05-01"
                                background: Rectangle { color: "transparent" }
                                font.pixelSize: 13
                            }
                        }
                    }

                    Rectangle {
                        width: 300; height: 36; radius: 8
                        visible: apptRoot.showMsg
                        color: apptRoot.msgColor === "#005F6B" ? "#d4f5e9" : "#fde8e8"
                        Text {
                            anchors.centerIn: parent
                            text: apptRoot.msgText
                            color: apptRoot.msgColor
                            font.pixelSize: 13
                            font.bold: true
                        }
                    }

                    Row {
                        spacing: 10

                        Rectangle {
                            width: 140; height: 44; radius: 10; color: "#3A9AD9"
                            Text { anchors.centerIn: parent; text: "Book"; font.pixelSize: 14; font.bold: true; color: "white" }
                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    if (patientField.text === "" || apptDoctorField.text === "" || dateField.text === "") {
                                        apptRoot.msgText = "⚠️ Please fill all fields!"
                                        apptRoot.msgColor = "#c0392b"
                                    } else {
                                        apptRoot.msgText = "✅ Appointment booked!"
                                        apptRoot.msgColor = "#005F6B"
                                    }
                                    apptRoot.showMsg = true
                                }
                            }
                        }

                        Rectangle {
                            width: 140; height: 44; radius: 10; color: "#007B8A"
                            Text { anchors.centerIn: parent; text: "Cancel Appt"; font.pixelSize: 14; font.bold: true; color: "white" }
                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    apptRoot.msgText = "❌ Appointment cancelled!"
                                    apptRoot.msgColor = "#c0392b"
                                    apptRoot.showMsg = true
                                }
                            }
                        }

                        Rectangle {
                            width: 140; height: 44; radius: 10; color: "#005F6B"
                            Text { anchors.centerIn: parent; text: "⬅  Back"; font.pixelSize: 14; font.bold: true; color: "white" }
                            MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: stack.pop() }
                        }
                    }
                }

                Rectangle {
                    width: parent.width; height: 36; anchors.bottom: parent.bottom; color: "#005F6B"
                    Text { anchors.centerIn: parent; text: "Hospital Management System  •  v1.0"; color: "#B2DFF7"; font.pixelSize: 11 }
                }
            }
        }
    }
}
