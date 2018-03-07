#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <librealsense/rs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

bool         _loop = true;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mainwindow w;
    w.show();
    if( !w.initialize_streaming())
    {
        qDebug() << "Unable to locate a camera ";
        return EXIT_FAILURE;
    }

    cv::namedWindow("Depth Image", 0);
    cv::namedWindow("RGB Image", 0);
    cv::namedWindow("Infrared Image", 0);

    while( _loop ){
        if( w._rs_camera.is_streaming() )
        {
            w._rs_camera.wait_for_frames();
            w.display_next_frame();
        }
    }
    w._rs_camera.stop();
    cv::destroyAllWindows();
    return EXIT_SUCCESS;
    return a.exec();
}

static void onMouse( int event, int x, int y, int, void* window_name )
{
       if( event == cv::EVENT_LBUTTONDOWN )
       {
             _loop = false;
       }
}
