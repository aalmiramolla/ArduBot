//------------------------------------
//-- Miniskybot 2 configuration file
//------------------------------------

//-- drills
drill_M3 = 3.2;

//-- captive Nuts
nut_h = 2.6;
nut_radius = 6.6/2;

//------------------------------------------------
//-- Servo parameters
//-- See the doc/futaba-doc.pdf file
//------------------------------------------------
//-- Servo futaba 3003 dimensions
servo_c1 = 20.7;
servo_c2 = 7.5;
servo_c3 = 29;
servo_c4 = 41;
servo_c5 = 31;
servo_c6 = 10;
servo_c7 = 12.75;
servo_c8 = 4;
servo_c9 = 4.5;
servo_c10 = 10;

//-------------------------------------------
//-- Battery holder parameters
//-- See the doc/battery_holder-doc.pdf file
//-------------------------------------------
battery_c1 = 49;
battery_c2 = 51;
battery_c3 = 11.75;
battery_ear_diam = 9;
battery_ear_h = 3.2;
battery_top_gap = 1;  
//-- Real battery height whith batteries inserted
battery_height = battery_c3 + battery_top_gap;

//-------------------------------------------------
//-- Wheels parameters. 
//-- See the doc/Servo-wheels-doc.pdf
//------------------------------------------------
wheel_or_idiam = 50;                   //-- O-ring inner diameter
wheel_or_diam = 3;                     //-- O-ring section diameter
wheel_height = 2*wheel_or_diam+0;     //-- Wheel height: change the 0 for 
                                      //-- other value (0 equals minimun height)
                                      
//-- Wheel diameter is calculated from the o_ring                                      
wheels_diam = wheel_or_idiam + 2*wheel_or_diam;
wheel_gap = 1;  //-- For the final view. space between servo and wheel


//-------------------------------------------------
//-- Chassis (see doc/chassis-doc.pdf)
//-------------------------------------------------

robot_height = 47;

//-------- Rear part parameters ------------
rear_c1 = servo_c2 + 3;
rear_c2 = servo_c3*2;
rear_c3 = servo_c1 + battery_height -battery_ear_h;
rear_edge_rad = 3;

//-- Ball caster parameters
WallThickness = 2.25; //thickness of the retaining wall
BallSize = 16.4;  //diameter of  your ball bearing.
Airgap = .65;  // Gap between ball and wall  
BallProtrude = .35; //percentage of ball radius sticking out 
ball_caster_height = robot_height-(BallSize*BallProtrude);

//-- Front part parameters
front_c1 = battery_ear_diam + 4;
front_thickness = 3;
frame_corner_radius = 3;


//-- Top plate
top_plate_c1 = battery_c1 + front_c1 + rear_c1;
top_plate_c2 = rear_c2+5;
top_plate_thickness = 4;


//-- Skymega board dimensions
skymega_lx = 51.4;
skymega_ly = 51.4;
skymega_width=3;
skymega_dx = 15;
skymega_dy = 15;

//-- ultrasounds
ultrasound_hole = 16.5;
ultrasound_base_lx = 24+1;
ultrasound_base_ly = 20+1;
ultrasound_base_lz = 3;
ultrasound_length = 12.5;
ultrasound_drill_1 = [-9,7,0];
ultrasound_drill_2 = [9,-8,0];


//-- IR Sensors
IRSensors_radio = 1.25;
IRSensors_largoPlaca = 75;
IRSensors_anchoPlaca = 13;
IRSensors_gruesoPlaca = 1.6;
IRSensors_distanciaBordeTornillo = 1.6;
IRSensors_cubo4Pin = [3.75,10.8,11.85];
IRSensors_cubo2Pin = [3.75,5.7,11.85];
IRSensors_cubo11Pin = [7,28.7,11.85];
IRSensors_cuboSensor = [3.4,2.75,1.6];
