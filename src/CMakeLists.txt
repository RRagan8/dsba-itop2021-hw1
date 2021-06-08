add_executable(videosModel
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    tablemodel.cpp tablemodel.h
    aboutdialog.cpp aboutdialog.h aboutdialog.ui
    renderarea.cpp renderarea.h
    dialogadd.cpp dialogadd.h dialogadd.ui
    getinfo.cpp getinfo.h getinfo.ui
)
target_link_libraries(videosModel Qt5::Widgets)
