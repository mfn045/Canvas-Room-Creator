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

include_directories(${CMAKE_SOURCE_DIR})

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


        AbstractQtWidgets/layers.h
        AbstractQtWidgets/layers.cpp
        resources.qrc
        AbstractQtWidgets/canvas.h
        AbstractQtWidgets/canvas.cpp
        Dialogs/propertiesdialog.h Dialogs/propertiesdialog.cpp Dialogs/propertiesdialog.ui
        Interface/Widgets/ToolBar/toolbar.h Interface/Widgets/ToolBar/toolbar.cpp
        Interface/Widgets/Buttons/AbstractButton/abstractbutton.h Interface/Widgets/Buttons/AbstractButton/abstractbutton.cpp
        Interface/Widgets/Buttons/CircleButton/circlebutton.h Interface/Widgets/Buttons/CircleButton/circlebutton.cpp
        Interface/World/Buttons/Map/map.h Interface/World/Buttons/Map/map.cpp
        Interface/World/Buttons/News/news.h Interface/World/Buttons/News/news.cpp
        Interface/World/Buttons/Moderator/moderator.h Interface/World/Buttons/Moderator/moderator.cpp
        Interface/World/Buttons/Mail/mail.h Interface/World/Buttons/Mail/mail.cpp
        Interface/World/Buttons/Friend_Requests/friend_requests.h Interface/World/Buttons/Friend_Requests/friend_requests.cpp
        Interface/Common/TextBox/textbox.h Interface/Common/TextBox/textbox.cpp
        Interface/World/ChatBubble/chatbubble.h Interface/World/ChatBubble/chatbubble.cpp
        Interface/Widgets/Dialogs/abstractdialog.h Interface/Widgets/Dialogs/abstractdialog.cpp
        AbstractQtWidgets/scene.h AbstractQtWidgets/scene.cpp
        Interface/Widgets/Buttons/OrangeButton/orangebutton.h Interface/Widgets/Buttons/OrangeButton/orangebutton.cpp
        Interface/Widgets/Buttons/BlueButton/bluebutton.h Interface/Widgets/Buttons/BlueButton/bluebutton.cpp
        Interface/Widgets/Dialogs/YesNoDialog/yesnodialog.h Interface/Widgets/Dialogs/YesNoDialog/yesnodialog.cpp
        Interface/Common/TextLabel/textlabel.h Interface/Common/TextLabel/textlabel.cpp
        Interface/Common/TextLabel/textlabelinput.h Interface/Common/TextLabel/textlabelinput.cpp
        Interface/World/ChatHistory/chathistory.h Interface/World/ChatHistory/chathistory.cpp
        Interface/Widgets/Buttons/BlueRectButton/bluerectbutton.h Interface/Widgets/Buttons/BlueRectButton/bluerectbutton.cpp
        Interface/World/ChatHistory/chathistory_message.h Interface/World/ChatHistory/chathistory_message.cpp


        Interface/Common/Containers/GridContainer/gridcontainer.h Interface/Common/Containers/GridContainer/gridcontainer.cpp
        Interface/Widgets/Buttons/WhiteSquareButton/whitesquarebutton.h Interface/Widgets/Buttons/WhiteSquareButton/whitesquarebutton.cpp
        Interface/interface.h Interface/interface.cpp
        Interface/World/Buttons/Notification/notification.h Interface/World/Buttons/Notification/notification.cpp
        Interface/Widgets/PlayerCard/playercard.h Interface/Widgets/PlayerCard/playercard.cpp
        Interface/Widgets/DialogGrid/dialoggrid.h Interface/Widgets/DialogGrid/dialoggrid.cpp
        Interface/Widgets/Buttons/CircleButton/circlebutton.h
        AbstractQtWidgets/openglwidget.h AbstractQtWidgets/openglwidget.cpp
        Interface/World/Penguin/clothes.h Interface/World/Penguin/clothes.cpp
        Interface/Widgets/PlayerCard/Badge/badge.h Interface/Widgets/PlayerCard/Badge/badge.cpp

        Objects/Items/items.h Objects/Items/items.cpp
        Interface/Widgets/Buttons/Inventory/CategoryButton/categorybutton.h Interface/Widgets/Buttons/Inventory/CategoryButton/categorybutton.cpp
        Interface/Widgets/Buttons/WhiteRectButton/whiterectbutton.h Interface/Widgets/Buttons/WhiteRectButton/whiterectbutton.cpp
        Interface/Widgets/Buttons/OvalButton/ovalbutton.h Interface/Widgets/Buttons/OvalButton/ovalbutton.cpp
        Interface/Widgets/PlayerCard/Inventory/inventory.h Interface/Widgets/PlayerCard/Inventory/inventory.cpp
        Objects/Constants/constants.h
        Interface/World/Penguin/Sprite/penguinspritebase.h Interface/World/Penguin/Sprite/penguinspritebase.cpp
        Interface/World/Penguin/Sprite/penguinsprite.h Interface/World/Penguin/Sprite/penguinsprite.cpp
        Interface/World/Penguin/Sprite/Clothing/penguinspriteclothing.h Interface/World/Penguin/Sprite/Clothing/penguinspriteclothing.cpp
        Interface/World/Penguin/Paper/penguinpaper.h Interface/World/Penguin/Paper/penguinpaper.cpp
        Interface/Common/CanvasObject/Atlas/atlascanvasobject.h Interface/Common/CanvasObject/Atlas/atlascanvasobject.cpp
        Interface/Common/CanvasObject/abstractcanvasobject.h Interface/Common/CanvasObject/abstractcanvasobject.cpp
        Interface/Common/CanvasObject/Multi/multicanvasobject.h Interface/Common/CanvasObject/Multi/multicanvasobject.cpp
        Interface/Common/CanvasObject/Multi/Masked/maskedmulticanvasobject.h Interface/Common/CanvasObject/Multi/Masked/maskedmulticanvasobject.cpp
        Objects/Player/playerfactory.h Objects/Player/playerfactory.cpp
        Objects/Player/player.h Objects/Player/player.cpp
        Game/game.h Game/game.cpp
        SoundManager/soundmanager.h SoundManager/soundmanager.cpp
        InputManager/inputmanager.h InputManager/inputmanager.cpp
        Interface/Screens/LoadingScreen/loadingbar.h Interface/Screens/LoadingScreen/loadingbar.cpp
        Interface/Screens/LoadingScreen/loading.h Interface/Screens/LoadingScreen/loading.cpp
        ThreadPoolManager/LoadingBarWorker/loadingbarworker.h ThreadPoolManager/LoadingBarWorker/loadingbarworker.cpp
        ThreadPoolManager/PenguinSpriteMoveWorker/penguinspritemoveworker.h ThreadPoolManager/PenguinSpriteMoveWorker/penguinspritemoveworker.cpp
        ThreadPoolManager/threadpoolmanager.h ThreadPoolManager/threadpoolmanager.cpp


        Interface/Common/TitleLabel/titlelabel.h Interface/Common/TitleLabel/titlelabel.cpp
        Interface/Widgets/Settings/settings.h Interface/Widgets/Settings/settings.cpp
        Interface/Widgets/BackgroundContainer/backgroundcontainer.h Interface/Widgets/BackgroundContainer/backgroundcontainer.cpp
        LocalizationManager/localizationmanager.h LocalizationManager/localizationmanager.cpp
        AssetsManager/assetsmanager.h AssetsManager/assetsmanager.cpp




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

target_include_directories(Clubpenguin-Room-Creator PRIVATE ${CMAKE_SOURCE_DIR})
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
