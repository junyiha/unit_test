#!/usr/bin/env python3

import xyz_sensor
import numpy as np

cam = xyz_sensor.Sensor()
status, sensor_infos = cam.EnumerateConnectedSensors()
if not status.ok():
    print(status)
print(sensor_infos)
if len(sensor_infos) > 0:
    status = cam.Open(sensor_infos[0])
    status = cam.Capture()
    status, color_frame = cam.GetColorFrame()
    status, depth_frame = cam.GetDepthFrame()
    status, xyz_frame = cam.GetPointXYZFrame()
    # convert to numpy array if you want
    np_color = np.array(color_frame, copy=False)
