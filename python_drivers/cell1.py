from pynq import Overlay, allocate
import numpy as np
import time

print("Loading overlay...")
ol = Overlay("ntt_bd.bit")
ip = ol.top_ntt_0
print("Overlay loaded.")

N = 256

print("Allocating buffers in DDR...")
inp  = allocate((N,), dtype=np.uint32)
outp = allocate((N,), dtype=np.uint32)
zet  = allocate((N,), dtype=np.uint32)
print("Buffers allocated.")

print("Preparing input data...")
for i in range(N):
    inp[i] = i
    zet[i] = (17 * i + 3) % 8380417
print("Input arrays ready.")

print("Flushing caches to DDR...")
inp.flush()
zet.flush()
print("Flush done.")

print("\n=== Register setup ===")

print("Writing input address")
ip.write(0x10, inp.physical_address)

print("Writing output address")
ip.write(0x1C, outp.physical_address)

print("Writing zeta address")
ip.write(0x28, zet.physical_address)

print("CTRL before start:", hex(ip.read(0x00)))

print("\nStarting accelerator...")
ip.write(0x00, 0x1)

t0 = time.time()

# ---- progress monitor ----
last_print = 0
while True:
    status = ip.read(0x00)

    # print every 0.5 sec
    if time.time() - last_print > 0.5:
        print("CTRL:", hex(status))
        last_print = time.time()

    # DONE bit = 0x2
    if status & 0x2:
        break

t1 = time.time()

print("\nAccelerator finished.")
print("Total hardware time:", round(t1 - t0, 4), "sec")

print("Invalidating output cache...")
outp.invalidate()

print("\nFirst 10 outputs:")
print(outp[:10])