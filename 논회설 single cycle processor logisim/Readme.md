# A RISC-based Single Cycle Processor designed using Logism

This processor supports a limited subset of RISC-V instructions. The supported instruction types and their opcodes are:  
### Supported Instruction Types  
- **R-type (`0x33`)**: Arithmetic and logical operations (`add`, `sub`, `and`, `or`, `xor`).  
- **I-type (`0x13`)**: Immediate operations (`addi`, `andi`, `ori`).  
- **Load (`lw`, `0x03`)**: Load word from memory.  
- **Store (`sw`, `0x23`)**: Store word into memory.  
- **Branch (`0x63`)**: Conditional branching (`beq`, `bne`).  
- **Jump (`jal`, `0x6F`)**: Unconditional jump and link.

<br>  

### Circuit diagram
![image](https://github.com/user-attachments/assets/ae8e790c-fb8a-4b1f-8605-0f150c0be12f)
<br>

### ALU
![image](https://github.com/user-attachments/assets/6761db8e-08c3-42c4-8435-69053601dae7)
<br>

### RF4
![image](https://github.com/user-attachments/assets/f12a85ea-3ebd-4626-be3f-90b4c5119db3)
<br>

### RF16 
![image](https://github.com/user-attachments/assets/528258ac-eb6a-4a2f-afea-adeb0dd429a5)
<br>

### RF32
![image](https://github.com/user-attachments/assets/4c9078ba-528d-4cf4-bc00-6794550d269b)
<br>

### DataMemory
![image](https://github.com/user-attachments/assets/1eeafbb1-a109-436c-8c28-0d65c42be123)
<br>

### ImmGen
![image](https://github.com/user-attachments/assets/44f1f985-4d53-4a1b-b471-628634d10f64)
<br>

### InsTypeDecoder
![image](https://github.com/user-attachments/assets/e1e708ab-8706-4546-b14a-e412fcf3257f)
<br>

### ALUDecoder
![image](https://github.com/user-attachments/assets/f4d4a729-6c74-4bab-9d5c-55850736620a)
<br>

### MainDecoder
![image](https://github.com/user-attachments/assets/c1a2b6e6-bc86-4114-9a9b-ca373d1bd4d0)
<br>

### ControlUnit
![image](https://github.com/user-attachments/assets/8f49b57b-755f-4bfe-a17c-c620836fed35)
<br>
