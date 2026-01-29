from pynq import Overlay, allocate
import numpy as np
import time

N = 256
Q = 8380417

# -------------------------------
# 1. Load Overlay
# -------------------------------
print("Loading overlay...")
ol = Overlay("ntt_bd.bit")
ip = ol.top_ntt_0
print("IP found:", ol.ip_dict.keys())

# -------------------------------
# 2. Allocate Buffers
# -------------------------------
print("Allocating buffers...")
buf_in  = allocate(shape=(N,), dtype=np.uint32)
buf_out = allocate(shape=(N,), dtype=np.uint32)
buf_z   = allocate(shape=(N,), dtype=np.uint32)

# -------------------------------
# 3. FPGA-MIRROR SOFTWARE NTT
# -------------------------------
def modq(x):
    return x % Q

def fpga_style_ntt(a, z):
    a = a.copy()
    k = 0

    len_ = 128
    while len_ >= 1:
        start = 0

        while start < N:
            for j in range(len_):

                u = int(a[start + j])
                v = int(a[start + j + len_])

                t = modq(v * int(z[k + j]))

                a[start + j] = modq(u + t)
                a[start + j + len_] = modq(u + Q - t)

            start += 2 * len_

        k += len_
        len_ >>= 1

    return a

# -------------------------------
# 4. Generate Test Data
# -------------------------------
print("Preparing data...")

A = np.random.randint(0, Q, size=N, dtype=np.uint32)

# Use same zetas as FPGA input
Z = np.random.randint(0, Q, size=N, dtype=np.uint32)

buf_in[:] = A
buf_z[:]  = Z

buf_in.flush()
buf_z.flush()

# -------------------------------
# 5. Run Software Reference
# -------------------------------
print("Running SOFTWARE reference...")
sw = fpga_style_ntt(A, Z)

# -------------------------------
# 6. Run FPGA
# -------------------------------
print("Starting FPGA accelerator...")

ip.write(0x10, buf_in.device_address)
ip.write(0x1C, buf_out.device_address)
ip.write(0x28, buf_z.device_address)

start = time.time()

ip.write(0x00, 1)

while True:
    status = ip.read(0x00)
    if status & 0x2:
        break

hw_time = time.time() - start

buf_out.invalidate()

print("FPGA time:", hw_time)

# -------------------------------
# 7. Compare
# -------------------------------
print("Validating...")

err = 0
for i in range(20):
    if sw[i] != buf_out[i]:
        print(f"Mismatch {i}: SW={sw[i]} HW={buf_out[i]}")
        err += 1

if err == 0:
    print("NTT MATCH SUCCESS")
else:
    print("Errors:", err)