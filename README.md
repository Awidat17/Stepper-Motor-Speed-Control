# Stepper-Motor-Speed-Control

Files:
 - Uncontrolled Speed: Code does nothing till the remotes right vertical axis is moved up. Once moved, the motor accelerates till a specified max speed is reached then it decelerates back to 0. When moving, no input from the controller is read.
 - Controlled Speed: The acceleration of the motor is controlled by the right vertical axis of the remote. When moved up, motor accelerates, and when moved down the motor bdecelerates.
 - Controlled then Uncontrolled Speed: Remote controlls motors acceleration till the motor reachs a specified speed. Once this speed is reached, the arduino stops reading input from the remote and begins to accelerate to its max speed. Once reached, it then begins to decelerated back to controlled region.
