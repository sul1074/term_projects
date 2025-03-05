# A RISC-based Single Cycle Processor designed using Logism

## This processor can only execute a limited subset of instructions based on the given opcode decoder. The supported instruction types are:
- R-type (33): Arithmetic and logical operations (e.g., add, sub, and, or, xor).
- I-type (13): Immediate operations (e.g., addi, andi, ori).
- Load (lw, 03): Loading data from memory.
- Store (sw, 23): Storing data into memory.
- Branch (63): Conditional branching (e.g., beq, bne).
- Jump (jal, 6F): Unconditional jump and link.

### Circuit diagram
![image](https://github.com/user-attachments/assets/ae8e790c-fb8a-4b1f-8605-0f150c0be12f)

### ALU
![image](https://github.com/user-attachments/assets/6761db8e-08c3-42c4-8435-69053601dae7)

### RF4
![image](https://github.com/user-attachments/assets/f12a85ea-3ebd-4626-be3f-90b4c5119db3)

### RF16 
![image](https://github.com/user-attachments/assets/528258ac-eb6a-4a2f-afea-adeb0dd429a5)

### RF32
![image](https://github.com/user-attachments/assets/4c9078ba-528d-4cf4-bc00-6794550d269b)

### DataMemory
![image](https://github.com/user-attachments/assets/1eeafbb1-a109-436c-8c28-0d65c42be123)

### ImmGen
![image](https://github.com/user-attachments/assets/44f1f985-4d53-4a1b-b471-628634d10f64)

### InsTypeDecoder
![image](https://github.com/user-attachments/assets/e1e708ab-8706-4546-b14a-e412fcf3257f)

### ALUDecoder
![image](https://github.com/user-attachments/assets/f4d4a729-6c74-4bab-9d5c-55850736620a)

### MainDecoder
![image](https://github.com/user-attachments/assets/c1a2b6e6-bc86-4114-9a9b-ca373d1bd4d0)

### ControlUnit
![image](https://github.com/user-attachments/assets/8f49b57b-755f-4bfe-a17c-c620836fed35)
