### Describe the effect each of the P, I, D components had in your implementation

#### P (proportional) controller:
P controller is able to provide the stength of the control in proportion to the current error. In our case, P controller provides the steer angle adjustment in porportion to the CTE(cross track error). In other words, P controller will give bigger angle when the CTE is bigger, and smaller feedback if the error is smaller.

#### D (derivative) controller:
D controller is able to provide the feedback control based on the trend of the error, or the "speed" of the change of error. In our case, D controller will give counter-steering angle feedback if our CTE is getting smaller. D controller is able to reduce the feedback control when we are reaching the goal so we can reduce the "overshoot" effect that happens if we only applied with P controller.

#### I (integral) controller:
I controller is able to provide the feedback control based on overall error accumulated in the past. It's main use case is when there's system error, such as control error or measurement error, that P and D controller don't consider.

### Describe how the final hyperparameters were chosen
This is actually a pretty long process.

First I did implement a "twiddle"-like algorithm learned in the class. But I found it not very easy to use in practice. The reason is :

- The effect of each tuning is not very clear to me. I'm not sure which direction I'm going when following the semi-automatic tunning process by using twiddle.
- Each tunning requires collecting laps of data, which is very very time consuming.

In the end I decide to tune the pid parameter manually. Here's how I do it:

- First I tune the P parameter. I increase the P parameter if the steering angle is not able to get the car back on the road, and decrease it if the overshoot is large enough to make the car not drivable.
- Then I tune the D parameter. I found that bigger D parameter will ajust the oscillation faster, but end up with more rounds of oscillation. Small D parameter will not adjust the overshot as fast, but the car will end up with less rounds of oscillation. It's tricky process and I end up with a D parameter that feels not too aggressive but not still fast enough to react to the overshoot.
- Then I tune the I parameter. I found that the system error is not very noticable and I don't need big I parameter value to adjust it. In the end I choose a very small I parameter because I don't find it very useful in our simulation system.
- The final step is fine-tunning both P and D paramters, and add acceleration control. At this time, I was able to make the car drive the whole lap with 20mph. I tried to add some throttle control to increase the car speed. Here's what I use

```
throttle_value = base_throttle_value + (1 - abs(steer_value)) * steer_to_throttle_coefficient
```

I use a bigger than 0 `base_throttle_value` so I can accelerate the car's speed a little bit (to increase the max possible speed). Then I adjust the `steer_to_throttle_coefficient` to increase or decrease the acceleration value based on the steering angle value.

After this, I go back and fine tune the P and D paramters again and again. This process is to make sure the car don't go off road, while trying to keep the speed as high as possible.

In the end, these are the paramter that I choose:

- P: 0.1
- D: 4.0
- I: 0.005
- base_throttle_value: 0.1
- steer_to_throttle_coefficient: 0.3

My car is able to drive the whole lap at around 30~35mph.