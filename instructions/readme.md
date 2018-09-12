# Assembly instructions

For glue hot glue works well.

Servo horns are the things you put on servos. Friction fit is probably enough but optionally you can screw them on or use a little hot glue. 

Center each servo before permanently connecting a servo horm. Just turn them to figure out their range and turn it to the center, or use a servo tester or receiver or something to have the servo center itself.

## Step 1

![Step 1](1.jpg)

Take inventory. Left side is the servo arm, right is the control arm.

---

## Step 2

![Step 2](2.jpg)

Servo arm first. Glue these.

---

## Step 3

![Step 3](3.jpg)

Glue in the base servo. Put a servo horn on the servo. Glue the part 2 part on top.

---

## Step 4

![Step 4](4.jpg)

Glue in the elbow servo with the turning part up.

---

## Step 5

![Step 5](5.jpg)

Carefully glue the grabber servo into the grabber servo mount with the wire facing forward and the slots on the right.

---

## Step 6

![Step 6](6.jpg)

Glue in the wrist servo with the turning part towards the end.

---

## Step 7

![Step 7](7.jpg)

Glue the arm part onto the elbow servo.

---

## Step 8

![Step 8](8.jpg)

Glue the first wrist part onto the wrist servo with the 90deg corner on top and the slightly wider angle corner on the bottom.

---

## Step 9

![Step 9](9.jpg)

Slide the grabber servo mount onto the first wrist part. Glue if needed.

---

## Step 10

![Step 10](10.jpg)

Slide the grabber "hand" onto the grabber servo holder.

---

## Step 11

![Step 11](11.jpg)

Slide together the grabber "thumb" pieces and glue them onto the grabber servo. Made sure the end of the hand and thumb line up.

---

## Step 12

![Step 12](12.jpg)

Next the controller arm. First *solder wires to the potentiometers*. I just stripped one end of some jumper wires and soldered them on. Jumper wires are nice because they are stuck together and are easy to extend by plugging more wires onto the first ones.

Press or glue a potentiometer (aka pot) into the base.

---

## Step 13

![Step 13](13.jpg)

Center the pot and press the next piece on as shown.

---

## Step 14

![Step 14a](14a.jpg)
![Step 14b](14b.jpg)

Press the elbow pot on in the orientation shown.

---

## Step 15

![Step 15](15.jpg)

Glue that to the base.

---

## Step 16

![Step 16a](16a.jpg)
![Step 16b](16a.jpg)

Press the wrist pot onto the arm piece and press the arm onto the elbow pot.


---

## Step 17

![Step 17a](17a.jpg)
![Step 17b](17b.jpg)

Press the wrist piece onto the wrist pot and slide the grabber pot holder onto the wrist piece.

---

## Step 18

![Step 18](18.jpg)

Press the grabber pot onto the holder piece and press the grabber controller piece onto the pot.

---

## Step 19

![Step 19](19.jpg)

Add extension wires as needed.

---

## Step 20

![Step 20](20.jpg)

Connect everything to the arduino. In the example code I have the servos connected to pins 8,9,10,11 starting with the base servo. The potentiometers are connected to a5,a4,a3,a2 starting with the base pot.

It is easiest to use a sensor shield on the arduino. The sensor shield has G, V, and S rows. On the servos, made sure the orange wire goes into the S row of pins. 

The middle pin on the pots should be connected to the "S" row. The other two pins can be connected either way. Switching them reverses the pot.

---

## Step 21

Upload the example arduino sketch.

## Step 22

Next we need to calibrate it so the controller and arm move together. The sketch can be modified to do this, or the easier way is to turn on the arm and remove and replace each joint on the controller arm so that it matches the servo arm. If the joint turnes the wrong way, switch the G and V pins of that pot.

Good luck!

