### Timetemps and Deltatime

### Reason (Taking a look as to what exactly is it)
- In the application-side of things when you we update it from the mainloop, \
    where now we need the dt/timestep to check how fast the applications running.
    -> Whereas thhe frame per second could possibly be updated 60x per sec, 20x per sec, \
        if the frame rate is low, or even updated 144 times per second if vsynced \
        to a 144 hertz monitor or something like that.
- In this case the camera could potentially be moving at 4000, if we are running at 4000 frames per sec \
    then we'll be moving at 0.1 units per frame. Meaning it'll move 400 units in one second.
- Whereas if we were to run at 60 fps, then we move the camera to 0.1 units everytime, thhen it'll potentially be 16 units, 400 \
    which is a huge difference
- Whole point is that the camera would be moving at the same speed, no matter what.
- Basically of saying that movement to be time-based
- Essentially by that, it means that we do not essentially want the movement to be as fast as the computer, but rather \
    the operation like math operations to be computed as quickly as the computer, but not the camera (like taking a second, which it shouldn't).
- Referred to as either time stamp or deltatime (dt)

### Deltatime (Quick Overview and Idea why it's needed)
- Reason called deltatime is because moving a camera by a specific amount
- Meaning checking how long our frame took
    - Such as a frame may be taking 16 milliseconds in real-world time passes
- Essentially to measure how long a frame takes, then propagate that duration to the rest \
    of our update functions. Telling us how long that  frame took.
    - Then from that we can move our character (or camera) in respective to that actual time.

### How Deltatime works! (Idea behind it)
- Essentially why we need the number from deltatime.

** Visually Example **
T = 0.016 (60 fps) or T = 0.033 (30 fps)

onUpdate(dt)

- Exactly what we are going to be doing is taking in those time values (from T) between our frames and multiply it with our movement velocity (speed).

** Analogy to theh visual example **
- Reason is done is because if we have a cube, and moving at a certain speed.
    - Like if we wanted to move to the other side of the screen in exactly 1 second.
    - How many times it would need to move.
        - In this case if we are at 60 fps then we would need to perform 60 little movements to get to the otherside
        - Whereas if we were to be running at 30 fps, then that frame is how we are able to render in one second real-world time.
            - And we would need to rendering twice as much as frames if we are running 30.

** Unit example **
If we have 1 unit
This is what that'd look like -> 1 unit * T = 0.016 => 60
                                            = 0.033 => 30



### Features
- Added Timestep helper class
    - operator float() just allows us to consider the class as a float (essentially)