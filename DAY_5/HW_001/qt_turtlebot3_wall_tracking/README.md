# qt_turtlebot3_wall_tracking

## Description
Control to a turtlebot3 in gazebo.


## 어떻게 벽을 따라가게 만들었는가
1. Turtlebo3로부터 LiDAR 센서 값을 받아온다.
2. 사용자로부터 벽과 로봇의 거리 지정한 값(target_distance_)을 받아온다.
3. Turtlebot3의 우측 면과 World에 존재하는 벽면과의 거리를 이용해 이동을 처리한다.
이때, Turtlebot3와 벽면과의 거리는 target_distance_ 값이 되어야 한다. (사용자로부터 값을 받지 않은 상태일 때는, 초기값으로 지정됨)
4. 오차범위를 줘서, 사용자로부터 입력 받는 값(target_distance_)에 대한 범위를 유동있게 조정한다.
5. 우측으로 이동할 것 이기에, 우측으로 회전 중 현재 Turtlebot3와 벽면과의 거리에 대한 값(current_distance_right)이 조건을 충족하지 못 하는 경우가 있는데, 세부 조건으로 Turtlebot3의 정면이 2.0(m) 미만일 경우에는 좌회전을 하게 하여 방향을 바로 잡는다.
6. current_distance_right 값이 target_distance_ 값에 오차 범위를 적용한 값보다 작다면, 벽면과 가까이 있으므로 좌회전을 한다.
7. Turtlebot3의 이동 방향 조건 외에는 직진 주행을 처리하게 하여 Turtlebot3가 올바르게 벽면을 따라 주행을 할 수 있게 했다.
8. 예외처리로 기본적인 Turtlebot3의 이동 조건 감지가 끝나고 코너를 감지하면, 좌회전을 하는 조건을 추가하였다.

## Demo Video
<video controls width="600">
  <source src="TestCaseVideo.mp4" type="video/mp4">
  Demo Video
</video>
