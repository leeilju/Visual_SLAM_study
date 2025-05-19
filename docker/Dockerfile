# Author: leeilju
# email: iljujjang@gmail.com

FROM ubuntu:24.04

# Install PCL & Eigen & essential libraries
RUN apt-get update && apt-get install -y cmake \
    libatlas-base-dev libeigen3-dev \
    libpcl-dev libgoogle-glog-dev \
    libsuitesparse-dev libglew-dev \
    wget unzip git python3-pip

WORKDIR /home/visual_slam_ws

# Load environment at each run
COPY ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]

CMD ["bash"]
