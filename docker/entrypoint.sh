#!/bin/bash

set -e

echo "==============Visual SLAM Docker Env Ready================"

cd /home/visual_slam_ws

exec "$@"
