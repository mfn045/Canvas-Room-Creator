cmake_minimum_required(VERSION 3.5)

project(Clubpenguin-Room-Creator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Svg)
find_package(Qt6 REQUIRED COMPONENTS SvgWidgets)
find_package(Qt6 REQUIRED COMPONENTS Xml)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)

set(PROJECT_SOURCES
        main.cpp
        roomcanvas.cpp
        roomcanvas.h
        roomcanvas.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Clubpenguin-Room-Creator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}


        widgets/layers.h
        widgets/layers.cpp
        resources.qrc
        widgets/canvas.h
        widgets/canvas.cpp
        Dialogs/propertiesdialog.h Dialogs/propertiesdialog.cpp Dialogs/propertiesdialog.ui
        Interface/MenuBar/menubar.h Interface/MenuBar/menubar.cpp
        Interface/Buttons/AbstractButton/abstractbutton.h Interface/Buttons/AbstractButton/abstractbutton.cpp
        Interface/Buttons/CircleButton/circlebutton.h Interface/Buttons/CircleButton/circlebutton.cpp
        Interface/Map/map.h Interface/Map/map.cpp
        Interface/News/news.h Interface/News/news.cpp
        Interface/Moderator/moderator.h Interface/Moderator/moderator.cpp
        Interface/Mail/mail.h Interface/Mail/mail.cpp
        Interface/Friend_Requests/friend_requests.h Interface/Friend_Requests/friend_requests.cpp
        Interface/TextBox/textbox.h Interface/TextBox/textbox.cpp
        Interface/ChatBubble/chatbubble.h Interface/ChatBubble/chatbubble.cpp
        Interface/Dialogs/abstractdialog.h Interface/Dialogs/abstractdialog.cpp
        widgets/scene.h widgets/scene.cpp
        Interface/Buttons/OrangeButton/orangebutton.h Interface/Buttons/OrangeButton/orangebutton.cpp
        Interface/Buttons/BlueButton/bluebutton.h Interface/Buttons/BlueButton/bluebutton.cpp
        Interface/Dialogs/YesNoDialog/yesnodialog.h Interface/Dialogs/YesNoDialog/yesnodialog.cpp
        Interface/TextLabel/textlabel.h Interface/TextLabel/textlabel.cpp
        Interface/TextLabel/textlabelinput.h Interface/TextLabel/textlabelinput.cpp
        Interface/ChatHistory/chathistory.h Interface/ChatHistory/chathistory.cpp
        Interface/Buttons/BlueRectButton/bluerectbutton.h Interface/Buttons/BlueRectButton/bluerectbutton.cpp
        Interface/ChatHistory/chathistory_message.h Interface/ChatHistory/chathistory_message.cpp


        Interface/SvgGridContainer/gridcontainer.h Interface/SvgGridContainer/gridcontainer.cpp
        Interface/Buttons/WhiteSquareButton/whitesquarebutton.h Interface/Buttons/WhiteSquareButton/whitesquarebutton.cpp
        Interface/interface.h Interface/interface.cpp
        Interface/Notification/notification.h Interface/Notification/notification.cpp
        Interface/PlayerCard/playercard.h Interface/PlayerCard/playercard.cpp
        Interface/DialogGrid/dialoggrid.h Interface/DialogGrid/dialoggrid.cpp
        Interface/Buttons/CircleButton/circlebutton.h
        widgets/openglwidget.h widgets/openglwidget.cpp
        Objects/Penguin/clothes.h Objects/Penguin/clothes.cpp
        Objects/Badge/badge.h Objects/Badge/badge.cpp

        Objects/Items/items.h Objects/Items/items.cpp
        Interface/Buttons/Inventory/CategoryButton/categorybutton.h Interface/Buttons/Inventory/CategoryButton/categorybutton.cpp
        Interface/Buttons/WhiteRectButton/whiterectbutton.h Interface/Buttons/WhiteRectButton/whiterectbutton.cpp
        Interface/Buttons/OvalButton/ovalbutton.h Interface/Buttons/OvalButton/ovalbutton.cpp
        Interface/PlayerCard/Inventory/inventory.h Interface/PlayerCard/Inventory/inventory.cpp
        Objects/Constants/constants.h
        Objects/Penguin/Sprite/penguinspritebase.h Objects/Penguin/Sprite/penguinspritebase.cpp
        Objects/Penguin/Sprite/penguinsprite.h Objects/Penguin/Sprite/penguinsprite.cpp
        Objects/Penguin/Sprite/Clothing/penguinspriteclothing.h Objects/Penguin/Sprite/Clothing/penguinspriteclothing.cpp
        Objects/Penguin/Paper/penguinpaper.h Objects/Penguin/Paper/penguinpaper.cpp
        CanvasObject/Atlas/atlascanvasobject.h CanvasObject/Atlas/atlascanvasobject.cpp
        CanvasObject/abstractcanvasobject.h CanvasObject/abstractcanvasobject.cpp
        CanvasObject/Multi/multicanvasobject.h CanvasObject/Multi/multicanvasobject.cpp
        CanvasObject/Multi/Masked/maskedmulticanvasobject.h CanvasObject/Multi/Masked/maskedmulticanvasobject.cpp
        Objects/Player/playerfactory.h Objects/Player/playerfactory.cpp
        Objects/Player/player.h Objects/Player/player.cpp
        Game/game.h Game/game.cpp
        SoundManager/soundmanager.h SoundManager/soundmanager.cpp
        InputManager/inputmanager.h InputManager/inputmanager.cpp


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Clubpenguin-Room-Creator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Clubpenguin-Room-Creator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Clubpenguin-Room-Creator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Clubpenguin-Room-Creator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Clubpenguin-Room-Creator PRIVATE Qt6::Svg)
target_link_libraries(Clubpenguin-Room-Creator PRIVATE Qt6::SvgWidgets)
target_link_libraries(Clubpenguin-Room-Creator PRIVATE Qt6::Xml)
target_link_libraries(Clubpenguin-Room-Creator PRIVATE Qt6::Core)
target_link_libraries(Clubpenguin-Room-Creator PRIVATE Qt6::OpenGLWidgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Clubpenguin-Room-Creator)
endif()
set_target_properties(Clubpenguin-Room-Creator PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Clubpenguin-Room-Creator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Clubpenguin-Room-Creator)
endif()
