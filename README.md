# Stepper-Motor-Speed-Control

Files:
- Arduino one: handles the input from the controller. Since, switch C(the first input) has 3 positions which need to be recognised by the second arduino, 2 output pins are send to the second arduino as either high and low. different combinations of high and low indicate different operations mode. Switch C up position is LOW LOW, mid position is HIGH LOW and down position is HIGH HIGH. A second switch, switch D, only has 2 positions meaning that only one output pin needs to be used, with up positions being LOW and down position being HIGH.
- Arduino two: handles the ouput to the motor driver. When the 2 pins correlating to switch C's position are both HIGH the arduino outputs an accelerating signal. When both LOW, the ouput decelerates and when LOW HIGH, the acceleration is 0. When the pin correlating to switch D is HIGH, all input from the second arduino are ignored and a freqeuency sweep begins going from the current output frequency to the max frquency ouptut and back. Once it's returned to the controlled max speed, the controlls are re-engaged(assuming the ouput from the pin is LOW).

Reasoning:
- Short: The reason 2 arduinos were used is because the time it takes an arduino to read a pwm input takes longer than the time it takes to ouput the frequnecy. Reading a pins high or low state is much faster, and so the the first arduino is used to convert the pwm into high or low depending on the pwm rate.

(old)(
 - Uncontrolled Speed: Code does nothing till the remotes right vertical axis is moved up. Once moved, the motor accelerates till a specified max speed is reached then it decelerates back to 0. When moving, no input from the controller is read.
 - Controlled Speed: The acceleration of the motor is controlled by the right vertical axis of the remote. When moved up, motor accelerates, and when moved down the motor bdecelerates.
 - Controlled then Uncontrolled Speed: Remote controlls motors acceleration till the motor reachs a specified speed. Once this speed is reached, the arduino stops reading input from the remote and begins to accelerate to its max speed. Once reached, it then begins to decelerated back to controlled region.
)
