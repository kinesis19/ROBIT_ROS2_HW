/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date August 2024
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/qt_usb_cam_vision/qnode.hpp"

QNode::QNode()
{
  int argc = 0;
  char** argv = NULL;
  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("qt_usb_cam_vision");

  // 파라미터 선언 및 기본값 설정 (라벨 크기에 맞춰 조정)
  // node->declare_parameter("hsv_lower", std::vector<int>{0, 100, 100}); // HSV에서 색상, 채도, 명도에 대한 값이라고함
  // node->declare_parameter("hsv_upper", std::vector<int>{180, 255, 255}); // HSV에서 색상, 채도, 명도에 대한 값이라고함
  node->declare_parameter("hsv_lower", std::vector<int>{0, 100, 50});   // H, S, V의 하한 값을 유지하거나 조정
  node->declare_parameter("hsv_upper", std::vector<int>{180, 255, 150}); // V의 상한 값을 낮추어 밝은 부분을 제외

  node->declare_parameter("width", 400);   // UI 라벨 크기에 맞춤
  node->declare_parameter("height", 240);  // UI 라벨 크기에 맞춤
  node->declare_parameter("erode_iterations", 1); // 한 번 침식
  node->declare_parameter("dilate_iterations", 1); // 한 번 팽창
  node->declare_parameter("canny_threshold1", 100); // canny_threshold1: 낮은 임계값
  node->declare_parameter("canny_threshold2", 200); // canny_threshold2: 높은 임계값
  node->declare_parameter("roi_x", 0); // 시작 위치
  node->declare_parameter("roi_y", 0); // 시작 위치
  node->declare_parameter("roi_width", 400);  // ROI 크기도 라벨 크기와 동일하게 설정
  node->declare_parameter("roi_height", 240); // ROI 크기도 라벨 크기와 동일하게 설정

  image_subscription_ = node->create_subscription<sensor_msgs::msg::Image>("/camera1/camera/image_raw", 10, std::bind(&QNode::imageCallback, this, std::placeholders::_1));

  this->start();
}

QNode::~QNode()
{
  if (rclcpp::ok())
  {
    rclcpp::shutdown();
  }
}

void QNode::run()
{
  rclcpp::WallRate loop_rate(20);
  while (rclcpp::ok())
  {
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }
  rclcpp::shutdown();
  Q_EMIT rosShutDown();
}

// 이미지 콜백 메서드
void QNode::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
{
  /* ROS2 이미지 메시지를 OpenCV 이미지로 변환
  * ROS의 sensor_msgs::msg::Image 형식을 OpenCV의 이미지 형식으로 바꾸기 위해 사용해야 함 -> toCvCopy
  * bgr8: OpenCV의 기본 색상 형식
  */ 
  cv::Mat cv_image = cv_bridge::toCvCopy(msg, "bgr8")->image;

  /* 파라미터 값 가져오기
  * get_parameter()를 통해 파라미터를 가져오고, 값들을 정수형태로 가져옴
  */ 
  auto hsv_lower = node->get_parameter("hsv_lower").as_integer_array();
  auto hsv_upper = node->get_parameter("hsv_upper").as_integer_array();

  // HSV 변환하고 색상 필터링
  cv::Mat hsv_image, binary_image;
  // cvtColor(): bgr에서 HSV 색상으로 변경함
  cv::cvtColor(cv_image, hsv_image, cv::COLOR_BGR2HSV);
  // inRange(): hsv_lower와 hsv_upper 사이의 값은 흰색(255)으로 나타내고, 나머지는 검은색(0)으로 나타냄 -> 바이너리 이미지 생성
  cv::inRange(hsv_image, cv::Scalar(hsv_lower[0], hsv_lower[1], hsv_lower[2]), cv::Scalar(hsv_upper[0], hsv_upper[1], hsv_upper[2]), binary_image);

  /* 이미지 크기 설정
  * 파라미터 값을 가져와서 이미지를 설정함
   */ 
  int width = node->get_parameter("width").as_int();
  int height = node->get_parameter("height").as_int();
  // resize(): 바이너리 이미지를 파라미터에서 지정한 사이즈로 변경
  cv::resize(binary_image, binary_image, cv::Size(width, height));

  // 침식 및 팽창 처리
  // 파라미터에서 설정한 침식과 팽창에 대한 값을 가져옴
  int erode_iterations = node->get_parameter("erode_iterations").as_int();
  int dilate_iterations = node->get_parameter("dilate_iterations").as_int();

  // 값들이 0보다 크면, 각각 침식과 팽창 처리를 진행함
  if (erode_iterations > 0) cv::erode(binary_image, binary_image, cv::Mat(), cv::Point(-1, -1), erode_iterations);
  if (dilate_iterations > 0) cv::dilate(binary_image, binary_image, cv::Mat(), cv::Point(-1, -1), dilate_iterations);


  // Canny 엣지 검출
  // 파라미터에서 설정한 canny에 대한 낮은 임계값과 높은 임계값을 가져옴
  int canny_threshold1 = node->get_parameter("canny_threshold1").as_int();
  int canny_threshold2 = node->get_parameter("canny_threshold2").as_int();
  cv::Mat edges;
  // 바이너리 이미지에서 윤곽선을 찾고, edges 이미지에 저장함
  cv::Canny(binary_image, edges, canny_threshold1, canny_threshold2);


  // ROI 설정
  // 파라미터에서 설정한 roi에 대한 값들(시작 위치, 사이즈)을 가져옴
  int roi_x = node->get_parameter("roi_x").as_int();
  int roi_y = node->get_parameter("roi_y").as_int();
  int roi_width = node->get_parameter("roi_width").as_int();
  int roi_height = node->get_parameter("roi_height").as_int();

  // roi를 정의함
  cv::Rect roi(roi_x, roi_y, roi_width, roi_height);
  // edges(roi): 엣지 이미지에서 roi 영역만 선택하여 roi_image에 저장함
  cv::Mat roi_image = edges(roi);


  /* 허프 변환 적용
  * 하프 변환 검출은 감을 못 잡겠어서 GPT를 사용함
  */ 

  // 동적 배열 lines 생성 Vec4i: OpenCV의 벡터 타입(int 4개)
  std::vector<cv::Vec4i> lines;
  
  cv::HoughLinesP(roi_image, lines, 1, CV_PI/180, 50, 50, 10);
  for (size_t i = 0; i < lines.size(); i++) {
      cv::line(roi_image, cv::Point(lines[i][0], lines[i][1]), cv::Point(lines[i][2], lines[i][3]), cv::Scalar(255, 0, 0), 2, cv::LINE_AA);
  }


   // 원본 이미지를 QImage로 변환하여 QPixmap으로 변환
  QImage originalQImage(cv_image.data, cv_image.cols, cv_image.rows, cv_image.step, QImage::Format_BGR888);
  QPixmap originalPixmap = QPixmap::fromImage(originalQImage);

  // 결과 이미지를 QImage로 변환 후, QPixmap으로 전환하여 UI에 표시
  QImage qImage(roi_image.data, roi_image.cols, roi_image.rows, roi_image.step, QImage::Format_Grayscale8);
  QPixmap cannyPixmap = QPixmap::fromImage(qImage);

  // 두 이미지를 시그널로 emit
  emit imageReceived(originalPixmap, cannyPixmap);
}
