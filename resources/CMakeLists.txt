# Add QML files to project tree in Qt Creator
file(GLOB QML_DESKTOP "./*.qml")
add_custom_target(QML_files SOURCES ${QML_DESKTOP})
