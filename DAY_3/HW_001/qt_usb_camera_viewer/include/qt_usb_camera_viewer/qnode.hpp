/**
 * @file /include/qt_usb_camera_viewer/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qt_usb_camera_viewer_QNODE_HPP_
#define qt_usb_camera_viewer_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#endif
#include <QThread>
#include <sensor_msgs/msg/image.hpp>
#include <QImage>
#include <QPixmap>

/*****************************************************************************
** Class
*****************************************************************************/
class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();

protected:
  void run();

private:
  void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg);  // 이미지 데이터 콜백 메서드

  std::shared_ptr<rclcpp::Node> node;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscription_; // 이미지 서브스크라이브

Q_SIGNALS:
  void rosShutDown();
  void imageReceived(QPixmap pixmap);  // label에 이미지를 표기하기 위한 메서드
};

#endif /* qt_usb_camera_viewer_QNODE_HPP_ */
