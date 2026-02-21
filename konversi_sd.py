input_file  = "/home/callin/data_sd/data backup/23-01-2026.txt"
output_file = "/home/callin/data_radioaktif/data_sd_card/23-01-2026.txt"

DAY = 23   # ganti jika perlu
MINUTE_OUT = "00"

with open(input_file, "r") as fin, open(output_file, "w") as fout:
    for line in fin:
        line = line.strip()

        # lewati header / baris kosong
        if not line or line.startswith("TIME"):
            continue

        # contoh baris: 11:00:48,16,25.9,83.0
        try:
            time_str, cpm, temp, hum = line.split(",")

            hh, mm, ss = time_str.split(":")

            # format keluaran
            out = f"{DAY},{hh},{MINUTE_OUT},{cpm},{temp},{hum}"
            fout.write(out + "\n")

        except ValueError:
            # lewati baris rusak
            continue

print("Selesai! File hasil:", output_file)
