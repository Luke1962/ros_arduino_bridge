# ros_arduino_bridge
Arduino Mega2560 firmware adapted from ros_arduino_bridge to manage additional Bluetooth  channel (HC05) for debugging

Rosserial is unreliable. After many headaches, I decided to abandon it, in favour of this protocol.
This version of ros_arduino_bridge has been derived from https://github.com/hbrobotics/ros_arduino_bridge, by hrobotics.
I've made the following changes:
a] commands can be sent also froom an additional serial communication channel for debug purposes (eg. HC05 bluetooth module attached to Serial1.
b] Changed the motor driver to interface the Cytron MDDS10 via Serial interface (simplified protocol)
c] Replaced Encoder driver with Encoder library from https://github.com/PaulStoffregen/Encoder


To do
Setting publish frequency for each sensor, instead of one common.
Improve response time to commands (e.g. cmd_vel) from other nodes.

