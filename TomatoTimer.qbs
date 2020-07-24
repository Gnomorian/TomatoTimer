import qbs.FileInfo

QtGuiApplication {
    Depends { name: "Qt.widgets" }
    Depends { name: "Qt.multimedia" }

    version: "20200723"

    consoleApplication: false

    // The following define makes your compiler emit warnings if you use
    // any Qt feature that has been marked deprecated (the exact warnings
    // depend on your compiler). Please consult the documentation of the
    // deprecated API in order to know how to port your code away from it.
    // You can also make your code fail to compile if it uses deprecated APIs.
    // In order to do so, uncomment the second entry in the list.
    // You can also select to disable deprecated APIs only up to a certain version of Qt.
    cpp.defines: [
        "QT_DEPRECATED_WARNINGS",
        /* "QT_DISABLE_DEPRECATED_BEFORE=0x060000" */ // disables all the APIs deprecated before Qt 6.0.0
        "APP_VERSION=2020-724",
        "APP_ORGANISATION_NAME=\"Williamc\"",
        "APP_ORGANISATION_DOMAIN=\"Williamc.nz\"",
        "APP_NAME=\"Will's TomatoTimer\""
    ]
    files: [
        "main.cpp",
        "res.rc",
        "resource.qrc",
        "screenshot.PNG",
        "timerform.cpp",
        "timerform.h",
        "timerform.ui",
        "TomatoTimer_en_NZ.ts",
        "tomatoapplication.cpp",
        "tomatoapplication.h",
        "tomatosettingsdialog.cpp",
        "tomatosettingsdialog.h",
        "tomatosettingsdialog.ui",
        "tomato.ico",
    ]

    install: true
    installDir: qbs.targetOS.contains("qnx") ? FileInfo.joinPaths("/tmp", name, "bin") : base
}
