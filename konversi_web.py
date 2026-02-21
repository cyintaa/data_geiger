import os

# ====== INPUT FILE ======
input_file = "2026-02-20.txt"

# ====== AMBIL TANGGAL DARI FILE ======
with open(input_file, "r") as f:
    first_line = f.readline().strip()

_, _, date_str, _, _, _ = first_line.split(",")

year, month, day = date_str.split("-")
output_file = f"{day}-{month}-{year}.txt"

# ====== PROSES FILE ======
with open(input_file, "r") as fin, open(output_file, "w") as fout:
    fout.write("jam,menit,detik,cpm,temp,hum\n")

    for line in fin:
        parts = line.strip().split(",")
        if len(parts) < 6:
            continue

        jam = parts[0]
        menit = parts[1]
        detik = "00"              # default detik
        cpm = parts[3]
        temp = parts[4]
        hum = parts[5]

        fout.write(f"{jam},{menit},{detik},{cpm},{temp},{hum}\n")

print(f"Selesai ✔ File tersimpan sebagai: {output_file}")
