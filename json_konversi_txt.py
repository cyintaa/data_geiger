import json
import os

# ==========================
# PATH FILE
# ==========================
input_json = "/home/callin/file_json/radioaktif-monitoring-default-rtdb-export (1).json"
output_dir = "/home/callin/file_json"

os.makedirs(output_dir, exist_ok=True)

# ==========================
# LOAD JSON
# ==========================
with open(input_json, "r") as f:
    data = json.load(f)

# ==========================
# AMBIL DATA MONITORING
# ==========================
monitoring = data["geiger"]

# ==========================
# PROSES PER TANGGAL
# ==========================
for tanggal, jam_data in monitoring.items():
    # ubah format tanggal YYYY-MM-DD → DD-MM-YYYY
    y, m, d = tanggal.split("-")
    nama_file = f"{d}-{m}-{y}.txt"
    output_path = os.path.join(output_dir, nama_file)

    with open(output_path, "w") as out:
        for waktu in sorted(jam_data.keys()):
            hh, mm = waktu.split(":")
            ss = "00"

            cpm  = jam_data[waktu].get("cpm", 0)
            temp = jam_data[waktu].get("temp", 0)
            hum  = jam_data[waktu].get("hum", 0)

            out.write(f"{hh},{mm},{ss},{cpm},{temp},{hum}\n")

    print(f"✔ File dibuat: {output_path}")
