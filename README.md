# Understanding Bits, Registers, Logic Operations, GPIO, Interrupts, Timers, and PWM in Arduino

## Bits in Arduino
Arduino operates on an **8-bit architecture** for its registers and ports. Each register consists of 8 bits, as shown below:

| MSB | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | LSB |
|-----|---|---|---|---|---|---|---|---|-----|

## Registers for GPIO
### 1. Data Direction Registers (DDRx)
- Configure pins as either **input** or **output**:
  - `0` -> Input
  - `1` -> Output

### 2. Port Registers (PORTx)
- Set the **output value** (HIGH/LOW) for the pins configured as output.

### 3. Input Pin Registers (PINx)
- **Read the value** of the input pins.

---

## Logic Operations Required for Register Setting in Arduino
- **AND** operation: `&`
- **OR** operation: `|`

---

## Data Direction Register (DDRx)
### Structure of DDRB:

| DDB7 | DDB6 | DDB5 | DDB4 | DDB3 | DDB2 | DDB1 | DDB0 |
|------|------|------|------|------|------|------|------|

The DDRB register configures whether the pins in port **B** are inputs or outputs.

### Examples:

#### Q1: Set DDB0 as output.
- **Code:**
  ```c
  DDRB = DDRB | (1 << DDB0);
  ```
  or can be written as
  ```c
  DDRB |= (1 << DDB0);
  ```
- **Explanation:**
  - Initial DDRB:

    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
    |---|---|---|---|---|---|---|---|
  - Apply `(1 << DDB0)`:

    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
    |---|---|---|---|---|---|---|---|
  - Resulting DDRB:

    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
    |---|---|---|---|---|---|---|---|

#### Q2: Set DDB0 and DDB1 as outputs.
- **Code:**
  ```c
  DDRB |= (1 << DDB0) | (1 << DDB1);
  ```

#### Q3: Set DDB0 as input.
- **Code:**
  ```c
  DDRB = DDRB & ~(1 << DDB0);
  ```
  or can be written as
  ```c
  DDRB &= ~(1 << DDB0);
  ```
- **Explanation:**
  - Initial DDRB:

    | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |
    |---|---|---|---|---|---|---|---|
  - Apply `~(1 << DDB0)`:

    | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 |
    |---|---|---|---|---|---|---|---|
  - Resulting DDRB:

    | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |
    |---|---|---|---|---|---|---|---|

#### Q4: Set DDB0, DDB1, DDB2, and DDB3 as outputs and the rest as inputs.
- **Code:**
  ```c
  DDRB = 0x00001111;
  ```
  or can be written as    
  ```c
  DDRB = 0x0F;
  ```

#### Q5: Set DDB0, DDB5, and DDB6 as outputs.
- **Code:**
  ```c
  DDRB = 0x01100001;
  ```
  or can be written as   
  ```c
  DDRB = 0x61;
  ```

---

## Control Registers for GPIO
### PORTB:

| PB7 | PB6 | PB5 | PB4 | PB3 | PB2 | PB1 | PB0 |
|-----|-----|-----|-----|-----|-----|-----|-----|

### PORTC:

|  X  | PC6 | PC5 | PC4 | PC3 | PC2 | PC1 | PC0 |
|-----|-----|-----|-----|-----|-----|-----|-----|

### PORTD:

| PD7 | PD6 | PD5 | PD4 | PD3 | PD2 | PD1 | PD0 |
|-----|-----|-----|-----|-----|-----|-----|-----|

- `0` -> LOW
- `1` -> HIGH

#### Q6: Turn on pin PB5.
- **Code:**
  ```c
  PORTB |= (1 << PB5);
  ```
  or
  ```c
  PORTB = 0x00100000;
  ```
  or
  ```c
  PORTB = 0x20;
  ```

---

## Input Pin Registers (PINx)
### PINB:

| PINB7 | PINB6 | PINB5 | PINB4 | PINB3 | PINB2 | PINB1 | PINB0 |
|-------|-------|-------|-------|-------|-------|-------|-------|

### PINC:

|   X   | PINC6 | PINC5 | PINC4 | PINC3 | PINC2 | PINC1 | PINC0 |
|-------|-------|-------|-------|-------|-------|-------|-------|

### PIND:

| PIND7 | PIND6 | PIND5 | PIND4 | PIND3 | PIND2 | PIND1 | PIND0 |
|-------|-------|-------|-------|-------|-------|-------|-------|

#### Q7: Read the status of pin PB0.
- **Code:**
  ```c
  if (PINB & (1 << PINB0)) {
    // Pin PB0 is HIGH
  } else {
    // Pin PB0 is LOW
  }
  ```
- **Explanation:**
  - If `PINB & (1 << PINB0)` evaluates to:
    - `0` -> Pin is LOW.
    - `1` -> Pin is HIGH.

  - Case 1: LOW value in pin B
    - **PINB** 
 
    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
    |---|---|---|---|---|---|---|---|  

    - **(1 << PINB0)**  

    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |  
    |---|---|---|---|---|---|---|---|

    - **PINB & (1 << PINB0)**  

    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 
    |---|---|---|---|---|---|---|---| 

  - Case 2: HIGH value in pin B
    - **PINB**  

    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 
    |---|---|---|---|---|---|---|---| 

    - **(1 << PINB0)**  

    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |  
    |---|---|---|---|---|---|---|---|

    - **PINB & (1 << PINB0)**  

    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |  
    |---|---|---|---|---|---|---|---|

---

## Interrupts

### Types of Interrupts:
1. **Hardware Interrupts**
   - Triggered by external events.
   - Example: External interrupts on pins.

2. **Software Interrupts**
   - Triggered by internal events.
   - Example: ADC, Timer, or USART interrupts.

#### Status Register (SREG)
- Bit 7: I (Global Interrupt Enable bit)
  - **Code to enable:**
    ```c
    SREG |= (1 << 7);
    ```

#### External Interrupt Mask Register (EIMSK)
- Bit 1: INT1 - External Interrupt 1
- Bit 0: INT0 - External Interrupt 0

#### External Interrupt Control Register A (EICRA)
- Bit 3: ISC11 - Interrupt Sense Control for INT1 (Bit 1)
- Bit 2: ISC10 - Interrupt Sense Control for INT1 (Bit 0)
- Bit 1: ISC01 - Interrupt Sense Control for INT0 (Bit 1)
- Bit 0: ISC00 - Interrupt Sense Control for INT0 (Bit 0)

- **Rising edge interrupt request:**
  ```rise_edge_int_req
  ISC11 = 1; ISC10 = 1;
  ISC01 = 1; ISC00 = 1;
  ```

---

## Timers

### Purpose of Timers:
- Generate delays or time intervals.
- Measure time or frequency.
- Generate PWM signals.
- Trigger external devices.

### Working:
- The timer increments at each clock cycle.
- Timer clock can be reduced using a **prescaler**.

### Timer Clock:
```c
Timer Clock = System_Clock / Prescaler
```

### Timer Period:
```c
Timer Period = 1 / 16 MHz = 62.5 ns
```

### Timer Types:
1. **TIMER 0**: 8-bit
2. **TIMER 1**: 16-bit
3. **TIMER 2**: 8-bit

### Global Interrupt Enable:
```c
SREG |= (1 << 7); // sei();
```

#### Timer/Counter Control Registers:
##### **TCCR1A**
- **TCCR1A Register Overview**: The TCCR1A register controls the behavior of Timer/Counter 1 in terms of output compare behavior and the PWM mode. This register is crucial for configuring how the microcontroller generates PWM signals and how it interacts with output pins.
  
- **PWM Configuration**:
  - **PWM Mode (Waveform Generation Mode)**: The WGM11 and WGM10 bits in TCCR1A set the waveform generation mode, which determines how the timer operates. In PWM mode, Timer/Counter 1 generates a pulse-width modulation (PWM) signal on the output pin (OC1A or OC1B).
  - **COM1A and COM1B Bits**: The COM1A1, COM1A0, COM1B1, and COM1B0 bits control the output compare behavior on pins OC1A and OC1B. These bits specify whether the output will be toggled, cleared, or set when the timer reaches a certain value. They help in controlling whether the waveform is inverted (active high or low) or non-inverted.

- **TCCR1A Register**:

  | Bit 7    | Bit 6    | Bit 5    | Bit 4    | Bit 3    | Bit 2    | Bit 1    | Bit 0    |
  |----------|----------|----------|----------|----------|----------|----------|----------|
  | **COM1A1** | **COM1A0** | **COM1B1** | **COM1B0** |     -    |     -    | **WGM11** | **WGM10** |


###### **COM1A (OC1A Output Pin Control)**

| **COM1A1** | **COM1A0** | **Description**                        |
|------------|------------|----------------------------------------|
| 0          | 0          | Normal port operation (OC1A disconnected) |
| 0          | 1          | Toggle OC1A on compare match          |
| 1          | 0          | Clear OC1A on compare match (non-inverted) |
| 1          | 1          | Set OC1A on compare match (inverted)  |


###### **COM1B (OC1B Output Pin Control)**

| **COM1B1** | **COM1B0** | **Description**                        |
|------------|------------|----------------------------------------|
| 0          | 0          | Normal port operation (OC1B disconnected) |
| 0          | 1          | Toggle OC1B on compare match          |
| 1          | 0          | Clear OC1B on compare match (non-inverted) |
| 1          | 1          | Set OC1B on compare match (inverted)  |


###### **WGM1[1:0] (Waveform Generation Mode)**

| **WGM11** | **WGM10** | **Description**                        |
|-----------|-----------|----------------------------------------|
| 1         | 1         | Fast PWM (with ICR1 as the TOP value) |
| 0         | 0         | Normal mode                           |
| 1         | 0         | CTC (Clear Timer on Compare Match)    |
| 0         | 1         | Phase Correct PWM                     |


##### **TCCR1B**
- **TCCR1B Register Overview**: The TCCR1B register controls Timer/Counter 1's behavior in terms of clock selection, waveform generation modes, and prescaling. It is essential for setting the timer's frequency, mode of operation, and the output signal's characteristics.

- **PWM Configuration**:
  - **WGM13, WGM12**: These bits, in combination with WGM11 and WGM10 from TCCR1A, define the waveform generation mode for Timer/Counter 1. They determine whether the timer is operating in normal mode, CTC, PWM, or phase-correct PWM.
  - **CS1[2:0]**: The CS1 bits define the clock source for the timer and the prescaling factor. These bits allow the user to select the clock frequency for the timer, which can be divided by a factor to slow down the timer and generate PWM signals with desired frequencies.

- **TCCR1B Register**:

  | Bit 7    | Bit 6    | Bit 5    | Bit 4    | Bit 3    | Bit 2    | Bit 1    | Bit 0    |
  |----------|----------|----------|----------|----------|----------|----------|----------|
  | **ICNC1** | **ICES1** |     | **WGM13** | **WGM12** | **CS12**  | **CS11**  | **CS10**  | 


###### **ICNC1 (Input Capture Noise Canceler)**

| **ICNC1** | **Description**                     |
|-----------|-------------------------------------|
| 0         | Disable the noise canceler          |
| 1         | Enable the noise canceler           |



###### **ICES1 (Input Capture Edge Select)**

| **ICES1** | **Description**                     |
|-----------|-------------------------------------|
| 0         | Capture on falling edge             |
| 1         | Capture on rising edge              |



###### **WGM1[3:2] (Waveform Generation Mode)**

| **WGM13** | **WGM12** | **Description**                        |
|-----------|-----------|----------------------------------------|
| 1         | 1         | Fast PWM (with ICR1 as the TOP value) |
| 0         | 0         | Normal mode                           |
| 1         | 0         | CTC (Clear Timer on Compare Match)    |
| 0         | 1         | Phase Correct PWM                     |


###### **CS1[2:0] (Clock Select)**

| **CS12**  | **CS11**  | **CS10**  | **Description**                        |
|-----------|-----------|-----------|----------------------------------------|
| 0         | 0         | 0         | No clock source (Timer/Counter stopped) |
| 0         | 0         | 1         | Clock with no prescaling              |
| 0         | 1         | 0         | Clock divided by 8                    |
| 0         | 1         | 1         | Clock divided by 64                   |
| 1         | 0         | 0         | Clock divided by 256                  |
| 1         | 0         | 1         | Clock divided by 1024                 |
| 1         | 1         | 0         | External clock on T1 pin, falling edge |
| 1         | 1         | 1         | External clock on T1 pin, rising edge  |

---

## PWM (Pulse Width Modulation)

### Purpose:
- **Pulse Width Modulation (PWM)** is used to control the average power delivered to a load by varying the duty cycle of a signal.
- It is widely used in various applications such as motor control, audio control, and lighting control, among others.

### Applications:
- **Motor Control**: Used to control the speed of motors by adjusting the average voltage applied.
- **Audio Control**: Used in audio systems to adjust sound levels or modulate audio signals.
- **Lighting Control**: Commonly used in LED dimming applications where light intensity is controlled by adjusting the duty cycle.

### WGM1[3:0] Configuration Table:

| Mode | WGM1[3] | WGM1[2] | WGM1[1] | WGM1[0] | Timer/Counter Mode of Operation | TOP  |
|------|---------|---------|---------|---------|---------------------------------|------|
| 0    | 0       | 0       | 0       | 0       | Normal                          | 0xFFFF |
| 1    | 0       | 0       | 0       | 1       | PWM, Phase Correct, 8-bit       | 0x00FF |
| 2    | 0       | 0       | 1       | 0       | PWM, Phase Correct, 9-bit       | 0x01FF |
| 3    | 0       | 0       | 1       | 1       | PWM, Phase Correct, 10-bit      | 0x03FF |
| 4    | 0       | 1       | 0       | 0       | CTC                             | OCR1A |
| 5    | 0       | 1       | 0       | 1       | Fast PWM, 8-bit                 | 0x00FF |
| 6    | 0       | 1       | 1       | 0       | Fast PWM, 9-bit                 | 0x01FF |
| 7    | 0       | 1       | 1       | 1       | Fast PWM, 10-bit                | 0x03FF |
| 8    | 1       | 0       | 0       | 0       | PWM, Phase and Frequency Correct| ICR1  |
| 9    | 1       | 0       | 0       | 1       | PWM, Phase and Frequency Correct| OCR1A |
| 10   | 1       | 0       | 1       | 0       | PWM, Phase Correct              | ICR1  |
| 11   | 1       | 0       | 1       | 1       | PWM, Phase Correct              | OCR1A |
| 12   | 1       | 1       | 0       | 0       | CTC                             | ICR1  |
| 13   | 1       | 1       | 0       | 1       | Reserved                        | -     |
| 14   | 1       | 1       | 1       | 0       | Fast PWM                        | ICR1  |
| 15   | 1       | 1       | 1       | 1       | Fast PWM                        | OCR1A |

### WGM1 Modes Overview:

1. **Normal Mode (WGM1[3:0] = 0000)**:
   - The timer counts from 0 to 255, then resets to 0, allowing for simple counting.
   - Typically used for simple timing and frequency generation.

2. **Phase Correct PWM Mode (WGM1[3:0] = 0001, 0010, 0011)**:
   - The timer counts up to a specified value and then counts back down.
   - It generates a symmetrical waveform, where the duty cycle can be adjusted from 0 to 100%.
   - Commonly used for motor control, smooth LED dimming, and audio applications.

3. **CTC (Clear Timer on Compare Match) Mode (WGM1[3:0] = 0100, 1100)**:
   - The timer counts to a specified value (OCR1A or ICR1) and resets to 0 on a match.
   - Used for precise frequency generation, event timing, and generating periodic interrupts.

4. **Fast PWM Mode**:
   - The timer counts to a specified value (ICR1 or OCR1A) and resets to 0.
   - Offers high-frequency PWM with resolutions of 8, 9, or 10 bits.
   - Ideal for applications requiring high-speed control of motors, LEDs, and other power-sensitive devices, with very fine control over the duty cycle.

## ADC (Analog-to-Digital Converter)

### Purpose:
The **Analog-to-Digital Converter (ADC)** converts an analog signal (like the output from a sensor) into a digital value that the microcontroller can understand. This is important because most microcontrollers only work with digital data.

### ADC Components:

Here’s an overview of the key parts of the ADC:

- **ADC Multiplexer**: This selects which analog input to convert. It allows the ADC to work with multiple inputs (like ADC0, ADC1, etc.).
- **Sample & Hold Circuit**: This captures the analog voltage at a specific time so it can be converted.
- **Comparator**: Compares the analog signal to a reference voltage to determine how the signal measures.
- **Conversion Logic**: Converts the comparison result into a digital number.
- **Data Registers**: The converted digital value is stored in these registers.

### How the ADC Works Step-by-Step:

1. **Select the Input Channel**: Choose the sensor input you want to measure by setting the appropriate control bits.
2. **Choose Reference Voltage**: Set the reference voltage (internal or external).
3. **Enable the ADC**: Turn on the ADC by setting the necessary control bit.
4. **Start the Conversion**: Begin the process by triggering the conversion.
5. **Sample the Input**: The ADC takes a snapshot of the analog input voltage.
6. **Compare the Voltage**: The ADC compares the input to a series of reference voltages using a Successive Approximation Register (SAR).
7. **Convert to Digital**: The ADC converts the result of the comparison into a 10-bit digital number.
8. **Store the Result**: The result is stored in two memory registers: **ADCL** (lower 8 bits) and **ADCH** (higher 8 bits).

### Key Concepts:

- **Reference Voltage**: This is the voltage that the ADC compares the input signal to. It can be set to an internal or external reference.
- **Left Adjustment**: You can adjust the result so that the most significant bits are stored in the higher register, which is useful for 8-bit precision.
- **Power Consumption**: The ADC uses power when it's on. It’s a good idea to turn it off when you’re not using it to save power.

### Step Size:

The **step size** is an important concept in ADC conversion. It refers to the smallest difference between two distinct digital values that the ADC can detect. This depends on the reference voltage and the resolution of the ADC.

- **Formula for Step Size**:
  \[
  \text{Step Size} = \frac{\text{Reference Voltage}}{2^{\text{Resolution of ADC}}-1}
  \]
  Where:
  - **Reference Voltage** is the voltage range (e.g., 0V to 5V).
  - **Resolution of ADC** is the number of bits the ADC uses to represent the digital value.

For example, if you have a 10-bit ADC with a reference voltage of 5V:
\[
\text{Step Size} = \frac{5V}{2^{10}} = \frac{5V}{1024} \approx 0.00488V
\]
This means that the ADC can detect changes in the input voltage as small as 0.00488V.

### **ADMUX**
- **ADMUX Register Overview**: The ADMUX register controls the selection of the input channel, reference voltage, and the adjustment of the ADC result in the ATmega328P. It is crucial for configuring which analog pin to sample, selecting the reference voltage for conversion, and adjusting the format of the output result.

- **ADC Configuration**:
  - **MUX[4:0]**: These bits select the analog input channel for the ADC. The ATmega328P has 8 input channels (ADC0-ADC7), which can be configured using these bits.
  - **REFS[1:0]**: These bits define the reference voltage used by the ADC. The reference voltage can either be external or come from an internal source such as Vcc or an internal 1.1V bandgap.
  - **ADLAR**: This bit controls the left-adjustment of the ADC result. When set, the ADC result is left-adjusted, which is useful for applications where only 8-bit precision is needed.
  
- **ADMUX Register**:

  | Bit 7    | Bit 6    | Bit 5    | Bit 4    | Bit 3    | Bit 2    | Bit 1    | Bit 0    |
  |----------|----------|----------|----------|----------|----------|----------|----------|
  | **REFS1** | **REFS0** | **ADLAR** |    | **MUX3**  | **MUX2**  | **MUX1**  | **MUX0**  | 


#### **REFS[1:0] (Reference Voltage Selection)**

| **REFS[1:0]** | **Description**                                          |
|---------------|----------------------------------------------------------|
| 00            | AREF, Internal Vref turned off                           |
| 01            | AVCC with external capacitor at AREF pin                 |
| 10            | Reserved, do not use                                     |
| 11            | Internal 1.1V Voltage Reference with external capacitor  |

#### **ADLAR (ADC Left Adjust Result)**

##### **ADLAR = 0 (Right Adjusted Result)**

When **ADLAR** is set to **0**, the 10-bit ADC result is right-adjusted. In this case:
- The **ADCL** register stores the lower 8 bits (ADC0-ADC7).
- The **ADCH** register stores the upper 2 bits (ADC8-ADC9).

###### **Register Mapping (ADLAR = 0)**

| Address  | Bit 7   | Bit 6   | Bit 5   | Bit 4   | Bit 3   | Bit 2   | Bit 1   | Bit 0   |
|----------|---------|---------|---------|---------|---------|---------|---------|---------|
| **0x79** | -       | -       | -       | -       | -       | -       | **ADC9** | **ADC8** |
| **0x78** | **ADC7** | **ADC6** | **ADC5** | **ADC4** | **ADC3** | **ADC2** | **ADC1** | **ADC0** |

- **ADCL (0x78)**: Stores the lower 8 bits of the ADC result (ADC0-ADC7).
- **ADCH (0x79)**: Stores the upper 2 bits of the ADC result (ADC8-ADC9).

In this mode, the complete 10-bit result is obtained by reading both **ADCL** and **ADCH**.


##### **ADLAR = 1 (Left Adjusted Result)**

When **ADLAR** is set to **1**, the 10-bit ADC result is left-adjusted. In this case:
- The **ADCL** register stores the upper 8 bits (ADC0-ADC7).
- The **ADCH** register stores the lower 2 bits (ADC8-ADC9), which can be ignored if only 8-bit precision is required.

###### **Register Mapping (ADLAR = 1)**

| Address  | Bit 7   | Bit 6   | Bit 5   | Bit 4   | Bit 3   | Bit 2   | Bit 1   | Bit 0   |
|----------|---------|---------|---------|---------|---------|---------|---------|---------|
| **0x79** | **ADC9** | **ADC8** | **ADC7** | **ADC6** | **ADC5** | **ADC4** | **ADC3** | **ADC2** |
| **0x78** | **ADC1** | **ADC0** | -       | -       | -       | -       | -       | - |

- **ADCL (0x78)**: Stores the upper 8 bits of the ADC result (ADC0-ADC7).
- **ADCH (0x79)**: Stores the lower 2 bits of the ADC result (ADC8-ADC9), which can be ignored in most cases if only 8-bit precision is needed.

In this mode, the 8-bit result is obtained directly by reading **ADCL**, and **ADCH** contains the lower bits (which can be ignored).

#### **MUX[3:0] (Single Ended Input Channel Selection)**

| **MUX[3:0]** | **Input Channel**         |
|--------------|---------------------------|
| 0000         | ADC0 (Pin 23)             |
| 0001         | ADC1 (Pin 24)             |
| 0010         | ADC2 (Pin 25)             |
| 0011         | ADC3 (Pin 26)             |
| 0100         | ADC4 (Pin 27)             |
| 0101         | ADC5 (Pin 28)             |
| 0110         | ADC6 (Pin 29)             |
| 0111         | ADC7 (Pin 30)             |
| 1000         | Temperature sensor        |
| 1001         | Reserved                  |
| 1010         | Reserved                  |
| 1011         | Reserved                  |
| 1100         | Reserved                  |
| 1101         | Reserved                  |
| 1110         | 1.1V (VBG)                |
| 1111         | 0V (GND)                  |


### **ADCSRA**
- **ADCSRA Register Overview**: The **ADCSRA** register controls the operation of the ADC (Analog-to-Digital Converter) in the ATmega328P. It is responsible for enabling the ADC, starting conversions, enabling interrupts, and setting the ADC prescaler to control the ADC conversion speed. This register is essential for configuring and managing ADC operations.

- **Key Configuration**:
  - **ADEN (ADC Enable)**: This bit enables or disables the ADC. Setting it to 1 enables the ADC and allows conversions to be performed.
  - **ADSC (ADC Start Conversion)**: When this bit is set to 1, the ADC conversion process begins. This bit is automatically cleared once the conversion is complete.
  - **ADATE (ADC Auto Trigger Enable)**: This bit enables the auto-triggering of the ADC, allowing continuous conversions based on a trigger source.
  - **ADIF (ADC Interrupt Flag)**: This flag is set when an ADC conversion is complete and an interrupt is triggered. It is cleared by writing a 1 to it.
  - **ADIE (ADC Interrupt Enable)**: This bit enables or disables ADC conversion interrupts. Setting it to 1 enables interrupts.
  - **ADPS[2:0] (ADC Prescaler Selection)**: These bits select the division factor for the ADC clock. The prescaler is used to slow down the ADC clock to ensure proper operation.

- **ADCSRA Register**:

  | Bit 7    | Bit 6    | Bit 5    | Bit 4    | Bit 3    | Bit 2    | Bit 1    | Bit 0    |
  |----------|----------|----------|----------|----------|----------|----------|----------|
  | **ADEN** | **ADSC** | **ADATE** | **ADIF** | **ADIE** | **ADPS2** | **ADPS1** | **ADPS0** |


#### **ADEN (ADC Enable)**

| **ADEN** | **Description**                       |
|----------|---------------------------------------|
| 0        | Disable ADC operation                |
| 1        | Enable ADC operation                 |

#### **ADSC (ADC Start Conversion)**

| **ADSC** | **Description**                       |
|----------|---------------------------------------|
| 0        | No conversion in progress            |
| 1        | Start an ADC conversion              |

#### **ADATE (ADC Auto Trigger Enable)**

| **ADATE** | **Description**                       |
|-----------|---------------------------------------|
| 0         | Auto triggering disabled              |
| 1         | Enable auto triggering of ADC        |

#### **ADIF (ADC Interrupt Flag)**

| **ADIF** | **Description**                       |
|----------|---------------------------------------|
| 0        | ADC conversion is not complete       |
| 1        | ADC conversion is complete           |

#### **ADIE (ADC Interrupt Enable)**

| **ADIE** | **Description**                       |
|----------|---------------------------------------|
| 0        | Disable ADC conversion interrupt     |
| 1        | Enable ADC conversion interrupt      |


#### **ADPS[2:0] (ADC Prescaler Selection)**

| **ADPS2** | **ADPS1** | **ADPS0** | **Division Factor**  |
|-----------|-----------|-----------|----------------------|
| 0         | 0         | 0         | 2                    |
| 0         | 0         | 1         | 2                    |
| 0         | 1         | 0         | 4                    |
| 0         | 1         | 1         | 8                    |
| 1         | 0         | 0         | 16                   |
| 1         | 0         | 1         | 32                   |
| 1         | 1         | 0         | 64                   |
| 1         | 1         | 1         | 128                  |


### How to Use this?
- Enable the global interrupt (SREG |= (1 << 7); or sei();)
- Set Refernece voltage pin to 0 (ADMUX -> ref[1:0] to 0)
- ADLAR is set to 0 //For 10bit
- Enable ADEN, ADATE, ADIE 
- Set ADPS[2:0] to desired prescaler value
- Start convertion by enabling ADSC.
- Select ADC channel by enabling required MUX[3:0] values in ADMUX register.
- ISR(ADC_vect){} Interrupt Serive Routine for ADC

