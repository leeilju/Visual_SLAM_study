#include <Eigen/Core>
#include <Eigen/Dense>
#include <ctime>
#include <iostream>

#define MATRIX_SIZE 50

int main(int argc, char **argv) {
  //  Eigen에서 모든 벡터와 행렬은 클래스인 Eigen::Matrix이다.
  //  해당 클래스의 첫 세가지 매개 변수는 데이터 유형, 행, 열 이다.

  Eigen::Matrix<float, 2, 3> matrix_23;

  //  동시에 Eigen은 typedef를 통해 많은 내장 유형을 제공한다.
  //  예시로 vetor3d 와 matix<double, 3, 1>은 동일하다.

  Eigen::Vector3d v_3d;
  Eigen::Matrix<float, 3, 1> vd_3d;

  //  다른 예시로 Matrix3d는 matrix<double, 3, 3>이다.
  Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero();
  Eigen::Matrix<float, 3, 3> matrix_33d = Eigen::Matrix3d::Zero().cast<float>();

  //  행렬의 크기가 확실하지 않은 경우, 동적으로 조정이 가능한 행렬을 사용할 수
  //  있다.
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_dynamic;
  Eigen::MatrixXd matrix_x;

  //  고유행렬에 대한 연산.
  matrix_23 << 1, 2, 3, 4, 5, 6;
  std::cout << "matrix 2x3 from 1 to 6: \n" << matrix_23 << std::endl;

  //  행렬의 요소에 접근하는 법
  std::cout << "print matrix 2x3: " << std::endl;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      std::cout << matrix_23(i, j) << " \t";
    }
    std::cout << std::endl;
  }

  //  행렬과 벡터의 연산(실제로는 행렬곱임)
  v_3d << 3, 2, 1;
  vd_3d << 4, 5, 6;

  //  Eigen에서는 서로 다른 두가지 유형의 행렬을 혼합할 수 없다.
  //  따라서 cast<>()함수를 사용해서 명시적으로 변환해준다.
  Eigen::Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;
  std::cout << "[1,2,3;4,5,6]*[3,2,1] = " << result.transpose() << std::endl;

  Eigen::Matrix<float, 2, 1> result2 = matrix_23 * vd_3d;
  std::cout << "[1,2,3;4,5,6]*[4,5,6] = " << result2.transpose() << std::endl;

  //  또 행렬의 차원을 잘못 가져올 수도 있다.
  //  Eigen::Matrix<double, 2, 3> result_wrong =
  //                      matrix_23.cast<double>() * v_3d;

  //  부분 행렬 연산
  // 사칙연산은 시연하지 않으며 + - * / 로 사용 가능하다.
  matrix_33 = Eigen::Matrix3d::Random();
  std::cout << "random matrix : \n" << matrix_33 << std::endl;
  std::cout << "transpose : \n " << matrix_33.transpose() << std::endl;
  std::cout << "sum : \n" << matrix_33.sum() << std::endl;
  std::cout << "trace : \n" << matrix_33.trace() << std::endl;
  std::cout << "times 10 : \n" << matrix_33 * 10 << std::endl;
  std::cout << "inverse : \n" << matrix_33.inverse() << std::endl;
  std::cout << "determinant : \n" << matrix_33.determinant() << std::endl;

  //  고유값
  //  실제 대칭행렬은 성공적인 대각화를 보장함
  Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver(
      matrix_33.transpose() * matrix_33);

  std::cout << "Eigen values = \n" << eigen_solver.eigenvalues() << std::endl;
  std::cout << "Eigen vectors = \n" << eigen_solver.eigenvectors() << std::endl;

  //  방정식 풀기
  //  matrix_NN * x = v_Nd 방정식을 푼다.
  //  N의 크기는 앞의 매크로에서 정의 되며, 이는 난수로 생성
  //  직접 역행하는 것이 가장 직접적이지만, 연산량이 많다.

  Eigen::Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN =
      Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);

  matrix_NN = matrix_NN * matrix_NN.transpose();
  Eigen::Matrix<double, MATRIX_SIZE, 1> v_Nd =
      Eigen::MatrixXd::Random(MATRIX_SIZE, 1);

  clock_t time_stt = clock();

  //  역행렬 구하기
  Eigen::Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse() * v_Nd;
  std::cout << "time of normal inverse is "
            << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms\n";
  std::cout << "x = " << x.transpose() << std::endl;

  //  보통 행렬 분해로 풀면, 예로 QR 분해는, 속도가 휠씬 빠르다.
  time_stt = clock();
  x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
  std::cout << "time of Qr decomposition is "
            << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms\n";
  std::cout << "x = " << x.transpose() << std::endl;

  return 0;
}
