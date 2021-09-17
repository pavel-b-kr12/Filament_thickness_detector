# Filament_thickness_detector

some simple methods to detect thickness using arduino-based hardware

## hall sensor + movable magnet 

key of success is maximisation of magnetic field change gradient. This setup have to be еру best with commonly available chinese magnets 

![hall_sensor_setup](hall_sensor_setup.jpg)


## video

### linear CCD sensors

use draft software Linear_CCD_TCD1201D.ino

and online viewer:

<https://pavel-b-kr12.github.io/serial_com_port_view_online/serial_com_port_view_online.htm>

properly setup diaphragm and optics is the key. Without appropriate optics you will have something like this:

![TCD1201D image](TCD1201D_img1.jpg)

![TCD1201D plot](TCD1201D_img2_plot.jpg)

### camera
LiveOV7670

