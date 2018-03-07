#include "mainwindow.h"
#include "ui_mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainwindow)
{
    ui->setupUi(this);
    ui->centralWidget->setFixedWidth(720);
    ui->centralWidget->setFixedHeight(480);

}

Mainwindow::~Mainwindow()
{
    delete ui;
}
// Comment
bool Mainwindow::initialize_streaming(){
  bool success = false;
  if( _rs_ctx.get_device_count( ) > 0 )
  {
    //RGB Stream at 60 fps and 640x480 resolution.
    _rs_camera.enable_stream( rs::stream::color, 640, 480, rs::format::rgb8, 30 );
    //Depth stream at 30 fps and 640x480 resolution.
    _rs_camera.enable_stream( rs::stream::depth, 640, 480, rs::format::z16, 60);
    //Infrared stream at 30 fps and 640x480 resolution.
    _rs_camera.enable_stream(rs::stream::infrared,640, 480, rs::format::any,60);
    _rs_camera.start( );
    success = true;
  }
  return success;
}

cv::Mat Mainwindow::display_next_frame(){

  _depth_intrin       = _rs_camera.get_stream_intrinsics( rs::stream::depth );
  _color_intrin       = _rs_camera.get_stream_intrinsics( rs::stream::color );
  _infrared = _rs_camera.get_stream_intrinsics(rs::stream::infrared);

  // Create depth image
  cv::Mat depth16( _depth_intrin.height,
  _depth_intrin.width,
  CV_16U,
  (uchar *)_rs_camera.get_frame_data( rs::stream::depth ) );

  // Create color image
  cv::Mat rgb( _color_intrin.height,
               _color_intrin.width,
               CV_8UC3,
               (uchar *)_rs_camera.get_frame_data( rs::stream::color ) );

  // Create infrared image
  cv::Mat infra(_infrared.height,
                _infrared.width,
                CV_8U,
                (uchar *)_rs_camera.get_frame_data(rs::stream::infrared));
  cv::imshow("Infrared Image", infra);
  cvWaitKey(1);

  // < 800
  cv::Mat depth8u = depth16;
  depth8u.convertTo( depth8u, CV_8UC3 );//255.0/1000

  cv::imshow( "Depth Image", depth16 );
  cvWaitKey(1);

  cv::Mat rgb_(_color_intrin.height,
                _color_intrin.width,
                CV_8UC3);

  cv::cvtColor( rgb, rgb_, cv::COLOR_BGR2RGB);
  cvWaitKey(1);
  //drawSquare(rgb);
  cv::imshow( "RGB Image", rgb_ );
  cvWaitKey(1);



  return rgb;
}
