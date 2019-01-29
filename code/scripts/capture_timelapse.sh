#!/bin/bash
capture_soft="$(which fswebcam)"
if [[ -z "$fswebcam" ]]
then
    echo "This script needs fswebcam installed"
fi

output_dir=/home/pi/serre/captures

default_resolution="1280x720"
default_delay_s="20"

mkdir -p "$output_dir"

while true;
do
    fswebcam -c capture.config "$(date +%Y%m%d_%H%M%S).jpg"
    sleep "$default_delay_s"
done

