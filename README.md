IODelegate
==========

simple delegate around the Arduino Serial library that supports sprintf style messages, in addition to provide simple logging, although only two levels are supported, `DEBUG` and `INFO`.

the original sprintf implementation comes from:

  https://github.com/mrRobot62/Arduino-logging-library

and the function to handle float/double conversion from: 

  http://forum.arduino.cc/index.php/topic,44216.0.html
