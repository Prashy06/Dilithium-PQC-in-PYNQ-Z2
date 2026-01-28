# CRYSTALS-Dilithium on PYNQ Z2 FPGA

This project demonstrates a hardware–software co-design for accelerating the NIST post-quantum digital signature scheme **CRYSTALS-Dilithium** using a custom **Number Theoretic Transform (NTT) FPGA accelerator** on the **PYNQ Z2 (Zynq-7000 SoC)**.

The ARM Cortex-A9 processor executes Dilithium protocol logic, hashing, and control flow, while the FPGA fabric performs high-throughput polynomial transforms required for Dilithium using a Vitis HLS-based NTT IP.

The result is a practical, quantum-resilient digital signature pipeline suitable for embedded and VLSI systems.

---

## Why This Project

Dilithium relies heavily on polynomial arithmetic over 256 coefficients.
In software on ARM, this is slow and energy-intensive.

This project moves the **computational bottleneck (NTT)** into hardware.

**Measured Result**

* Software NTT: **132.82 ms per run**
* FPGA NTT: **1.16 ms per run**
* **114× speedup**

This makes Dilithium feasible for:

* Secure boot
* Firmware authentication
* Embedded/IoT security
* Future quantum-safe SoCs

---

## System Architecture

**Processing System (PS)**

* Dilithium keygen, sign, verify logic
* SHAKE hashing
* Random sampling
* Control of FPGA IP via AXI

**Programmable Logic (PL)**

* Custom NTT accelerator (Vitis HLS)
* Modular arithmetic butterfly pipeline
* BRAM-based coefficient storage

**Interfaces**

* AXI-MM for data transfer
* AXI-Lite for control

---

## Tech Stack

* Hardware: **PYNQ Z2 (Zynq-7000 ARM + FPGA)**
* Tools: **Vivado, Vitis HLS**
* Languages: **C/C++ (HLS), Python (PYNQ)**
* Crypto: **CRYSTALS-Dilithium-2**
* Math Core: **256-point NTT accelerator**

---

## Repository Structure

```
/hls_ntt_ip        → Vitis HLS source for NTT
/vivado_design     → Block design and bitstream
/python_driver     → PYNQ control and demo notebooks
/reports      → Reports
/docs              → Block diagrams and reports
```

---

## How It Works

1. Python allocates polynomial buffers in DDR
2. ARM writes addresses to AXI registers
3. FPGA performs NTT on 256-point polynomial
4. Result returned to ARM for Dilithium operations
5. Used in sign and verify flow

---

## Demo

The demo shows:

* Signing a text/image using Dilithium
* Verifying the signature
* Timing comparison of software vs hardware NTT
* Validation: FPGA output matches software reference

Console output shows:

* Overlay load
* Benchmark runs (1000 iterations)
* Speedup factor
* NTT match success

---

## Performance

| Metric   | Software (ARM) | Hardware (FPGA) |
| -------- | -------------- | --------------- |
| NTT Time | 132.82 ms      | 1.16 ms         |
| Speedup  | –              | **114×**        |

---

## Applications

* Quantum-safe secure boot
* Firmware authentication
* Embedded device identity
* VLSI/SoC cryptographic acceleration
* Blockchain node signing (future work)

---

## Future Work

* Add INTT and pointwise multiply in hardware
* Full polynomial arithmetic IP
* Side-channel resistant design
* Port to ASIC / advanced FPGA

---

## References

* NIST PQC Project: [https://csrc.nist.gov/projects/post-quantum-cryptography](https://csrc.nist.gov/projects/post-quantum-cryptography)
* CRYSTALS-Dilithium Paper: [https://eprint.iacr.org/2017/633.pdf](https://eprint.iacr.org/2017/633.pdf)
* Zynq-7000 TRM: [https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf](https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)

---

## Author

FPGA implementation and integration of Dilithium NTT accelerator for post-quantum embedded security.
