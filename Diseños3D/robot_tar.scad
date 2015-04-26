include <portapilas.scad>
include <ultrasonido.scad>

ancho_arduino = 20;
largo_arduino = 35;
alto_arduino = 15;

ancho_driver_motores = 61;
largo_driver_motores = 57;
alto_driver_motores = 30;

ancho_base_robot = 70; // 70
largo_base_robot = 100; // 100x
alto_base_robot = 3;

ancho_caja_endstop=14;
largo_caja_endstop=6;

module rear_part()
{
  total_height = robot_height;
  cyl_height = total_height;
  cylrad = (BallSize/2) + WallThickness + Airgap;

  ball_caster_height = total_height-(BallSize*BallProtrude);

  difference() {
    union() {
  //    rear_part_body();
      translate([-cylrad,rear_c2/2,-ball_caster_height +servo_c1+top_plate_thickness])
      cylinder(r=cylrad, h=ball_caster_height);
  }
  
   translate([-cylrad,rear_c2/2,-cyl_height/2 + (BallSize/2)+top_plate_thickness])
      cube([cylrad/2, cylrad*2+5, BallSize*1.25],center=true);
    
   translate([-cylrad,rear_c2/2,-cyl_height/2 + (BallSize/2)+top_plate_thickness]) 
    #sphere (BallSize/2+Airgap, $fa=5, $fs=0.1);

//   translate([-rear_c1-8,rear_c2/2,servo_c3+5])
//   rotate (a = [0,20,0])
//   cube ([20,23,80],center=true);

  }

}

module arduino_pro_mini() {
    cube([ancho_arduino,largo_arduino,alto_arduino],center=true);
}

module driver_motores(){
    cube([ancho_driver_motores,largo_driver_motores,alto_driver_motores],center=true);
}

module agujeros_motores(){
    cylinder(r=1.5,h=alto_base_robot*10,$fn=200,center=true);
}

module endstop(){
    difference(){
    hull(){
        translate([ancho_base_robot/6,-largo_base_robot/2-2.5,10])
        rotate(90,[1,0,0])
        cylinder(r=1,h=5,center=true);

        translate([-ancho_base_robot/6,-largo_base_robot/2-2.5,10])
        rotate(90,[1,0,0])
        cylinder(r=1,h=5,center=true);

        translate([ancho_base_robot/4,-largo_base_robot/2-2.5,0])
        rotate(90,[1,0,0])
        cylinder(r=1,h=5,center=true);

        translate([-ancho_base_robot/4,-largo_base_robot/2-2.5,0])
        rotate(90,[1,0,0])
        cylinder(r=1,h=5,center=true);
    }
    translate([0,-largo_base_robot/2,6])
    cube([ancho_caja_endstop,100,largo_caja_endstop],center=true);
    }
}

module sensor_luz_aux(){
    
    translate([0,-largo_base_robot/2+4,0])
    difference(){
        difference(){
            cube([16,7,alto_base_robot],center=true);
            translate([5,0,-1])
            cube([8,8,4],center=true);
            translate([-5,0,-1])
            cube([8,8,4],center=true);
        }
        translate([5,0,0])
        cylinder(r=2,h=100,center=true,$fn=100);
        translate([-5,0,0])
        cylinder(r=2,h=100,center=true,$fn=100);

    }
}

module sensor_luz(){
    difference(){
        translate([0,-largo_base_robot/2+4,0])
        cube([16,5,alto_base_robot],center=true);
        sensor_luz_aux();        
    }
}

module agujeros_motores_en_base(){
        translate([ancho_base_robot/2,-largo_base_robot+60,0])
        agujeros_motores();
        translate([ancho_base_robot/2,-largo_base_robot+78,0])
        agujeros_motores();
}

module base_robot(){
    difference(){
        hull(){
            translate([ancho_base_robot/2,largo_base_robot/2,0])
            cylinder(r=5,h=alto_base_robot,center=true);
            translate([-ancho_base_robot/2,-largo_base_robot/2,0])
            cylinder(r=5,h=alto_base_robot,center=true);
            translate([ancho_base_robot/2,-largo_base_robot/2,0])
            cylinder(r=5,h=alto_base_robot,center=true);
            translate([-ancho_base_robot/2,largo_base_robot/2,0])
            cylinder(r=5,h=alto_base_robot,center=true);
        }
        
        translate([0,largo_base_robot/4-2,alto_driver_motores/2])
        #driver_motores();
        
        translate([0,-22,alto_arduino/2])
//        rotate(90)
        #arduino_pro_mini();

        agujeros_motores_en_base();
        mirror([1,0,0]){
            agujeros_motores_en_base();
        }

        // Varillas de las 4 esquinas
        translate([(ancho_base_robot/2),(largo_base_robot/2),20])
        #cylinder(r=2.5,h=alto_base_robot*20,$fn=200,center=true);
        mirror([1,0,0]){
            translate([(ancho_base_robot/2),(largo_base_robot/2),20])
            #cylinder(r=2.5,h=alto_base_robot*20,$fn=200,center=true);
        }
        mirror([0,1,0]){
            translate([(ancho_base_robot/2),(largo_base_robot/2),20])
            #cylinder(r=2.5,h=alto_base_robot*20,$fn=200,center=true);
        }
        mirror([1,0,0]){
            mirror([0,1,0]){
                translate([(ancho_base_robot/2),(largo_base_robot/2),20])
                #cylinder(r=2.5,h=alto_base_robot*20,$fn=200,center=true);
            }
        }
    }
}

module rueda_loca(){
    difference(){
    translate([10,10,-50])
    rear_part();
    translate([-1,39,-50])
    #cylinder(r=15,h=40);
}
}

module planta1_robot(){
    union(){
        
        translate([0,-largo_base_robot/2-2,4])
        //rotate([0,0,180])
        #SoporteSensor();
        mirror(){
        rotate([0,0,90])
        translate([-20,-largo_base_robot/2+13,4])
        #SoporteSensor();
        }
        rotate([0,0,90])
        translate([-20,-largo_base_robot/2+13,4])
        #SoporteSensor();
        difference(){
            difference(){
                hull(){
                    translate([ancho_base_robot/2,largo_base_robot/2,0])
                    cylinder(r=5,h=alto_base_robot,center=true);
                    translate([-ancho_base_robot/2,-largo_base_robot/2,0])
                    cylinder(r=5,h=alto_base_robot,center=true);
                    translate([ancho_base_robot/2,-largo_base_robot/2,0])
                    cylinder(r=5,h=alto_base_robot,center=true);
                    translate([-ancho_base_robot/2,largo_base_robot/2,0])
                    cylinder(r=5,h=alto_base_robot,center=true);
                }
                
                // Varillas de las 4 esquinas
                translate([(ancho_base_robot/2),(largo_base_robot/2),0])
                cylinder(r=2.5,h=alto_base_robot*10,$fn=200,center=true);
                mirror([1,0,0]){
                    translate([(ancho_base_robot/2),(largo_base_robot/2),0])
                    cylinder(r=2.5,h=alto_base_robot*10,$fn=200,center=true);
                }
                mirror([0,1,0]){
                    translate([(ancho_base_robot/2),(largo_base_robot/2),0])
                    cylinder(r=2.5,h=alto_base_robot*10,$fn=200,center=true);
                }
                mirror([1,0,0]){
                    mirror([0,1,0]){
                        translate([(ancho_base_robot/2),(largo_base_robot/2),0])
                        cylinder(r=2.5,h=alto_base_robot*10,$fn=200,center=true);
                    }
                }
            }
            translate([0,20,8.5])
            #battery_holder(1,4);
            translate([20,-40,-5])
            #cylinder(r=3,h=10,$fn=100);
            translate([-20,-40,-5])
            #cylinder(r=3,h=10,$fn=100);
        }
    }
}

module planta0_robot(){
    difference(){
        union(){
            endstop();
            base_robot();
        }
        translate([30,-15,-5])
        #cylinder(r=3,h=10,$fn=100);
        translate([-30,-15,-5])
        #cylinder(r=3,h=10,$fn=100);
        sensor_luz();
    }
    translate([0,3,50])
    %rueda_loca();
}

module robot(){
    planta0_robot();
    translate([0,0,50])
    planta1_robot();
}

robot();
//battery_holder(1,6);
//rueda_loca();