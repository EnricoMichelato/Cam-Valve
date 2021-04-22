HOMEWORK 1

I'm creating a Cam-Valve sistem.

DEFINITION OF THE PIECES

VALVE:
The Valve is the piece that moves just in one direction (vertically). It is always in contact with the Cam.

CAM:
The Cam rotates on the axis passing through its center.

PARAMETERS
If we consider the Cam as en ellipse, it can be defined with two parameters:

rMin: the minimum height the point of contact between Cam and Valve is going to be.

rMin: the maximum height the point of contact between Cam and Valve is going to be.

lenValve: the principal length of the Valve

diamValve: the diameter of the base of the Valve

CONSTRAINS

1) rMin needs to be smaller than rMax -> rMin<rMax

2) The lift of the Valve is defined as the maximum excursion the Valve has. Since the Valve and the Cam are always in contact, the lift of the Valve is equal to: valveLift = rMax - rMin.
In order for the sistem to be assembled, the lift cannot exceed the valve length. -> rMax - rMin <= lenValve