#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstdio>
#include <QDebug>
#include <librealsense/rs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace Ui {
class Mainwindow;
}

class Mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = 0);
    ~Mainwindow();
    void onMouse( int event ); // , int x, int y, int, void* window_name
    bool initialize_streaming();
    cv::Mat display_next_frame();
    rs::context      _rs_ctx;
    rs::device&      _rs_camera = *_rs_ctx.get_device( 0 );
    rs::intrinsics   _depth_intrin;
    rs::intrinsics  _color_intrin;
    rs::intrinsics  _infrared;


private:
    Ui::Mainwindow *ui;
};

#endif // MAINWINDOW_H
