#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>
#include <iostream>

int main(int argc, char **argv) {
  //  Eigen/Geometry 모듈은 다양한 회전과 이동 표현을 제공한다.
  //  3D 회전 행렬은 Matrix3d 혹은 Matrix3f를 사용한다.
  Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();

  //  회전 방향량은 AngleAxis를 이용해 결정한다.
  //  그 밑바닥은 Matrix는 아니지만, 연산은 행렬로 사용할 수 있다.
  //  z축으로 45도 회저
  Eigen::AngleAxisd rotation_vector(M_PI / 4, Eigen::Vector3d(0, 0, 1));
  rotation_matrix = rotation_vector.toRotationMatrix();
  std::cout.precision(3);
  std::cout << "rotation matrix = \n" << rotation_vector.matrix() << std::endl;
  //  matrix()를 사용하여 행렬로 변환

  //  배열을 직접 할당하는 것도 가능하다.
  Eigen::Vector3d v(1, 0, 0);
  Eigen::Vector3d v_rotated = rotation_vector * v;
  std::cout << "(1, 0, 0) after rotation (by angle axis) = "
            << v_rotated.transpose() << std::endl;
  //  또는 회전행렬 사용
  v_rotated = rotation_matrix * v;
  std::cout << "(1, 0, 0) after rotation (by matrix) = "
            << v_rotated.transpose() << std::endl;

  //  오일러각 : 회전 행렬을 오일러각으로 바로 변환이 가능하다!
  //  ZYX순서 (yaw, pitch, roll)
  Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0);
  std::cout << "yaw pitch roll" << euler_angles.transpose() << std::endl;

  // Eigen::Isometry 를 사용한 유클리디안 변환 행렬
  // 3d라고 표기되어있지만 4*4 행렬임
  Eigen::Isometry3d T = Eigen::Isometry3d::Identity();
  T.rotate(rotation_vector);  // rotation_vector에 따라 회전
  T.pretranslate(Eigen::Vector3d(1, 3, 4));
  std::cout << "Transform matrix = \n" << T.matrix() << std::endl;

  // 변환행려을 이용한 좌표 변환
  Eigen::Vector3d v_transformed = T * v;
  std::cout << "v_transformed = " << v_transformed.transpose() << std::endl;

  //  아핀 변환 및 두영 변환에는 Affine3d, Projective3d를 사용한다.

  //  쿼터니언
  //  쿼터니언에 AngleAxis를 직접 할당할 수 있으며 그 반대도 가능하다.
  Eigen::Quaternion q = Eigen::Quaterniond(rotation_vector);

  //  계수의 순서는 x, y, z, w이고 w는 실수부이고 처음 세개는 허수부이다.
  std::cout << "quaternion from rotation vector" << q.coeffs().transpose()
            << std::endl;
  //  회전 행렬 또한 할당할 수 있다.
  q = Eigen::Quaterniond(rotation_matrix);
  std::cout << "quaternion from rotation matrix" << q.coeffs().transpose()
            << std::endl;

  v_rotated = q * v;  // v * q = q * v
  std::cout << "(1,0,0) after rotation = " << v_rotated.transpose()
            << std::endl;
  //  통상적인 벡터 곱으로 나타내면 다음과 같이 계산된다.
  std::cout
      << "should be equal to "
      << (q * Eigen::Quaterniond(0, 1, 0, 0) * q.inverse()).coeffs().transpose()
      << std::endl;

  return 0;
}
