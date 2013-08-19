
if(WIN32 OR APPLE)
  return()
endif()
set(LIVRE_PACKAGE_VERSION 1.0.0)
set(LIVRE_REPO_URL https://github.com/BlueBrain/Livre.git)
set(LIVRE_DEPENDS Qt4 REQUIRED Boost Collage Equalizer Lunchbox OpenGL PNG Threads)
set(LIVRE_BOOST_COMPONENTS "date_time")
set(LIVRE_QT4_COMPONENTS "QtCore QtGui")
set(LIVRE_DEB_DEPENDS libboost-date-time-dev libtclap-dev)
set(LIVRE_FORCE_BUILD ${CI_BUILD})

if(CI_BUILD_COMMIT)
  set(LIVRE_REPO_TAG ${CI_BUILD_COMMIT})
else()
  set(LIVRE_REPO_TAG master)
endif()
set(LIVRE_FORCE_BUILD ON)
set(LIVRE_SOURCE ${CMAKE_SOURCE_DIR})
