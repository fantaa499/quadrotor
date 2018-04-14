#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
    DESTDIR_ARG="--root=$DESTDIR"
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/anton/Documents/catkin_ws/src/moveit/moveit_ros/planning_interface"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/anton/Documents/catkin_ws/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/anton/Documents/catkin_ws/install/lib/python2.7/dist-packages:/home/anton/Documents/catkin_ws/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/anton/Documents/catkin_ws/build" \
    "/usr/bin/python" \
    "/home/anton/Documents/catkin_ws/src/moveit/moveit_ros/planning_interface/setup.py" \
    build --build-base "/home/anton/Documents/catkin_ws/build/moveit/moveit_ros/planning_interface" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/anton/Documents/catkin_ws/install" --install-scripts="/home/anton/Documents/catkin_ws/install/bin"
