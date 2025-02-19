# CycloComm (Cyclist Communicator)

Cyclists often struggle to effectively communicate their intentions or emotions to drivers on the road. The CycloComm bridges this gap by enabling cyclists to express themselves clearly and genuinely, enhancing road safety and harmony. With CycloComm, making specific hand gestures triggers corresponding emojis or messages displayed on an LED screen mounted on the cyclist's back or bag. For instance, a raised hand to apologize can be paired with a crying face emoji, amplifying the sincerity of the gesture. Similarly, a heartfelt “thank you” can be displayed as a cheerful face or a heart, making the message more genuine. This system really amplifies a cyclist's emotions and intentions, enhancing emotional connection and understanding on the road. By allowing cyclists to communicate with drivers more effectively and authentically, CycloComm contributes to a safer, more empathetic driving environment, making every ride a little better for everyone.

---

## File Descriptions

### final_glove_bluetooth_send.ino
This file contains the primary code responsible for capturing hand gesture inputs from the glove’s sensor setup. It processes these gestures and sends corresponding signals to the LED matrix for displaying emojis or messages.

### final_LED_screen_receive.ino
This file focuses on controlling the LED matrix display. It receives the signals from the glove code and translates them into the appropriate visuals, managing brightness, patterns, and text or emoji output.

---

## Assembly and Prototyping

We built everything from scratch: from designing the PCB layout and soldering the electronics to assembling the glove module. The images below showcase the different stages and prototypes, illustrating our hands-on approach to crafting both the hardware and software elements of CycloComm.

1. **Glove Communicator**  
   ![Glove Prototype](images/glove_prototype.png)  
   *Our custom-built glove featuring integrated sensors that detect specific hand gestures.*

2. **LED Display Module**  
   ![LED Display (Back)](images/LED_back.png)
   *Backside of our created LED module*
   
   ![LED Display (Front)](images/LED_front.png)  
   *The LED matrix mounted on a bag or back panel, ready to display emojis, text, or other signals.*

4. **All Prototypes & PCB Design**  
   <img src="images/all_prototypes.png" alt="All Prototypes" style="max-width:100%; height:auto;" />

   *A showcase of our PCB designs, soldered boards, and fully assembled prototypes that bring the CycloComm concept to life.*

5. **Hand Gesture Manual**
   Full hand gesture manual.
   ![Gesture Manual](images/gesture_manual.png)

## How it Works (Simple Overview)

1. Click the Button
- Tap your hand on the underside of the bike’s handlebar to activate the input.
- Once pressed, you have 1.5 seconds to make a gesture before the system reads and sends the signal.

2. Make a Hand Gesture
- Choose from up to 7 possible hand gestures (shown above)
- Bend sensors on the glove detect and convert each finger’s motion into a digital signal (1 or 0).

3. Gesture Sent via Bluetooth
- After the 1.5-second window, the recognized gesture (e.g., “L” for left) is transmitted wirelessly from the glove to the Arduino controlling the LED display.

4. Gesture Interpreted & Displayed
- The Arduino interprets the received character signal and lights up the pre-defined pattern on the LED screen (e.g., an arrow or an emoji). This makes it easier for drivers to see and understand your intent.

