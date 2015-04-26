largoSoporte = 50;
anchoSoporte = 6;
anchoHueco = 3;
largoHueco = 46;
altoSoporte = 5;


radioSensor = 16/2;
profundidadPlaca = 2;
anchoPlaca = 45;
altoPlaca = 21;
distanciaLargoPlacaSensor = 15;
distanciaAnchoPlacaSensor = 10.5;

anchoPin = 8;
altoPin = 3;
profundidadPin = 8;

radioTornillo = 2.5/2;
largoTornillo = 10;
module SoporteSensor()
{
    difference(){ 
        Soporte();
        translate([0,0,8.75])
        #Sensores();
        /*rotate([90,0,0])
        translate([anchoPlaca/2-2,0,0])
        cylinder(r = radioTornillo,h=largoTornillo,$fn=100);*/
    }
    
}

module Sensores()
{
    union(){
        union()
        {
            cube([anchoPlaca, profundidadPlaca, altoPlaca],center =true);
            rotate([90,0,0])
            translate([distanciaAnchoPlacaSensor,0,distanciaPlacaSensor])
            cylinder(r=radioSensor, $fn = 100, center = false, h=13);
            mirror(){
                rotate([90,0,0])
                translate([distanciaAnchoPlacaSensor,0,distanciaPlacaSensor])
                cylinder(r=radioSensor, $fn = 100, center = false, h=13);
            }
            translate([0,profundidadPin/4,-altoPlaca/2+altoPin/2+2])
            cube([anchoPin,profundidadPin,altoPin+3],center = true);
            
        }
        mirror(){
            rotate([90,0,0])
            translate([anchoPlaca/2-2,-altoPlaca/2+2,-5])
            #cylinder(r=radioTornillo,h=largoTornillo,$fn=100);
        }
             rotate([90,0,0])
            translate([anchoPlaca/2-2,-altoPlaca/2+2,-5])
            #cylinder(r=radioTornillo,h=largoTornillo,$fn=100);
    }
}

module Soporte()
{
    cube([largoSoporte,anchoSoporte,altoSoporte],center = true);
}
